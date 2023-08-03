#include "lib/lazy.h"

bool is_even(int number) {
  if (number == 0) {
    return true;
  }
  if (number < 0) {
    return false;
  }
  return FN(is_odd)(number - 1);
}

REGISTER_FN(is_even);

