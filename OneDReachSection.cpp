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

#include "OneDReachSection.hpp"

namespace HyNDAL {

  OneDReachSection::OneDReachSection(const boost::property_tree::ptree& config)
    : OneDStructure(config),
      length_(config.get<double>("length", 0.0)),
      end_of_reach_(config.get<bool>("end-of-reach", false))
  {
  }

  boost::property_tree::ptree OneDReachSection::configuration(void)
  {
    boost::property_tree::ptree config = OneDStructure::configuration();
    config.put("is-reach-section", true);
    config.put("length", length_);
    config.put("end-of-reach", end_of_reach_);
    return config;
  }

};
