// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Radu Serban
// =============================================================================
//
// Base class for segmented track shoes.
//
// =============================================================================

#ifndef CH_TRACK_SHOE_SEGMENTED_H
#define CH_TRACK_SHOE_SEGMENTED_H

#include "chrono_vehicle/ChApiVehicle.h"
#include "chrono_vehicle/ChSubsysDefs.h"

#include "chrono_vehicle/tracked_vehicle/ChTrackShoe.h"

namespace chrono {
namespace vehicle {

/// @addtogroup vehicle_tracked_shoe
/// @{

/// Base class for segmented track shoes.
/// These are track shoes modeled with one or more rigid bodies connected through joints and/or bushings.
class CH_VEHICLE_API ChTrackShoeSegmented : public ChTrackShoe {
  public:
    virtual ~ChTrackShoeSegmented() {}

    /// Get the contact material for the track shoe part interacting with the sprocket.
    std::shared_ptr<ChMaterialSurface> GetSprocketContactMaterial() const { return m_shoe_sprk_material; }

  protected:
    ChTrackShoeSegmented(const std::string& name);

    /// Create the contact materials for the shoe, consistent with the specified contact method. A derived class must
    /// set m_shoe_sprk_material (used for contact with the sprocket) and m_shoe_materials which must include one or more
    /// contact materials for the collision shapes of the shoe itself (for contact with the wheels, idler, and ground).
    virtual void CreateContactMaterials(ChContactMethod contact_method) = 0;

    /// Add contact geometry for the track shoe.
    /// Note that this is for contact with wheels, idler, and ground only.
    /// This contact geometry does not affect contact with the sprocket.
    /// The default implementation uses the given collision boxes and cylinders for the main track shoe body. 
    virtual void AddShoeContact();

    /// Add visualization assets for the track-shoe subsystem.
    /// This function uses the given visualization boxes and cylinders for the main track shoe body.
    void AddShoeVisualization();

    /// Definition of a box shape for collision or visualization.
    struct BoxShape {
        BoxShape(const ChVector<>& pos, const ChQuaternion<>& rot, const ChVector<>& dims, int matID = -1)
            : m_pos(pos), m_rot(rot), m_dims(dims), m_matID(matID) {}
        ChVector<> m_pos;
        ChQuaternion<> m_rot;
        ChVector<> m_dims;
        int m_matID;
    };

    /// Definition of a cylinder shape for collision or visualization.
    struct CylinderShape {
        CylinderShape(const ChVector<>& pos, const ChQuaternion<>& rot, double radius, double length, int matID = -1)
            : m_pos(pos), m_rot(rot), m_radius(radius), m_length(length), m_matID(matID) {}
        ChVector<> m_pos;
        ChQuaternion<> m_rot;
        double m_radius;
        double m_length;
        int m_matID;
    };

    std::vector<BoxShape> m_coll_boxes;                                ///< collision boxes on shoe body
    std::vector<CylinderShape> m_coll_cylinders;                       ///< collision cylinders on shoe body
    std::vector<std::shared_ptr<ChMaterialSurface>> m_shoe_materials;  ///< contact materials for shoe collision shapes
    std::shared_ptr<ChMaterialSurface> m_shoe_sprk_material;  ///< contact material for shoe shape contacting sprocket

    std::vector<BoxShape> m_vis_boxes;           ///< visualization boxes for shoe body
    std::vector<CylinderShape> m_vis_cylinders;  ///< visualization cylinders for shoe body
};

/// @} vehicle_tracked_shoe

}  // end namespace vehicle
}  // end namespace chrono

#endif
