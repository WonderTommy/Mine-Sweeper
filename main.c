// This is the main module for the mine sweeper(dynamic) program.

#include <stdio.h>
#include <stdlib.h>
#include "start.h"
#include "random.h"
#include "produce_board.h"

int *display = NULL;
int *hide = NULL;

int main(void) {
	m_start(display, hide);
	getch();
	return 0;
}
