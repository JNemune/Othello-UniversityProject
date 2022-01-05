#include <iostream>
#include <stdio.h>
#include <time.h>
#include <random>
// #include<Windows.h>
#include <unistd.h>
// #include<fcntl.h>
// #include<io.h>
using namespace std;
struct Map{
	int empty_cells;
	int turn; // 1 white va 2 black
	int map_size;
};
struct Player{
	int num_choice;
	int mode; // 0 for player -1 for easy cpu -2 for normal cpu
	int win_cells;
};

char menu(int n){
	char inp;
	// system("cls");
	system("clear");
	cout << "Welcome here, THE BEST OTHELLO GAME!" << endl;
	cout << "   Enter a number from the menu:" << endl;
	cout << "      1. New game" << endl;
	cout << "      2. Change the map size (current size: " << n << ")" << endl;
	cout << "      3. Demo" << endl;
	cout << "      4. Exit" << endl;
	cin >> inp;
	while (inp != '1' && inp != '2' && inp != '3' && inp != '4'){
		cout << "Invalid input. Enter '1', '2', '3' or '4':" << endl;
		cin >> inp;
	}
	return inp;
}

char menu2(){
	char inp;
	// system("cls");
	system("clear");
	cout << "Enter a number from the menu:" << endl;
	cout << "   1. Tow-player mode" << endl;
	cout << "   2. CPU: easy" << endl;
	cout << "   3. CPU: normal" << endl;
	cout << "   4. CPU: Hard"<<endl;
	cin >> inp;
	while (inp != '1' && inp != '2' && inp != '3' && inp!='4'){
		cout << "Invalid input. Enter '1', '2' or '3':" << endl;
		cin >> inp;
	}
	return inp;
}

void change_size(Map &map){
	cout << "Enter the map size (4 <= an even number <= 20): " << endl;
	cin >> map.map_size;
	while (map.map_size != 4 && map.map_size != 6 && map.map_size != 8 && map.map_size != 10 && map.map_size != 12 && map.map_size != 14 && map.map_size != 16 && map.map_size != 18 && map.map_size != 20){
		cout << "Invalid input" << endl;
		cout << "Enter the map size (4 <= an even number <= 20): " << endl;
		cin >> map.map_size;
	}
	map.empty_cells = map.map_size * map.map_size - 4;
	return;
}

void print(char field[][20], Map& map, Player& p1, Player& p2, int allowed[][2], int n) { // برای پرینت زمین ازین تابع استفاده میشود همینطور تعداد خانه ای خالی و تعداد خانه های تصاحب شده هر بازیکن را ثبت میکد
	// _setmode(_fileno(stdout), _O_U16TEXT);
	int i, j, k, flag;
	printf("     ");
	for (i = 0; i < map.map_size; i++) {
		printf(" %2d ", i);
	}
	printf("\n     ╔");
	for (i = 1; i < map.map_size; i++) {
		printf("═══╤");
	}
	printf("═══╗\n");
	for (i = 0; i < map.map_size; i++) {
		printf("   %2d║", i);
		for (j = 0; j < map.map_size; j++) {
			flag = 0;
			for (k = 0; k < n; k++) {
				if (i == allowed[k][0] && j == allowed[k][1]) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				printf(" . ");
			}
			else {
				printf(" %c ", field[i][j]);
			}
			j != map.map_size - 1 ? printf("│") : printf("║");
		}
		i != map.map_size - 1 ? printf("\n     ╟") : printf("\n     ╚");
		for (j = 1; j < map.map_size; j++) {
			i != map.map_size - 1 ? printf("───┼") : printf("═══╧");
		}
		i != map.map_size - 1 ? printf("───╢\n") : printf("═══╝\n");
	}
	map.empty_cells = 0;
	p1.win_cells = 0;
	p2.win_cells = 0;
	for (i = 0; i < map.map_size; i++) {
		for (j = 0; j < map.map_size; j++) {
			if (field[i][j] == ' ') {
				map.empty_cells++;
			}
			else if (field[i][j] == 'b') {
				p2.win_cells++;
			}
			else if (field[i][j] == 'w') {
				p1.win_cells++;
			}
		}
	}
	cout << endl;
	cout << "White's wins: " << p1.win_cells << "     ";
	cout << "Black's wins: " << p2.win_cells << endl
		<< endl;
	return;
}

