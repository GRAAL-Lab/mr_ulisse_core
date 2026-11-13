#ifndef ULISSE_CTRL_GENERICCOMMAND_HPP
#define ULISSE_CTRL_GENERICCOMMAND_HPP

#include "ulisse_ctrl/ulisse_defines.hpp"
#include <fsm/fsm.h>
#include <memory>

namespace ulisse {

namespace states {
class GenericState;
}

namespace commands {

    class GenericCommand : public fsm::BaseCommand {

    public:
        GenericCommand();
        virtual ~GenericCommand();

        virtual void SetState(std::shared_ptr<states::GenericState> state) = 0;
    };
}
}
#endif // ULISSE_CTRL_GENERICCOMMAND_HPP
