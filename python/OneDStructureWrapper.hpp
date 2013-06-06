/***********************************************************************
 * OneDStructureWrapper.hpp
 *
 * Wrapper class to make OneDStructure objects available to the python
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

struct OneDStructureWrapper
  : HyNDAL::OneDStructure, wrapper<HyNDAL::OneDStructure> {

  OneDStructureWrapper(const boost::property_tree::ptree& config
		       = boost::property_tree::ptree())
    : HyNDAL::OneDStructure(config), wrapper<HyNDAL::OneDStructure>()
  {}
  
  boost::property_tree::ptree configuration(void)
  {
    if (override configuration = this->get_override("configuration"))
      return configuration();
    return HyNDAL::OneDStructure::configuration();
  }
  
  boost::property_tree::ptree default_configuration(void)
  {
    return this->HyNDAL::OneDStructure::configuration();
  }
};
