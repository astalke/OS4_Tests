/*
 * setbid(0) must return -1 and set errno to EPERM.
 */

#include "../setbid_include.h"
#include <stdlib.h>
#include <errno.h>

int main() {
  errno = 0;
  int result = setbid(0);
  if (result != -1) return EXIT_FAILURE;
  if (errno != EPERM) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
