#include <stdio.h>
#include <stdlib.h>
#include "produce_board.h"
#include "random.h"

static int n_mine = 42;
static int emp = 32;

int *produce_top(int height, int width) {
	int length = height * width;
	int *top_board = malloc(length * sizeof(int));
	for (int i = 0; i < length; ++i) {
		top_board[i] = '#';
	}
	return top_board;
}
static count_mines(int *board, int height, int width, int y, int x) {
	int num_mines = 0;
	for (int vertical = -1; vertical <= 1; ++vertical) {
		for (int horizontal = -1; horizontal <= 1; ++horizontal) {
			if (((y + vertical) <= height) && ((y + vertical >= 1))
				&& ((x + horizontal <= width)) && ((x + horizontal) >= 1)
				&& ((vertical != 0) || (horizontal != 0))) {
				if (board[(y + vertical - 1) * width + (x + horizontal - 1)] == n_mine) {
					++num_mines;
				}
			}
		}
	}
	return num_mines;
}

static assign_number(int *board, int height, int width) {
	for (int y = 1; y <= height; ++y) {
		for (int x = 1; x <= width; ++x) {
			if (board[(y - 1) * width + (x - 1)] != n_mine) {
				int num_mines = count_mines(board, height, width, y, x);
				if (num_mines != 0) {
					board[(y - 1) * width + (x - 1)] = count_mines(board, height, width, y, x);
				}
				else {
					board[(y - 1) * width + (x - 1)] = emp;
				}
			}
		}
	}
}

int *produce_bottom(int height, int width, int mine) {
	int length = height * width;
	int pos = 0;
	int *bottom_board = malloc(length * sizeof(int));
	for (int i = 0; i < length; ++i) {
		bottom_board[i] = 0;
	}
	int *store_pos = m_random(length, mine);

	for (int i = 0; i < mine; ++i) {
		pos = store_pos[i];
		if (bottom_board[pos] == 0) {
			bottom_board[pos] = n_mine;
		}
		else {
			int j = pos + 1;
			while (1) {
				if (j == length) {
					j = pos - 1;
					continue;
				}
				else if (j < 0) {
					break;
				}
				else if (j > pos) {
					if (bottom_board[j] == 0) {
						bottom_board[j] = n_mine;
						break;
					}
					else {
						++j;
					}
				}
				else {
					if (bottom_board[j] == 0) {
						bottom_board[j] = n_mine;
						break;
					}
					else {
						--j;
					}
				}
			}
		}
	}
	free(store_pos);
	assign_number(bottom_board, height, width);
	return bottom_board;
}