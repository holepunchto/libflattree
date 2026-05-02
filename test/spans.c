#include <assert.h>
#include "../include/flattree.h"

int
main () {
  assert(flat_tree_left_span(0) == 0);
  assert(flat_tree_right_span(0) == 0);
  assert(flat_tree_left_span(1) == 0);
  assert(flat_tree_right_span(1) == 2);
  assert(flat_tree_left_span(3) == 0);
  assert(flat_tree_right_span(3) == 6);
  assert(flat_tree_left_span(5) == 4);
  assert(flat_tree_right_span(5) == 6);
  assert(flat_tree_count(0) == 1);
  assert(flat_tree_count(1) == 3);
  assert(flat_tree_count(3) == 7);
  assert(flat_tree_spans(0) == 2);
  assert(flat_tree_spans(1) == 4);
  assert(flat_tree_spans(3) == 8);
  return 0;
}
