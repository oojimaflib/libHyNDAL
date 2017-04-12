/***********************************************************************
 * error_reporting.cpp
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

#include "error_reporting.hpp"

boostio::filtering_ostream* output_stream_;

void set_log_file(std::string log_filename) {
  output_stream_ = new boostio::filtering_ostream;
  boostio::basic_file_sink<char> filesink(log_filename);
  output_stream_->push(boostio::tee_device< decltype(std::cout),
		       decltype(filesink) >(std::cout, filesink));
}
