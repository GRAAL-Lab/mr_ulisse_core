#ifndef ULISSE_CTRL_COMMANDPATHFOLLOW_ALOS_HPP
#define ULISSE_CTRL_COMMANDPATHFOLLOW_ALOS_HPP

#include "ulisse_ctrl/commands/generic_command.hpp"

namespace ulisse {

namespace states {
class StatePathFollowALOS;
}

namespace commands {

    class CommandPathFollowALOS : public GenericCommand {

        std::shared_ptr<states::StatePathFollowALOS> statePathFollowingALOS_;

    public:
        CommandPathFollowALOS();
        virtual ~CommandPathFollowALOS() override;
        virtual fsm::retval Execute() override;

        void SetState(std::shared_ptr<states::GenericState> state) override;
    };
}
}
#endif // ULISSE_CTRL_COMMANDPATHFOLLOW_ALOS_HPP
