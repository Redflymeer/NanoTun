#include "NanoBurn.h"
#include "simple_base64.h"
#include <iostream>
#include <cstring>

namespace NanoTun {

// SS парсер
SSConfig NanoBurn::parse_ss_url(const std::string& ss_url) {
    SSConfig config;
    
    size_t at = ss_url.find('@');
    size_t method_end = ss_url.find(':', 5);
    
    std::string b64_auth = ss_url.substr(5, at - 5);
    std::string decoded = simple_base64::decode(b64_auth);
    
    size_t pass_pos = decoded.find(':');
    config.method = decoded.substr(0, pass_pos);
    config.password = decoded.substr(pass_pos + 1);
    
    size_t colon = ss_url.find(':', at + 1);
    config.server = ss_url.substr(at + 1, colon - at - 1);
    config.port = std::stoi(ss_url.substr(colon + 1));
    
    return config;
}

// VLESS парсер
VlessConfig NanoBurn::parse_vless_url(const std::string& vless_url) {
    VlessConfig config;
    
    size_t at = vless_url.find('@');
    size_t colon = vless_url.find(':', at + 1);
    size_t qmark = vless_url.find('?', colon);
    
    config.uuid = vless_url.substr(8, at - 8);
    config.server = vless_url.substr(at + 1, colon - at - 1);
    config.port = std::stoi(vless_url.substr(colon + 1, qmark - colon - 1));
    
    config.sni = config.server;
    config.flow = "";
    
    if (qmark != std::string::npos) {
        size_t flow_pos = vless_url.find("flow=", qmark);
        if (flow_pos != std::string::npos) {
            size_t flow_end = vless_url.find('&', flow_pos);
            if (flow_end == std::string::npos) flow_end = vless_url.size();
            config.flow = vless_url.substr(flow_pos + 5, flow_end - flow_pos - 5);
        }
    }
    
    return config;
}

bool NanoBurn::running_ = false;

// Init
bool NanoBurn::init(const SSConfig& ss) {
    std::cout << "SS: " << ss.method << "@" << ss.server 
              << ":" << ss.port << "\n";
    return true;
}

bool NanoBurn::init(const VlessConfig& vless) {
    std::cout << "VLESS: " << vless.uuid.substr(0,8) << "...@" 
              << vless.server << ":" << vless.port 
              << " flow=" << vless.flow << "\n";
    return true;
}
bool NanoBurn::start() {
    running_ = true;
    std::cout << "NanoBurn VPN started\n";
    
   
    while (running_) {
        std::cout << "[VPN] Proxy active... (Ctrl+C для выхода)\r";
        sleep(1);
    }
    return true;
}


void NanoBurn::stop() {
    running_ = false;
    std::cout << "NanoBurn VPN stopped\n";
}

}
