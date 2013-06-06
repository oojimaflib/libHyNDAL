/***********************************************************************
 * ISISDataTable.hpp
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

#ifndef ISIS_ISISDataTable_hpp
#define ISIS_ISISDataTable_hpp

#include "boost/property_tree/ptree.hpp"

#include <vector>
#include <string>
#include <iostream>

namespace HyNDAL {
  namespace ISIS {

    class ISISDataTable {
    private:

      std::string format_;

      bool special_case_;

      std::vector<std::string> data_;

      char col_to_label(size_t col);

      size_t no_of_columns_;

    public:

      ISISDataTable(std::string format,
		    std::vector<std::string> data = std::vector<std::string>());

      ISISDataTable(const boost::property_tree::ptree& config
		    = boost::property_tree::ptree());

      virtual ~ISISDataTable(void) {}

      size_t no_of_rows(void);

      size_t no_of_columns(void) { return no_of_columns_; }

      std::string get_row(size_t i) {
	return data_.at(i);
      }

      void append_row(const std::string& row) {
	data_.push_back(row);
      }

      void insert_row(size_t before, const std::string& row = std::string());

      void remove_row(const size_t row) {
	data_.erase(data_.begin() + row);
      }

      std::string get_string(size_t row, size_t col);
      double get_double(size_t row, size_t col);
      long int get_long_int(size_t row, size_t col);
      bool get_bool(size_t row, size_t col);

      void set_string(size_t row, size_t col, std::string value);
      void set_double(size_t row, size_t col, double value);
      void set_long_int(size_t row, size_t col, long int value);
      void set_bool(size_t row, size_t col, bool value);

      void read_raw(std::istream&, size_t no_of_lines);
      void write_raw(std::ostream&);

      virtual boost::property_tree::ptree configuration(void);
  
    };

  };
};
#endif
