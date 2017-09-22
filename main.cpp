#include "Calc.h"

int main()
{    while (1)
    {
        Initialize();
        std::string input;
        std::getline(std::cin, input);
        const char * str = input.c_str();
        if (strcmp(input.c_str(), "quit") == 0)
            exit(0);
        calculate(str);
    }
    _getch();
    return 0;
}
