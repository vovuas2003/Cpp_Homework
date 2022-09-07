#include <iostream>

void countLetters(const char* str, int& numLetters, int& numDigits, int& numOther) {
    numLetters = 0;
    numDigits = 0;
    numOther = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            numLetters++;
        } else if(str[i] >= '0' && str[i] <= '9') {
            numDigits++;
        } else {
            numOther++;
        }
    }
}

int main() {
    char s[] = "Hell0, w0rld!";
    int l, d, o;
    countLetters(s, l, d, o);
    std::cout << l << " " << d << " " << o << std::endl;
}
