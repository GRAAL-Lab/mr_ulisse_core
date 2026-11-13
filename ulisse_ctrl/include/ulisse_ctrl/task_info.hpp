#ifndef ULISSE_CTRL_TASK_INFO_HPP
#define ULISSE_CTRL_TASK_INFO_HPP

#include <memory>
#include <rclcpp/publisher.hpp>
#include "ulisse_msgs/msg/task_status.hpp"

namespace tpik {
class Task;
}

namespace ulisse {

struct TasksInfo {

    std::shared_ptr<tpik::Task> task;
    rclcpp::Publisher<ulisse_msgs::msg::TaskStatus>::SharedPtr taskPub;
};

} // namespace ulisse

#endif // ULISSE_CTRL_TASK_INFO_HPP
