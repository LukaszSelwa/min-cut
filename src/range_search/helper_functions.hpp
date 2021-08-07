#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS
#include <cstddef>

int parent_interval(int tIdx);
int left_child_interval(int tIdx);
int right_child_interval(int tIdx);

bool is_left_child(int tIdx);
bool is_right_child(int tIdx);

#endif /* HELPER_FUNCTIONS */