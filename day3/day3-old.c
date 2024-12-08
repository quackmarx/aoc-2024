#include <stdio.h>
#include <stdbool.h>

#define FILE_PATH "input.txt"

enum State {
	PRE,
	NUM1,
	MID,
	NUM2,
	END
};

bool pre_state(char ch);
bool num1_state(char ch);
bool mid_state(char ch);
bool num2_state(char ch);
bool end_state(char ch);

bool (*state_ptr)(char);

int state_i = 0;

void switch_state(bool (*new_state)(char)) {
	state_ptr = new_state;
	state_i = 0;
}

bool pre_state(char ch) {
	printf("PRE");

	char mul[] = "mul";

	if (ch == mul[state_i]) {
		switch_state(&num1_state);
		return true;
	}
	return true;
}

bool num1_state(char ch) {
	printf("NUM1");
	
	switch_state(&mid_state);
	return true;
}

bool mid_state(char ch) {
	printf("MID");
	
	//if (ch == ',') {
	//	printf("%c", ch);
	//	state_ptr = &pre_state;
	//	return true;
	//}
	
	switch_state(&num2_state);
	return true;
}

bool num2_state(char ch) {
	printf("NUM2");

	switch_state(&end_state);
	return true;	
}

bool end_state(char ch) {
	printf("END");

	return true;
}

void read_file() {
	FILE *file_ptr;
	
	file_ptr = fopen(FILE_PATH, "r");
	
	if (file_ptr == NULL) {
		printf("Couldn't read file.");
		return;
	}
	
	printf("FILE BEGIN: \n");
	
	char ch;
	enum State state = PRE;
	state_ptr = &pre_state;

	ch = fgetc(file_ptr);
	while (ch != EOF) {
		bool proceed = (*state_ptr)(ch);
		if (proceed == true) {
			printf("%c", ch);
			ch = fgetc(file_ptr);
			state_i++;
		}
	}

	printf("\nEND OF FILE.\n");
	
	fclose(file_ptr);
}

int main () {
	read_file();
}