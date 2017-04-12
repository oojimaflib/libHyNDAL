/***********************************************************************
 * structure_definition_includes.hpp
 *
 * File to include ISIS Structure Definitions.
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

#ifndef ISIS_STRUCTURE_START
#define ISIS_STRUCTURE_START(NAME, ISIS_NAME)
#endif

#ifndef ISIS_STRUCTURE_END
#define ISIS_STRUCTURE_END
#endif

#ifndef ISIS_REACH_SECTION_START
#define ISIS_REACH_SECTION_START(NAME, ISIS_NAME)
#endif

#ifndef ISIS_REACH_SECTION_END
#define ISIS_REACH_SECTION_END
#endif

#ifndef ISIS_NEW_LINE
#define ISIS_NEW_LINE
#endif

#ifndef ISIS_NO_OF_DATA
#define ISIS_NO_OF_DATA(TABLE)
#endif

#ifndef ISIS_PROPERTY
#define ISIS_PROPERTY(TYPE, NAME, DEFAULT, DISPLAY_NAME, HELP_TEXT)
#endif

#ifndef ISIS_REACH_LENGTH
#define ISIS_REACH_LENGTH
#endif

#ifndef ISIS_DATA_TABLE
#define ISIS_DATA_TABLE(NAME, FORMAT)
#endif

#ifndef ISIS_END_DATA_TABLE
#define ISIS_END_DATA_TABLE(NAME)
#endif

#ifndef ISIS_TABLE_COLUMN
#define ISIS_TABLE_COLUMN(TYPE, NAME, COLUMN, TABLE)
#endif

#ifndef ISIS_KEYWORD
#define ISIS_KEYWORD(KEYWORD)
#endif

#ifndef ISIS_IF
#define ISIS_IF(CONDITION)
#endif

#ifndef ISIS_END_IF
#define ISIS_END_IF
#endif



#include "structure_definitions/ISISAbstraction.unit"
#include "structure_definitions/ISISBernoulliLoss.unit"
#include "structure_definitions/ISISBlockage.unit"
#include "structure_definitions/ISISQHBoundary.unit"
#include "structure_definitions/ISISHTBoundary.unit"
#include "structure_definitions/ISISQTBoundary.unit"
#include "structure_definitions/ISISTidalHarmonicsBoundary.unit"
#include "structure_definitions/ISISNCDBoundary.unit"
#include "structure_definitions/ISISArchBridge.unit"
#include "structure_definitions/ISISUSBPRBridge.unit"
#include "structure_definitions/ISISComment.unit"
#include "structure_definitions/ISISCircularConduit.unit"
#include "structure_definitions/ISISFullArchConduit.unit"
#include "structure_definitions/ISISSymmetricConduit.unit"
#include "structure_definitions/ISISRectangularConduit.unit"
#include "structure_definitions/ISISSprungArchConduit.unit"
#include "structure_definitions/ISISCulvertInlet.unit"
#include "structure_definitions/ISISCulvertOutlet.unit"
#include "structure_definitions/ISISCulvertBend.unit"
#include "structure_definitions/ISISFloodplainSection.unit"
#include "structure_definitions/ISISGeneralLoss.unit"
#include "structure_definitions/ISISFSSR16Boundary.unit"
#include "structure_definitions/ISISSCSBoundary.unit"
#include "structure_definitions/ISISFEHBoundary.unit"
#include "structure_definitions/ISISReFHBoundary.unit"
#include "structure_definitions/ISISReFHUrbanBoundary.unit"
#include "structure_definitions/ISISInterpolate.unit"
#include "structure_definitions/ISISOpenJunction.unit"
#include "structure_definitions/ISISEnergyJunction.unit"
#include "structure_definitions/ISISLateralInflow.unit"
#include "structure_definitions/ISISManhole.unit"
#include "structure_definitions/ISISOrifice.unit"
#include "structure_definitions/ISISOutfall.unit"
#include "structure_definitions/ISISFlap.unit"
#include "structure_definitions/ISISFlapOF.unit"
#include "structure_definitions/ISISPump.unit"
#include "structure_definitions/ISISRatingCurve.unit"
#include "structure_definitions/ISISReplicate.unit"
#include "structure_definitions/ISISReservoir.unit"
#include "structure_definitions/ISISReservoirOld.unit"
#include "structure_definitions/ISISRiverSection.unit"
#include "structure_definitions/ISISCESSection.unit"
#include "structure_definitions/ISISMuskinghamSection.unit"
#include "structure_definitions/ISISVPMCRouting.unit"
#include "structure_definitions/ISISVPMCSection.unit"
#include "structure_definitions/ISISVPMCRoutingSection.unit"
#include "structure_definitions/ISISRadialSluice.unit"
#include "structure_definitions/ISISVerticalSluice.unit"
#include "structure_definitions/ISISSpill.unit"
#include "structure_definitions/ISISCrumpWeir.unit"
#include "structure_definitions/ISISGatedWeir.unit"
#include "structure_definitions/ISISNotionalWeir.unit"
#include "structure_definitions/ISISFlatVWeir.unit"
#include "structure_definitions/ISISQHControlWeir.unit"
#include "structure_definitions/ISISBroadCrestedWeir.unit"
#include "structure_definitions/ISISLabyrinthWeir.unit"
#include "structure_definitions/ISISSharpCrestedWeir.unit"
#include "structure_definitions/ISISSyphonSpillway.unit"
#include "structure_definitions/ISISWeir.unit"

// Pseudo-structures (structures that can only occur after particular
// other structures in an ISIS model) Note that the "RULES" structure
// has now been incorporated into the units with which it is
// associated. This may eventually happen to the "GATE" structure too.

// Note that the definition of this structure _MUST_ occur after the
// definition of the gated weir structure or string matching routines
// will match the gated weir structure for this structure.
#include "structure_definitions/ISISSluiceGate.unit"


#undef ISIS_STRUCTURE_START
#undef ISIS_STRUCTURE_END
#undef ISIS_REACH_SECTION_START
#undef ISIS_REACH_SECTION_END
#undef ISIS_PROPERTY
#undef ISIS_DATA_TABLE
#undef ISIS_END_DATA_TABLE
#undef ISIS_TABLE_COLUMN
#undef ISIS_NEW_LINE
#undef ISIS_NO_OF_DATA
#undef ISIS_IF
#undef ISIS_END_IF
#undef ISIS_REACH_LENGTH
#undef ISIS_KEYWORD
