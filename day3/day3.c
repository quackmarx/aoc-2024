#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define FILE_PATH "input.txt"

void pre_state(char ch);
void num1_state(char ch);
void mid_state(char ch);
void num2_state(char ch);
void end_state(char ch);
void do_state(char ch);
void dont_state(char ch);

FILE *file_ptr;

int state_i = 0;

char num1_buf[] = {'n','n','n','n','n',};
char num2_buf[] = {'n','n','n','n','n',};

int sum = 0;

bool instr_enabled = true;

void pre_state(char ch) {
	printf("PRE");
	
	for (int i = 0; i < 5; i++)
	{
		num1_buf[i] = 'n';
		num2_buf[i] = 'n';
	}
	

	if (ch == EOF) {
		return;
	}	

	char mul[] = "mul(";

	if (ch == mul[state_i] && instr_enabled) {
		if (state_i == 3) {
			state_i = 0;
			num1_state(fgetc(file_ptr));
			return;
		} else {
			state_i++;
			pre_state(fgetc(file_ptr));
			return;
		}
	} else if (ch == 'd') {
		state_i = 0;
		do_state(ch);
		return;
	}

	state_i = 0;
	pre_state(fgetc(file_ptr));
}

void num1_state(char ch) {
	printf("NUM1");
	
	if (isdigit(ch)) {
		printf(" %c ", ch);
		num1_buf[state_i] = ch;
		state_i++;
		num1_state(fgetc(file_ptr));
		return;
	}

	if (state_i > 0) {
		state_i = 0;
		mid_state(ch);
	} else {
		state_i = 0;
		pre_state(ch);
	}
}

void mid_state(char ch) {
	printf("MID");

	if (ch == ',') {
		state_i = 0;
		num2_state(fgetc(file_ptr));
	} else {
		state_i = 0;
		pre_state(ch);
	}
}

void num2_state(char ch) {
	printf("NUM2");
	
	if (isdigit(ch)) {
		printf(" %c ", ch);
		num2_buf[state_i] = ch;
		state_i++;
		num2_state(fgetc(file_ptr));
		return;
	}

	if (state_i > 0) {
		state_i = 0;
		end_state(ch);
	} else {
		state_i = 0;
		pre_state(ch);
	}
}

void end_state(char ch) {
	printf("END");

	if (ch == ')') {
		int result = atoi(num1_buf) * atoi(num2_buf);
		sum += result;
		printf("=== %d ===", result);
	}

	state_i = 0;
	pre_state(fgetc(file_ptr));
}

void do_state(char ch) {
	printf("DO");

	char do_str[] = "do()";

	if (ch == do_str[state_i]) {
		if (state_i == 3) {
			printf("|YES|");
			state_i = 0;
			instr_enabled = true;
			pre_state(fgetc(file_ptr));
			return;
		} else {
			state_i++;
			do_state(fgetc(file_ptr));
			return;
		}
	} else if (state_i == 2 && ch == 'n') {
		state_i = 0;
		dont_state(ch);	
		return;
	}
	
	state_i = 0;
	pre_state(ch);
}

void dont_state(char ch) {
	printf("DONT");

	char dont_str[] = "n't()";

	if (ch == dont_str[state_i]) {
		if (state_i == 4) {
			printf("|NO|");
			state_i = 0;
			instr_enabled = false;
			pre_state(fgetc(file_ptr));
			return;
		} else {
			state_i++;
			dont_state(fgetc(file_ptr));
			return;
		}
	}
	
	state_i = 0;
	pre_state(ch);
}

void read_file() {
	
	file_ptr = fopen(FILE_PATH, "r");
	
	if (file_ptr == NULL) {
		printf("Couldn't read file.");
		return;
	}
	
	printf("FILE BEGIN: \n");
	
	char ch = fgetc(file_ptr);
	pre_state(ch);

	printf("\nEND OF FILE.\n");
	
	fclose(file_ptr);
}

int main () {
	read_file();
	printf("\n SUM: %d \n", sum);
}