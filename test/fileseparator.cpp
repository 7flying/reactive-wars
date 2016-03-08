#include <iostream>

int main()
{
#ifdef _WIN32
    std::cout << "\\" << std::endl;
#else
    std::cout << "/" << std::endl;
#endif

    return 0;
}
