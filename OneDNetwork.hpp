/***********************************************************************
 * OneDNetwork.hpp
 *
 * Class representing a branched one-dimensional hydraulic network
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

#ifndef OneDNetwork_hpp
#define OneDNetwork_hpp

#include <vector>
#include <map>
#include <string>

#include "boost/property_tree/ptree.hpp"

namespace HyNDAL {
  
  class OneDReach;
  class OneDStructure;
  
  class OneDNetwork {
  protected:

    typedef std::pair<std::string, OneDStructure*> NamedStructure;

    struct OneDConnection {
      // A named connection object linking two named structures (the
      // pointers must be to objects stored in the structures_ vector).
      std::string label;
      NamedStructure* upstream;
      NamedStructure* downstream;    
    };

  private:

    // Components in the network
    std::vector<NamedStructure> structures_;

    // Links between components in the network
    std::vector<OneDConnection> connections_;

    bool connections_are_up_to_date_;

    size_t find_structure(const std::string& name);
    size_t find_structure(OneDStructure* structure);

  public:

    std::vector< std::pair<std::string, OneDStructure*> >& structures(void) {
      return structures_;
    }

    virtual void append_structure(const std::string& name,
				  OneDStructure* structure);

    virtual void insert_structure(const size_t before,
				  const std::string& name,
				  OneDStructure* structure);

    virtual void insert_structure(const std::string& before,
				  const std::string& name,
				  OneDStructure* structure);

    virtual void remove_structure(const size_t structure_no);

    virtual void remove_structure(const std::string& structure_name);

    virtual void replace_structure(OneDStructure* old_structure,
				   OneDStructure* new_structure,
				   bool delete_old_structure = true);

    virtual size_t no_of_connections(void) { return connections_.size(); }
  
    // Return the name of the kth connection
    virtual std::string connection_label(size_t k);

    // Reverse the direction of a connection
    virtual void connection_swap_direction(size_t k);

    // Test whether the kth connection has links upstream and downstream
    virtual bool connected_us(size_t k);
    virtual bool connected_ds(size_t k);

    // Set the kth connection's upstream and downstream structure
    virtual void connection_set_us(size_t k, size_t i);
    virtual void connection_set_ds(size_t k, size_t i);

    virtual size_t connection_us_structure_no(size_t k);
    virtual size_t connection_ds_structure_no(size_t k);
  
    virtual OneDStructure* connection_us_structure_ptr(size_t k);
    virtual OneDStructure* connection_ds_structure_ptr(size_t k);
  
    // Make a new connection
    virtual size_t append_connection(std::string label);

  public:

    OneDNetwork(const boost::property_tree::ptree& config 
		= boost::property_tree::ptree());

    virtual ~OneDNetwork(void);

    virtual size_t no_of_structures(void) { return structures_.size(); }

    virtual const std::string& get_name(const size_t structure_no);

    virtual OneDStructure* get_structure_ptr(const size_t structure_no);
    virtual OneDStructure* get_structure_ptr(const std::string& name);

    virtual OneDStructure& get_structure(const size_t structure_no);
    virtual OneDStructure& get_structure(const std::string& name);

    virtual boost::property_tree::ptree configuration(void);

  };

}; // End Namespace HyNDAL

#endif
