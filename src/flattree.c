#include <stdbool.h>
#include <stdint.h>
#include "../include/flattree.h"

extern uint64_t flat_tree_depth (uint64_t i);
extern uint64_t flat_tree_index (uint64_t depth, uint64_t offset);
extern uint64_t flat_tree_offset (uint64_t i);
extern uint64_t flat_tree_parent (uint64_t i);
extern uint64_t flat_tree_sibling (uint64_t i);
extern uint64_t flat_tree_left_child (uint64_t i);
extern uint64_t flat_tree_right_child (uint64_t i);
extern uint64_t flat_tree_left_span (uint64_t i);
extern uint64_t flat_tree_right_span (uint64_t i);
extern uint64_t flat_tree_count (uint64_t i);
extern uint64_t flat_tree_spans (uint64_t i);
extern int flat_tree_full_roots (uint64_t index, uint64_t *roots);
extern void flat_tree_iterator_init (flat_tree_iterator_t *it, uint64_t index);
extern void flat_tree_iterator_seek (flat_tree_iterator_t *it, uint64_t index);
extern bool flat_tree_iterator_is_leaf (flat_tree_iterator_t *it);
extern bool flat_tree_iterator_is_left (flat_tree_iterator_t *it);
extern bool flat_tree_iterator_is_right (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_parent (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_left_child (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_right_child (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_sibling (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_next (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_prev (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_next_tree (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_prev_tree (flat_tree_iterator_t *it);
extern bool flat_tree_iterator_contains (flat_tree_iterator_t *it, uint64_t index);
extern uint64_t flat_tree_iterator_count (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_count_leaves (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_peek_left_span (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_peek_right_span (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_left_span (flat_tree_iterator_t *it);
extern uint64_t flat_tree_iterator_right_span (flat_tree_iterator_t *it);
extern bool flat_tree_iterator_full_root (flat_tree_iterator_t *it, uint64_t index);
extern bool flat_tree_iterator_is_root (flat_tree_iterator_t *it, uint64_t length);
