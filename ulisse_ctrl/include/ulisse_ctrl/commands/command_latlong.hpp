#ifndef ULISSE_CTRL_COMMANDMOVE_HPP
#define ULISSE_CTRL_COMMANDMOVE_HPP

#include "ulisse_ctrl/commands/generic_command.hpp"

namespace ctb {
struct LatLong;
}

namespace ulisse {

namespace states {
class StateLatLong;
}

namespace commands {

    class CommandLatLong : public GenericCommand {

    protected:
        std::shared_ptr<states::StateLatLong> stateLatLong_;

    public:
        CommandLatLong();
        virtual ~CommandLatLong() override;
        virtual fsm::retval Execute(void) override;
        bool SetGoTo(ctb::LatLong goalPosition, double acceptanceRadius);

        void SetState(std::shared_ptr<states::GenericState> state) override;
    };
}
}
#endif // ULISSE_CTRL_COMMANDMOVE_HPP
