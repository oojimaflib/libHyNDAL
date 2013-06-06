/***********************************************************************
 * ISISStructure.hpp
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

#ifndef ISISStructure_hpp
#define ISISStructure_hpp

#include "ISISDataTable.hpp"

#include <vector>
#include <string>

namespace HyNDAL {
  namespace ISIS {

    class ISISStructure { 
    private:

      std::vector<std::string> node_labels_;

      std::string comment_;

    public:

      ISISStructure(std::vector<std::string> node_labels, std::string comment);

      ISISStructure(const boost::property_tree::ptree& config
		    = boost::property_tree::ptree());

      virtual ~ISISStructure(void);

      virtual std::string type(void) { return "ISIS-structure"; }

      virtual size_t no_of_node_labels(void) { return node_labels_.size(); }

      virtual std::string& node_label(size_t i = 0) { return node_labels_.at(i); }

      virtual void insert_node_label(size_t before = 0,
				     const std::string& label = std::string()) {
	if (before > 0) {
	  node_labels_.insert(node_labels_.begin() + before, label);
	} else {
	  node_labels_.push_back(label);
	}
      }

      virtual std::string& comment(void) { return comment_; }

      //void update_connections(ISISNetwork* isis_network);

      virtual boost::property_tree::ptree configuration(void);

    };

    void register_structures(void);

  };
};

#endif
