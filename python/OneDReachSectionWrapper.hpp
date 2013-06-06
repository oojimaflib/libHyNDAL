/***********************************************************************
 * OneDReachSectionWrapper.hpp
 *
 * Wrapper class to make OneDReachSection objects available to the
 * python interface.
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

struct OneDReachSectionWrapper
  : HyNDAL::OneDReachSection, wrapper<HyNDAL::OneDReachSection> {

  OneDReachSectionWrapper(const boost::property_tree::ptree& config
			  = boost::property_tree::ptree())
    : HyNDAL::OneDReachSection(config), wrapper<HyNDAL::OneDReachSection>()
  {}
  
  double get_length(void)
  {
    if (override get_length = this->get_override("get_length"))
      return get_length();
    return get_length_();
  }

  double get_length_(void)
  {
    return HyNDAL::OneDReachSection::length();
  }

  double default_get_length(void)
  {
    return this->get_length_();
  }

  void set_length(double value)
  {
    if (override set_length = this->get_override("set_length"))
      set_length(value);
    set_length_(value);
  }

  void set_length_(double value) {
    HyNDAL::OneDReachSection::length() = value;
  }

  void default_set_length(double value)
  {
    this->set_length_(value);
  }

  bool is_end_of_reach(void)
  {
    if (override is_end_of_reach = this->get_override("is_end_of_reach"))
      return is_end_of_reach();
    return is_end_of_reach_();
  }

  bool is_end_of_reach_(void)
  {
    return HyNDAL::OneDReachSection::end_of_reach();
  }

  bool default_is_end_of_reach(void)
  {
    return this->is_end_of_reach_();
  }

  void set_end_of_reach(bool value)
  {
    if (override set_end_of_reach = this->get_override("set_end_of_reach"))
      set_end_of_reach(value);
    set_end_of_reach_(value);
  }

  void set_end_of_reach_(bool value) {
    HyNDAL::OneDReachSection::end_of_reach() = value;
  }

  void default_set_end_of_reach(bool value)
  {
    this->set_end_of_reach_(value);
  }

  boost::property_tree::ptree configuration(void)
  {
    if (override configuration = this->get_override("configuration"))
      return configuration();
    return HyNDAL::OneDReachSection::configuration();
  }
  
  boost::property_tree::ptree default_configuration(void)
  {
    return this->HyNDAL::OneDReachSection::configuration();
  }

};
