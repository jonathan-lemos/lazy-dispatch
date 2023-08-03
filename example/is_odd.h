#include "lib/lazy.h"

bool is_odd(int number) {
  if (number == 1) {
    return true;
  }
  if (number < 1) {
    return false;
  }
  return FN(is_even)(number - 1);
}

REGISTER_FN(is_odd);

