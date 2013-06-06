/***********************************************************************
 * ISISStructures.hpp
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

#ifndef ISISStructures_hpp
#define ISISStructures_hpp

#include "../OneDStructure.hpp"
#include "../OneDReachSection.hpp"
#include "ISISStructure.hpp"
#include "ISISDataTable.hpp"

namespace HyNDAL {
  namespace ISIS {

#define ISIS_STRUCTURE_START(NAME, ISIS_NAME)				\
    HyNDAL::OneDStructure*						\
    make_##NAME(const boost::property_tree::ptree& config		\
		= boost::property_tree::ptree());			\
    class NAME								\
      : public HyNDAL::OneDStructure,					\
	public ISISStructure						\
    {									\
  private:								\
      boost::property_tree::ptree extra_data_;				\
  public:								\
  NAME(const boost::property_tree::ptree& config			\
       = boost::property_tree::ptree());				\
  virtual ~NAME(void);							\
  virtual std::string type(void);					\
  virtual boost::property_tree::ptree& extra_data(void);		\
  virtual boost::property_tree::ptree configuration(void);
    
#define ISIS_REACH_SECTION_START(NAME, ISIS_NAME)			\
    HyNDAL::OneDStructure*						\
    make_##NAME(const boost::property_tree::ptree& config		\
		= boost::property_tree::ptree());			\
    class NAME								\
      : public HyNDAL::OneDReachSection,				\
	public ISISStructure						\
    {									\
  private:								\
      boost::property_tree::ptree extra_data_;				\
  public:								\
  NAME(const boost::property_tree::ptree& config			\
       = boost::property_tree::ptree());				\
  virtual ~NAME(void);							\
  virtual std::string type(void);					\
  virtual boost::property_tree::ptree& extra_data(void);		\
  virtual boost::property_tree::ptree configuration(void);
    
#define ISIS_STRUCTURE_END			\
    };
    
#define ISIS_REACH_SECTION_END			\
    };
    
#define ISIS_PROPERTY(TYPE, NAME, DEFAULT)		\
    private:						\
    TYPE NAME##_;					\
  public:						\
  virtual TYPE& NAME(void) { return NAME##_; }
    
#define ISIS_DATA_TABLE(NAME, FORMAT)			\
    private:						\
    ISISDataTable NAME##_;				\
  public:						\
  virtual ISISDataTable& NAME(void) { return NAME##_; }
    
#define ISIS_TABLE_COLUMN(TYPE, NAME, COLUMN, TABLE)		\
    public:							\
    virtual TYPE get_##NAME(size_t row) {			\
      return TABLE##_.get_##TYPE(row, COLUMN); }		\
    virtual void set_##NAME(size_t row, TYPE value) {		\
      return TABLE##_.set_##TYPE(row, COLUMN, value); }
    
#include "structure_definitions.hpp"
    
  };
};

#endif
