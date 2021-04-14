#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS
#include <cstddef>

size_t ceilingLog(size_t x);

int parentInterval(int tIdx);
int leftChildInterval(int tIdx);
int rightChildInterval(int tIdx);

bool isLeftChild(int tIdx);
bool isRightChild(int tIdx);

#endif /* HELPER_FUNCTIONS */