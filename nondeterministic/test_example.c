/*
 * Example test from task.
 */

#include "../setbid_include.h"
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

/*
 * Number of iterations in do_stuff. If you have fast machine, you should
 * increase this constant.
 */
#define NUM_OF_ITER (100000000)

/*
 * Function that takes a lot of time.
 * Since it does literally nothing, compiler may delete it, so avoid
 * compiling with -O3 flag. We want this to be slow.
 */
uint64_t do_stuff(void) {
  uint64_t result =  0;
  for (size_t i = 0; i < NUM_OF_ITER; ++i) {
    result += rand();
  }
  return result;
}

int child(int id, int bid) {
  // Set bid.
  errno = 0;
  int result = setbid(bid);
  assert(result == 0 && errno == 0);
  if (do_stuff() == 1) return -1;  // Unlikely.
  return bid;
}

int main() {
  int const bids[] = {20, 40, 50, 60, 20, 50};
  size_t const n = 6;
  for (size_t i = 0; i < n; ++i) {
    if (!fork()) {
      int id = i;
      int bid = bids[i];
      return child(id, bid);
    }
  }
  int results[n];
  for (size_t i = 0; i < n; ++i) {
    int child;
    wait(&child);
    results[i] = WEXITSTATUS(child);
  }
  int const expected[] = {40, 60, 50, 50, 20, 20};
  int result = EXIT_SUCCESS;
  for (size_t i = 0; i < n; ++i) {
    if (results[i] != expected[i]) {
      fprintf(stderr, "race_test: At %d got %d!\n", i + 1, results[i]);
      result = EXIT_FAILURE;
    }
  }
  return result;
}
