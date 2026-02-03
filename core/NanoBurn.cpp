#include <core/NanoBurn.h>
#include <net/if.h>  // TUN
#include <sodium.h>  // ChaCha20-Poly [web:8][web:11]
#include <core/simple_base64.h>  // URI decode [web:9]

bool ss_start(const std::string& uri) {
    // sodium_init(); chacha20poly1305_encrypt()
    // tun_setup("tun0"); proxy_loop();
    return true;  // TODO
}
