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

namespace HyNDAL {
  namespace ISIS {

    class ISISNetwork : public HyNDAL::OneDNetwork {
    private:
      
      // ISIS Model metadata stored in a property tree
      boost::property_tree::ptree metadata_;
      
      // Table of initial conditions
      ISISDataTable* initial_conditions_;

      /// Function to search the initial conditions table and, if the node
      /// label is not already represented, add a simple default initial
      /// condition
      void add_default_initial_condition(const std::string& node_label);
      
      /// Function to search the structures and see if a node label is
      /// represented. If the node label is not represented in the
      /// network, delete its initial condition from the table.
      void maybe_clear_initial_condition(const std::string& node_label);
      
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

      /*
      virtual void replace_structure(OneDStructure* old_structure,
				     OneDStructure* new_structure,
				     bool delete_old_structure = true);
      */
      
      // Add structures in ISIS DAT file format from a stream (read
      // structures with GENERAL unit and INITIAL CONDITIONS)
      virtual void add_dat_structures(std::istream& is);
      
      // Add structures in ISIS DAT file format from a stream (read
      // raw structures)
      virtual void add_structures(std::istream& is);
      
      virtual void write_dat_structures(std::ostream& os);
      virtual void write_structures(std::ostream& os);
      
      virtual boost::property_tree::ptree configuration(void);
      
    };
    
  };
};

#endif
