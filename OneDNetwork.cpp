/***********************************************************************
 * OneDNetwork.cpp
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

#include "OneDNetwork.hpp"

#include "OneDStructure.hpp"

#include "util/string_list.hpp"

#include <stdexcept>

namespace HyNDAL {

  OneDNetwork::OneDNetwork(const boost::property_tree::ptree& config)
  {
    boost::property_tree::ptree::const_iterator it;
    for (it = config.begin(); it != config.end(); it++) {
      OneDStructure* ods = make_structure(it->first, it->second, true);
      if (ods != NULL)
	append_structure(it->second.data(), ods);
    }
  }

  OneDNetwork::~OneDNetwork(void)
  {
    std::vector< std::pair<std::string, OneDStructure*> >::iterator it;
    for (it = structures_.begin(); it != structures_.end(); it++) {
      delete it->second;
    }
  }

  size_t OneDNetwork::find_structure(const std::string& name)
  {
    for (size_t i = 0; i < structures_.size(); i++) {
      if (structures_.at(i).first == name) return i;
    }
    throw std::runtime_error("Structure not found.");
  }

  size_t OneDNetwork::find_structure(OneDStructure* structure)
  {
    for (size_t i = 0; i < structures_.size(); i++) {
      if (structures_.at(i).second == structure) return i;
    }
    throw std::runtime_error("Structure not found.");
  }

  void OneDNetwork::append_structure(const std::string& name,
				     OneDStructure* structure)
  {
    structures_.push_back( std::make_pair(std::string(name), structure) );
  }

  void OneDNetwork::insert_structure(const size_t before,
				     const std::string& name,
				     OneDStructure* structure)
  {
    structures_.insert(structures_.begin() + before,
		       std::make_pair(std::string(name), structure));
  }

  void OneDNetwork::insert_structure(const std::string& before,
				     const std::string& name,
				     OneDStructure* structure)
  {
    insert_structure(find_structure(before), name, structure);
  }

  void OneDNetwork::remove_structure(const size_t structure_no)
  {
    delete structures_.at(structure_no).second;
    structures_.erase(structures_.begin() + structure_no);
  }

  void OneDNetwork::remove_structure(const std::string& structure_name)
  {
    remove_structure(find_structure(structure_name));
  }

  const std::string& OneDNetwork::get_name(const size_t structure_no)
  {
    return structures_.at(structure_no).first;
  }

  std::string OneDNetwork::connection_label(size_t k)
  {
    return connections_.at(k).label;
  }

  void OneDNetwork::connection_swap_direction(size_t k)
  {
    NamedStructure* ns = connections_.at(k).upstream;
    connections_.at(k).upstream = connections_.at(k).downstream;
    connections_.at(k).downstream = ns;
  }

  bool OneDNetwork::connected_us(size_t k)
  {
    return (connections_.at(k).upstream != NULL);
  }

  bool OneDNetwork::connected_ds(size_t k)
  {
    return (connections_.at(k).downstream != NULL);
  }

  void OneDNetwork::connection_set_us(size_t k, size_t structure_no)
  {
    connections_.at(k).upstream = &structures_.at(structure_no);
  }

  void OneDNetwork::connection_set_ds(size_t k, size_t structure_no)
  {
    connections_.at(k).downstream = &structures_.at(structure_no);
  }

  size_t OneDNetwork::connection_us_structure_no(size_t k)
  {
    NamedStructure* nsptr = connections_.at(k).upstream;
    for (size_t i = 0; i < structures_.size(); i++) {
      if (&(structures_.at(i)) == nsptr) {
	return i;
      }
    }
    throw;
  }

  size_t OneDNetwork::connection_ds_structure_no(size_t k)
  {
    NamedStructure* nsptr = connections_.at(k).downstream;
    for (size_t i = 0; i < structures_.size(); i++) {
      if (&(structures_.at(i)) == nsptr) {
	return i;
      }
    }
    throw;
  }

  OneDStructure* OneDNetwork::connection_us_structure_ptr(size_t k)
  {
    return connections_.at(k).upstream->second;
  }

  OneDStructure* OneDNetwork::connection_ds_structure_ptr(size_t k)
  {
    return connections_.at(k).downstream->second;
  }

  size_t OneDNetwork::append_connection(std::string label)
  {
    OneDConnection conn;
    conn.label = label;
    conn.upstream = NULL;
    conn.downstream = NULL;

    size_t k = connections_.size();
    connections_.push_back(conn);

    return k;
  }

  OneDStructure* OneDNetwork::get_structure_ptr(const size_t structure_no)
  {
    return structures_.at(structure_no).second;
  }

  OneDStructure* OneDNetwork::get_structure_ptr(const std::string& name)
  {
    return get_structure_ptr(find_structure(name));
  }

  OneDStructure& OneDNetwork::get_structure(const size_t structure_no)
  {
    return *get_structure_ptr(structure_no);
  }

  OneDStructure& OneDNetwork::get_structure(const std::string& name)
  {
    return *get_structure_ptr(find_structure(name));
  }

  /*
    void OneDNetwork::add_structure(std::string name, OneDStructure* structure)
    {
    structures_.push_back( std::make_pair(name, structure) );
    }

    void OneDNetwork::remove_structure(std::string name)
    {
    std::vector< std::pair<std::string, OneDStructure*> >::iterator it;
    for (it = structures_.begin(); it != structures_.end(); it++) {
    if (it->first == name) {
    delete it->second;
    structures_.erase(it);
    return;
    }
    }
    throw std::runtime_error("Tried to remove non-existent structure.");
    }

    OneDStructure* OneDNetwork::get_structure(std::string name)
    {
    std::vector< std::pair<std::string, OneDStructure*> >::iterator it;
    for (it = structures_.begin(); it != structures_.end(); it++) {
    if (it->first == name) {
    return it->second;
    }
    }
    throw std::runtime_error("Tried to get non-existent structure.");
    }

  */

  boost::property_tree::ptree OneDNetwork::configuration(void)
  {
    boost::property_tree::ptree config;

    std::vector< std::pair<std::string, OneDStructure*> >::iterator it;
    for (it = structures_.begin(); it != structures_.end(); it++) {
      boost::property_tree::ptree& child = 
	config.add_child(it->second->type(), it->second->configuration());
      child.put_value(it->first);
    }
  
    return config;
  }

};
