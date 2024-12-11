#include <stdio.h>
#include <stdbool.h>

#define INPUT_PATH "day8.input"
#define MAP_SIZE 50 

char antens[MAP_SIZE][MAP_SIZE];
char annos[MAP_SIZE][MAP_SIZE];

void read_input () {
	FILE *pFile;
	pFile = fopen(INPUT_PATH, "r");
	if (pFile == NULL) {
		printf("Couldn't read file.\n");
		return;
	}
	
	char ch;
	int x = 0, y = 0;
	while (ch != EOF) {
		ch = fgetc(pFile);
		if (ch == '\n') {
			y++;
			x = 0;
			continue;
		}
		antens[x][y] = ch;
		annos[x][y] = '.';
		x++;
	}
	
	fclose(pFile);
}

void print_map (char map[MAP_SIZE][MAP_SIZE]) {
	for (size_t y = 0; y < MAP_SIZE; y++)
	{
		for (size_t x = 0; x < MAP_SIZE; x++)
		{
			printf("%c", map[x][y]);
		}
		printf("\n");
	}
}

bool find_antn (char antn, int* pX, int* pY, int xoff, int yoff) {
	for (size_t y = yoff; y < MAP_SIZE; y++)
	{
		for (size_t x = xoff; x < MAP_SIZE; x++)
		{
			if (antens[x][y] == antn) {
				*pX = x;
				*pY = y;
				return true;
			}
		}
		xoff = 0;
	}
	return false;
}

bool in_bounds(int x, int y) {
	return x >= 0 && y >= 0 && x < MAP_SIZE && y < MAP_SIZE;
}

void create_annos () {
	char antn;
	// loop over antennas
	for (size_t y = 0; y < MAP_SIZE; y++)
	{
		for (size_t x = 0; x < MAP_SIZE; x++)
		{
			antn = antens[x][y];
			if (antn == '.') {
				continue;
			}
			
			int mx = x, my = y;
			int xdist, ydist;
			while (find_antn(antn, &mx, &my, mx + 1, my)) {
				xdist = mx - x;
				ydist = my - y;
				//printf("xdist:%d|", xdist);
				//printf("ydist:%d|", ydist);
				if (in_bounds(x - xdist, y - ydist)) {
					annos[x - xdist][y - ydist] = '#';
				}
				if (in_bounds(mx + xdist, my + ydist)) {
					annos[mx + xdist][my + ydist] = '#';
				}
			}
		}
	}
}

void create_resonant_annos () {
	char antn;
	// loop over antennas
	for (size_t y = 0; y < MAP_SIZE; y++)
	{
		for (size_t x = 0; x < MAP_SIZE; x++)
		{
			antn = antens[x][y];
			if (antn == '.') {
				continue;
			}
			
			int mx = x, my = y;
			int xdist, ydist;
			while (find_antn(antn, &mx, &my, mx + 1, my)) {
				xdist = mx - x;
				ydist = my - y;
				int n = 0;
				while (in_bounds(x - xdist * n, y - ydist * n)) {
					annos[x - xdist * n][y - ydist * n] = '#';
					n++;
				}
				n = 0;
				while (in_bounds(mx + xdist * n, my + ydist * n)) {
					annos[mx + xdist * n][my + ydist * n] = '#';
					n++;
				}
			}
		}
	}
}

int main () {
	read_input();
	printf("ANTENNAS\n");
	print_map(antens);
	create_resonant_annos();
	printf("ANNOS\n");
	print_map(annos);
	int annocnt = 0;
	for (size_t y = 0; y < MAP_SIZE; y++)
		for (size_t x = 0; x < MAP_SIZE; x++)
			if (annos[x][y] == '#')
				annocnt++;
	printf("RESONANT ANTI-NODE COUNT: %d\n", annocnt);
}