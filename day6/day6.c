#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define FILE_PATH "day6.input"
#define MAP_X 130 
#define MAP_Y 130 

char map[MAP_X][MAP_Y];

int pos_x;
int pos_y;

int start_pos_x;
int start_pos_y;

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
				start_pos_x = pos_x;
				start_pos_y = pos_y;
			}
			x++;
		}
	}

	fclose(pFile);
}

void move_by(int x, int y) {
	if (map[pos_x][pos_y] != 'O') {
		map[pos_x][pos_y] = 'X';
	}
	pos_x += x;
	pos_y += y;
	if (map[pos_x][pos_y] != 'O') {
		map[pos_x][pos_y] = '^';
	}
}

void get_move(int *mx, int *my, enum Direction d) {
	switch (d)
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

void turn(enum Direction *dP) {
	if (*dP == 3) { *dP = 0; }
	else { *dP += 1; }
}

int move() {
	int move_x = 0;
	int move_y = 0;
	
	get_move(&move_x, &move_y, dir);

	char next_ch = map[pos_x + move_x][pos_y + move_y];

	if (pos_x + move_x == MAP_X || pos_x + move_x < 0 || pos_y + move_y == MAP_Y || pos_y + move_y < 0) {
		printf("\nTHE END!\n");
		map[pos_x][pos_y] = 'X';
		return 1;
	} else if (next_ch == '#') {
		turn(&dir);
		get_move(&move_x,&move_y, dir);
		next_ch = map[pos_x + move_x][pos_y + move_y];
	}
	
	if (next_ch != 'X') {
		pos_count++;
	}

	move_by(move_x, move_y);
	return 0;
}

// Simulates walking around
// If reaches starting pos with same dir we've made a loop
// If times out or reaches edge of map, not so much
bool place_obst() {
	enum Direction d = dir;
	turn(&d);
	int px = pos_x;
	int py = pos_y;
	
	int mx = 0;
	int my = 0;
	get_move(&mx, &my, d);
	
	int timeout = 90000;

	while(px + mx < MAP_X && py + my < MAP_Y && px + mx >= 0 && py + my >= 0) {
		if (map[px+mx][py+my] == '#') {
			turn(&d);
			get_move(&mx, &my, d);
		}
		px += mx;
		py += my;
		if (px == pos_x && py == pos_y && d == dir) {
			return true;
		}
		
		timeout--;
		if (timeout < 0) { break; }
	}
	
	return false;
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
	int obst_count = 0;
	while (move() == 0) {
		int mx, my;
		get_move(&mx, &my, dir);
		
		if (pos_x + mx == start_pos_x || pos_y + my == start_pos_y) {
			continue;
		}
		
		if (pos_x + mx < 0 || pos_x + mx == MAP_X || pos_y + my < 0 || pos_y + my == MAP_Y) {
			continue;
		}

		if (map[pos_x + mx][pos_y + my] != 'O' && map[pos_x + mx][pos_y + my] != '#') {
			if (place_obst()) {
				map[pos_x + mx][pos_y + my] = 'O';
				obst_count++;
				//print_map();
			}
		}
	}
	print_map();
	printf("OBST COUNT: %d\n", obst_count);
}