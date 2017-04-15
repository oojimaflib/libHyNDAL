/***********************************************************************
 * ISISDataTable.cpp
 *
 * Class representing a table of values from an ISIS model
 *
 * This file is part of HyNDAL.
 *
 * HyNDAL is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * HyNDAL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with HyNDAL. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Gerald C J Morgan 2013
 ***********************************************************************/

#include "ISISDataTable.hpp"
#include "../util/string_list.hpp"
#include <boost/algorithm/string.hpp>

#include <sstream>
#include <iomanip>

namespace HyNDAL {
  namespace ISIS {

    typedef long int long_int;

    char ISISDataTable::col_to_label(size_t col)
    {
      if (col < 10) {
	return ((char) col) + 48;
      } else if (col < 36) {
	return ((char) col) + 65;
      } else if (col < 62) {
	return ((char) col) + 97;
      } else {
	throw std::runtime_error("Requested out-of-range column number.");
      }
    }

    ISISDataTable::ISISDataTable(std::string format,
				 std::vector<std::string> data)
      : format_(format),
	data_(data),
	no_of_columns_(1)
    {
      if (format_.at(0) == '~') {
	special_case_ = true;
      } else {
	special_case_ = false;
      }

      no_of_columns_ = 0;
      for (char col = '0'; col <= '9'; col++) {
	if (format.find(col) != std::string::npos) {
	  no_of_columns_++;
	} else {
	  return;
	}
      }
      for (char col = 'A'; col <= 'Z'; col++) {
	if (format.find(col) != std::string::npos) {
	  no_of_columns_++;
	} else {
	  return;
	}
      }
      for (char col = 'a'; col <= 'z'; col++) {
	if (format.find(col) != std::string::npos) {
	  no_of_columns_++;
	} else {
	  return;
	}
      }
    }

    ISISDataTable::ISISDataTable(const boost::property_tree::ptree& config)
    {
      std::string table_type = config.get<std::string>("table-type", "fixed width");

      if (table_type == "fixed width") {
	format_ = config.get<std::string>("format", "");
	data_ = string_to_list(config.get<std::string>("data", ""));
	special_case_ = false;

	no_of_columns_ = 0;
	for (char col = '0'; col <= '9'; col++) {
	  if (format_.find(col) != std::string::npos) {
	    no_of_columns_++;
	  } else {
	    return;
	  }
	}
	for (char col = 'A'; col <= 'Z'; col++) {
	  if (format_.find(col) != std::string::npos) {
	    no_of_columns_++;
	  } else {
	    return;
	  }
	}
	for (char col = 'a'; col <= 'z'; col++) {
	  if (format_.find(col) != std::string::npos) {
	    no_of_columns_++;
	  } else {
	    return;
	  }
	}
	return;
      }
      no_of_columns_ = 1;
      if (table_type == "text block") {
	format_ = "~block~";
	data_.push_back(config.get<std::string>("data",""));
	special_case_ = true;
	return;
      }
      if (table_type == "rules table") {
	format_ = "~rules~";
	data_ = string_to_list(config.get<std::string>("data", ""), "£");
	special_case_ = true;
	return;
      }
    }

    size_t ISISDataTable::no_of_rows(void)
    { 
      if (special_case_) {
	if (format_ == "~block~") {
	  // Count new-line characters in the string
	  size_t count = 0;
	  for (size_t i = 0; i < data_.at(0).size(); i++) {
	    if (data_.at(0).at(i) == '\n') count++;
	  }
	  return count + 1; // We add one as the final new line is not
	  // included in the comment string.
	}
      }
      return data_.size();
    }

    void ISISDataTable::insert_row(size_t before,
				   const std::string& row)
    {
      if (row.size() == 0) {
	data_.insert(data_.begin() + before,
		     std::string(format_.size(), ' '));
	return;
      }
      data_.insert(data_.begin() + before, row);
    }

    std::string ISISDataTable::get_string(size_t row, size_t col)
    {
      if (special_case_) {
	if (format_ == "~block~") return data_.at(0);
	if (format_ == "~rules~") return data_.at(row);
	return "";
      } else {
	if (row >= data_.size()) return "";
	size_t start_char = format_.find_first_of(col_to_label(col));
	if (start_char >= data_.at(row).size()) return "";
	size_t end_char = format_.find_last_of(col_to_label(col)) + 1;
	std::string value = data_.at(row).substr(start_char, end_char - start_char);
	return boost::algorithm::trim_copy(value);
      }
    }

