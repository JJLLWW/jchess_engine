#include <iostream>
#include <fmt/core.h>

#include "uci.hpp"

namespace uci {
    // assume all commands have been validated beforehand.
    bool Execute(Command& cmd) {
        switch(cmd.ctype) {
            case CmdType::UCI:
                ExecuteUCI();
                break;
            case CmdType::QUIT:
                return true;
            default:
                throw(fmt::format("UCI: Command Not Implemented '{}'", ToString(cmd.ctype)));
        }
        return false;
    }

    void ExecuteUCI() {
        std::cout << "id name jchess 0.0.0" << std::endl;
        std::cout << "id author Jack Wright" << std::endl;
        std::cout << std::endl;
        // for now no engine options.
        std::cout << "uciok" << std::endl;
    }
} // namespace uci