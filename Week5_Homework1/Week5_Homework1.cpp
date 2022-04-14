/*
* Description - Minesweeper game
*/

#include <iostream>
#include <cstdlib>
#include <string.h>

#define MAX_ROWVALUE 10

using namespace std;

//check the . point
int search_pointaxis(char** origin_arr, char** current_arr, int x, int y) {

	int count = 0;

	//set the origin_arr based on bomb location
	for (int n = x - 1; n <= x + 1; n++) {
		for (int o = y - 1; o <= y + 1; o++) {
			if (n < 0 || n > 9 || o < 0 || o > 9) {
				//protect the underflow
			}
			else {
				if (origin_arr[n][o] == '.' && current_arr[n][o] == '#') {
					count++;
					current_arr[n][o] = '.';
					count += search_pointaxis(origin_arr, current_arr, n, o);

				}
			}
		}
	}

	return count;
}

void print_minetable(char** origin_arr, char** current_arr, int noselect_cell) {

	//tmp function - answer

	for (int i = 0; i < MAX_ROWVALUE; i++) {
		cout << i << " ";
	}

	cout << "\n--------------------" << endl;

	int cell_count = 0;

	for (int i = 0; i < MAX_ROWVALUE; i++) {
		for (int j = 0; j < MAX_ROWVALUE; j++) {
			cout << origin_arr[i][j] << " ";
			cell_count++;
		}
		cout << " | " << i << endl;
	}

	cout << "\n\n" << endl;

	//Real Game-panel start


	for (int i = 0; i < MAX_ROWVALUE; i++) {
		cout << i << " ";
	}

	cout << "\n--------------------" << endl;

	cell_count = 0;

	for (int i = 0; i < MAX_ROWVALUE; i++) {
		for (int j = 0; j < MAX_ROWVALUE; j++) {
			cout << current_arr[i][j] << " ";
			cell_count++;
		}
		cout << " | " << i << endl;
	}

	//input mine-free cell

	string input_cell = ""; //user selected cell variable

	cout << "Choose one of " << noselect_cell << " mine-free cells : ";
	cin >> input_cell;

	int select_cell = atoi(input_cell.c_str()); //type conversion string -> int

	while (select_cell >= 100 || select_cell <= 0) { //if range is not 1~99, 0 value is atoi failure ret code is 0
		if (input_cell.compare("0") == 0) //if 0 value is real "0"
			break;
		cout << "Choose again (Enter Q if you want to quit.): ";
		cin >> input_cell;
		if (strcmp(input_cell.c_str(), "Q") == 0) {
			return;
		}

		select_cell = atoi(input_cell.c_str());
	}

	int x, y; //axis of input value

	x = select_cell / 10;
	y = select_cell - (x * 10);

	if (origin_arr[x][y] == 'B') { //if user input point is bomb?
		cout << "BOOM! Game Over." << endl;
	}
	else if (current_arr[x][y] != '#') { //if user input is duplicate?
		print_minetable(origin_arr, current_arr, noselect_cell);
	}
	else if (origin_arr[x][y] == '.') { //if user input is . -> recursive function required
		int recursive_cellcount = search_pointaxis(origin_arr, current_arr, x, y);
		noselect_cell = noselect_cell - recursive_cellcount;
		print_minetable(origin_arr, current_arr, noselect_cell);
	}
	else if (noselect_cell == 0) {
		cout << "Congratulations! You cleared the game." << endl;
	}
	else { //else condition
		current_arr[x][y] = origin_arr[x][y];
		noselect_cell--;
		print_minetable(origin_arr, current_arr, noselect_cell);
	}
}

int main(void) {
	int game_seed_value; //game seed value variable
	int noselect_cell = 80; //not selected cell count - default is 80
	cout << "Please specify the game seed number : ";
	cin >> game_seed_value; //input the game seed number
	srand(game_seed_value); //deploy based on input_seed_value

	//set the array of origin_arr, current_arr, and randomaxis_arr
	char** origin_arr = new char* [9];
	char** current_arr = new char* [9];
	int* randomaxis_arr = new int[19];

	//initialize the arrays
	for (int n = 0; n < MAX_ROWVALUE; n++) {
		origin_arr[n] = new char[n];
		current_arr[n] = new char[n];
	}

	int random_count = 0; //random count
	bool exist_check[100] = { false, }; //check duplicate value

	while (random_count < 20) {
		int rv = rand() % 100; //random value range as 0~99
		if (exist_check[rv] == false) { //if this value is init?
			exist_check[rv] = true;
			randomaxis_arr[random_count] = rv;
			++random_count;
		}
	}

	//initialize the array current_arr and origin_arr
	for (int i = 0; i < MAX_ROWVALUE; i++) {
		for (int j = 0; j < 10; j++) {
			current_arr[i][j] = '#';
			origin_arr[i][j] = '.';
		}
	}

	//set the bomb based on pre-created randomaxis
	for (int k = 0; k < 20; k++) {
		int x = randomaxis_arr[k] / 10;
		int y = randomaxis_arr[k] - (x * 10);

		origin_arr[x][y] = 'B';

	}

	char count = '0';

	//set the origin_arr based on bomb location
	for (int l = 0; l < MAX_ROWVALUE; l++) {
		for (int m = 0; m < MAX_ROWVALUE; m++) {
			if (origin_arr[l][m] != 'B') {
				for (int n = l - 1; n <= l + 1; n++) {
					for (int o = m - 1; o <= m + 1; o++) {
						if (n < 0 || n > 9 || o < 0 || o > 9) {
							//protect the underflow
						}
						else {
							if (origin_arr[n][o] == 'B') {
								count++;
							}
						}
					}
				}

				if (count != '0')
					origin_arr[l][m] = count;

				count = '0';
			}
		}
	}

	print_minetable(origin_arr, current_arr, noselect_cell);

	return 0;
}
