/***********************************************************************
 * error_reporting.hpp
 *
 * Set of convenience functions, macros and classes to provide error
 * reporting and exception handling.
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
 * Copyright (C) Gerald C J Morgan 2012
 ***********************************************************************/

#ifndef util_error_reporting_hpp
#define util_error_reporting_hpp

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/tee.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>

namespace boostio = boost::iostreams;

// Set the global default verbosity at compile time. Specification on
// the command line overrides this.
#ifndef VERBOSITY
#  define VERBOSITY 10
#endif

// External definition of the global log file
extern boostio::filtering_ostream* output_stream_;

// Function to set the log file
void set_log_file(std::string log_filename);

// Macro for printing (debugging) messages to the console
#define PRINT(level)				\
  if (level < VERBOSITY) (*output_stream_)




#endif
