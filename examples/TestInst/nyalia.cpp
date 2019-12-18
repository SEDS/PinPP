#include <iostream>
#include <string>

void Nyalia(std::string& a, int b, int c) {
    std::cout << "Actual: ";
    std::cout << a << " | ";
    std::cout << b << " | ";
    std::cout << c << std::endl;
}

int main(void) {

    std::string val("CS363");
    Nyalia(val, 1000, -30);

    return 0;
};
