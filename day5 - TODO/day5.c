#include <stdio.h>

#define RULES_PATH "rules.txt"
#define UPDATES_PATH "updates.txt"

#define RULES_LENGTH 14
#define UPDATES_LENGTH 5

int xRules[RULES_LENGTH];
int yRules[RULES_LENGTH];

void read_rules() {
	FILE *pFile;

	pFile = fopen(RULES_PATH, "r");
	if (pFile == NULL) {
		printf("\nCouldn't read file.\n");
		return;
	}
	
	int x;
	int y;
	int i = 0;
	while (fscanf(pFile,"%d|%d", &x, &y) == 2) {
		printf("%d %d\n", x, y);
		xRules[i] = x;
		yRules[i] = y;
		i++;
	}
	
	printf("END OF FILE.\n");
	
	pclose(pFile);
	
}

void get_x_rules(int *arr, int y_rule) {
	for (int i = 0; i < RULES_LENGTH; i++)
	{
		if (yRules[i] == y_rule) {
			// Add xRules[i] to array
		}
	}
	
	// "return" array
}

int main () {
	read_rules();
}