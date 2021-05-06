/*
 * setbid(1) must return 0
 */

#include "../setbid_include.h"
#include <stdlib.h>
#include <errno.h>

int main() {
  errno = 0;
  int result = setbid(1);
  if (result) return EXIT_FAILURE;
  if (errno != 0) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
