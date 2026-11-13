#include "ulisse_ctrl/controller_configuration.hpp"

#include <ctrl_toolbox/HelperFunctions.h>
#include <iostream>

namespace ulisse {

std::ostream& operator<<(std::ostream& os, DCLConfiguration const& a)
{
    os << "======= DCL CONF =======\n"
       << "ControlLoopRate: " << a.controlLoopRate << "\n"
       << "CtrlMode: " << static_cast<int>(a.ctrlMode) << "\n"
       << "EnableThrusters: " << a.enableThrusters << "\n"
       << "ThrusterPercLimit: " << a.thrusterPercLimit << "\n"
       << "----------------------\n"
       << a.ulisseModel
       << "----------------------\n";
    if (a.ctrlMode == ControlMode::ThrusterMapping) {
        os << a.thrusterMapping;
    } else if (a.ctrlMode == ControlMode::ClassicPIDControl) {
        os << a.classicPidControl;
    } else {
        os << a.computedTorqueControl;
    }

    os << "==============================\n";
    return os;
}

bool DCLConfiguration::ConfigureUlisseModel(libconfig::Config& confObj)
{

    if (!ulisseModel.LoadConfiguration(confObj))
        return false;

    return true;
}

bool DCLConfiguration::LoadConfiguration(libconfig::Config& confObj) noexcept(false)
{
    const libconfig::Setting& root = confObj.getRoot();

    // Load DCL Config
    if (!ctb::GetParam(confObj, controlLoopRate, "controlLoopRate"))
        return false;
    int tmpCtrlMode;
    if (!ctb::GetParam(confObj, tmpCtrlMode, "ctrlMode"))
        return false;
    ctrlMode = static_cast<ControlMode>(tmpCtrlMode);
    if (!ctb::GetParam(confObj, enableThrusters, "enableThrusters"))
        return false;
    if (!ctb::GetParam(confObj, thrusterPercLimit, "thrusterPercLimit"))
        return false;
    if (!ctb::GetParam(confObj, surgeMin, "surgeMin"))
        return false;
    if (!ctb::GetParam(confObj, surgeMax, "surgeMax"))
        return false;
    if (!ctb::GetParam(confObj, yawRateMin, "yawRateMin"))
        return false;
    if (!ctb::GetParam(confObj, yawRateMax, "yawRateMax"))
        return false;

    if (ctrlMode == ControlMode::ThrusterMapping) {
        const libconfig::Setting& thrusterMap = root["thrusterMapping"];
        if (!thrusterMapping.ConfigureFromFile(thrusterMap))
            return false;
        std::cerr << "ThrusterMapping configured" << std::endl;
    } else if (ctrlMode == ControlMode::ClassicPIDControl) {
        const libconfig::Setting& classicPidCtr = root["classicPidControl"];
        if (!classicPidControl.ConfigureFromFile(classicPidCtr))
            return false;
        std::cerr << "ClassicPIDControl configured" << std::endl;
    } else if (ctrlMode == ControlMode::ComputedTorque) {
        const libconfig::Setting& computedTorqueCtr = root["computedTorqueControl"];
        if (!computedTorqueControl.ConfigureFromFile(computedTorqueCtr))
            return false;

    } else {
        std::cerr << "Type of control not recognized" << std::endl;
    }

    return true;
}

bool DynamicPid::ConfigureFromFile(const libconfig::Setting& confObj) noexcept(false)
{
    const libconfig::Setting& pidSurge = confObj["pidSurge"];

    if (!ctb::GetParam(pidSurge, pidGainsSurge.Kd, "kd"))
        return false;
    if (!ctb::GetParam(pidSurge, pidGainsSurge.Kp, "kp"))
        return false;
    if (!ctb::GetParam(pidSurge, pidGainsSurge.Ki, "ki"))
        return false;
    if (!ctb::GetParam(pidSurge, pidGainsSurge.Kff, "kff"))
        return false;
    if (!ctb::GetParam(pidSurge, pidGainsSurge.N, "n"))
        return false;
    if (!ctb::GetParam(pidSurge, pidGainsSurge.Tr, "tr"))
        return false;
    if (!ctb::GetParam(pidSurge, pidSatSurge, "sat"))
        return false;

    const libconfig::Setting& pidYawRate = confObj["pidYawRate"];

    if (!ctb::GetParam(pidYawRate, pidGainsYawRate.Kd, "kd"))
        return false;
    if (!ctb::GetParam(pidYawRate, pidGainsYawRate.Kp, "kp"))
        return false;
    if (!ctb::GetParam(pidYawRate, pidGainsYawRate.Ki, "ki"))
        return false;
    if (!ctb::GetParam(pidYawRate, pidGainsYawRate.Kff, "kff"))
        return false;
    if (!ctb::GetParam(pidYawRate, pidGainsYawRate.N, "n"))
        return false;
    if (!ctb::GetParam(pidYawRate, pidGainsYawRate.Tr, "tr"))
        return false;
    if (!ctb::GetParam(pidYawRate, pidSatYawRate, "sat"))
        return false;

    return true;
}

std::ostream& operator<<(std::ostream& os, DynamicPid const& a)
{
    return os << "======= Classic Pid Control CONF =======\n"
              << "Pid Surge: "
              << "\n"
              << "Kd: " << a.pidGainsSurge.Kd << "\n"
              << "Kp: " << a.pidGainsSurge.Kp << "\n"
              << "Ki: " << a.pidGainsSurge.Ki << "\n"
              << "Kff: " << a.pidGainsSurge.Kff << "\n"
              << "N: " << a.pidGainsSurge.N << "\n"
              << "Tr: " << a.pidGainsSurge.Tr << "\n"
              << "Saturation: " << a.pidSatSurge << "\n"
              << "----------------------\n"
              << "Pid Yaw Rate: "
              << "\n"
              << "Kd: " << a.pidGainsYawRate.Kd << "\n"
              << "Kp: " << a.pidGainsYawRate.Kp << "\n"
              << "Ki: " << a.pidGainsYawRate.Ki << "\n"
              << "Kff: " << a.pidGainsYawRate.Kff << "\n"
              << "N: " << a.pidGainsYawRate.N << "\n"
              << "Tr: " << a.pidGainsYawRate.Tr << "\n"
              << "Saturation: " << a.pidSatYawRate << "\n"
              << "==============================\n";
}

bool ThrusterMapping::ConfigureFromFile(const libconfig::Setting& confObj) noexcept(false)
{
    const libconfig::Setting& pidSurge = confObj["pidSurge"];

    if (!ctb::GetParam(pidSurge, pidGainsSurge.Kd, "kd"))
        return false;
    if (!ctb::GetParam(pidSurge, pidGainsSurge.Kp, "kp"))
        return false;
    if (!ctb::GetParam(pidSurge, pidGainsSurge.Ki, "ki"))
        return false;
    if (!ctb::GetParam(pidSurge, pidGainsSurge.Kff, "kff"))
        return false;
    if (!ctb::GetParam(pidSurge, pidGainsSurge.N, "n"))
        return false;
    if (!ctb::GetParam(pidSurge, pidGainsSurge.Tr, "tr"))
        return false;
    if (!ctb::GetParam(pidSurge, pidSatSurge, "sat"))
        return false;

    return true;
}

std::ostream& operator<<(std::ostream& os, ThrusterMapping const& a)
{
    return os << "======= Thruster Mapping CONF =======\n"
              << "Pid Surge: "
              << "\n"
              << "Kd: " << a.pidGainsSurge.Kd << "\n"
              << "Kp: " << a.pidGainsSurge.Kp << "\n"
              << "Ki: " << a.pidGainsSurge.Ki << "\n"
              << "Kff: " << a.pidGainsSurge.Kff << "\n"
              << "N: " << a.pidGainsSurge.N << "\n"
              << "Tr: " << a.pidGainsSurge.Tr << "\n"
              << "Saturation: " << a.pidSatSurge << "\n"
              << "==============================\n";
}

bool KCLConfiguration::ConfigureFromFile(libconfig::Config& confObj)
{

    if (!ctb::GetParam(confObj, goToHoldAfterMove, "goToHoldAfterMove"))
        return false;
    if (!ctb::GetParam(confObj, controlLoopRate, "controlLoopRate"))
        return false;
    if (!ctb::GetParam(confObj, posAcceptanceRadius, "posAcceptanceRadius"))
        return false;
    if (!ctb::GetParamVector(confObj, saturationMax, "saturationMax"))
        return false;
    if (!ctb::GetParamVector(confObj, saturationMin, "saturationMin"))
        return false;
    //if (!ctb::GetParamVector(confObj, pathFollowMode, "pathFollowMode")) // ILOS or LOS
    //    return false;

    return true;
}

std::ostream& operator<<(std::ostream& os, KCLConfiguration const& a)
{
    return os << "======= KCL CONF =======\n"
              << "ControlLoopRate: " << a.controlLoopRate << "\n"
              << "PosAcceptanceRadius: " << a.posAcceptanceRadius << "\n"
              << "GoToHoldAfterMove: " << a.goToHoldAfterMove << "\n"
              << "SaturationMin: " << a.saturationMin.transpose() << "\n"
              << "SaturationMax: " << a.saturationMax.transpose() << "\n"
              << "===============================\n";
}

} // namespace ulisse
