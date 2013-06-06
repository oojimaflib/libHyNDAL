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

#define ISIS_PROPERTY(TYPE, NAME, DEFAULT)	\
    NAME##_ = config.get<TYPE>(#NAME, DEFAULT);

#define ISIS_DATA_TABLE(NAME, FORMAT)				\
    boost::property_tree::ptree NAME##_config			\
    = config.get_child(#NAME, boost::property_tree::ptree());	\
    NAME##_ = ISISDataTable(NAME##_config);

#include "structure_definitions.hpp"

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

#define ISIS_PROPERTY(TYPE, NAME, DEFAULT)	\
    config.put<TYPE>(#NAME, this->NAME());

#include "structure_definitions.hpp"

  };
};
