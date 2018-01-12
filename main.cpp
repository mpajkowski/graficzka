#include <GL/freeglut.h>
#include <iostream>

namespace ex1
{
    extern int execute(int argc, char** argv);
}

namespace ex2
{
    extern int execute(int argc, char** argv);
}

namespace ex3
{
    extern int execute(int argc, char** argv);
}

int main(int argc, char** argv)
{
    int exNumber = 0;

    do {
        std::cout << "Wybierz zadanie[1-3]: " << std::endl;
        std::cin.clear(); std::cin.sync();
    }
    while (!(std::cin >> exNumber) || std::cin.get() != '\n');

    std::cout << exNumber;
    switch (exNumber) {
        case 1:
            return ex1::execute(argc, argv);
        case 2:
            return ex2::execute(argc,argv);
        case 3:
            return ex3::execute(argc,argv);
        default:
            return 1;
    }
}
