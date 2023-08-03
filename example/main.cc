#include <iostream>
#include "lib/lazy.h"
#include "is_even.h"
#include "is_odd.h"

struct big_struct {
  size_t x[32];
};

big_struct g() {
  big_struct x;
  x.x[0] = 69;
  x.x[31] = 42;
  return x;
}

REGISTER_FN(g);

int main() {
  big_struct x = FN(g)();

  std::cout << "x.x[0]: " << x.x[0] << std::endl;
  std::cout << "x.x[31]: " << x.x[31] << std::endl;

  std::cout << "5 is even: " << is_even(5) << std::endl;
  std::cout << "6 is even: " << is_even(6) << std::endl;
  std::cout << "5 is odd:  " << is_odd(5) << std::endl;
  std::cout << "6 is odd:  " << is_odd(6) << std::endl;
}
