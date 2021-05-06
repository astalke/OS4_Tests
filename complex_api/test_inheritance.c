/*
 * Children must not inherit queue.
 */

#include "../setbid_include.h"
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void child(int x) {
  errno = 0;
  int result = setbid(x);
  if (result) exit(EXIT_FAILURE);
  if (errno != 0) exit(EXIT_FAILURE);
  exit(EXIT_SUCCESS);
}

int main() {
  errno = 0;
  // Children should not inherit this.
  int result = setbid(MAX_BID);
  if (result) exit(EXIT_FAILURE);
  if (errno != 0) exit(EXIT_FAILURE);

  // Making children.
  for (int i = 1; i <= MAX_BID; ++i) {
    if (!fork()) child(i);
  }
  result = EXIT_SUCCESS;
  // Waiting for children's death.
  for (int i = 1; i <= MAX_BID; ++i) {
    int code;
    wait(&code);
    // Child returned wrong code.
    if (WEXITSTATUS(code) != 0) {
      // We wait for everyone to avoid zombie.
      result = EXIT_FAILURE;
    }
  }
  return result;
}



