#include <iostream>

void count_letters(char str[], int& n_letters, int& n_digits, int& n_other) {
    n_letters = 0;
    n_digits = 0;
    n_other = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            n_letters++;
        } else if(str[i] >= '0' && str[i] <= '9') {
            n_digits++;
        } else {
            n_other++;
        }
    }
}

int main() {
    char s[] = "Hell0, w0rld!";
    int l, d, o;
    count_letters(s, l, d, o);
    std::cout << l << " " << d << " " << o << std::endl;
}
