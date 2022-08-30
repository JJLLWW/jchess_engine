#include <iostream>
#include <string>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "uci.hpp"

namespace uci {
    int uci_loop() {
        bool is_quit = false;
        while(!is_quit) {
            std::string line;
            std::getline(std::cin, line);
            try {
                Command cmd = parse_cmd(line);
                is_quit = Execute(cmd);
            } catch(UciException& e) {
                spdlog::warn(e.what());
            }
        }
        return 0;
    }
}