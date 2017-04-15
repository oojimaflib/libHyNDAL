/***********************************************************************
 * ISISStructures.cpp
 *
 * Definitions of ISIS structures
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

#include "../OneDStructure.hpp"
#include "../OneDReachSection.hpp"
#include "ISISStructure.hpp"

#include "ISISStructures.hpp"

namespace HyNDAL {
  namespace ISIS {
    
//----------------------------------------------------------------------
// Constructor

#define ISIS_STRUCTURE_START(NAME, ISIS_NAME)				\
    HyNDAL::OneDStructure*						\
    make_##NAME(const boost::property_tree::ptree& config)		\
    {									\
      return new NAME(config);						\
    }									\
    NAME::~NAME(void) { }						\
    std::string NAME::type(void) { return "ISIS-" ISIS_NAME; }		\
    NAME::NAME(const boost::property_tree::ptree& config)		\
      : HyNDAL::OneDStructure(config), ISISStructure(config)		\
    {									\
      extra_data_ = config.get_child("extra",				\
				     boost::property_tree::ptree());
    
    
#define ISIS_REACH_SECTION_START(NAME, ISIS_NAME)			\
    HyNDAL::OneDStructure*						\
    make_##NAME(const boost::property_tree::ptree& config)		\
    {									\
      return new NAME(config);						\
    }									\
    NAME::~NAME(void) { }						\
    std::string NAME::type(void) { return "ISIS-" ISIS_NAME; }		\
    NAME::NAME(const boost::property_tree::ptree& config)		\
      : HyNDAL::OneDReachSection(config), ISISStructure(config)		\
    {									\
      extra_data_ = config.get_child("extra",				\
				     boost::property_tree::ptree());


#define ISIS_STRUCTURE_END			\
    }

#define ISIS_REACH_SECTION_END			\
    }

#define ISIS_PROPERTY(TYPE, NAME, DEFAULT, DISPLAY_NAME, HELP_TEXT)	\
  NAME##_ = config.get<TYPE>(#NAME, DEFAULT);

#define ISIS_DATA_TABLE(NAME, FORMAT)				\
    boost::property_tree::ptree NAME##_config			\
    = config.get_child(#NAME, boost::property_tree::ptree());	\
    NAME##_ = ISISDataTable(NAME##_config);

#include "structure_definitions.hpp"

//----------------------------------------------------------------------
// Get property type by name

#define ISIS_STRUCTURE_START(NAME, ISIS_NAME)			\
  std::string NAME::property_type_by_name(const std::string& name)	\
  {

#define ISIS_REACH_SECTION_START(NAME, ISIS_NAME)			\
  std::string NAME::property_type_by_name(const std::string& name)	\
  {

#define ISIS_PROPERTY(TYPE, NAME, DEFAULT, DISPLAY_NAME, HELP_TEXT)	\
  if (name == #NAME) return #TYPE;

#define ISIS_DATA_TABLE(NAME, FORMAT)		\
  if (name == #NAME) return "ISISDataTable";

#define ISIS_STRUCTURE_END			\
  return "void";				\
  }
  
#define ISIS_REACH_SECTION_END			\
  return "void";				\
  }

#include "structure_definitions.hpp"

//----------------------------------------------------------------------
// Get property by name as string

#define ISIS_STRUCTURE_START(NAME, ISIS_NAME)			\
  std::string NAME::property_by_name(const std::string& name)	\
  {								\
    std::ostringstream oss;

#define ISIS_REACH_SECTION_START(NAME, ISIS_NAME)			\
  std::string NAME::property_by_name(const std::string& name)		\
  {									\
    std::ostringstream oss;
    
#define ISIS_PROPERTY(TYPE, NAME, DEFAULT, DISPLAY_NAME, HELP_TEXT)	\
  if (name == #NAME) {							\
    oss << NAME##_;							\
    return oss.str();							\
  }

#define ISIS_DATA_TABLE(NAME, FORMAT)

#define ISIS_STRUCTURE_END			\
  return "NULL";				\
  }
  
#define ISIS_REACH_SECTION_END			\
  return "NULL";				\
  }

#include "structure_definitions.hpp"

//----------------------------------------------------------------------
// Get table row count by name

#define ISIS_STRUCTURE_START(NAME, ISIS_NAME)				\
  size_t NAME::table_no_of_rows_by_name(const std::string& name)		\
  {

#define ISIS_REACH_SECTION_START(NAME, ISIS_NAME)			\
  size_t NAME::table_no_of_rows_by_name(const std::string& name)		\
  {

#define ISIS_DATA_TABLE(NAME, FORMAT)		\
  if (name == #NAME) {				\
    return NAME##_.no_of_rows();		\
  }

#define ISIS_STRUCTURE_END			\
  return 0;					\
  }
  
#define ISIS_REACH_SECTION_END			\
  return 0;					\
  }

#include "structure_definitions.hpp"

//----------------------------------------------------------------------
// Get table entry by name, column number and row number

#define ISIS_STRUCTURE_START(NAME, ISIS_NAME)				\
  std::string NAME::table_entry_by_name(const std::string& name, size_t row, size_t col) \
  {
    
#define ISIS_REACH_SECTION_START(NAME, ISIS_NAME)			\
  std::string NAME::table_entry_by_name(const std::string& name, size_t row, size_t col) \
  {

#define ISIS_DATA_TABLE(NAME, FORMAT)		\
  if (name == #NAME) {				\
    return NAME##_.get_string(row, col);	\
  }

#define ISIS_STRUCTURE_END			\
  return "NULL";				\
  }

#define ISIS_REACH_SECTION_END			\
  return "NULL";				\
  }

#include "structure_definitions.hpp"

//----------------------------------------------------------------------
// Set table entry by name, column number and row number

#define ISIS_STRUCTURE_START(NAME, ISIS_NAME)				\
  void NAME::set_table_entry_by_name(const std::string& name, size_t row, size_t col, const std::string& newval)		\
  {

#define ISIS_REACH_SECTION_START(NAME, ISIS_NAME)			\
  void NAME::set_table_entry_by_name(const std::string& name, size_t row, size_t col, const std::string& newval)		\
  {

#define ISIS_DATA_TABLE(NAME, FORMAT)			\
  if (name == #NAME) {					\
    NAME##_.set_string(row, col, newval);		\
  }

#define ISIS_STRUCTURE_END			\
  }
  
#define ISIS_REACH_SECTION_END			\
  }

#include "structure_definitions.hpp"

//----------------------------------------------------------------------
// Remaining methods

#define ISIS_STRUCTURE_START(NAME, ISIS_NAME)				\
    boost::property_tree::ptree& NAME::extra_data(void) {		\
      return extra_data_;						\
    }									\
    boost::property_tree::ptree NAME::configuration(void) {		\
    boost::property_tree::ptree config					\
    = HyNDAL::OneDStructure::configuration();				\
    boost::property_tree::ptree iconfig = ISISStructure::configuration(); \
    config.put<std::string>("node-labels",				\
			    iconfig.get<std::string>("node-labels", "")); \
    config.put<std::string>("comment",					\
			    iconfig.get<std::string>("comment", ""));	\
    config.put_child("extra", extra_data_);

#define ISIS_STRUCTURE_END			\
    return config;				\
  }

#define ISIS_REACH_SECTION_START(NAME, ISIS_NAME)			\
    boost::property_tree::ptree& NAME::extra_data(void) {		\
      return extra_data_;						\
    }									\
    boost::property_tree::ptree NAME::configuration(void) {		\
    boost::property_tree::ptree config					\
    = HyNDAL::OneDReachSection::configuration();			\
    boost::property_tree::ptree iconfig = ISISStructure::configuration(); \
    config.put<std::string>("node-labels",				\
			    iconfig.get<std::string>("node-labels", "")); \
    config.put<std::string>("comment",					\
			    iconfig.get<std::string>("comment", ""));	\
    config.put_child("extra", extra_data_);

#define ISIS_REACH_SECTION_END			\
    return config;				\
  }

#define ISIS_DATA_TABLE(NAME, FORMAT)					\
    boost::property_tree::ptree NAME##_config = NAME().configuration();	\
    config.put_child(#NAME, NAME##_config);

#define ISIS_PROPERTY(TYPE, NAME, DEFAULT, DISPLAY_NAME, HELP_TEXT)	\
    config.put<TYPE>(#NAME, this->NAME());

#include "structure_definitions.hpp"

  };
};
