#include <stdio.h>
#include "print_display.h"
void print_display(int *board, int height, int width) {
	printf("\n    ");
	for (int i = 1; i <= width; ++i) {
		if (i < 10) {
			printf("%d   ", i);
		}
		else {
			printf("%d  ", i);
		} 
	}
	printf("\n\n");
	for (int y = 1; y <= height; ++y) {
		if (y < 10) {
			printf("%d   ", y);
		}
		else {
			printf("%d  ", y);
		}
		for (int x = 1; x <= width; ++x) {
			int value = board[(y - 1) * width + (x - 1)];
			if ((value <= 8) && (value >= 1)) {
				printf("%d", value);
			}
			else {
				printf("%c", value);
			}
			if (x != width) {
				printf("   ");
			}
		}
		printf("\n");
	}
}