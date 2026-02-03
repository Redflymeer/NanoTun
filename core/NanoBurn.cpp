#include "NanoBurn.h"
#include "simple_base64.h"
#include <iostream>

namespace NanoTun {
SSConfig NanoBurn::config_;
bool NanoBurn::running_ = false;

bool NanoBurn::init(const SSConfig& config) {
    config_ = config;
    std::cout << "NanoBurn SS: " << config.server 
              << ":" << config.port << "\n";
    return true;
}

bool NanoBurn::start() {
    running_ = true;
    std::cout << "NanoBurn started\n";
    return true;
}

void NanoBurn::stop() {
    running_ = false;
    std::cout << "NanoBurn stopped\n";
}
}
