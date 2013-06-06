/***********************************************************************
 * ISISNetwork.cpp
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

#include "ISISNetwork.hpp"
#include "ISISDataTable.hpp"
#include "ISISStructures.hpp"

#include "../util/string_list.hpp"

#include <boost/algorithm/string.hpp>

#include <sstream>
#include <string>
#include <iomanip>

namespace HyNDAL {
  namespace ISIS {

    void ISISNetwork::
    add_default_initial_condition(const std::string& node_label)
    {
      // Special cases: no initial conditions for GATE or COMMENT units
      if (node_label == "COMMENT" || node_label == "") return;

      // Initial check: are there any initial conditions at all?
      if (initial_conditions_->no_of_rows() == 0) {
	initial_conditions_->append_row("             y     0.000     0.000     "
					"0.000     0.000     0.000     0.000");
	initial_conditions_->set_string(initial_conditions_->no_of_rows() - 1,
					0, node_label);
	return;
      }

      bool represented = false;
      for (size_t i = 0; i < initial_conditions_->no_of_rows(); i++) {
	if (initial_conditions_->get_string(i, 0) == node_label) {
	  represented = true;
	  break;
	}
      }

      if (!represented) {
	initial_conditions_->append_row(initial_conditions_->get_row(0));
	initial_conditions_->set_string(initial_conditions_->no_of_rows() - 1,
					0, node_label);
      }
    }

    void ISISNetwork::
    maybe_clear_initial_condition(const std::string& node_label)
    {
      bool present = false;
      for (size_t i = 0; i < structures().size(); i++) {
	ISISStructure* istruct
	  = dynamic_cast<ISISStructure*>(structures().at(i).second);
	for (size_t j = 0; j < istruct->no_of_node_labels(); j++) {
	  if (istruct->node_label(j) == node_label) {
	    present = true;
	    break;
	  }
	}
	if (present) break;
      }

      if (!present) {
	// Node label is no longer in the network. Find it in the initial
	// conditions and remove it.
	for (size_t i = 0; i < initial_conditions_->no_of_rows(); i++) {
	  if (initial_conditions_->get_string(i,0) == node_label) {
	    initial_conditions_->remove_row(i);
	    break;
	  }
	}
      }
    }

    ISISNetwork::ISISNetwork(const boost::property_tree::ptree& config) 
      : OneDNetwork(config)
    {
      metadata_ = config.get_child("metadata",
				   boost::property_tree::ptree());

      boost::property_tree::ptree ic_config
	= config.get_child("initial-conditions", boost::property_tree::ptree());

      if (ic_config == boost::property_tree::ptree()) {
	initial_conditions_ = new ISISDataTable("00000000000011222222222233333333334444444444555555555566666666667777777777", std::vector<std::string>());
      } else {
	initial_conditions_ = new ISISDataTable(ic_config);
      }

    }

    ISISNetwork::~ISISNetwork(void)
    {
      delete initial_conditions_;
    }

    void ISISNetwork::append_structure(const std::string& name,
				       HyNDAL::OneDStructure* structure)
    {
      // Check that the structure is an ISIS structure
      if (structure->type().find("ISIS") != 0)
	throw std::runtime_error("Can only add ISIS structures to ISIS network.");
      //std::cout << "Appending structure with type "
      //	    << structure->type() << std::endl;
      // Update the initial conditions table as needed
      ISISStructure* istruct = dynamic_cast<ISISStructure*>(structure);
  
      //std::cout << "Created ISISStructure object." << std::endl;
      for (size_t i = 0; i < istruct->no_of_node_labels(); i++) {
	std::string node_label
	  = boost::algorithm::trim_copy(istruct->node_label(i));
	add_default_initial_condition(node_label);
      }
  
      // Call the generic append_structure code for the rest of the work
      OneDNetwork::append_structure(name, structure);
    }

    /*
    bool ISISNetwork::remote_node_label(ISISStructure* istruct, size_t nl_no) {
      // TODO: Should return false when the node label in this position in
      // the structure connects to something real and true when it does
      // not (e.g. a remote label)
      return true;
    }

    bool ISISNetwork::upstream_node_label(ISISStructure* istruct, size_t nl_no) {
      // Should return true if the node label with index nl_no is an
      // upstream node wrt. the structure istruct. False otherwise.

      // Handle junctions and junction-like units
      if (istruct->type() == "ISIS JUNCTION|OPEN" or
	  istruct->type() == "ISIS JUNCTION|ENERGY" or
	  istruct->type() == "ISIS RESERVOIR #REVISION#1") {
    
      }

      // By and large, the first label is the upstream label
      if (nl_no == 0) return true;
      return false;
    }

    void ISISNetwork::generate_connections(void) {
      for (size_t i = 0; i < no_of_structures(); i++) {
	OneDStructure* ostruct = get_structure_ptr(i);
	ISISStructure* istruct = dynamic_cast<ISISStructure*>(ostruct);
	for (size_t j = 0; j < istruct->no_of_node_labels(); j++) {
	  std::string nl = boost::algorithm::trim_copy(istruct->node_label(i));

	  // Move on if the node label consists entirely of whitespace
	  if (nl.size() < 1) continue;
	  if (remote_node_label(istruct, j)) continue;

	  // See if the node label is already present in the connections
	  // list
	  bool found_it = false;
	  for (size_t k = 0; k < no_of_connections(); k++) {
	    if (nl == connection_label(k)) {
	      found_it = true;
	      if (connected_us(k)) {
		connection_set_ds(k, i);
	      } else {
		connection_set_us(k, i);
	      }
	      break;
	    }
	  }

	  if (!found_it) {
	    // It doesn't already exist, we need to take an (educated)
	    // guess as to whether this node label should be on the
	    // upstream or downstream end of the connection and connect
	    // it.
	    size_t k = append_connection(nl);
	    if (j == 0) {
	      connection_set_ds(k, i);
	    } else {
	      connection_set_us(k, i);
	    }
	  }
	}
      }

      // That should have constructed all of the connections in the model
      // We now need to backtrack through them and check that they are all
      // oriented correctly as, until we had constructed everything we did
      // not always have enough information to correctly assume
      // upstream/downstreamness of certain units.

      // We also need to check that the model is consistently connected
      // and that all the connections have both us and ds units
      for (size_t k = 0; k < no_of_connections(); k++) {
	if (not connected_ds(k))
	  throw;

	OneDStructure* odsstruct = connection_ds_structure(k);

	if (not connected_us(k)) {
	  if (odsstruct->is_reach_section()) {
	    // ISIS Reach sections have an implicit connection to the unit
	    // that precedes them in the data file (if they are not
	    // explicitly linked by node label)
	    size_t structure_no = connection_ds_structure_no(k);
	    if (structure_no == 0) throw;
	    connection_set_us(k, structure_no - 1);
	  } else {
	    throw;
	  }
	}
    
	if (odsstruct->is_reach_section()) {
	  OneDReachSection* odssect = dynamic_cast<OneDReachSection*>(odsstruct);
	  if (odssect->end_of_reach()) {
	    connection_swap_direction(k);
	  }
	}
    
	// OneDStructure* ousstruct = connection_us_structure(k);

      }
    }
    */

    void ISISNetwork::insert_structure(const size_t before,
				       const std::string& name,
				       HyNDAL::OneDStructure* structure)
    {
      // Note that we only have to overload the void ()(size_t,...)
      // version of this function as this version is called by all the
      // others
  
      if (structure->type().find("ISIS") != 0) 
	throw std::runtime_error("Can only add ISIS structures to ISIS network.");
  
      // Update the initial conditions table as needed
      ISISStructure* istruct = dynamic_cast<ISISStructure*>(structure);
      for (size_t i = 0; i < istruct->no_of_node_labels(); i++) {
	std::string node_label
	  = boost::algorithm::trim_copy(istruct->node_label(i));
	add_default_initial_condition(node_label);
      }

      OneDNetwork::insert_structure(before, name, structure);
    }

    void ISISNetwork::remove_structure(const size_t structure_no)
    {
      // Get the structure pointer (we are an ISISNetwork so we can
      // guarantee that it will be castable to an ISISStructure*)
      ISISStructure* istruct
	= dynamic_cast<ISISStructure*>(get_structure_ptr(structure_no));
      std::string primary_node_label = istruct->node_label();
  
      // Get the list of node labels for future reference
      std::vector<std::string> node_labels;
      for (size_t i = 0; i < istruct->no_of_node_labels(); i++) {
	node_labels.push_back(istruct->node_label(i));
      }

      OneDNetwork::remove_structure(structure_no);

      // If there are no more references to the node labels, clear their
      // initial condition
      for (size_t i = 0; i < node_labels.size(); i++) {
	maybe_clear_initial_condition(node_labels.at(i));
      }
    }

