/***********************************************************************
 * string_list.hpp
 *
 * Utility functions for converting between std::vector's and
 * delimited lists of std::string objects.
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

#include "string_list.hpp"
#include <iostream>

std::string list_to_string(std::vector<std::string> list,
			   std::string delimiter) {
  std::string result = "";
  if (list.size() == 0) return result;
  result += list.at(0);
  if (list.size() == 1) return result;
  for (size_t i = 1; i < list.size(); i++) {
    result += delimiter;
    result += list.at(i);
  }
  return result;
}

std::vector<std::string> string_to_list(std::string list,
					std::string delimiter) {
  std::string locallist = list;
  std::vector<std::string> result;
  if (list.size() == 0) return result;
  size_t next_delim = locallist.find(delimiter);
  while (next_delim != std::string::npos) {
    result.push_back(locallist.substr(0, next_delim));
    locallist = locallist.substr(next_delim + delimiter.size());
    next_delim = locallist.find(delimiter);
  }
  result.push_back(locallist);
  return result;
}

std::string filelist_to_string(std::vector<boost::filesystem::path> list,
			       std::string delimiter) {
  std::string result = "";
  if (list.size() == 0) return result;
  result += list.at(0).string();
  if (list.size() == 1) return result;
  for (size_t i = 1; i < list.size(); i++) {
    result += delimiter;
    result += list.at(i).string();
  }
  return result;
}

std::vector<boost::filesystem::path> string_to_filelist(std::string list,
					      std::string delimiter) {
  std::string locallist = list;
  std::vector<boost::filesystem::path> result;
  if (list.size() == 0) return result;
  size_t next_delim = locallist.find(delimiter);
  while (next_delim != std::string::npos) {
    result.push_back(boost::filesystem::path(locallist.substr(0, next_delim)));
    locallist = locallist.substr(next_delim + delimiter.size());
    next_delim = locallist.find(delimiter);
  }
  result.push_back(boost::filesystem::path(locallist));
  return result;
}




