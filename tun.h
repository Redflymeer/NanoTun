#ifndef TUN_H
#define TUN_H



#include <iostream>
#include "src/json.hpp"
using json = nlohmann::json;


json tun_base(bool ss, vless, vmess, hysteria, trojan, shadowtls, tproxy, http)   {   
   json tun_json = json::parse(R"({
      "log": {
         "level": "info",
         "output": "sing-box.log"
      },
      "inbounds": [
         {
            "type": "tun",
            "tag": "tun-in",
            "options": {
               "interface_name": "nanotun",
               "inet4_address": "198.18.0.1/15",
               "auto_route": true,
               "strict_route": true,
               "mtu": 9000
            }
         }
      ],
      "outbounds": [
         {
            "type": "direct",
            "tag": "direct"
         }
      ]
   })");
   
   return tun_json;
}


#endif
