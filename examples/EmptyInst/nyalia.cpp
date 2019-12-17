#include <iostream>
#include <string>

void Nyalia(std::string a, int b, int c) {
    std::cout << "Actual: ";
    std::cout << a << " | ";
    std::cout << b << " | ";
    std::cout << c << std::endl;
}

int main(void) {

    Nyalia(std::string("CS363"), 1000, -30);

    return 0;
};
