#include <assert.h>
#include "../include/flattree.h"

int
main () {
  uint64_t roots[64];
  int len;

  len = flat_tree_full_roots(0, roots);
  assert(len == 0);

  len = flat_tree_full_roots(2, roots);
  assert(len == 1);
  assert(roots[0] == 0);

  len = flat_tree_full_roots(4, roots);
  assert(len == 1);
  assert(roots[0] == 1);

  len = flat_tree_full_roots(6, roots);
  assert(len == 2);
  assert(roots[0] == 1);
  assert(roots[1] == 4);

  len = flat_tree_full_roots(8, roots);
  assert(len == 1);
  assert(roots[0] == 3);

  len = flat_tree_full_roots(10, roots);
  assert(len == 2);
  assert(roots[0] == 3);
  assert(roots[1] == 8);

  return 0;
}
