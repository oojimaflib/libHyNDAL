/***********************************************************************
 * OneDStructure.hpp
 *
 * Represents a boundary condition (internal or external) in a 1d
 * hydraulic network.
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

#ifndef OneDStructure_hpp
#define OneDStructure_hpp

#include "boost/property_tree/ptree.hpp"

#include <list>
#include <map>

namespace HyNDAL {

  class OneDStructure;

  extern std::map<std::string, OneDStructure* (*)(const boost::property_tree::ptree&)> structure_factory_table_;

  class OneDStructure {
  private:

    // Connections
    std::list<OneDStructure*> connections_;

  public:

    OneDStructure(const boost::property_tree::ptree& config
		  = boost::property_tree::ptree());

    virtual ~OneDStructure(void) {}

    virtual std::string type(void) { return "structure"; }

    virtual bool is_reach_section(void) { return false; }

    virtual size_t no_of_connections(void) { return connections_.size(); }

    //virtual void add_connection(OneDStructure* structure) {}

    //virtual void remove_connection(OneDStructure* structure) {}

    //virtual bool is_connected(OneDStructure* structure) {}

    virtual boost::property_tree::ptree configuration(void);

  };

  OneDStructure* make_structure(std::string type,
				const boost::property_tree::ptree& config
				= boost::property_tree::ptree(),
				bool ignore_unknown = false);

};

#endif
