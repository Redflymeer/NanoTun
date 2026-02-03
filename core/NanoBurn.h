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

struct VlessConfig {
    std::string uuid;
    std::string server;
    uint16_t port;
    std::string sni;
    std::string flow;
};

class NanoBurn {
public:
    static SSConfig parse_ss_url(const std::string& ss_url);
    static VlessConfig parse_vless_url(const std::string& vless_url);
    
    static bool init(const SSConfig& ss);
    static bool init(const VlessConfig& vless);
    static bool start();
    static void stop();
    
private:
    static Config config_;
    static bool running_;
};
}
