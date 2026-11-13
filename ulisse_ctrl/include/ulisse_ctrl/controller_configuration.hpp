#ifndef ULISSE_CTRL_CONTROLLER_CONFIGURATION_HPP
#define ULISSE_CTRL_CONTROLLER_CONFIGURATION_HPP

#include <ctrl_toolbox/DataStructs.h>
#include <iosfwd>
#include <libconfig.h++>
#include "surface_vehicle_model/surfacevehiclemodel.hpp"

namespace ulisse {

enum class ControlMode : int {
    ThrusterMapping,
    ClassicPIDControl,
    ComputedTorque
};

struct KCLConfiguration {

    bool goToHoldAfterMove;
    double posAcceptanceRadius;
    double controlLoopRate;
    Eigen::VectorXd saturationMin, saturationMax;
    int pathFollowMode; // ILOS or LOS

    KCLConfiguration()
        : goToHoldAfterMove(false)
    {
    }

    bool ConfigureFromFile(libconfig::Config& confObj);

    friend std::ostream& operator<<(std::ostream& os, KCLConfiguration const& a);
};

struct ThrusterMapping {
    ctb::PIDGains pidGainsSurge;
    double pidSatSurge;

    bool ConfigureFromFile(const libconfig::Setting& confObj) noexcept(false);

    friend std::ostream& operator<<(std::ostream& os, ThrusterMapping const& a);
};

struct DynamicPid {
    ctb::PIDGains pidGainsSurge;
    double pidSatSurge;
    ctb::PIDGains pidGainsYawRate;
    double pidSatYawRate;

    bool ConfigureFromFile(const libconfig::Setting& confObj) noexcept(false);

    friend std::ostream& operator<<(std::ostream& os, DynamicPid const& a);
};

struct DCLConfiguration {

    double controlLoopRate;
    bool enableThrusters;
    double thrusterPercLimit;
    ControlMode ctrlMode;
    double surgeMin, surgeMax;
    double yawRateMin, yawRateMax;

    SurfaceVehicleModelParameters ulisseModel;
    ThrusterMapping thrusterMapping;
    DynamicPid classicPidControl;
    DynamicPid computedTorqueControl;

    friend std::ostream& operator<<(std::ostream& os, DCLConfiguration const& a);

    bool ConfigureUlisseModel(libconfig::Config& confObj);

    bool LoadConfiguration(libconfig::Config& confObj) noexcept(false);
};

} // namespace ulisse

#endif // ULISSE_CTRL_CONTROLLER_CONFIGURATION_HPP
