#include "utils.h"
int mod(int x, int y) {
  int m = x%y;
  if (m < 0)
    m += y;
  return m;
}