// void print(char field[][20], Map &map, Player &p1, Player &p2, int allowed[][2], int n){
// 	int i, j;
// 	cout << "   ";
// 	for (i = 0; i < map.map_size; i++){
// 		cout.width(2);
// 		cout << left << i << ' ';
// 	}
// 	cout << endl;
// 	for (i = 0; i < map.map_size; i++){
// 		cout.width(2);
// 		cout << right << i << ' ';
// 		for (j = 0; j < map.map_size; j++){
// 			cout << field[i][j] << "  ";
// 		}
// 		cout << endl;
// 	}
// 	map.empty_cells = 0;
// 	p1.win_cells = 0;
// 	p2.win_cells = 0;
// 	for (i = 0; i < map.map_size; i++){
// 		for (j = 0; j < map.map_size; j++){
// 			if (field[i][j] == ' '){
// 				map.empty_cells++;
// 			}
// 			else if (field[i][j] == 'b'){
// 				p2.win_cells++;
// 			}
// 			else if (field[i][j] == 'w'){
// 				p1.win_cells++;
// 			}
// 		}
// 	}
// 	cout << endl;
// 	cout << "White's wins: " << p1.win_cells << "     ";
// 	cout << "Black's wins: " << p2.win_cells << endl
// 		 << endl;
// 	return;
// }

void reset(char field[][20], Map &map){
	int i, j;
	for (i = 0; i < map.map_size; i++)
		for (j = 0; j < map.map_size; j++){
			field[i][j] = ' ';
			if (i == map.map_size / 2 - 1 && j == map.map_size / 2 - 1)
				field[i][j] = 'w';
			if (i == map.map_size / 2 - 1 && j == map.map_size / 2)
				field[i][j] = 'b';
			if (i == map.map_size / 2 && j == map.map_size / 2 - 1)
				field[i][j] = 'b';
			if (i == map.map_size / 2 && j == map.map_size / 2)
				field[i][j] = 'w';
		}
	map.empty_cells = map.map_size * map.map_size - 4;
	map.turn = 1;
	return;
}

int search(char field[][20], Map map, int x, int y, int out[][2]){
	int i = x - 1, j = y - 1, c = 0;
	char _turn;
	if (field[x][y] == 'w'){
		_turn = 'b';
	}
	if (field[x][y] == 'b'){
		_turn = 'w';
	}
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn){
		i--;
		j--;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i + 1][j + 1] == _turn){
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x - 1;
	j = y;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn){
		i--;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i + 1][j] == _turn){
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x - 1;
	j = y + 1;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn){
		i--;
		j++;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i + 1][j - 1] == _turn){
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x;
	j = y - 1;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn){
		j--;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i][j + 1] == _turn){
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x;
	j = y + 1;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn){
		j++;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i][j - 1] == _turn){
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x + 1;
	j = y - 1;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn){
		i++;
		j--;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i - 1][j + 1] == _turn){
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x + 1;
	j = y;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn){
		i++;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i - 1][j] == _turn){
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x + 1;
	j = y + 1;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn){
		i++;
		j++;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i - 1][j - 1] == _turn){
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	return c;
}

