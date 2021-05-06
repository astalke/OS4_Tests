/*
 * setbid(MAX_BID + 1) must return -1 and set errno to EINVAL.
 */

#include "../setbid_include.h"
#include <stdlib.h>
#include <errno.h>

int main() {
  errno = 0;
  int result = setbid(MAX_BID + 1);
  if (result != -1) return EXIT_FAILURE;
  if (errno != EINVAL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
