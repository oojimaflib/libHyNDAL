/***********************************************************************
 * OneDNetworkWrapper.hpp
 *
 * Wrapper class to make OneDNetwork objects available to the python
 * interface.
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

using namespace boost::python;

struct OneDNetworkWrapper
  : HyNDAL::OneDNetwork, wrapper<HyNDAL::OneDNetwork> {

  OneDNetworkWrapper(const boost::property_tree::ptree& config
		     = boost::property_tree::ptree())
    : HyNDAL::OneDNetwork(config), wrapper<HyNDAL::OneDNetwork>()
  {}

  void append_structure(const std::string& name,
			HyNDAL::OneDStructure* structure)
  {
    if (override append_structure = this->get_override("append_structure"))
      append_structure(name, structure);
    HyNDAL::OneDNetwork::append_structure(name, structure);
  }

  void default_append_structure(const std::string& name,
				HyNDAL::OneDStructure* structure)
  {
    this->HyNDAL::OneDNetwork::append_structure(name, structure);
  }
};  
