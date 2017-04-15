/***********************************************************************
 * ISISNetwork.hpp
 *
 * OneDNetwork specialisation for the ISIS hydraulic model
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

#ifndef ISIS_ISISNetwork_hpp
#define ISIS_ISISNetwork_hpp

#include "boost/property_tree/ptree.hpp"

#include "../OneDNetwork.hpp"
#include "ISISDataTable.hpp"

#include <array>
#include <unordered_map>
#include <set>

namespace HyNDAL {
  namespace ISIS {

    class InitialConditionData : public std::array<double, 7> {
    public:

      InitialConditionData(double Q = 0.0, double h = 0.0, double Fr = 0.0,
			   double u = 0.0, double mode = 0.0,
			   double state = 0.0, double z = 0.0)
	: std::array<double, 7>({ Q, h, Fr, u, mode, state, z })
      {}

      double& flow(void) { return at(0); }
      double& stage(void) { return at(1); }
      double& froude(void) { return at(2); }
      double& velocity(void) { return at(3); }
      double& mode(void) { return at(4); }
      double& state(void) { return at(5); }
      double& z(void) { return at(6); }
      
    };
    
    class ISISNetwork : public HyNDAL::OneDNetwork {
    private:
      
      // ISIS Model metadata stored in a property tree
      boost::property_tree::ptree metadata_;
      
      // Table of initial conditions
      //ISISDataTable* initial_conditions_;

      // Unordered map of initial conditions
      std::unordered_map<std::string, InitialConditionData> initial_conditions_map_;

      // Function to return a list (set) of all the node labels in the model
      std::set<std::string> node_label_set(void);
      
      // Function to count the unique node labels in the model
      size_t no_of_node_labels(void);

      /// Function to search the initial conditions table and, if the node
      /// label is not already represented, add a simple default initial
      /// condition
      // void add_default_initial_condition(const std::string& node_label);
      
      /// Function to search the structures and see if a node label is
      /// represented. If the node label is not represented in the
      /// network, delete its initial condition from the table.
      // void maybe_clear_initial_condition(const std::string& node_label);
      
    public:
      
      ISISNetwork(const boost::property_tree::ptree& config
		  = boost::property_tree::ptree());
      
      virtual ~ISISNetwork(void);
      
      virtual void append_structure(const std::string& name,
				    HyNDAL::OneDStructure* structure);
      
      virtual void insert_structure(const size_t before,
				    const std::string& name,
				    HyNDAL::OneDStructure* structure);
      
      virtual void remove_structure(const size_t structure_no);

      virtual InitialConditionData& get_initial_condition(std::string node_label)
      {
	return initial_conditions_map_[node_label];;
      }

      /*
      virtual void replace_structure(OneDStructure* old_structure,
				     OneDStructure* new_structure,
				     bool delete_old_structure = true);
      */
      
      // Add structures in ISIS DAT file format from a stream (read
      // structures with GENERAL unit and INITIAL CONDITIONS)
      virtual size_t add_dat_structures(std::istream& is);
      
      // Add structures in ISIS DAT file format from a stream (read
      // raw structures)
      virtual size_t add_structures(std::istream& is);
      
      virtual void write_dat_structures(std::ostream& os);
      virtual void write_structures(std::ostream& os);
      
      virtual boost::property_tree::ptree configuration(void);
      
    };
    
  };
};

#endif
