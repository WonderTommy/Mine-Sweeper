#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "play_game.h"
#include "print_display.h"


static int n_flag = 94; // '^'
static int n_emp = 35; // '#'
static int n_unsure = 63; // '?'
static int n_mine = 42; // '*'
static int n_space = 32; // ' '
static int n_mistake = 88; // 'X'


static void instructions(void) {
	printf("\n\n");
	printf("Please enter what you want to do, followed with the coordinate. X followed by Y.\n");
	printf("e.g. \"F 1 2\" put flag on the first spot of the second row.\n\n");
	printf("  F for flag\n  Q for unsure\n  U for cancel the flag or unsure\n  C for click\n  D for double click\n");
	printf("The case of the letter doesn't matter.\n\n");
}

static void p_flag(int *display, int height, int width) {
	int x = 0;
	int y = 0;
	char garbage1 = '\0';
	char garbage2 = '\0';
	while (1) {
		int i = scanf_s("%d", &x);
		int j = scanf_s("%d", &y);
		int k = i + j;

		if ((k == 2) && (x > 0) && (x <= width) && (y > 0) && (y <= height)) {
			int check = display[(y - 1) * width + (x - 1)];
			if (((check >= 1) && (check <= 8)) || (check == n_mine) || (check == n_space)) {
				print_display(display, height, width);
				printf("Cannot flag the spot that has been revealed, please re-enter coordinate.\n\n");
			}
			else {
				display[(y - 1) * width + (x - 1)] = n_flag;
				break;
			}
		}
		else if (k == 1) {
			scanf_s(" %c", &garbage1);
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter coordinate.\n\n");

		}
		else if (k == 0) {
			scanf_s(" %c", &garbage1);
			scanf_s(" %c", &garbage2);
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter coordinate.\n\n");
		}
		else {
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter coordinate.\n\n");
		}
	}
}

static void p_unsure(int *display, int height, int width) {
	int x = 0;
	int y = 0;
	char garbage1 = '\0';
	char garbage2 = '\0';
	while (1) {
		int i = scanf_s("%d", &x);
		int j = scanf_s("%d", &y);
		int k = i + j;

		if ((k == 2) && (x > 0) && (x <= width) && (y > 0) && (y <= height)) {
			int check = display[(y - 1) * width + (x - 1)];
			if (((check >= 1) && (check <= 8)) || (check == n_mine)) {
				print_display(display, height, width);
				printf("Cannot flag the spot that has been revealed, please re-enter coordinate.\n\n");
			}
			else {
				display[(y - 1) * width + (x - 1)] = n_unsure;
				break;
			}
		}
		else if (k == 1) {
			scanf_s(" %c", &garbage1);
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter coordinate.\n\n");

		}
		else if (k == 0) {
			scanf_s(" %c", &garbage1);
			scanf_s(" %c", &garbage2);
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter coordinate.\n\n");
		}
		else {
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter coordinate.\n\n");
		}
	}
}

static void p_cancel(int *display, int height, int width) {
	int x = 0;
	int y = 0;
	char garbage1 = '\0';
	char garbage2 = '\0';
	while (1) {
		int i = scanf_s("%d", &x);
		int j = scanf_s("%d", &y);
		int k = i + j;

		if ((k == 2) && (x > 0) && (x <= width) && (y > 0) && (y <= height)) {
			int check = display[(y - 1) * width + (x - 1)];
			if ((check == n_emp) || (check == n_flag) || (check = n_unsure)) {
				display[(y - 1) * width + (x - 1)] = n_emp;
				break;
			}
			else {
				print_display(display, height, width);
				printf("Cannot flag the spot that has been revealed, please re-enter coordinate.\n\n");
			}
		}
		else if (k == 1) {
			scanf_s(" %c", &garbage1);
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter coordinate.\n\n");

		}
		else if (k == 0) {
			scanf_s(" %c", &garbage1);
			scanf_s(" %c", &garbage2);
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter coordinate.\n\n");
		}
		else {
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter coordinate.\n\n");
		}
	}
}



static void p_open_around(int *display, int *hide, int height, int width, int horizontal, int vertical) {
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			if ((horizontal + x > 0) && (horizontal + x <= width) && (vertical + y > 0) && (vertical + y <= height) && ((x != 0) || (y != 0)) && (display[(vertical + y - 1) * width + (horizontal + x - 1)] == n_emp)) {
				display[(vertical + y - 1) * width + (horizontal + x - 1)] = hide[(vertical + y - 1) * width + (horizontal + x - 1)];
				if (display[(vertical + y - 1) * width + (horizontal + x - 1)] == n_space) {
					p_open_around(display, hide, height, width, horizontal + x, vertical + y);
				}
			}
		}
	}
}

