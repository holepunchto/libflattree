#include <assert.h>
#include "../include/flattree.h"

int
main () {
  assert(flat_tree_index(0, 0) == 0);
  assert(flat_tree_index(0, 1) == 2);
  assert(flat_tree_index(0, 2) == 4);
  assert(flat_tree_index(0, 3) == 6);
  assert(flat_tree_index(1, 0) == 1);
  assert(flat_tree_index(1, 1) == 5);
  assert(flat_tree_index(1, 2) == 9);
  assert(flat_tree_index(2, 0) == 3);
  assert(flat_tree_index(2, 1) == 11);
  assert(flat_tree_index(3, 0) == 7);
  assert(flat_tree_index(4, 0) == 15);

  /* round-trip: index(depth(i), offset(i)) == i */
  for (uint64_t i = 0; i < 64; i++) {
    assert(flat_tree_index(flat_tree_depth(i), flat_tree_offset(i)) == i);
  }

  return 0;
}
