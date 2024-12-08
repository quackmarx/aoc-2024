#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILE_PATH "day2_input.txt"

int data[1000][10];

void read_file() {
	FILE *file_ptr;
	
	file_ptr = fopen(FILE_PATH, "r");
	
	if (file_ptr == NULL) {
		printf("File can't be opened.");
		return;
	}
	
	printf("FILE START: \n\n");

	char ch;
	char num_str[2];

	int report_i = 0;
	int level_i = 0;	
	while(ch != EOF) {
		ch = fgetc(file_ptr);

		if (ch == '\n') {
			data[report_i][level_i] = atoi(num_str);
			printf("%d\n", data[report_i][level_i]);
			num_str[0] = ' ';
			num_str[1] = ' ';
			level_i++;
			report_i++;
			level_i = 0;
		} else if (ch == ' ') {
			data[report_i][level_i] = atoi(num_str);
			printf("%d  ", data[report_i][level_i]);
			num_str[0] = ' ';
			num_str[1] = ' ';
			level_i++;
		} else if (num_str[0] == ' ') {
			num_str[0] = ch;
		} else {
			num_str[1] = ch;
		}
	}

	fclose(file_ptr);

	printf("\nFILE END.\n");
}

void print_arr(int *arr) {
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");	
}

void gen_deltas(int *deltas, int report[]) {
	for (int j = 0; j < 9; j++)
	{
		if (report[j + 1] == -1) {
			deltas[j] = 99999;
			break;
		}
		
		deltas[j] = report[j + 1] - report[j];
		//printf("%d ", deltas[j]);
	}
	//printf("\n");
}

bool eval_report(int report[]) {
	
	int deltas[10];
	gen_deltas(deltas, report);

	bool ascending = true;	
	bool descending = true;
	bool within_range = true;

	int dir_problem_i = -1;
	int range_problem_i = -1;

	for (int j = 0; j < 10; j++)
	{
		//printf("%d ", report[j]);

		if (deltas[j] == 99999) {
			break;
		}
		if (deltas[j] > 0) {
			descending = false;
			if (ascending == false) {
				dir_problem_i = j;
			}
		} else if (deltas[j] < 0) {
			ascending = false;
			if (descending == false) {
				dir_problem_i = j;
			}
		}

		if (abs(deltas[j]) < 1 || abs(deltas[j]) > 3) {
			within_range = false;
			range_problem_i = j;
		}
	}

	if (within_range == false) {
		print_arr(deltas);
		print_arr(report);
		printf("PROBLEM: range at %d\n", range_problem_i);
		return false;
	}

	if (ascending == false && descending == false) {
		print_arr(deltas);
		print_arr(report);
		printf("PROBLEM: asc/desc at %d\n", dir_problem_i);
		return false;
	}

	//printf("\nSAFE!\n");
	return true;
}

bool problem_dampener(int report[]) {
	printf("Attempting damping:\n");

	int damp_rep[10];
	for (int i = 0; i < 10; i++)
	{
		int damp_j = 0;
		for (int j = 0; j < 10; j++)
		{
			if (j != i) {
				damp_rep[damp_j] = report[j];
				damp_j++;
			}
		}
		
		if (eval_report(damp_rep)) {
			return true;
		}
	}
	
	return false;
}

int main () {
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 10; j++)
		{
			data[i][j] = -1;
		}
	}

	read_file();

	int safe_count = 0;	
	int ln_count = 0;
	for (int i = 0; i < 1000; i++)
	{
		printf("\n-------- LINE %d --------\n", ln_count);
		if (eval_report(data[i])) {
			safe_count++;
		} else {
			if (problem_dampener(data[i])) {
				safe_count++;
			}
		}
		ln_count++;
	}
	
	printf("\n\n Safe count: %d", safe_count);
	
}