#include <stdio.h>
#include "costomize.h"

void costo_info(int *height, int *width, int *mine) {
	printf("Please enter the height of the board\n\n");
	char garbage = '\0';
	while (1) {
		int k = scanf_s("%d", height);
		if ((k == 1) && (*height > 0)) {
			printf("The height you put in is: %d\n\n", *height);
			break;
		} else {
			if (k != 1) {
				scanf_s(" %c", &garbage);
			}
			printf("Invalid input. Please re-enter\n\n");
		}
	}
	printf("Please enter the width of the board\n\n");
	while (1) {
		int k = scanf_s("%d", width);
		if ((k == 1) && (*width > 0)) {
			printf("The width you put in is: %d\n\n", *width);
			break;
		}
		else {
			if (k != 1) {
				scanf_s(" %c", &garbage);
			}
			printf("Invalid input. Please re-enter\n\n");
		}
	}
	printf("Please enter the number of mines. Please note that the number of mines cannot be greater than height * width\n\n");
	while (1) {
		int k = scanf_s("%d", mine);
		if ((k == 1) && (*mine <= (*height) * (*width)) && (*mine >= 0)) {
			printf("The number of mines you put in is: %d\n\n", *mine);
			break;
		}
		else {
			if (k != 1) {
				scanf_s(" %c", &garbage);
			}
			printf("Invalid input. Please re-enter\n\n");
		}
	}
}