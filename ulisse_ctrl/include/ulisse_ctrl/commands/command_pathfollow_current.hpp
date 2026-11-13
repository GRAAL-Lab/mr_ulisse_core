#ifndef ULISSE_CTRL_COMMANDPATHFOLLOWCURRENT_HPP
#define ULISSE_CTRL_COMMANDPATHFOLLOWCURRENT_HPP

#include "ulisse_ctrl/commands/generic_command.hpp"

namespace ulisse {

namespace states {
class StatePathFollowCurrent;
}

namespace commands {

    class CommandPathFollowCurrent : public GenericCommand {

        std::shared_ptr<states::StatePathFollowCurrent> statePathFollowingCurrent_;

    public:
        CommandPathFollowCurrent();
        virtual ~CommandPathFollowCurrent() override;
        virtual fsm::retval Execute() override;

        void SetState(std::shared_ptr<states::GenericState> state) override;
    };
}
}
#endif // ULISSE_CTRL_COMMANDPATHFOLLOWCURRENT_HPP
