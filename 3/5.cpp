#include <iostream>

int main() {
    std::string s;
    getline(std::cin, s);
    int n = 0;
    if((s[0] != '[') || (s[s.size() - 1] != ']')) {
        throw std::invalid_argument("Incorrect input!");
    }
    std::string buf = "";
    for(int i = 1; i < s.size() - 1; i++) {
        if(s[i] == ',') {
            if(s[i + 1] != ' ') {
                throw std::invalid_argument("Incorrect input!");
            }
            if(buf.size() == 0) {
                throw std::invalid_argument("Incorrect input!");
            }
            n += stoi(buf);
            buf = "";
            i++;
            continue;
        }
        if(isdigit(s[i])) {
            buf += s[i];
        } else {
            throw std::invalid_argument("Incorrect input!");
        }
    }
    if(s.size() != 2) {
        n += stoi(buf);
    }
    std::cout << n;
    return 0;
}