    double ISISDataTable::get_double(size_t row, size_t col)
    {
      return atof(get_string(row, col).c_str());
    }

    long int ISISDataTable::get_long_int(size_t row, size_t col)
    {
      return atol(get_string(row, col).c_str());
    }

    bool ISISDataTable::get_bool(size_t row, size_t col)
    {
      return (get_string(row, col) != " " ? true : false);
    }

    void ISISDataTable::set_string(size_t row, size_t col, std::string value)
    {
      if (special_case_) {
	if (format_ == "~block~") data_.at(0) == value;
	if (format_ == "~rules~") data_.at(row) == value;
	return;
      }

      size_t start_char = format_.find_first_of(col_to_label(col));
      size_t end_char = format_.find_last_of(col_to_label(col)) + 1;

      // Trim to length
      if (value.size() > end_char - start_char) {
	//std::cout << "Trimming string from " << value << " (" << value.size()
	//	  << ") to ";
	value = value.substr(0, end_char - start_char);
	//std::cout << value << " (" << value.size() << ")" << std::endl;
	//std::cout << "n.b. end_char - start_char = " << end_char - start_char
	//	  << std::endl;
      }

      // Pad out the new value with spaces
      std::string padded_value = value;
      padded_value.append(end_char - start_char - value.size(), ' ');

      // Replace with new value
      data_.at(row).replace(start_char, end_char - start_char,
			    padded_value, 0, end_char - start_char);
    }

    void ISISDataTable::set_double(size_t row, size_t col, double value)
    {
      std::ostringstream oss;
      oss << std::fixed << std::setprecision(9) << std::setw(10) << value;
      set_string(row, col, oss.str());
    }

    void ISISDataTable::set_long_int(size_t row, size_t col, long_int value)
    {
      std::ostringstream oss;
      oss << value;
      set_string(row, col, oss.str());
    }

    void ISISDataTable::set_bool(size_t row, size_t col, bool value)
    {
      std::ostringstream oss;
      oss << value;
      set_string(row, col, oss.str());
    }

    void ISISDataTable::read_raw(std::istream& is, size_t ndat) {
      if (special_case_) {
	if (format_ == "~block~") {
	  std::string block_text = "";
	  for (size_t i = 0; i < ndat; i++) {
	    std::string line;
	    std::getline(is,line);
	    boost::algorithm::trim_right(line);
	    if (i != 0) block_text += "\n";
	    block_text += line;
	  }
	  if (data_.size() == 0) data_.push_back("");
	  data_.at(0) = block_text;
	  return;
	}

	if (format_ == "~rules~") {
	  for (size_t i = 0; i < ndat; i++) {
	    std::string rule_text = "";
	    bool end_of_rule = false;
	    while (!end_of_rule) {
	      std::string line;
	      std::getline(is,line);
	      boost::algorithm::trim_right(line);
	      rule_text += line;
	      if (line.find("END") == 0 or line.find("end") == 0) end_of_rule = true;
	      if (!end_of_rule) rule_text += "\n";
	    }
	    data_.push_back(rule_text);
	  }
	  return;
	}
      }

      for (size_t i = 0; i < ndat; i++) {
	std::string line;
	std::getline(is,line);
	boost::algorithm::trim_right(line);
	data_.push_back(line);
      }
    }

    void ISISDataTable::write_raw(std::ostream& os) {
      for (size_t i = 0; i < data_.size(); i++) {
	if (i != 0) os << std::endl;
	os  << data_.at(i);
      }
    }

    boost::property_tree::ptree ISISDataTable::configuration(void) {
      boost::property_tree::ptree config;

      if (special_case_) {
	if (format_ == "~block~") {
	  config.put<std::string>("table-type", "text block");
	  config.put<std::string>("data", data_.at(0));
	}
	if (format_ == "~rules~") {
	  config.put<std::string>("table-type", "rules table");
	  config.put<std::string>("data", list_to_string(data_, "£"));
	}
      } else {
	config.put<std::string>("table-type", "fixed width");
	config.put<std::string>("format", format_);
	config.put<std::string>("data", list_to_string(data_));
      }

      return config;
    }


  };
};
