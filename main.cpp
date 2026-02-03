#include "сore/NanoBurn.h"
#include <iostream>
int main(int argc, char** argv) {
    if (argc != 2) { std::cout << "Usage: ./NanoTun 'ss://...'\n"; return 1; }
    ss_start(argv[1]);  // Turning on 
    std::cout << "SS on (Ctrl+C off)\n";
    std::cin.get();
    return 0;
}