void show_status(char field[][20], int out[][2], Map map, Player &p1,
				 Player &p2){
	int i, j, k, l, c = 0, c2 = 0, flag, pre_out[8][2], pre_out_num, out2[400][2] = {0};
	char turn;
	if (map.turn == 1){
		turn = 'w';
	}
	if (map.turn == 2){
		turn = 'b';
	}
	for (i = 0; i < map.map_size; i++){
		for (j = 0; j < map.map_size; j++){
			if (field[i][j] == 'w' || field[i][j] == 'b'){
				pre_out_num = search(field, map, i, j, pre_out);
				for (k = 0; k < pre_out_num; k++){
					flag = 0;
					if (field[i][j] == turn){
						for (l = 0; l < c; l++){
							if (out[l][0] == pre_out[k][0] && out[l][1] == pre_out[k][1]){
								flag = 1;
								break;
							}
						}
					}
					else{
						for (l = 0; l < c2; l++){
							if (out2[l][0] == pre_out[k][0] && out2[l][1] == pre_out[k][1]){
								flag = 1;
								break;
							}
						}
					}
					if (flag == 0){
						if (field[i][j] == turn){
							out[c][0] = pre_out[k][0];
							out[c][1] = pre_out[k][1];
							c++;
						}
						else{
							out2[c2][0] = pre_out[k][0];
							out2[c2][1] = pre_out[k][1];
							c2++;
						}
					}
				}
			}
		}
	}
	if (map.turn == 1){
		p1.num_choice = c;
		p2.num_choice = c2;
	}
	else{
		p1.num_choice = c2;
		p2.num_choice = c;
	}
	return;
}

int check_ok(int out[], int allowed[][2], int n){
	int i, flag = 0;
	cin >> out[0];
	cin >> out[1];
	if (out[0] == -1){
		return 0;
	}
	if (out[0] == -2){
		return 1;
	}
	for (i = 0; i < n; i++){
		if (out[0] == allowed[i][0] && out[1] == allowed[i][1]){
			flag = 1;
			break;
		}
	}
	while (flag == 0){
		cout << "Invalid input:" << endl;
		cin >> out[0];
		cin >> out[1];
		for (i = 0; i < n; i++){
			if (out[0] == allowed[i][0] && out[1] == allowed[i][1]){
				flag = 1;
				break;
			}
		}
	}
	return 2;
}

void cpu_easy(int out[], int allowed[][2], int n){
	int x = rand() % n;
	// sleep(3);
	// Sleep(3000);
	out[0] = allowed[x][0];
	out[1] = allowed[x][1];
	return;
}

void update_field(char field[][20], int move[], Map map){
	int i=move[0], j=move[1], m, n;
	char turn, _turn;
	if (map.turn == 1){
		turn = 'w';
		_turn = 'b';
	}
	if (map.turn == 2){
		turn = 'b';
		_turn = 'w';
	}
	field[i][j] = turn;
	m = i - 1;
	n = j - 1;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn){
		m--;
		n--;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m + 1][n + 1] == _turn){
		while (m != i || n != j){
			field[m][n] = turn;
			m++;
			n++;
		}
	}
	m = i - 1;
	n = j;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn){
		m--;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m + 1][n] == _turn){
		while (m != i || n != j){
			field[m][n] = turn;
			m++;
		}
	}
	m = i - 1;
	n = j + 1;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn){
		m--;
		n++;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m + 1][n - 1] == _turn){
		while (m != i || n != j){
			field[m][n] = turn;
			m++;
			n--;
		}
	}
	m = i;
	n = j - 1;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn){
		n--;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m][n + 1] == _turn){
		while (m != i || n != j){
			field[m][n] = turn;
			n++;
		}
	}
	m = i;
	n = j + 1;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn){
		n++;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m][n - 1] == _turn){
		while (m != i || n != j){
			field[m][n] = turn;
			n--;
		}
	}
	m = i + 1;
	n = j - 1;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn){
		m++;
		n--;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m - 1][n + 1] == _turn){
		while (m != i || n != j){
			field[m][n] = turn;
			m--;
			n++;
		}
	}
	m = i + 1;
	n = j;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn){
		m++;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m - 1][n] == _turn){
		while (m != i || n != j){
			field[m][n] = turn;
			m--;
		}
	}
	m = i + 1;
	n = j + 1;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn){
		m++;
		n++;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m - 1][n - 1] == _turn){
		while (m != i || n != j){
			field[m][n] = turn;
			m--;
			n--;
		}
	}
}

