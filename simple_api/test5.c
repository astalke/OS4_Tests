/*
 * setbid(1), setbid(0), setbid(2) must return 0
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
  
  // This one resets strategy.
  result = setbid(0);
  if (result) return EXIT_FAILURE;
  if (errno != 0) return EXIT_FAILURE;
  
  // This one mustn't fail.
  result = setbid(2);
  if (result) return EXIT_FAILURE;
  if (errno != 0) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
