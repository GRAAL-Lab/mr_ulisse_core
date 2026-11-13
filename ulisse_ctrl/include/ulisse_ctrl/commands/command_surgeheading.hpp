#ifndef ULISSE_CTRL_COMMANDSURGEHEADING_HPP
#define ULISSE_CTRL_COMMANDSURGEHEADING_HPP

#include "ulisse_ctrl/commands/generic_command.hpp"

namespace ulisse {

namespace states {
class StateSurgeHeading;
}

namespace commands {

    class CommandSurgeHeading : public GenericCommand {

        std::shared_ptr<states::StateSurgeHeading> stateSurgeHeading_;

    public:
        CommandSurgeHeading();
        virtual ~CommandSurgeHeading() override;
        virtual fsm::retval Execute(void) override;
        void SetTimeout(uint timeout_sec);

        void SetState(std::shared_ptr<states::GenericState> state) override;
    };
}
}
#endif // ULISSE_CTRL_COMMANDSURGEHEADING_HPP