void cpu_normal(char field[][20], Map map, int out[], int allowed[][2], int n){
	char test_field[20][20]={'\0'}, turn; int i, j, k, max, compare[400]={0}, pre=0, pass;
	turn=map.turn==1?'w':'b';
	for(i=0; i<map.map_size; i++){
		for(j=0; j<map.map_size; j++){
			if(field[i][j]==turn){
				pre++;
			}
			test_field[i][j]=field[i][j];
		}
	}
	for(k=0; k<n; k++){
		pass=0;
		update_field(test_field, allowed[k], map);
		for(i=0; i<map.map_size; i++){
			for(j=0; j<map.map_size; j++){
				if(test_field[i][j]==turn){
					pass++;
				}
				test_field[i][j]=field[i][j];
			}
		}
		compare[k]=pass;
	}
	max=0;
	for(i=0; i<n; i++){
		if(compare[i]>compare[max]){
			max=i;
		}
	}
	out[0]=allowed[max][0];
	out[1]=allowed[max][1];
	// sleep(3);
	// Sleep(3000);
	return;
}

void cpu_hard(char field[][20], Map map, int out[], int allowed[][2], int n) { // این تابع برای هر یک از لایه های بازی با توجه به الگوریتم یادگیری ماشین که فایل ان با نام 
// ai_main.cpp
// ذخیره شده است ارزش گذاری میکند یعنی هر مهره مکان خاصی ارزش خاصی دارد
	// sleep(3);
	// Sleep(3000);
	char test_field[20][20] = { '\0' }, turn; int i, j, k, max, compare[400] = { 0 }, pre = 0, pass;
	turn = map.turn == 1 ? 'w' : 'b';
	for (i = 0; i < map.map_size; i++) {
		for (j = 0; j < map.map_size; j++) {
			if (field[i][j] == turn) {
				if (i == 0 || i == map.map_size - 1 || j == 0 || j == map.map_size - 1) {
					if ((i == 0 && (j == 0 || j == map.map_size - 1)) || (i == map.map_size - 1 && (j == 0 || j == map.map_size - 1))) {
						pre++;
					}
					pre += 2;
				}
				else pre++;
			}
			test_field[i][j] = field[i][j];
		}
	}
	for (k = 0; k < n; k++) {
		pass = 0;
		update_field(test_field, allowed[k], map);
		for (i = 0; i < map.map_size; i++) {
			for (j = 0; j < map.map_size; j++) {
				if (test_field[i][j] == turn) {
					if (i == 0 || i == map.map_size - 1 || j == 0 || j == map.map_size - 1) {
						if ((i == 0 && (j == 0 || j == map.map_size - 1)) || (i == map.map_size - 1 && (j == 0 || j == map.map_size - 1))) {
							pass++;
						}
						pass += 2;
					}
					else pass++;
				}
				test_field[i][j] = field[i][j];
			}
		}
		compare[k] = pass;
	}
	max = 0;
	for (i = 0; i < n; i++) {
		if (compare[i] > compare[max]) {
			max = i;
		}
	}
	out[0] = allowed[max][0];
	out[1] = allowed[max][1];
	return;
}

int check_size(char field[][20], Map map, Player p1, Player p2){
	if (p1.num_choice != 0 || p2.num_choice != 0){
		return 0;
	}
	else{
		if (p1.win_cells > p2.win_cells){
			cout << "Congratulations to white player!!!" << endl;
			cout << "white: " << p1.win_cells << " vs black: " << p2.win_cells << endl;
		}
		else if (p1.win_cells < p2.win_cells){
			cout << "Congratulations to black player!!!" << endl;
			cout << "white: " << p1.win_cells << " vs black: " << p2.win_cells << endl;
		}
		// system("pause");
		// system("read -p 'Press Enter to continue...' var");
		return 1;
	}
}

