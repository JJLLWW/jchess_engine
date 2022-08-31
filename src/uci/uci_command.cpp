#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fmt/core.h>

#include "uci.hpp"

namespace {
    // TODO: cleanup duplication
    std::unordered_set<std::string> valid_cmds = {
        "uci",
        "debug",
        "isready",
        "setoption",
        "register",
        "ucinewgame",
        "position",
        "go",
        "stop",
        "ponderhit",
        "quit"
    };
    std::unordered_map<std::string, uci::CmdType> to_cmd {
        {"uci", uci::CmdType::UCI},
        {"debug", uci::CmdType::DEBUG},
        {"isready", uci::CmdType::ISREADY},
        {"setoption", uci::CmdType::SETOPTION},
        {"register", uci::CmdType::REGISTER},
        {"ucinewgame", uci::CmdType::UCINEWGAME},
        {"position", uci::CmdType::POSITION},
        {"go", uci::CmdType::GO},
        {"stop", uci::CmdType::STOP},
        {"ponderhit", uci::CmdType::PONDERHIT},
        {"quit", uci::CmdType::QUIT}
    };
    std::unordered_map<uci::CmdType, std::string> to_string {
        {uci::CmdType::UCI, "uci"},
        {uci::CmdType::DEBUG, "debug"},
        {uci::CmdType::ISREADY, "isready"},
        {uci::CmdType::SETOPTION, "setoption"},
        {uci::CmdType::REGISTER, "register"},
        {uci::CmdType::UCINEWGAME, "ucinewgame"},
        {uci::CmdType::POSITION, "position"},
        {uci::CmdType::GO, "go"},
        {uci::CmdType::STOP, "stop"},
        {uci::CmdType::PONDERHIT, "ponderhit"},
        {uci::CmdType::QUIT, "quit"}
    };
} // namespace

namespace uci {
    // RVO
    std::vector<std::string> get_words(const std::string& str) {
        std::string word;
        std::vector<std::string> words;
        std::istringstream iss(str);
        while(iss >> word) {
            words.push_back(word);
        }
        return words;
    }

    void validate_cmd(std::vector<std::string> words) {
        if(words.empty()) throw UciException("UCI: Empty Command\n");
        if(valid_cmds.count(words[0]) == 0) {
            std::string msg = fmt::format("UCI: Invalid Command Name '{}'\n", words[0]);
            throw UciException(msg);
        }
        // validate the commands arguments make sense.
        if(words[0] == "debug") {
            if(words.size() != 2) {
                std::string msg = fmt::format("UCI: debug expects 1 argument, recieved {}\n", words.size() - 1);
                throw UciException(msg);
            }
            if(words[1] != "on" && words[1] != "off") {
                std::string msg = fmt::format("UCI: debug expects 'on' or 'off', recieved {}\n", words[1]);
                throw UciException(msg);
            }
        }
        // TODO: setoption, position, go. 
    }

    PosData parse_pos(std::vector<std::string>& words) {
        PosData pd;
        if(words.size() == 1) {
            throw UciException("UCI: position called with no argument (expects 'startpos' or a FEN string)");
        }
        if(words[1] == "startpos") {
            pd.fen = get_start_fen();
            return pd;
        }
        if(!validate_fen(words, 1)) {
            throw UciException("UCI: position FEN string is invalid.");
        }
        // store the FEN in the PosData.
        // see if any 'moves' have been specified and validate them.
        return pd;
    }

    Command parse_cmd(const std::string& str) {
        std::vector<std::string> words = get_words(str);
        validate_cmd(words);
        CmdType ctype = ToCmd(words[0]);
        PosData pd;
        switch(ctype) {
            case CmdType::POSITION:
                pd = parse_pos(words);
                return Command(pd);
            default:
                return Command(ctype);
        }
    }

    std::string ToString(CmdType type) {
        return to_string[type];
    }

    CmdType ToCmd(std::string str) {
        if(valid_cmds.count(str) == 0) {
            std::string msg = fmt::format("UCI: Invalid Command Name '{}'\n", str);
            throw UciException(msg);
        }
        return to_cmd[str];
    }
} // namespace uci