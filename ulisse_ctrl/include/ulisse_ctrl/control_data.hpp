#ifndef ULISSE_CTRL_CONTROL_DATA_HPP
#define ULISSE_CTRL_CONTROL_DATA_HPP

#include <ctrl_toolbox/DataStructs.h>

namespace ulisse {

struct ControlData {
    ctb::LatLong inertialF_linearPosition;
    rml::EulerRPY bodyF_angularPosition;
    Eigen::Vector3d bodyF_linearVelocity;
    Eigen::Vector3d bodyF_angularVelocity;
    Eigen::Vector2d inertialF_waterCurrent;
    bool radioControllerEnabled;

    ControlData() : radioControllerEnabled(false) {}
};

} // namespace ulisse

#endif // ULISSE_CTRL_CONTROL_DATA_HPP
