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
