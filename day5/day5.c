#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RULES_PATH "rules.txt"
#define UPDATES_PATH "updates.txt"

#define RULES_LENGTH 1176 
#define UPDATES_LENGTH 185 
#define UPDATES_BUF 30

int xRules[RULES_LENGTH];
int yRules[RULES_LENGTH];
int updates[UPDATES_LENGTH][UPDATES_BUF];

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

void read_updates() {
	FILE *pFile;

	pFile = fopen(UPDATES_PATH, "r");
	if (pFile == NULL) {
		printf("\nCouldn't read file.\n");
		return;
	}
	
	for (size_t i = 0; i < UPDATES_LENGTH; i++)
	{
		for (size_t j = 0; j < UPDATES_BUF; j++)
		{
			updates[i][j] = -1;
		}
		
	}
	
	char *line = NULL;
	size_t len = 0;
	
	int i = 0;
	while (getline(&line, &len, pFile) != -1) {
		int x;
		int n;
		int j = 0;
		while (sscanf(line + n * j,"%d,%n", &x, &n) == 1) {
			printf("%d ", x);
			updates[i][j] = x;
			j++;
		}
		printf("\n");
		i++;
	}
	
	printf("END OF FILE.\n");
	
	pclose(pFile);
	if (line) {
		free(line);
	}
	
}

bool updt_has(int arr[], int x, int depth) {
	for (size_t i = 0; i < UPDATES_BUF; i++)
	{
		if (arr[i] == -1 || i == depth) {
			break;
		}
		if (arr[i] == x) {
			return true;
		}
	}
	
	return false;
}

bool eval_update(int updt[]) {
	for (size_t i = 0; i < UPDATES_BUF; i++)
	{
		if (updt[i] == -1) {
			break;
		}
		// Search for matching rules
		for (size_t j = 0; j < RULES_LENGTH; j++)
		{
			// If rule found
			if (yRules[j] == updt[i]) {
				// If other page is not in update we continue
				if (!updt_has(updt, xRules[j], UPDATES_BUF)) {
					continue;
				}
				// Otherwise, if page not before
				if (!updt_has(updt, xRules[j], i)) {
					return false;
				}
			}
		}
		
	}
	
	return true;
}

int get_mid(int updt[]) {
	int len = 0;
	for (size_t i = 0; i < UPDATES_BUF; i++)
	{
		if (updt[i] == -1) {
			break;
		}
		len++;
	}
	
	return len / 2;
}

int main () {
	read_rules();
	read_updates();
	int mid_page_sum = 0;
	for (size_t i = 0; i < UPDATES_LENGTH; i++)
	{
		bool is_correct = eval_update(updates[i]);
		if (is_correct) {
			int mid = get_mid(updates[i]);
			mid_page_sum += updates[i][mid];
			printf("%d\n", updates[i][mid]);
		}
	}
	
	printf("\nMID PAGE SUM: %d\n", mid_page_sum);
	
}