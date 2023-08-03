#include <iostream>
#include "lib/lazy.h"
#include "is_even.h"
#include "is_odd.h"

struct f {
  size_t x;
  size_t y;
};

__attribute__((fastcall)) f g() {
  return {1, 2};
}

REGISTER_FN(g);

int main() {
  f x = FN(g)();

  std::cout << "x: " << x.x << std::endl;
  std::cout << "y: " << x.y << std::endl;

  std::cout << "5 is even: " << is_even(5) << std::endl;
  std::cout << "6 is even: " << is_even(6) << std::endl;
  std::cout << "5 is odd:  " << is_odd(5) << std::endl;
  std::cout << "6 is odd:  " << is_odd(6) << std::endl;
}
