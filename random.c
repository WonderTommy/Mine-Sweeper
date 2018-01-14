#include <stdlib.h>
#include <time.h>
#include "random.h"

int *m_random(int length, int total) {
	int pos = 0;
	int *store_pos = malloc(total * sizeof(int));
	srand(time(NULL));
	for (int i = 0; i < total; ++i) {
		pos = rand() % length;
		store_pos[i] = pos;
	}
	return store_pos;
}