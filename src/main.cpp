#include <iostream>
#include <exception>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "uci/uci.hpp"

bool set_logger() {
    try {
        // TODO: clear log if already exists.
        auto file_logger = spdlog::basic_logger_mt("file_logger", "jengine_log.txt");
        spdlog::set_default_logger(file_logger);
        spdlog::flush_on(spdlog::level::info);
    } catch(spdlog::spdlog_ex& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

int main() {
    if(!set_logger()) {
        return 1;
    }
    uci::uci_loop();
}