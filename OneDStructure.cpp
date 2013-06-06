/***********************************************************************
 * OneDStructure.cpp
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

#include "OneDStructure.hpp"

#include <sstream>
#include <stdexcept>

namespace HyNDAL {

  std::map<std::string, OneDStructure* (*)(const boost::property_tree::ptree&)> structure_factory_table_;

  OneDStructure::OneDStructure(const boost::property_tree::ptree& config)
  {
  }

  boost::property_tree::ptree OneDStructure::configuration(void)
  {
    boost::property_tree::ptree config;
    config.put("is-reach-section", false);
    return config;
  }

  OneDStructure* make_structure(std::string type,
				const boost::property_tree::ptree& config,
				bool ignore_unknown)
  {
    if (structure_factory_table_.count(type) > 0) {
      return (*structure_factory_table_[type])(config);
    }

    if (ignore_unknown) return NULL;

    std::ostringstream oss;
    oss << "Error: unknown structure type " << type << "." << std::endl
	<< structure_factory_table_.size() << " types known." << std::endl;
    throw std::runtime_error(oss.str());
  }

};
