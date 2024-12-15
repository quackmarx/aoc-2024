#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILE_PATH "day9.test"

int *pDisk;
int diskLen;

void read_file() {
	FILE *pFile;

	pFile = fopen(FILE_PATH, "r");
	if (pFile == NULL) {
		printf("\nCouldn't open file.\n");
		return;
	}
	
	diskLen = 0;
	char ch = fgetc(pFile);
	while(ch != EOF) {
		diskLen += ch - '0';
		ch = fgetc(pFile);
	}

	printf("%d is the disk length.\n", diskLen);
	
	pDisk = (int*)malloc(diskLen * sizeof(int));
	
	rewind(pFile);
	
	ch = fgetc(pFile);
	int fI = 0;
	int dI = 0;
	int blckI = 0;
	while (ch != EOF) {
		int val = -1;
		if (fI % 2 == 0) {
			val = blckI;
			blckI++;
		}
		for (size_t j = 0; j < ch - '0'; j++)
		{
			pDisk[dI] = val;
			dI++;
		}
		fI++;
		ch = fgetc(pFile);
	}
	
	pclose(pFile);
}

void print_disk() {
	for (size_t i = 0; i < diskLen; i++)
	{
		if (pDisk[i] != -1) {
			printf("%d ", pDisk[i]);
		} else {
			printf(".");
		}
	}
	printf("\n");
}

int find_empty() {
	for (size_t i = 0; i < diskLen; i++)
	{
		if (pDisk[i] == -1) {
			return i;
		}
	}
	printf("\nNO EMPTY SPACE?\n");
	return -1;
}

void shift_block(int to, int end) {
	pDisk[to] = pDisk[end - 1];
	pDisk[end - 1] = -1;
}

bool has_gap() {
	bool space = false;
	for (size_t i = 0; i < diskLen; i++)
	{
		if (pDisk[i] == -1) {
			space = true;
		} else if (space) {
			return true;
		}
	}
	return false;
}

void move_blocks() {
	int end = diskLen;
	while (has_gap()) {
		shift_block(find_empty(), end);
		end--;
	}
}

int main () {
	read_file();

	print_disk();
	
	move_blocks();
	
	print_disk();
	
	long int checksum = 0;
	for (size_t i = 0; i < diskLen; i++)
	{
		if (pDisk[i] == -1) {
			continue;
		}
		checksum += i * pDisk[i];
	}
	
	printf("FILESYSTEM CHECKSUM: %ld\n", checksum);

	free(pDisk);
}