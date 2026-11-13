#ifndef ULISSE_CTRL_COMMANDHALT_HPP
#define ULISSE_CTRL_COMMANDHALT_HPP

#include "ulisse_ctrl/commands/generic_command.hpp"

namespace ulisse {

namespace states {
class StateHalt;
}

namespace commands {

    class CommandHalt : public GenericCommand {

    private:
        std::shared_ptr<states::StateHalt> stateHalt_;

    public:
        CommandHalt();
        virtual ~CommandHalt() override;
        virtual fsm::retval Execute() override;

        void SetState(std::shared_ptr<states::GenericState> state) override;
    };
}
}
#endif // ULISSE_CTRL_COMMANDHALT_HPP
