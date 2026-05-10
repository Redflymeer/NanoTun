#include "tun.h"
#include <iostream>

int main() {
   json tun_json = tun_base();
   std::cout << tun_json.dump(2) << "\n";
   return 0;
}
