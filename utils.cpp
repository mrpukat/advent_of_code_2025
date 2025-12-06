#include <string>
#include <vector>

namespace aoc {

    using ull = unsigned long long;
    using ll = long long;

    void for_lines_in_file(std::string &&file, 
                            std::function< bool(const std::string& )>&& comp, 
                            std::function< void(std::vector<std::string>&& ) >&& f) {
    	std::string line;
        std::ifstream file_in;
        file_in.open (file, std::ifstream::in);

        if (file_in.is_open()) {
            std::vector<std::string> lines;
    		while(getline(file_in, line)) {
                if (!comp(line)) {
                    lines.push_back(line);
                }
                else {
                    lines.push_back(line);
                    f(std::move(lines));
                    lines = std::vector<std::string>();
                }
            }
        }
    }

    void for_all_substrings(std::string in, std::string &&d, std::function< void( std::string&& ) >&& f) {

        size_t i{0};
        while ((i = in.find(d)) != std::string::npos) {
            f(in.substr(0, i));
            in.erase(0, i + d.length());
        }
        f(std::move(in));
    }

    template <typename T>
    void for_all_numbers(std::string in, std::function< void( T, int, int ) >&& f) = delete;

    template <>
    void for_all_numbers<int>(std::string in, std::function< void( int, int, int ) >&& f) {

        size_t i{0}, errased_lenth{0};
        while ((i = in.find_first_not_of("-0123456789")) != std::string::npos) {
            std::string tmp = in.substr(0, i);
            if (tmp.length() > 0 && tmp != "-") {
                f(stoi(tmp),errased_lenth,errased_lenth + tmp.length());
            }
            errased_lenth += i + 1;
            in.erase(0, i + 1);
        }
        if (in.length() > 0 && in != "-") {
            f(stoi(in),errased_lenth,errased_lenth + in.length());
        }
    }

    template <>
    void for_all_numbers<long>(std::string in, std::function< void( long, int, int ) >&& f) {

        size_t i{0}, errased_lenth{0};
        while ((i = in.find_first_not_of("-0123456789")) != std::string::npos) {
            std::string tmp = in.substr(0, i);
            if (tmp.length() > 0 && tmp != "-") {
                f(stol(tmp),errased_lenth,errased_lenth + tmp.length());
            }
            errased_lenth += i + 1;
            in.erase(0, i + 1);
        }
        if (in.length() > 0 && in != "-") {
            f(stol(in),errased_lenth,errased_lenth + in.length());
        }
    }

    template <>
    void for_all_numbers<ll>(std::string in, std::function< void( ll, int, int ) >&& f) {

        size_t i{0}, errased_lenth{0};
        while ((i = in.find_first_not_of("-0123456789")) != std::string::npos) {
            std::string tmp = in.substr(0, i);
            if (tmp.length() > 0 && tmp != "-") {
                f(stoll(tmp),errased_lenth,errased_lenth + tmp.length());
            }
            errased_lenth += i + 1;
            in.erase(0, i + 1);
        }
        if (in.length() > 0 && in != "-") {
            f(stoll(in),errased_lenth,errased_lenth + in.length());
        }
    }

    template <>
    void for_all_numbers<ull>(std::string in, std::function< void( ull, int, int ) >&& f) {
        
        size_t i{0}, errased_lenth{0};
        while ((i = in.find_first_not_of("-0123456789")) != std::string::npos) {
            std::string tmp = in.substr(0, i);
            if (tmp.length() > 0 && tmp != "-") {
                f(stoull(tmp),errased_lenth,errased_lenth + tmp.length());
            }
            errased_lenth += i + 1;
            in.erase(0, i + 1);
        }
        if (in.length() > 0 && in != "-") {
            f(stoull(in),errased_lenth,errased_lenth + in.length());
        }
    }


}

