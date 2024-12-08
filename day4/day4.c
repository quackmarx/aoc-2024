#include <stdio.h>
#include <stdbool.h>

#define FILE_PATH "input.txt"

char matrix[140][140];

void read_file() {
	FILE *pFile;

	pFile = fopen(FILE_PATH, "r");

	if (pFile == NULL) {
		printf("\nCouldn't read file.\n");
		return;
	}
	
	char ch;
	int x = 0;
	int y = 0;
	while (ch != EOF) {
		ch = fgetc(pFile);
		if (ch == '\n') {
			x = 0;
			y++;
		} else {
			matrix[x][y] = ch;
			x++;
		}
	}
	
	fclose(pFile);
}

void print_matrix() {
	for (int y = 0; y < 140; y++)
	{
		printf("%d|",y);
		for (int x = 0; x < 140; x++)
		{
			printf("%c", matrix[x][y]);
		}
		printf("\n");
	}
	
}

int xmas_at(int x, int y) {
	
	printf("Searching at %c\n", matrix[x][y]);
	
	int count = 0;
	char XMAS[] = "XMAS";
	
	// Check up
	for (int i = 0; i < 4; i++)
	{
		if (y - i < 0) {
			break;
		}
		char ch = matrix[x][y - i];
		if (ch != XMAS[i]) {
			break;
		}
		printf("%c", ch);
		if (i == 3) {
			count++;
			printf("%d", count);
		}
	}

	// Check down
	for (int i = 0; i < 4; i++)
	{
		if (y + i >= 140) {
			break;
		}
		char ch = matrix[x][y + i];
		if (ch != XMAS[i]) {
			break;
		}
		printf("%c", ch);
		if (i == 3) {
			count++;
			printf("%d", count);
		}
	}

	// Check right
	for (int i = 0; i < 4; i++)
	{
		if (x + i >= 140) {
			break;
		}
		char ch = matrix[x + i][y];
		if (ch != XMAS[i]) {
			break;
		}
		printf("%c", ch);
		if (i == 3) {
			count++;
			printf("%d", count);
		}
	}
	
	// Check left
	for (int i = 0; i < 4; i++)
	{
		if (x - i < 0) {
			break;
		}
		char ch = matrix[x - i][y];
		if (ch != XMAS[i]) {
			break;
		}
		printf("%c", ch);
		if (i == 3) {
			count++;
			printf("%d", count);
		}
	}
		
	// Check up right
	for (int i = 0; i < 4; i++)
	{
		if (x + i >= 140 | y - i < 0) {
			break;
		}
		char ch = matrix[x + i][y - i];
		if (ch != XMAS[i]) {
			break;
		}
		printf("%c", ch);
		if (i == 3) {
			count++;
			printf("%d", count);
		}
	}
	
	// Check up left
	for (int i = 0; i < 4; i++)
	{
		if (x - i < 0 | y - i < 0) {
			break;
		}
		char ch = matrix[x - i][y - i];
		if (ch != XMAS[i]) {
			break;
		}
		printf("%c", ch);
		if (i == 3) {
			count++;
			printf("%d", count);
		}
	}

	// Check down left
	for (int i = 0; i < 4; i++)
	{
		if (x - i < 0 | y + i >= 140) {
			break;
		}
		char ch = matrix[x - i][y + i];
		if (ch != XMAS[i]) {
			break;
		}
		printf("%c", ch);
		if (i == 3) {
			count++;
			printf("%d", count);
		}
	}

	// Check down right
	for (int i = 0; i < 4; i++)
	{
		if (x + i >= 140 | y + i >= 140) {
			break;
		}
		char ch = matrix[x + i][y + i];
		if (ch != XMAS[i]) {
			break;
		}
		printf("%c", ch);
		if (i == 3) {
			count++;
			printf("%d", count);
		}
	}
	
	return count;
}

int x_mas_at(int x, int y) {
	
	printf("\nSearching at %c: ", matrix[x][y]);
	
	int count = 0;
	char MAS[] = "MAS";
	char SAM[] = "SAM";
	bool is_MAS = true;
	bool is_SAM = true;
	bool line1 = false;
	bool line2 = false;
	
	// Check left->right up->down
	for (int i = 0; i < 3; i++)
	{
		int xi = x - 1 + i;
		int yi = y - 1 + i;
		if (xi < 0 | xi >= 140 | yi < 0 || yi >= 140) {
			is_SAM = false;
			is_MAS = false;
			break;
		}
		char ch = matrix[xi][yi];
		if (ch != MAS[i]) {
			is_MAS = false;
		}
		if (ch != SAM[i]) {
			is_SAM = false;
		}
		if (!is_SAM && !is_MAS) {
			break;
		}
		printf("%c", ch);
	}

	if (is_MAS) { line1 = true; }
	if (is_SAM) { line1 = true; }
	
	is_MAS = true;
	is_SAM = true;

	// Check right->left up->down
	for (int i = 0; i < 3; i++)
	{
		int xi = x + 1 - i;
		int yi = y - 1 + i;
		if (xi < 0 | xi >= 140 | yi < 0 || yi >= 140) {
			is_MAS = false;
			is_SAM = false;
			break;
		}
		char ch = matrix[xi][yi];
		if (ch != MAS[i]) {
			is_MAS = false;
		}
		if (ch != SAM[i]) {
			is_SAM = false;
		}
		if (!is_SAM && !is_MAS) {
			break;
		}
		printf("%c", ch);
	}
	
	if (is_MAS) { line2 = true; }
	if (is_SAM) { line2 = true; }
	
	if (line1 && line2) {
		count++;
		printf("   X%d",count);
	}
	
	return count;
}
int main () {
	read_file();
	print_matrix();
	int sum = 0;
	for (int y = 0; y < 140; y++)
	{
		for (int x = 0; x < 140; x++)
		{
			sum += x_mas_at(x,y);
		}
	}
	printf("\nX-MAS SUM: %d\n", sum);
	
}