int run(char field[][20], Map &map, Player &p1, Player &p2){
	int allowed[400][2] = {0}, move[2], i, flag;
	show_status(field, allowed, map, p1, p2);
	// system("cls");
	system("clear");
	for (i = 0; i < (map.turn == 1 ? (p1.num_choice) : (p2.num_choice)); i++){
		cout << '(' << allowed[i][0] << ", " << allowed[i][1] << ") ";
	}
	cout << endl
		 << endl;
	print(field, map, p1, p2, allowed, map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
	if (check_size(field, map, p1, p2) == 1){
		return 0;
	}
	if (map.turn == 1 && p1.num_choice == 0){
		map.turn = 2;
		return 2;
	}
	if (map.turn == 2 && p2.num_choice == 0){
		map.turn = 1;
		return 2;
	}
	if (p1.mode == 0 && p2.mode == 0){
		cout<<(map.turn==1?"White":"Black")<<"'s move ('-1 -1' to exit and '-1 0' to reset the field): "<<endl<<endl;
		flag =
			check_ok(move, allowed,
					 map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
	}
	else{
		if ((map.turn == 1 && p1.mode == 0) || (map.turn == 2 && p2.mode == 0)){
			cout << "Your's move ('-1 -1' to exit and '-1 0' to reset the field): "
				 << endl
				 << endl;
			flag =
				check_ok(move, allowed,
						 map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
		}
		else{
			if (p1.mode == -1 || p2.mode == -1){
				cpu_easy(move, allowed,
						 map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
			}
			else if (p1.mode == -2 || p2.mode == -2){
				cpu_normal(field, map, move, allowed,
						   map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
			}
			else if(p1.mode==-3 || p2.mode==-3){
				cpu_hard(field, map, move, allowed,
						   map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
			}
			flag = 2;
		}
	}
	if (flag == 1){
		return 1;
	}
	else if (flag == 0){
		return 0;
	}
	update_field(field, move, map);
	if (map.turn == 1){
		map.turn = 2;
	}
	else if (map.turn == 2){
		map.turn = 1;
	}
	return 2;
}

// int main(){
// 	char field[20][20] = {'\0'}, wb;
// 	int exit = 0, flag;
// 	Map map;
// 	Player p1, p2;
// 	srand(time(0));
// 	map.empty_cells = 60;
// 	map.map_size = 8;
// 	map.turn = 1;
// 	while (exit != 1){
// 		switch (menu(map.map_size)){
// 		case '1':
// 			switch (menu2()){
// 			case '1':
// 				p1.mode = 0;
// 				p2.mode = 0;
// 				flag = 2;
// 				while (flag != 0){
// 					flag = 2;
// 					reset(field, map);
// 					while (flag != 0 && flag != 1){
// 						flag = run(field, map, p1, p2);
// 					}
// 				}
// 				break;
// 			case '2':
// 				cout << "Do you want white or black? [w/b] ";
// 				cin >> wb;
// 				while (wb != 'w' && wb != 'b'){
// 					cout << "Invalid input. w or b? ";
// 					cin >> wb;
// 				}
// 				if (wb == 'w'){
// 					p1.mode = 0;
// 					p2.mode = -1;
// 				}
// 				else{
// 					p1.mode = -1;
// 					p2.mode = 0;
// 				}
// 				flag = 2;
// 				while (flag != 0){
// 					flag = 2;
// 					reset(field, map);
// 					while (flag != 0 && flag != 1){
// 						flag = run(field, map, p1, p2);
// 					}
// 				}
// 				break;
// 			case '3':
// 				cout << "Do you want white or black? [w/b] ";
// 				cin >> wb;
// 				while (wb != 'w' && wb != 'b'){
// 					cout << "Invalid input. w or b? ";
// 					cin >> wb;
// 				}
// 				if (wb == 'w'){
// 					p1.mode = 0;
// 					p2.mode = -2;
// 				}
// 				else{
// 					p1.mode = -2;
// 					p2.mode = 0;
// 				}
// 				flag = 2;
// 				while (flag != 0){
// 					flag = 2;
// 					reset(field, map);
// 					while (flag != 0 && flag != 1){
// 						flag = run(field, map, p1, p2);
// 					}
// 				}
// 				break;
// 			case '4':
// 				cout << "Do you want white or black? [w/b] ";
// 				cin >> wb;
// 				while (wb != 'w' && wb != 'b'){
// 					cout << "Invalid input. w or b? ";
// 					cin >> wb;
// 				}
// 				if (wb == 'w'){
// 					p1.mode = 0;
// 					p2.mode = -3;
// 				}
// 				else{
// 					p1.mode = -3;
// 					p2.mode = 0;
// 				}
// 				flag = 2;
// 				while (flag != 0){
// 					flag = 2;
// 					reset(field, map);
// 					while (flag != 0 && flag != 1){
// 						flag = run(field, map, p1, p2);
// 					}
// 				}
// 				break;
// 			}
// 			break;
// 		case '2':
// 			change_size(map);
// 			break;
// 		case '3':
// 			p1.mode = -1;
// 			p2.mode = -1;
// 			flag = 2;
// 			while (flag != 0){
// 				flag = 2;
// 				reset(field, map);
// 				while (flag != 0 && flag != 1){
// 					flag = run(field, map, p1, p2);
// 				}
// 			}
// 			break;
// 		case '4':
// 			exit = 1;
// 			break;
// 		}
// 	}
// 	return 0;
// }

int ai_test_run(char field[][20], Map &map, Player &p1, Player &p2){
	int allowed[400][2] = {0}, move[2];
	show_status(field, allowed, map, p1, p2);
	// system("cls");
	system("clear");
	print(field, map, p1, p2, allowed, map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
	if (check_size(field, map, p1, p2) == 1){
		return 0;
	}
	if (map.turn == 1 && p1.num_choice == 0){
		map.turn = 2;
		return 2;
	}
	if (map.turn == 2 && p2.num_choice == 0){
		map.turn = 1;
		return 2;
	}
    if ((map.turn==1 && p1.mode==-1) || (map.turn==2 && p2.mode==-1)){
        cpu_easy(move, allowed,
                    map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
    }
    else if ((map.turn==1 && p1.mode==-2) || (map.turn==2 && p2.mode==-2)){
        cpu_normal(field, map, move, allowed,
                    map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
    }
    else if((map.turn==1 && p1.mode==-3) || (map.turn==2 && p2.mode==-3)){
        cpu_hard(field, map, move, allowed,
                    map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
    }
	update_field(field, move, map);
	if (map.turn == 1){
		map.turn = 2;
	}
	else if (map.turn == 2){
		map.turn = 1;
	}
	return 2;
}

int main(){
	char field[20][20] = {'\0'};
	int p1_win=0, p2_win=0, flag;
	Map map;
	Player p1, p2;
	srand(time(0));
	map.map_size=8;
	cin>>p1.mode; // حالت بازیکن سفید
	cin>>p2.mode; // حالت بازیکن مشکی
	while(p1_win+p2_win<1000){
		map.empty_cells=60;
		map.turn=1;
		p1.num_choice=4;
		p1.win_cells=2;
		p2.num_choice=4;
		p2.win_cells=2;
		reset(field, map);
		flag=2;
		while (flag != 0){
			flag = ai_test_run(field, map, p1, p2); // داخل تابع سی پی یو هارد ایکس شماره لایه ای است که ارزش دوبرابری دارد
			}
		if(p1.win_cells>p2.win_cells){p1_win++;}
		if(p2.win_cells>p1.win_cells){p2_win++;}
	}
	cout<<"p1: "<<p1_win<<endl;
	cout<<"p2: "<<p2_win;
return 0;}
