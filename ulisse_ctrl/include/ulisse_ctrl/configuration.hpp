#ifndef ULISSE_CONFIGURATION_H
#define ULISSE_CONFIGURATION_H

#include "ulisse_ctrl/task_info.hpp"
#include <libconfig.h++>
#include <memory>
#include <string>
#include <unordered_map>

namespace tpik {
class ActionManager;
}
namespace ulisse {
namespace states {
class GenericState;
}
}

bool ConfigureTasksFromFile(std::unordered_map<std::string, ulisse::TasksInfo>& tasksMap, libconfig::Config& confObj);
bool ConfigurePriorityLevelsFromFile(std::shared_ptr<tpik::ActionManager> actionManager, std::unordered_map<std::string, ulisse::TasksInfo>& tasksMap, libconfig::Config& confObj);
bool ConfigureActionsFromFile(std::shared_ptr<tpik::ActionManager> actionManager, libconfig::Config& confObj);
bool ConfigureSatesFromFile(std::unordered_map<std::string, std::shared_ptr<ulisse::states::GenericState>> statesMap, libconfig::Config& confObj);
#endif // ULISSE_CONFIGURATION_H
