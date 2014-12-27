#include <iostream>
#include "fns.h"

int main()
{
  Register p, q, r, s, t;
  while(1) {
    std::cin >> p >> q;
    r = 1;
    s = 1;
    t = 1;
    Interpret(p, q);
    std::cerr << p << ", " << q << "\n";// << ", " << r << ", " << s << ", " << t << "\n";
  }

  return 0;
}