#define ISIS_STRUCTURE_START(NAME, ISIS_NAME)				\
    structname = ISIS_NAME;						\
    structname2 = "";							\
    barpos = structname.find('|');					\
    if (barpos != std::string::npos) {					\
      structname2 = structname.substr(barpos + 1);			\
      structname = structname.substr(0, barpos);			\
    }									\
    if (structure_started || line.find(structname) == 0) {		\
    std::string type = "ISIS-" ISIS_NAME;				\
    std::string comment_text = "";					\
    if (!structure_started && line.size() > structname.size() + 1) {	\
      config.put<std::string>("comment",				\
			      boost::algorithm::trim_copy(line.substr(structname.size() + 1))); \
    }									\
    if (!structure_started) std::getline(is, line);			\
    structure_started = true;						\
    if (structname2.size() > 0 && line.find(structname2) == 0) {	\
      std::getline(is,line);						\
      structname2 = "";							\
    }									\
    if (structname2 == "") {						\
    std::string structure_name = boost::algorithm::trim_copy(line);	\
    /* Special Case: Some structures have no node labels */		\
    if (structname != "COMMENT" && structname != "GATE") {		\
      std::vector<std::string> node_labels;				\
      while ( line.size() > 12 ) {					\
	node_labels.push_back(boost::algorithm::trim_copy(line.substr(0, 12))); \
	line = line.substr(12);						\
      }									\
      node_labels.push_back(boost::algorithm::trim_copy(line));		\
      config.put<std::string>("node-labels", list_to_string(node_labels)); \
      /* Special case: Some structures have nothing but node labels! */	\
      if (structname != "JUNCTION") std::getline(is, line);		\
      /* Special case: Reservoirs have two lines of node labels */	\
      if (structname == "RESERVOIR #REVISION#1") {			\
	boost::property_tree::ptree& extra =				\
	  config.put_child("extra", boost::property_tree::ptree());	\
	if ( line.size() >= 12 ) {					\
	  std::string lat = boost::algorithm::trim_copy(line.substr(0, 12)); \
	  line = line.substr(12);					\
	  extra.put<std::string>("lateral-1", lat);			\
	}								\
	if ( line.size() >= 12 ) {					\
	  std::string lat = boost::algorithm::trim_copy(line.substr(0, 12)); \
	  line = line.substr(12);					\
	  extra.put<std::string>("lateral-2", lat);			\
	}								\
	if ( line.size() >= 12 ) {					\
	  std::string lat = boost::algorithm::trim_copy(line.substr(0, 12)); \
	  line = line.substr(12);					\
	  extra.put<std::string>("lateral-3", lat);			\
	}								\
	if ( line.size() >= 12 ) {					\
	  std::string lat = boost::algorithm::trim_copy(line.substr(0, 12)); \
	  line = line.substr(12);					\
	  extra.put<std::string>("lateral-4", lat);			\
	}								\
	std::getline(is, line);						\
      }									\
    } else {								\
      std::ostringstream oss("COMMENT ");				\
      oss << no_of_structures();					\
      structure_name = oss.str();					\
      config.put<std::string>("node-labels", "COMMENT");		\
    }

#define ISIS_STRUCTURE_END						\
    this->append_structure(structure_name, make_structure(type, config)); \
    continue;								\
  }									\
  } // End of if from ISIS_STRUCTURE_START

