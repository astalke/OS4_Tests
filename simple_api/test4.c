/*
 * setbid(1), setbid(2) must return -1 and set errno to EPERM.
 */

#include "../setbid_include.h"
#include <stdlib.h>
#include <errno.h>

int main() {
  errno = 0;
  // This one changes strategy.
  int result = setbid(1);
  if (result) return EXIT_FAILURE;
  if (errno != 0) return EXIT_FAILURE;
  
  // This one must fail.
  result = setbid(2);
  if (result != -1) return EXIT_FAILURE;
  if (errno != EPERM) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
