#include <set>
#include "uci.hpp"

namespace {
    std::string start_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
} // anonymous namespace

namespace uci {
    bool is_num(std::string s) {
        for(char c: s) {
            if(!isdigit((int)c)) return false;
        }
        return true;
    }

    bool validate_alg(std::string alg) {
        return false;
    }

    bool validate_long_alg(std::string lalg) {
        return false;
    }

    // if in algebraic notation do we also have to worry about captures?
    bool validate_square(std::string sq) {
        if(sq.size() != 2) return false;
        if(!isalpha((int)sq[0])) return false;
        if(!isdigit((int)sq[1])) return false;
        return true;
    }
    
    bool validate_fen_board(std::string board) {
        std::set<char> pieces = {
            'p', 'n', 'b', 'r', 'k', 'q',
            'P', 'N', 'B', 'R', 'K', 'Q',
        };
        int sz_rank = 0, nrank = 0;
        for(char c: board) {
            if(c == '/') {
                if(sz_rank != 8) return false;
                sz_rank = 0;
                nrank++;
            } else if(pieces.count(c) == 1) {
                sz_rank++;
            } else if(isdigit(c) && c != '0') {
                sz_rank += c - '0';
            } else {
                return false;
            }
        }
        nrank++;
        if(nrank != 8) return false;
        return true;
    }

    // see if words starting from index i form a valid FEN string.
    bool validate_fen(std::vector<std::string> words, int i) {
        std::set<std::string> castling = {"-", "K", "Q", "k", "q"};
        if(words.size() - i < 6) return false;
        if(!validate_fen_board(words[i])) return false;
        if(words[i+1] != "w" && words[i+1] != "b") return false;
        // wrong, may be between 1 and 4 characters.
        if(castling.count(words[i+2]) == 0) return false;
        if(!validate_square(words[i+3])) return false;
        if(!is_num(words[i+4]) || !is_num(words[i+5])) return false;
        return true;
    }

    std::string get_start_fen() {
        return start_fen;
    }
} // namespace uci