#define ISIS_REACH_SECTION_START(NAME, ISIS_NAME)			\
    structname = ISIS_NAME;						\
    structname2 = "";							\
    barpos = structname.find('|');					\
    if (barpos != std::string::npos) {					\
      structname2 = structname.substr(barpos + 1);			\
      structname = structname.substr(0, barpos);			\
    }									\
    if (structure_started || line.find(structname) == 0) {		\
    std::string type = "ISIS-" ISIS_NAME;				\
    std::string comment_text = "";					\
    if (!structure_started && line.size() > structname.size() + 1) {	\
      config.put<std::string>("comment",				\
			      boost::algorithm::trim_copy(line.substr(structname.size() + 1))); \
    }									\
    if (!structure_started) std::getline(is, line);			\
    structure_started = true;						\
    if (structname2.size() > 0 && line.find(structname2) == 0) {	\
      std::getline(is,line);						\
      structname2 = "";							\
    }									\
    if (structname2 == "") {						\
    std::string structure_name = boost::algorithm::trim_copy(line);	\
    std::vector<std::string> node_labels;				\
    while ( line.size() > 12 ) {					\
      node_labels.push_back(boost::algorithm::trim_copy(line.substr(0, 12))); \
      line = line.substr(12);						\
    }									\
    node_labels.push_back(boost::algorithm::trim_copy(line));		\
    config.put<std::string>("node-labels", list_to_string(node_labels)); \
    std::getline(is, line);

#define ISIS_REACH_SECTION_END						\
    this->append_structure(structure_name, make_structure(type, config)); \
    continue;								\
  }									\
  } // End of if from ISIS_REACH_SECTION_START

