#include "uci.hpp"

namespace {
    
} // anonymous namespace

namespace uci {
    std::string start_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    bool validate_alg(std::string alg) {
        return false;
    }

    bool validate_long_alg(std::string lalg) {
        return false;
    }
    
    // see if words starting from index istart form a valid FEN string.
    bool validate_fen(std::vector<std::string> words, int istart) {
        if(words.size() - istart < 6) {
            return false;
        }

    }
} // namespace uci