#ifndef ULISSE_CTRL_COMMANDHOLD_HPP
#define ULISSE_CTRL_COMMANDHOLD_HPP

#include "ulisse_ctrl/commands/generic_command.hpp"

namespace ctb {
struct LatLong;
}

namespace ulisse {

namespace states {
class StateHold;
}

namespace commands {

    class CommandHold : public GenericCommand {

        std::shared_ptr<states::StateHold> stateHold_;

    public:
        CommandHold();
        virtual ~CommandHold() override;
        virtual fsm::retval Execute(void) override;

        void SetState(std::shared_ptr<states::GenericState> state) override;

        //void SetWaterCurrent(const std::shared_ptr<Eigen::Vector2d>& inertialF_waterCurrent);

        void SetPositionToHold(const ctb::LatLong& p);
    };
}
}
#endif // ULISSE_CTRL_COMMANDHOLD_HPP
