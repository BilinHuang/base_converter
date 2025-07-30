#include <stdio.h>
#include "base_adt.h"


void print_usage(void) {
	printf("Usage: ./base_converter (-<input base>) (-output base) (-<command>) -<number>");
	printf("<base for choosing>\n");
	printf("b - binary\n");
	printf("d/o - decimal/octal\n");
	printf("h - hexadecimal\n");
	printf("d - any integer\n");
	printf("<mode>\n");
	printf("s - simplified\n");
}

void calculate(struct command *cmd) {
    
}