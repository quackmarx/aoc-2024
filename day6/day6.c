#include <stdio.h>

#define FILE_PATH "day6.input"
#define MAP_X 130 
#define MAP_Y 130 

char map[MAP_X][MAP_Y];

int pos_x;
int pos_y;

enum Direction { UP, RIGHT, DOWN, LEFT };
enum Direction dir = UP;

int pos_count = 1;

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
			map[x][y]= ch;
			if(ch == '^') {
				pos_x = x;
				pos_y = y;
			}
			x++;
		}
	}

	fclose(pFile);
}

void move_by(int x, int y) {
	map[pos_x][pos_y] = 'X';
	pos_x += x;
	pos_y += y;
	map[pos_x][pos_y] = '^';
}

void get_move(int *mx, int *my) {
	switch (dir)
	{
	case UP:
		*mx = 0;
		*my = -1; 
		break;
	case RIGHT:
		*mx = 1;
		*my = 0;
		break;
	case DOWN:
		*mx = 0;
		*my = 1;
		break;
	case LEFT:
		*mx = -1;
		*my = 0;
		break;
	
	default:
		printf("\nWHAT?!");
		break;
	}
}

void turn() {
	if (dir == 3) { dir = 0; }
	else { dir++; }
}

int move() {
	int move_x = 0;
	int move_y = 0;
	
	get_move(&move_x, &move_y);

	char next_ch = map[pos_x + move_x][pos_y + move_y];

	if (pos_x + move_x == MAP_X || pos_y + move_y == MAP_Y) {
		printf("\nTHE END!\n");
		map[pos_x][pos_y] = 'X';
		return 1;
	} else if (next_ch == '#') {
		turn();
		get_move(&move_x,&move_y);
		next_ch = map[pos_x + move_x][pos_y + move_y];
	}
	
	if (next_ch != 'X') {
		pos_count++;
	}

	move_by(move_x, move_y);
	return 0;
}

void print_map() {
	for (size_t y = 0; y < MAP_Y; y++)
	{
		for (size_t x = 0; x < MAP_X; x++)
		{
			printf("%c", map[x][y]);
		}
		printf("\n");
	}
	
	printf("\n");
}

int main() {
	read_file();
	print_map();
	while (move() == 0) {
		// Still within map
	}
	print_map();
	printf("POS COUNT: %d\n", pos_count);
}