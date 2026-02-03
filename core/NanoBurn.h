#pragma once
#include <string>
#include <cstdint>

namespace NanoTun {
struct SSConfig {
    std::string method;
    std::string password;
    std::string server;
    uint16_t port;
};

class NanoBurn {
public:
    static bool init(const SSConfig& config);
    static bool start();
    static void stop();
    
private:
    static SSConfig config_;
    static bool running_;
};
}