#define ISIS_NEW_LINE				\
    std::getline(is,line);
  
#define ISIS_NO_OF_DATA(TABLE)						\
    size_t TABLE##_ndat = 0;						\
    if (line.size() < 10) {						\
      TABLE##_ndat = atol(boost::algorithm::trim_copy(line).c_str());	\
      line = "";							\
    } else {								\
      TABLE##_ndat = atol(boost::algorithm::trim_copy(line.substr(0, 10)).c_str()); \
      line = line.substr(10);						\
    }

#define ISIS_PROPERTY(TYPE, NAME, DEFAULT)			\
    std::string NAME;						\
    if (line.size() < 10) {					\
      NAME = boost::algorithm::trim_copy(line);			\
      line = "";						\
    } else {							\
      NAME = boost::algorithm::trim_copy(line.substr(0, 10));	\
      line = line.substr(10);					\
    }								\
    config.put(#NAME, NAME);

#define ISIS_REACH_LENGTH					\
    std::string dx;						\
    if (line.size() < 10) {					\
      dx = boost::algorithm::trim_copy(line);			\
      line = "";						\
    } else {							\
      dx = boost::algorithm::trim_copy(line.substr(0, 10));	\
      line = line.substr(10);					\
    }								\
    config.put("length", dx);
  

#define ISIS_DATA_TABLE(NAME, FORMAT)					\
    ISISDataTable NAME(FORMAT);						\
    NAME.read_raw(is, NAME##_ndat);					\
    boost::property_tree::ptree NAME##_config = NAME.configuration();	\
    config.put_child(#NAME, NAME##_config);

#define ISIS_TABLE_COLUMN(TYPE, NAME, COLUMN, TABLE)

#define ISIS_IF(CONDITION)			\
    if (CONDITION) {

#define ISIS_END_IF				\
    }
  
    void ISISNetwork::add_dat_structures(std::istream& is)
    {
      size_t initial_nodes = initial_conditions_->no_of_rows();

      // Read in the general block from the top of the file
      std::string line;
      
      std::getline(is, line);
      metadata_.put<std::string>("title", boost::algorithm::trim_copy(line));

      std::getline(is, line);
      // This line should contain the keyword "#REVISION#1"

      std::getline(is, line);
      /*
	metadata_->set_long_int("no of nodes",
	atol(line.substr(0,10).c_str()));
      */
      size_t no_of_nodes = atol(line.substr(0,10).c_str());
      metadata_.put<double>("lower-Fr-transition",
			    atof(line.substr(10,10).c_str()));
      metadata_.put<double>("upper-Fr-transition",
			    atof(line.substr(20,10).c_str()));
      metadata_.put<double>("minimum-depth", atof(line.substr(30,10).c_str()));
      metadata_.put<double>("direct-method-tolerance",
			    atof(line.substr(40,10).c_str()));

      std::getline(is, line);
      metadata_.put<double>("temperature", atof(line.substr(0,10).c_str()));
      metadata_.put<double>("head-tolerance", atof(line.substr(10,10).c_str()));
      metadata_.put<double>("flow-tolerance", atof(line.substr(20,10).c_str()));
      metadata_.put<double>("mathematical-damping",
			    atof(line.substr(30,10).c_str()));
      metadata_.put<double>("pivotal-choice-parameter",
			    atof(line.substr(40,10).c_str()));
      metadata_.put<double>("under-relaxation",
			    atof(line.substr(50,10).c_str()));
      metadata_.put<double>("matrix-dummy-coefficient",
			    atof(line.substr(60,10).c_str()));

      std::getline(is, line);
      // This line should contain the keyword "RAD FILE"

      std::getline(is, line);
      metadata_.put<std::string>("roughness-file",
				 boost::algorithm::trim_copy(line));

      std::getline(is, line);
      // This line should contain the keyword "END GENERAL"

      // Read in the structures
      add_structures(is);

      /*
      if (initial_conditions_->no_of_rows() != no_of_nodes - initial_nodes) {
	PRINT(5) << "Number of node labels added does not"
	  " match number claimed in .DAT file." << std::endl;
      }
      */

      // Read in the initial conditions table
      // TODO

    }

    void ISISNetwork::add_structures(std::istream& is)
    {
      while (is) {
	std::string line;
	std::getline(is, line);

	if (line.find("INITIAL CONDITIONS") == 0) break;

	std::string structname;
	std::string structname2;
	size_t barpos;

	// Boolean to allow some bits of structure reading to be skipped
	// if we have already processed the first line as part of an
	// earlier structure. This occurs when we have different
	// structures that have the same first line in the DAT file.
	bool structure_started = false;

	boost::property_tree::ptree config;

#include "structure_definitions.hpp"

      }
    }

#define ISIS_STRUCTURE_START(NAME, ISIS_NAME)				\
    if (structure->type() == "ISIS-" ISIS_NAME) {			\
      NAME* istruct = dynamic_cast<NAME*>(structure);			\
    std::string comment = istruct->comment();				\
    std::string structname = ISIS_NAME;					\
    std::string structname2 = "";					\
    size_t barpos = structname.find('|');				\
    if (barpos != std::string::npos) {					\
      structname2 = structname.substr(barpos + 1);			\
      structname = structname.substr(0, barpos);			\
    }									\
    os << structname << " " << comment << std::endl;			\
    if (structname2 != "") os << structname2 << std::endl;		\
    if (structname != "COMMENT" && structname != "GATE") {		\
      for (size_t i = 0; i < istruct->no_of_node_labels(); i++) {	\
	os << std::setw(12) << std::left << istruct->node_label(i);	\
      }									\
      if (structname != "JUNCTION") os << std::endl;			\
      if (structname == "RESERVOIR #REVISION#1") {			\
	os << std::setw(12) << std::left				\
	   << istruct->extra_data().get<std::string>("lateral-1","");	\
	os << std::setw(12) << std::left				\
	   << istruct->extra_data().get<std::string>("lateral-2","");	\
	os << std::setw(12) << std::left				\
	   << istruct->extra_data().get<std::string>("lateral-3","");	\
	os << std::setw(12) << std::left				\
	   << istruct->extra_data().get<std::string>("lateral-4","");	\
	os << std::endl;						\
      }									\
    }

#define ISIS_REACH_SECTION_START(NAME, ISIS_NAME)			\
    if (structure->type() == "ISIS-" ISIS_NAME) {			\
    NAME* istruct = dynamic_cast<NAME*>(structure);			\
    std::string comment = istruct->comment();				\
    std::string structname = ISIS_NAME;					\
    std::string structname2 = "";					\
    size_t barpos = structname.find('|');				\
    if (barpos != std::string::npos) {					\
      structname2 = structname.substr(barpos + 1);			\
      structname = structname.substr(0, barpos);			\
    }									\
    os << structname << " " << comment << std::endl;			\
    if (structname2 != "") os << structname2 << std::endl;		\
    for (size_t i = 0; i < istruct->no_of_node_labels(); i++) {		\
      os << std::setw(12) << std::left << istruct->node_label(i);	\
    }									\
    os << std::endl;

#define ISIS_STRUCTURE_END			\
    os << std::endl;				\
  }

#define ISIS_REACH_SECTION_END			\
    os << std::endl;				\
  }

#define ISIS_NEW_LINE				\
    os << std::endl;

#define ISIS_NO_OF_DATA(TABLE)						\
    os << std::setw(10) << std::right << istruct->TABLE().no_of_rows();

#define ISIS_PROPERTY(TYPE, NAME, DEFAULT)				\
    TYPE NAME = istruct->NAME();					\
    os << std::setw(10)							\
    << (std::string(#TYPE) == "string" ? std::left : std::right)	\
    << std::fixed << std::setprecision(3)				\
    << NAME;

#define ISIS_KEYWORD(KEYWORD)			\
    os << KEYWORD;

#define ISIS_REACH_LENGTH			\
    os << std::setw(10)				\
    << std::right				\
    << istruct->length();

#define ISIS_DATA_TABLE(NAME, FORMAT)		\
    if (istruct->NAME().no_of_rows() > 0) {	\
      os << std::endl;				\
      istruct->NAME().write_raw(os);		\
    }

#define ISIS_TABLE_COLUMN(TYPE, NAME, COLUMN, TABLE)

#define ISIS_IF(CONDITION)			\
    if (CONDITION) {

#define ISIS_END_IF				\
    }
  
    void ISISNetwork::write_dat_structures(std::ostream& os)
    {
      os << metadata_.get<std::string>("title", "") << std::endl
	 << "#REVISION#1" << std::endl
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << initial_conditions_->no_of_rows()
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << metadata_.get<double>("lower-Fr-transition", 0.7)
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << metadata_.get<double>("upper-Fr-transition", 0.9)
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << metadata_.get<double>("minimum-depth", 0.001)
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << metadata_.get<double>("direct-method-tolerance", 0.1)
	// This parameter is undocumented but it almost certainly refers
	// to the number of characters used for a single node label. We
	// only support 12.
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << 12 << std::endl
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << metadata_.get<double>("temperature", 10)
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << metadata_.get<double>("head-tolerance", 0.1)
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << metadata_.get<double>("flow-tolerance", 0.1)
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << metadata_.get<double>("mathematical-damping", 0.7)
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << metadata_.get<double>("pivotal-choice-parameter", 1.0)
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << metadata_.get<double>("under-relaxation", 0.7)
	 << std::setw(10) << std::fixed << std::setprecision(3)
	 << metadata_.get<double>("matrix-dummy-coefficient", 0.0) << std::endl
	 << "RAD FILE" << std::endl
	 << metadata_.get<std::string>("roughness-file", "") << std::endl
	 << "END GENERAL" << std::endl;
 
      write_structures(os);

      os << "INITIAL CONDITIONS" << std::endl
	 << " label   ?      flow     stage froude no"
	 <<"  velocity     umode    ustate         z" << std::endl;

      initial_conditions_->write_raw(os);
      os << std::endl;
    }

    void ISISNetwork::write_structures(std::ostream& os)
    {
      std::vector< std::pair<std::string, OneDStructure*> >::iterator it;
      for (it = this->structures().begin(); it != this->structures().end(); it++) {
    
	OneDStructure* structure = it->second;

#include "structure_definitions.hpp"
    
      }
    }

    boost::property_tree::ptree ISISNetwork::configuration(void) {
      boost::property_tree::ptree config = HyNDAL::OneDNetwork::configuration();
      config.put_child("metadata", metadata_);
      boost::property_tree::ptree icconfig
	= initial_conditions_->configuration();
      config.put_child("initial-conditions", icconfig);
      return config;
    }

  };
};
