#include "swap.h"

void int_swap(int* a, int* b) {
	int tmp = *a; // put value at ptr a in tmp
	*a = *b;
	*b = tmp;
}

void float_swap(float* a, float* b) {
	float tmp = *a; // put value at ptr a in tmp
	*a = *b;
	*b = tmp;
}