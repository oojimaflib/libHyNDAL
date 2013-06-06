/***********************************************************************
 * OneDReachSection.hpp
 *
 * Represents a OneDStructure that can only exist as part of a
 * reach. It has a length (distance to the next section in the reach)
 * and a flag indicating whether it is at the end of the reach.
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

#ifndef OneDReachSection_hpp
#define OneDReachSection_hpp

#include "OneDStructure.hpp"

namespace HyNDAL {

  class OneDReachSection : public OneDStructure {
  private:

    double length_;

    bool end_of_reach_;

  public:

    OneDReachSection(const boost::property_tree::ptree& config
		     = boost::property_tree::ptree());

    virtual ~OneDReachSection(void) {}

    virtual bool is_reach_section(void) { return true; }

    virtual double& length(void) { return length_; }

    virtual bool& end_of_reach(void) { return end_of_reach_; }

    virtual boost::property_tree::ptree configuration(void);
  
  };

}; // End namespace HyNDAL

#endif
