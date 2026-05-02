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
  assert(flat_tree_left_span(7) == 0);
  assert(flat_tree_right_span(7) == 14);
  assert(flat_tree_left_span(11) == 8);
  assert(flat_tree_right_span(11) == 14);
  assert(flat_tree_left_span(15) == 0);
  assert(flat_tree_right_span(15) == 30);

  assert(flat_tree_count(0) == 1);
  assert(flat_tree_count(1) == 3);
  assert(flat_tree_count(3) == 7);
  assert(flat_tree_count(7) == 15);
  assert(flat_tree_count(15) == 31);

  assert(flat_tree_spans(0) == 2);
  assert(flat_tree_spans(1) == 4);
  assert(flat_tree_spans(3) == 8);
  assert(flat_tree_spans(7) == 16);
  assert(flat_tree_spans(15) == 32);

  /* spans = right_span - left_span + 2 (leaf positions covered) */
  for (uint64_t i = 0; i < 32; i++) {
    assert(flat_tree_right_span(i) - flat_tree_left_span(i) + 2 == flat_tree_spans(i));
  }

  /* leaf nodes: left_span == right_span == i */
  for (uint64_t i = 0; i < 32; i += 2) {
    assert(flat_tree_left_span(i) == i);
    assert(flat_tree_right_span(i) == i);
  }

  return 0;
}
