/***********************************************************************
 * ISISStructure.cpp
 *
 * Represents a boundary condition (internal or external) in a 1d
 * ISIS hydraulic network.
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

#include "ISISStructure.hpp"
#include "ISISDataTable.hpp"

#include "ISISStructures.hpp"

#include "../util/string_list.hpp"

namespace HyNDAL {
  namespace ISIS {

    ISISStructure::ISISStructure(std::vector<std::string> node_labels,
				 std::string comment)
      : node_labels_(node_labels),
	comment_(comment)
    {
    }

    ISISStructure::ISISStructure(const boost::property_tree::ptree& config)
      : node_labels_(string_to_list(config.get<std::string>("node-labels", ""))),
	comment_(config.get<std::string>("comment", ""))
    {
      /*
      std::cout << "Created ISISStructure object with " << node_labels_.size()
		<< " labels" << std::endl;
      */
    }

    ISISStructure::~ISISStructure(void) {
    }

    boost::property_tree::ptree ISISStructure::configuration(void)
    {
      boost::property_tree::ptree config;
      config.put<std::string>("comment", comment_);
      config.put<std::string>("node-labels", list_to_string(node_labels_));
      return config;
    }

#define ISIS_STRUCTURE_START(NAME, ISIS_NAME)			\
    structure_factory_table_["ISIS-" ISIS_NAME] = &make_##NAME;

#define ISIS_REACH_SECTION_START(NAME, ISIS_NAME)		\
    structure_factory_table_["ISIS-" ISIS_NAME] = &make_##NAME;

    void register_structures(void)
    {
#include "structure_definitions.hpp"
    }

  };
};
