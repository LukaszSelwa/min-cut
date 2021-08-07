#include "helper_functions.hpp"

int parent_interval(int tIdx) { return tIdx / 2; }

int left_child_interval(int tIdx) { return 2 * tIdx; }

int right_child_interval(int tIdx) { return 2 * tIdx + 1; }

bool is_left_child(int tIdx) { return (tIdx & 1) == 0; }

bool is_right_child(int tIdx) { return (tIdx & 1) == 1; }