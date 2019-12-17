#include <iostream>

enum ERTYPE {OK, BAD};

ERTYPE Nyalia(int a, int b, int c) {
    std::cout << "Actual: ";
    std::cout << a << " | ";
    std::cout << b << " | ";
    std::cout << c << std::endl;

    return OK;
}

int main(void) {

    ERTYPE er = Nyalia(10, 1000, -30);
    std::cout << "Status:" << (er == OK ? "OK" : "BAD") << std::endl;

    return 0;
};