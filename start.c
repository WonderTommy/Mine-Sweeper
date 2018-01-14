#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "start.h"
#include "produce_board.h"
#include "print_display.h"
#include "costomize.h"
#include "play_game.h"

int *display;
int *hide;

static const int beginer_height = 9;
static const int beginer_width = 9;
static const int beginer_mine = 10;
static const int intermediate_height = 16;
static const int intermediate_width = 16;
static const int intermediate_mine = 40;
static const int expert_height = 16;
static const int expert_width = 30;
static const int expert_mine = 99;


void m_start(int *top, int *bottom) {
	printf("Welcome to mine sweeper. Please select the mode (size of the board) you would like to play\n\n");
	printf("Please type in:\n'b' for small\n'i' for medium\n'e' for large\n'c' for costomize\n\n");
	int height = 0;
	int width = 0;
	int mine = 0;
	while (1) {
		char choice = '\0';
		int k = scanf_s(" %c", &choice);
		if (!k) {
			printf("Program failed. Please re-open the program.\n\n");
			exit(EXIT_FAILURE);
		}
		else if ((choice == 'b') || (choice == 'B')) {
			printf("You have chosen beginner.\n\n");
			height = beginer_height;
			width = beginer_width;
			mine = beginer_mine;
			//produce_top(beginer_height, beginer_width);
			break;
		}
		else if ((choice == 'i') || (choice == 'I')) {
			printf("You have chosen intermediate.\n\n");
			height = intermediate_height;
			width = intermediate_width;
			mine = intermediate_mine;
			//produce_top(intermediate_height, intermediate_width);
			break;
		}
		else if ((choice == 'e') || (choice == 'E')) {
			printf("You have chosen expert.\n\n");
			height = expert_height;
			width = expert_width;
			mine = expert_mine;
			//produce_top(expert_height, expert_width);
			break;
		}
		else if ((choice == 'c') || (choice == 'C')) {
			printf("You have chosen costomize.\n\n");
			costo_info(&height, &width, &mine);
			break;
		}
		else {
			printf("Invalid choice. Please re_enter\n\n");
		}
	}
	top = produce_top(height, width);
	bottom = produce_bottom(height, width, mine);
	system("cls");
	print_display(top, height, width);
	/*print_display(bottom, height, width);
	int sum = 0;
	for (int i = 0; i < height * width; i++) {
		if (bottom[i] == 42) {
			++sum;
		}
	}
	printf("total mines: %d\n", sum);*/
	play_game(top, bottom, height, width);
	free(top);
	free(bottom);
	char new_game = '\0';
	printf("Do you want to start a new game?\n\n");
	printf("  Yes(Y)\n  No(N)\n\n");
	while (1) {
		int k = scanf_s("%c", &new_game);
		if (k == 1) {
			if ((new_game == 'Y') || (new_game == 'y')) {
				system("cls");
				m_start(display, hide);
				break;
			}
			else if ((new_game == 'N') || (new_game == 'n')){
				printf("The program is stopped\n\n");
				exit(EXIT_SUCCESS);
				break;
			}
		}
		else {
			printf("Invalid operation. Please re-enter.\n\n");
		}
	}
}