static void p_click(int *display, int *hide, int height, int width) {
	int x = 0;
	int y = 0;
	char garbage1 = '\0';
	char garbage2 = '\0';
	while (1) {
		int i = scanf_s("%d", &x);
		int j = scanf_s("%d", &y);
		int k = i + j;

		if ((k == 2) && (x > 0) && (x <= width) && (y > 0) && (y <= height)) {
			int check = display[(y - 1) * width + (x - 1)];
			if (check == n_emp) {
				display[(y - 1) * width + (x - 1)] = hide[(y - 1) * width + (x - 1)];
				if (display[(y - 1) * width + (x - 1)] == n_space) {
					p_open_around(display, hide, height, width, x, y);
				} 
				return;
			}
			else {
				print_display(display, height, width);
				printf("Invalid operation on the current coordinate, please re-enter action.\n\n");
				break;
			}
		}
		else if (k == 1) {
			scanf_s(" %c", &garbage1);
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter action.\n\n");
			break;

		}
		else if (k == 0) {
			scanf_s(" %c", &garbage1);
			scanf_s(" %c", &garbage2);
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter action.\n\n");
			break;
		}
		else {
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter action.\n\n");
			break;
		}
	}
	play_game(display, hide, height, width);
}

static int c_flag_around(int *board, int height, int width, int horizontal, int vertical) {
	int c_flag = 0;
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			if ((horizontal + x > 0) && (horizontal + x <= width) && (vertical + y > 0) && (vertical + y <= height) && ((x != 0) || (y != 0))) {
				if (board[(vertical + y - 1) * width + (horizontal + x - 1)] == n_flag) {
					++c_flag;
				}
			}
		}
	}
	return c_flag;
}




static void p_double_click(int *display, int *hide, int height, int width) {
	int x = 0;
	int y = 0;
	char garbage1 = '\0';
	char garbage2 = '\0';
	while (1) {
		int i = scanf_s("%d", &x);
		int j = scanf_s("%d", &y);
		int k = i + j;

		if ((k == 2) && (x > 0) && (x <= width) && (y > 0) && (y <= height)) {
			int check = c_flag_around(display, height, width, x, y);
			if (check == display[(y - 1) * width + (x - 1)]) {
				p_open_around(display, hide, height, width, x, y);
				return;
			}
			else {
				print_display(display, height, width);
				printf("Invalid operation on the current coordinate, please re-enter action.\n\n");
				break;
			}
		}
		else if (k == 1) {
			scanf_s(" %c", &garbage1);
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter action.\n\n");
			break;

		}
		else if (k == 0) {
			scanf_s(" %c", &garbage1);
			scanf_s(" %c", &garbage2);
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter action.\n\n");
			break;
		}
		else {
			print_display(display, height, width);
			printf("Invalid coordinate. Please re-enter action.\n\n");
			break;
		}	
	}
	play_game(display, hide, height, width);
}

static int count_mine(int *board, int height, int width) {
	int len = height * width;
	int c_mine = 0;
	for (int i = 0; i < len; ++i) {
		if (board[i] == n_mine) {
			++c_mine;
		}
	}
	return c_mine;
}

static bool check_lost(int *board, int height, int width) {
	return (count_mine(board, height, width) != 0);
}

static int count_unreveal(int *board, int height, int width) {
	int len = height * width;
	int c_un = 0;
	for (int i = 0; i < len; ++i) {
		if ((board[i] == n_flag) || (board[i] == n_unsure) || (board[i] == n_emp)) {
			++c_un;
		}
	}
	return c_un;
}

static bool check_win(int *display, int *hide, int height, int width) {
	if ((count_mine(display, height, width) == 0) && (count_unreveal(display, height, width) == count_mine(hide, height, width))) {
		return true;
	}
	else {
		return false;
	}
}


void play_game(int *display, int *hide, int height, int width) {
	char cmd = '\0';
	instructions();
	while (1) {
		int k = scanf_s(" %c", &cmd);
		if (k != 1) {
			printf("Invalid input. Please re-enter.\n\n");
		}
		else if ((cmd == 'i') || (cmd == 'I')){
			instructions();
		}
		else if ((cmd == 'f') || (cmd == 'F')) {
			system("cls");
			p_flag(display, height, width);
		}
		else if ((cmd == 'q') || (cmd == "Q")) {
			system("cls");
			p_unsure(display, height, width);
		}
		else if ((cmd == 'u') || (cmd == 'U')){
			system("cls");
			p_cancel(display, height, width);
		}
		else if ((cmd == 'c') || (cmd == 'C')) {
			system("cls");
			p_click(display, hide, height, width);
		}
		else if ((cmd == 'd') || (cmd == 'D')) {
			system("cls");
			p_double_click(display, hide, height, width);
		}
		print_display(display, height, width);
		printf("\n");
		printf("Enter I to see instruction again.\n\n");
		if (check_lost(display, height, width)){
			int len = height * width;
			for (int i = 0; i < len; ++i) {
				if ((display[i] == n_flag) && (hide[i] != n_mine)) {
					display[i] = n_mistake;
				}
				else if (display[i] != n_flag){
					display[i] = hide[i];
				}
			}
			system("cls");
			print_display(display, height, width);
			printf("\nYou Lost!\n\n");
			break;
		}
		if (check_win(display, hide, height, width)) {
			int len = height * width;
			for (int i = 0; i < len; ++i) {
				if (display[i] == n_emp) {
					display[i] = hide[i];
				}
			}
			system("cls");
			print_display(display, height, width);
			printf("\nYou Won!\n\n");
			break;
		}
	}
}