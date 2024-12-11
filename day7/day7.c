#include <stdio.h>
#include <stdlib.h>

#define INPUT_PATH "day7.test"
#define LINE_COUNT 9

enum Operator { ADD, MUL };

struct Equa {
	int result;
	int *pNums;
	size_t numLen;
	enum Operator *pOps;
};

struct Equa equas[LINE_COUNT];

void read_input() {
	FILE *pFile;

	pFile = fopen(INPUT_PATH, "r");
	if (pFile == NULL) {
		printf("\nCouldn't read file.\n");
		return;
	}
	
	char *line = NULL;
	size_t len = 0;

	int i = 0;
	// loop over lines
	while (getline(&line, &len, pFile) != -1) {
		// get first number
		int result = 0;
		int n = 0;
		int offset = 0;
		if (sscanf(line, "%d:%n", &result, &n) != 1) {
			printf("Couldn't find result?\n");
			return;
		}
		offset += n;
		equas[i].result = result;
		printf("%d:", result);
		
		// count numbers (by spaces)
		int numCount = 0;
		for (size_t j = 0; line[j]; j++)
		{
			if (line[j] == ' ') {
				numCount++;
			}
		}
		
		equas[i].numLen = numCount;
		//equas[i].pNums = (int*) malloc(numCount * sizeof(int));
		//equas[i].pOps = (enum Operator*) malloc(numCount * sizeof(enum Operator));
		
		// loop over numbers in line
		int x = 0;
		int j = 0;
		while(sscanf(line + offset, "%d%n", &x, &n) != -1) {
			//equas[i].pNums[j] = x;
			printf(" %d", x);
			offset += n;
			j++;
		}
		printf("\n");
	}

	printf("END OF FILE.\n");
	fclose(pFile);
}

int eval (struct Equa *pEqua) {
	int total = 0;
	for (size_t i = 0; i < pEqua->numLen; i++)
	{
		printf("%lu|%d", i, pEqua->pNums[i]);
		total += pEqua->pNums[i];
	}
	printf("Total: %d\n", total);
	return total;
}

int main () {
	read_input();
	
	printf("-%d-\n", equas[1].result);
	//eval(&equas[0]);

	// free dat memory
	for (size_t i = 0; i < LINE_COUNT; i++)
	{
		//free(equas[i].pNums);
		//free(equas[i].pOps);
	}
	
}