#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "day1_input.txt"

int list1[1000];
int list2[1000];

int dist_list[1000];

char id_buffer[] = "00000";

int read_file() {
	
	FILE *file_ptr;
	
	char ch;
	
	file_ptr = fopen(FILE_NAME, "r");
	
	if (file_ptr == NULL) {
		printf("file can't be opened.\n");
		return EXIT_FAILURE;
	}

	printf("file content is: \n\n");
	
	int ch_index = 0;
	int list_index = 0;
	int line_index = 0;
	while (ch != EOF) {
		ch = fgetc(file_ptr);
		if (ch == ' ') {
			printf(" ");
			list_index = 1;
			ch_index = 0;
		} else if (ch == '\n') {
			printf("\n");
			list_index = 0;
			ch_index = 0;
			line_index++;
		} else {
			id_buffer[ch_index] = ch;
			if (ch_index == 4) {
				int id = atoi(id_buffer);
				if (list_index == 0) {
					list1[line_index] = id;
				} else if (list_index == 1) {
					list2[line_index] = id;
				}
				printf("%d", id);
			}
			ch_index++;
		}
	}
	
	printf("\nEOF!\n");
	
	fclose(file_ptr);
	return 0;
}

void print_lists() {
	for (int i = 0; i < 1000; i++) {
		printf("%d   ", list1[i]);
		printf("%d", list2[i]);
		printf("  |  %d\n", dist_list[i]);
	}
}

void bubble_sort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

int calc_dists() {
	int acum_dist = 0;
	for (int i = 0; i < 1000; i++) {
		int dist = abs(list1[i] - list2[i]);
		dist_list[i] = dist;
		acum_dist += dist;
	}
	return acum_dist;
}

int find_occurances(int arr[], int id) {
	int occurances = 0;
	for (int i = 0; i < 1000; i++) {
		if (arr[i] == id) {
			occurances++;
		} else if (occurances != 0) {
			return occurances;
		}
	}
	return occurances;
}

int calc_simularities() {
	int acum_simularity = 0;	
	for (int i = 0; i < 1000; i++) {
		acum_simularity += list1[i] * find_occurances(list2, list1[i]);
	}
	return acum_simularity;
}

int main() {
	read_file();
	bubble_sort(list1, 1000);
	bubble_sort(list2, 1000);
	int total_dist = calc_dists();
	int total_simularity = calc_simularities();
	print_lists();
	printf("\n\nTotal distance: %d", total_dist);
	printf("\n\nTotal simularity: %d", total_simularity);
}
