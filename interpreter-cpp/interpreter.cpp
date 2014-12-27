#include <iostream>
#include "fns.h"

int main() {
  Register p, q;
  while (1) {
    std::cin >> p >> q;
    Interpret(p, q);
    std::cerr << p << ", " << q << "\n";
  }

  return 0;
}
