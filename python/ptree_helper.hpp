/***********************************************************************
 * ptree_helper.hpp
 *
 * Helper class to make boost::property_tree::ptree objects easily
 * usable from the python interface.
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

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/info_parser.hpp"

#include <fstream>
#include <sstream>

struct ptree_helper {
  static std::string get_string(boost::property_tree::ptree& config,
				std::string path)
  {
    return config.get<std::string>(path);
  }
  static std::string get_string_def(boost::property_tree::ptree& config,
				    std::string path, std::string def_val)
  {
    return config.get<std::string>(path, def_val);
  }
  static void put_string(boost::property_tree::ptree& config,
			 std::string path, std::string value)
  {
    config.put<std::string>(path, value);
  }
  static void add_string(boost::property_tree::ptree& config,
			 std::string path, std::string value)
  {
    config.add<std::string>(path, value);
  }
  
  static double get_double(boost::property_tree::ptree& config,
			   std::string path)
  {
    return config.get<double>(path);
  }
  static double get_double_def(boost::property_tree::ptree& config,
				std::string path, double def_val)
  {
    return config.get<double>(path, def_val);
  }
  static void put_double(boost::property_tree::ptree& config,
			 std::string path, double value)
  {
    config.put<double>(path, value);
  }
  static void add_double(boost::property_tree::ptree& config,
			 std::string path, double value)
  {
    config.add<double>(path, value);
  }

  static size_t get_index(boost::property_tree::ptree& config,
			  std::string path)
  {
    return config.get<size_t>(path);
  }
  static size_t get_index_def(boost::property_tree::ptree& config,
			      std::string path, size_t def_val)
  {
    return config.get<size_t>(path, def_val);
  }
  static void put_index(boost::property_tree::ptree& config,
			 std::string path, size_t value)
  {
    config.put<size_t>(path, value);
  }
  static void add_index(boost::property_tree::ptree& config,
			 std::string path, size_t value)
  {
    config.add<size_t>(path, value);
  }

  static long get_integer(boost::property_tree::ptree& config,
			  std::string path)
  {
    return config.get<long>(path);
  }
  static long get_integer_def(boost::property_tree::ptree& config,
			      std::string path, long def_val)
  {
    return config.get<long>(path, def_val);
  }
  static void put_integer(boost::property_tree::ptree& config,
			  std::string path, long value)
  {
    config.put<long>(path, value);
  }
  static void add_integer(boost::property_tree::ptree& config,
			  std::string path, long value)
  {
    config.add<long>(path, value);
  }

  static bool get_boolean(boost::property_tree::ptree& config,
			  std::string path)
  {
    return config.get<bool>(path);
  }
  static bool get_boolean_def(boost::property_tree::ptree& config,
			      std::string path, bool def_val)
  {
    return config.get<bool>(path, def_val);
  }
  static void put_boolean(boost::property_tree::ptree& config,
			  std::string path, bool value)
  {
    config.put<bool>(path, value);
  }
  static void add_boolean(boost::property_tree::ptree& config,
			  std::string path, bool value)
  {
    config.add<bool>(path, value);
  }
  
  static boost::property_tree::ptree get_child(boost::property_tree::ptree& config,
					       std::string path)
  {
    return config.get_child(path);
  }
  static void put_child(boost::property_tree::ptree& config,
			std::string path,
			boost::property_tree::ptree child)
  {
    config.put_child(path, child);
  }
  static void add_child(boost::property_tree::ptree& config,
			std::string path,
			boost::property_tree::ptree child)
  {
    config.add_child(path, child);
  }
  
};

boost::property_tree::ptree ptree_helper_read_info_stream(std::istream& is)
{
  boost::property_tree::ptree config;
  boost::property_tree::read_info(is, config);
  return config;
}

boost::property_tree::ptree ptree_helper_read_info_file(std::string filename)
{
  std::ifstream is(filename.c_str());
  if (!is.is_open()) {
    throw std::runtime_error("Could not open file in read_configuration()");
  }
  boost::property_tree::ptree config = ptree_helper_read_info_stream(is);
  is.close();
  return config;
}

boost::property_tree::ptree ptree_helper_read_info_string(std::string data)
{
  std::istringstream is(data);
  boost::property_tree::ptree config = ptree_helper_read_info_stream(is);
  return config;
}

