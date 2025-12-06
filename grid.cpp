#include <string>
#include <vector>
#include <iostream>

//#include "utils.cpp"
// mutiple includes

namespace aoc {

class grid {

public:
    void append_line(std::string &line) {
        array.push_back(line);
    }
    
    int higth() const {return array.size();}
    int with() const {return array.at(0).length();}

    void print() {
        for (int i{0}; i < higth(); ++i) {
            std::cout << array.at(i) << std::endl;
        }
    }

    bool inside(int x, int y) const {

        if (x < 0 || y < 0 || x >= with() || y >= higth()) {
            return false;
        }

        return true;
    }

    bool set(int x, int y, char c) {
        if (!inside(x,y)){
            return false;
        }
        array.at(y).at(x) = c;
        return true;
    }

    char at(int x,int y) const {return array.at(y).at(x); }

    bool find(char cmp, std::function< void( int, int ) >&& f) const {
        bool found{false};
        for (int y{0}; y < higth(); ++y) {
            for (int x{0}; x < with(); ++x) {
                if (at(x,y) == cmp) {
                    f(x,y);
                    found = true;
                }
            }
        }
        return found;
    }

    void for_node_neighbour(int x, int y, bool diag, std::function< void( char, int, int ) >&& f) const {
        
        for (int dx{-1}; dx <= 1; ++dx) {
            for (int dy{-1}; dy <= 1; ++dy) {

                if (dx == 0 && dy == 0) {
                    continue;
                }
                if (!diag && (dx != 0 && dy != 0)) {
                    continue;
                }

                int new_x = x + dx;
                int new_y = y + dy;
                if(inside(new_x, new_y)) {
                    f(at( new_x, new_y), new_x, new_y);
                }
            }
        }
    }

    void for_node_neighbour(int x, int y, bool diag, char cmp, std::function< void( int, int ) >&& f) const {
        for_node_neighbour(x, y, diag, [&](char c, int nx, int ny) {
            if (c == cmp) {
                f(nx, ny);
            }
        });
    }


private:
    std::vector<std::string> array;
};

}