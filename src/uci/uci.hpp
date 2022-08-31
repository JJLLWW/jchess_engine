#pragma once

#include <exception>
#include <string>
#include <vector>
#include <cstdint>

namespace uci {
    class UciException : public std::exception {
        private:
            std::string msg;
        public:
            UciException(std::string MSG) : msg{MSG} {}
            std::string what() { return msg; }
    };

    enum class CmdType {
        UCI,
        DEBUG,
        ISREADY,
        SETOPTION,
        REGISTER,
        UCINEWGAME,
        POSITION,
        GO,
        STOP,
        PONDERHIT,
        QUIT,
    };

    struct PosData {
        std::string fen;
        std::vector<std::string> moves;
    };

    struct DebugData {
        bool debug_on;
    };

    struct RegisterData {
        bool later;
        std::string name;
        int64_t code;
    };

    class Command {
        public:
            PosData posdata;
            DebugData dbgdata;
            RegisterData regdata;
            // go command specific
            CmdType ctype;
            Command(CmdType type) : ctype{type} {}
            Command(PosData pd) : posdata{pd}, ctype{CmdType::POSITION} {}
            Command(DebugData dd) : dbgdata{dd}, ctype(CmdType::DEBUG) {}
            Command(RegisterData rd) : regdata{rd}, ctype{CmdType::REGISTER} {}
    };

    int uci_loop();
    void validate_cmd(std::vector<std::string> words);
    Command parse_cmd(const std::string& cmd);
    std::vector<std::string> get_words(std::string& str);
    std::string ToString(CmdType type);
    CmdType ToCmd(std::string str);

    bool Execute(Command& cmd);
    void ExecuteUCI();

    std::string get_start_fen();
    bool validate_fen(std::vector<std::string> words, int i);
} // namespace uci