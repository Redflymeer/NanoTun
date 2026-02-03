#include "core/NanoBurn.h"

int main() {
    NanoTun::SSConfig config;
    config.method = "chacha20-ietf-poly1305";
    config.password = "mypass";
    config.server = "1.2.3.4";
    config.port = 8388;
    
    NanoTun::NanoBurn::init(config);
    NanoTun::NanoBurn::start();
    return 0;
}
