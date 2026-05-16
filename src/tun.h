#ifndef TUN_H
#define TUN_H



#include <iostream>
#include "src/json.hpp"
#include <string>

using json = nlohmann::json;


// Protocol = protocol of vpn (vless/vmess/trojan/ss (ShadoswSocks)/hy2 (Hysteria2)/tuic/anytls/naive/socks4 (or 5)/http/ssh) shadowtls, wireguard and tailscale is unsupported
// Type = Transport for TCP (none (default TCP)/http/ws/quic/grpc/httpupgrade) 
// Tag = name of config (example "Finland 1")
// Server = server to connect (example "123.123.123.13")
// Port = port to connect (example "443", but <=25565)
// Packet_encding = (xudp)
// uuid = key to connect (example "1234eeee-56789-aaaaa-101112-ooooo")
// tls-mode = mode of tls (none / tls / reality)
// fingerprint = browser what sees site (none / chrome / firefox / safari / ios (like webview) / android (like webview) / edge / 360 / qq / random)
// sni = what provider site sees if you turn VPN (example google.com) 
// type-mode = mod what in your transport will work (for grpc is gun/multi, for tcp is none/http, for kcp )
// flow = is mask for your vpn (none/xtls-rprx-vision)
// allowinsecure = allowing http connections (none/1)


json tun_base(std::string protocol tag server uuid tls-mode fingerprint sni type type-mode flow encoding; bool allowinsecure)   {   
   json tun_json = json::parse(R"({
      "log": {
         "level": "info",
         "output": "xray.log"
      },
      "dns": {
        "servers": [
          {
            "address": "77.88.8.88"
          },
        ]

      }
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
   

   if (protocol == vless) {
      json parsed = tun_json::parse();
      with_vless = json::parse(R"({
        "type": "vless",
        "tag": tag,
        "server": server,
        "server_port": port,
        "uuid": uuid,
        "flow": flow,
        "packet_encoding": encoding
      )}");

   }
  
   return tun_json;
}


#endif
