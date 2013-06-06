/***********************************************************************
 * HyNDAL.cpp
 *
 * Python interface to libHyNDAL
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

#include "../OneDNetwork.hpp"
#include "../OneDStructure.hpp"
#include "../OneDReachSection.hpp"

#include <boost/python.hpp>

#include "ptree_helper.hpp"
#include "OneDStructureWrapper.hpp"
#include "OneDReachSectionWrapper.hpp"
#include "OneDNetworkWrapper.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE(HyNDAL)
{
  class_<boost::property_tree::ptree>("PTree")
    .def("__len__", &boost::property_tree::ptree::size)
    .def("clear", &boost::property_tree::ptree::clear)

    .def("get_string", &ptree_helper::get_string)
    .def("get_string_def", &ptree_helper::get_string_def)
    .def("put_string", &ptree_helper::put_string)
    .def("add_string", &ptree_helper::add_string)

    .def("get_double", &ptree_helper::get_double)
    .def("get_double_def", &ptree_helper::get_double_def)
    .def("put_double", &ptree_helper::put_double)
    .def("add_double", &ptree_helper::add_double)

    .def("get_index", &ptree_helper::get_integer)
    .def("get_index_def", &ptree_helper::get_integer_def)
    .def("put_index", &ptree_helper::put_index)
    .def("add_index", &ptree_helper::add_index)

    .def("get_integer", &ptree_helper::get_integer)
    .def("get_integer_def", &ptree_helper::get_integer_def)
    .def("put_integer", &ptree_helper::put_integer)
    .def("add_integer", &ptree_helper::add_integer)

    .def("get_boolean", &ptree_helper::get_boolean)
    .def("get_boolean_def", &ptree_helper::get_boolean_def)
    .def("put_boolean", &ptree_helper::put_boolean)
    .def("add_boolean", &ptree_helper::add_boolean)

    .def("get_child", &ptree_helper::get_child)
    .def("put_child", &ptree_helper::put_child)
    .def("add_child", &ptree_helper::add_child)
    ;

  def("read_info_file", &ptree_helper_read_info_file);
  def("read_info_string", &ptree_helper_read_info_string);

  class_<OneDStructureWrapper,
	 boost::noncopyable>("OneDStructure",
			     init<const boost::property_tree::ptree&>())
    .def("configuration",
	 &HyNDAL::OneDStructure::configuration,
	 &OneDStructureWrapper::default_configuration)
    ;

  def("make_structure", &HyNDAL::make_structure,
      return_value_policy<manage_new_object>());

  class_<OneDReachSectionWrapper,
	 boost::noncopyable>("OneDReachSection",
			     init<const boost::property_tree::ptree&>())
    .def("get_length",
	 &OneDReachSectionWrapper::get_length_,
	 &OneDReachSectionWrapper::default_get_length)
    .def("set_length",
	 &OneDReachSectionWrapper::set_length_,
	 &OneDReachSectionWrapper::default_set_length)
    .def("is_end_of_reach",
	 &OneDReachSectionWrapper::is_end_of_reach_,
	 &OneDReachSectionWrapper::default_is_end_of_reach)
    .def("set_end_of_reach",
	 &OneDReachSectionWrapper::set_end_of_reach_,
	 &OneDReachSectionWrapper::default_set_end_of_reach)
    ;

  class_<OneDNetworkWrapper,
	 boost::noncopyable>("OneDNetwork",
			     init<const boost::property_tree::ptree&>())
    .def("append_structure",
	 &HyNDAL::OneDNetwork::append_structure,
	 &OneDNetworkWrapper::default_append_structure,
	 with_custodian_and_ward<1,3>())
    ;

  /*
  class_<HyNDAL::OneDNetwork>("OneDNetwork",
			      init<const boost::property_tree::ptree&>())
    //.def("append_structure", &HyNDAL::OneDNetwork::append_structure)
    //    .def("insert_structure", &OneDNetwork::insert_structure)
    //    .def("remove_structure", &OneDNetwork::remove_structure)
    .def("no_of_structures", &HyNDAL::OneDNetwork::no_of_structures)
    .def("no_of_connections", &HyNDAL::OneDNetwork::no_of_connections)
    //.def("get_name", &HyNDAL::OneDNetwork::get_name)
    .def("configuration", &HyNDAL::OneDNetwork::configuration)
    ;
  */
}
