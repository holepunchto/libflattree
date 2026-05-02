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

  len = flat_tree_full_roots(12, roots);
  assert(len == 2);
  assert(roots[0] == 3);
  assert(roots[1] == 9);

  len = flat_tree_full_roots(14, roots);
  assert(len == 3);
  assert(roots[0] == 3);
  assert(roots[1] == 9);
  assert(roots[2] == 12);

  len = flat_tree_full_roots(16, roots);
  assert(len == 1);
  assert(roots[0] == 7);

  /* roots collectively span [0, index) with no overlap */
  for (uint64_t index = 0; index <= 32; index += 2) {
    len = flat_tree_full_roots(index, roots);
    uint64_t next = 0;
    for (int i = 0; i < len; i++) {
      assert(flat_tree_left_span(roots[i]) == next);
      next = flat_tree_right_span(roots[i]) + 2;
    }
    assert(next == index);
  }

  return 0;
}
