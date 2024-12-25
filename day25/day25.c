#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_PATH "day25.test"

int *locks;
int lockLen = 0;
int *keys;
int keyLen = 0;

void read_file(char *fname) {
	FILE *pFile = fopen(fname, "r");
	if (pFile == NULL) {
		printf("ERR: Couldn't read file.\n");
		return;
	}
	
	char *line = NULL;
	size_t llen;
	int li = 0;

	// Count locks and keys
	while(getline(&line, &llen, pFile) != -1) {
		if (strcmp(line, "\n") == 0) {
			li = 0;
			continue;
		}
		if (li == 0) {
			if (line[0] == '#') {
				lockLen++;
			} else if (line[0] == '.') {
				keyLen++;
			}
		}
		li++;
	}
	
	printf("%d locks found.\n%d keys found.\n", lockLen, keyLen);
	
	// Allocate locks and keys
	locks = calloc((lockLen * 5), sizeof(int));
	keys = calloc((keyLen * 5), sizeof(int));
	
	li = 0;
	rewind(pFile);

	// Fill locks and keys
	char type = '0';
	int lock = 0;
	int key = 0;
	while (getline(&line, &llen, pFile) != -1) {
		printf("%s", line);

		if (strcmp(line, "\n") == 0) {
			li = 0;
			lock += type == 'l';
			keys += type == 'k';
			continue;
		}
		if (li == 0) {
			if (line[0] == '#') {
				type = 'l';
			} else if (line[0] == '.') {
				type = 'k';
			}
		} else {
			if (type == 'l') {
				for (size_t i = 0; i < 5; i++) {
					if (line[i] == '#') {
						locks[lock * 5 + i] = li;
					}
				}
			} else if (type == 'k') {
				for (size_t i = 0; i < 5; i++) {
					if (line[i] == '#') {
						if (keys[key * 5 + i] < 6 - li) {
							//keys[key * 5 + i] = 6 - li;
						}
					}
				}
			}
		}
		
		li++;
	}
	
	fclose(pFile);
}

int main() {
	read_file(INPUT_PATH);
	for (size_t i = 0; i < lockLen; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			printf("%d ", locks[i * 5 + j]);
		}
		printf("\n");
	}
	for (size_t i = 0; i < keyLen; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			printf("%d ", keys[i * 5 + j]);
		}
		printf("\n");
	}
	
	free(locks);
	// Why u no?
	free(keys);
}