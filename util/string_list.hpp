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

#ifndef util_string_list_hpp
#define util_string_list_hpp

#include "boost/filesystem.hpp"

#include <vector>
#include <string>

std::string list_to_string(std::vector<std::string> list,
			   std::string delimiter = ",");

std::vector<std::string> string_to_list(std::string list,
					std::string delimiter = ",");

std::string filelist_to_string(std::vector<boost::filesystem::path> filelist,
			       std::string delimiter = ",");

std::vector<boost::filesystem::path> string_to_filelist(std::string filelist,
							std::string delimiter = ",");

#endif
