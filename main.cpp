#include "core/NanoBurn.h"
#include <iostream>

int main() {
    std::string url;
    std::cout << "Enter URL (ss:// or vless://): ";
    std::getline(std::cin, url);
    
    if (url.substr(0, 5) == "ss://") {
        auto ss = NanoTun::NanoBurn::parse_ss_url(url);
        NanoTun::NanoBurn::init(ss);
    } else if (url.substr(0, 8) == "vless://") {
        auto vless = NanoTun::NanoBurn::parse_vless_url(url);
        NanoTun::NanoBurn::init(vless);
    }
    
    NanoTun::NanoBurn::start();
    return 0;
}
