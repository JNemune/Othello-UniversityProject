#include <iostream>
#include <stdio.h>
#include <time.h>
#include <random>
#include<Windows.h>
// #include <unistd.h>
#include<fcntl.h> // برای پرینت کردن زمین و پرینت کردن کد اسکی ها استفاده شده است
#include<io.h>
using namespace std;
struct Map {
	int empty_cells;
	int turn; // 1 white va 2 black
	int map_size;
};
struct Player {
	int num_choice;
	int mode; // 0 for player -1 for easy cpu -2 for normal cpu -3 for hard cpu
	int win_cells;
};

char menu(int n) { // منو را پرینت میکند و ورودی منو را میگیرد و بررسی میکند که ایا ورودی درست داده شده است یا خیر
	char inp;
	system("cls");
	// system("clear");
	// cout << "Welcome here, THE BEST OTHELLO GAME!" << endl;
	// cout << "   Enter a number from the menu:" << endl;
	// cout << "      1. New game" << endl;
	// cout << "      2. Change the map size (current size: " << n << ")" << endl;
	// cout << "      3. Demo" << endl;
	// cout << "      4. Exit" << endl;
	wprintf(L"Welcome here, THE BEST OTHELLO GAME!\n");
	wprintf(L"   Enter a number from the menu:\n");
	wprintf(L"      1. New game\n");
	wprintf(L"      2. Change the map size (current size: %d)\n", n);
	wprintf(L"      3. Demo\n");
	wprintf(L"      4. Exit\n");
	cin >> inp;
	while (inp != '1' && inp != '2' && inp != '3' && inp != '4') {
		// cout << "Invalid input. Enter '1', '2', '3' or '4':" << endl;
		wprintf(L"Invalid input. Enter '1', '2', '3' or '4':");
		cin >> inp;
	}
	return inp;
}

char menu2() { // منو دوم را پرینت میکند گزینه های منو برای انتخاب حالت بازی میباشد
	char inp;
	system("cls");
	// system("clear");
	// cout << "Enter a number from the menu:" << endl;
	// cout << "   1. Tow-player mode" << endl;
	// cout << "   2. CPU: easy" << endl;
	// cout << "   3. CPU: normal" << endl;
	// cout << "   4. CPU: Hard" << endl;
	wprintf(L"Enter a number from the menu:\n");
	wprintf(L"   1. Tow-player mode\n");
	wprintf(L"   2. CPU: easy\n");
	wprintf(L"   3. CPU: normal\n");
	wprintf(L"   4. CPU: Hard\n");
	cin >> inp;
	while (inp != '1' && inp != '2' && inp != '3' && inp != '4') {
		// cout << "Invalid input. Enter '1', '2' or '3':" << endl;
		wprintf(L"Invalid input. Enter '1', '2' or '3':");
		cin >> inp;
	}
	return inp;
}

void change_size(Map& map) { // برای تغییر اندازه زمین ازین منو استفاده میشود ورودی را میگیرد و بررسی میکند که زوج و بین چهار تا بیست باشد
	// cout << "Enter the map size (4 <= an even number <= 20): " << endl;
	wprintf(L"Enter the map size (4 <= an even number <= 20): ");
	cin >> map.map_size;
	while (map.map_size != 4 && map.map_size != 6 && map.map_size != 8 && map.map_size != 10 && map.map_size != 12 && map.map_size != 14 && map.map_size != 16 && map.map_size != 18 && map.map_size != 20) {
		// cout << "Invalid input" << endl;
		// cout << "Enter the map size (4 <= an even number <= 20): " << endl;
		wprintf(L"Invalid input");
		wprintf(L"Enter the map size (4 <= an even number <= 20): ");
		cin >> map.map_size;
	}
	map.empty_cells = map.map_size * map.map_size - 4;
	return;
}

void print(char field[][20], Map& map, Player& p1, Player& p2, int allowed[][2], int n) { // برای پرینت زمین ازین تابع استفاده میشود همینطور تعداد خانه ای خالی و تعداد خانه های تصاحب شده هر بازیکن را ثبت میکد
	_setmode(_fileno(stdout), _O_U16TEXT);
	int i, j, k, flag;
	wprintf(L"     ");
	for (i = 0; i < map.map_size; i++) {
		wprintf(L" %2d ", i);
	}
	wprintf(L"\n     \x2554");
	for (i = 1; i < map.map_size; i++) {
		wprintf(L"\x2550\x2550\x2550\x2564");
	}
	wprintf(L"\x2550\x2550\x2550\x2557\n");
	for (i = 0; i < map.map_size; i++) {
		wprintf(L"   %2d\x2551", i);
		for (j = 0; j < map.map_size; j++) {
			flag = 0;
			for (k = 0; k < n; k++) {
				if (i == allowed[k][0] && j == allowed[k][1]) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				wprintf(L" . ");
			}
			else {
				wprintf(L" %c ", field[i][j]);
			}
			j != map.map_size - 1 ? wprintf(L"\x2502") : wprintf(L"\x2551");
		}
		i != map.map_size - 1 ? wprintf(L"\n     \x255F") : wprintf(L"\n     \x255A");
		for (j = 1; j < map.map_size; j++) {
			i != map.map_size - 1 ? wprintf(L"\x2500\x2500\x2500\x253C") : wprintf(L"\x2550\x2550\x2550\x2567");
		}
		i != map.map_size - 1 ? wprintf(L"\x2500\x2500\x2500\x2562\n") : wprintf(L"\x2550\x2550\x2550\x255d\n");
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
	// cout << endl;
	// cout << "White's wins: " << p1.win_cells << "     ";
	// cout << "Black's wins: " << p2.win_cells << endl
	// 	<< endl;
	wprintf(L"\nWhite's wins: %d     Black's wins: %d\n\n", p1.win_cells, p2.win_cells);
	return;
}

// void print(char field[][20], Map &map, Player &p1, Player &p2, int allowed[][2], int n){ // تابع پرینت کلاسیک به سبکی که داخل پی دی اف گفته شده است این تابع مانند تابع بالا عمل میکند با این تفاوت که دیگر کد اسکی چاپ نمیکند
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

void reset(char field[][20], Map& map) { // این تابع زیمن بازی را گرفته و با توجه به اندازه زمین ان را به فرمت استاندار با چهار مهره در مرکز در میاورد و همچینن تعداد خانه های خالی و نوبت را در استراکت مپ ذخیره میکند
	int i, j;
	for (i = 0; i < map.map_size; i++)
		for (j = 0; j < map.map_size; j++) {
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

int search(char field[][20], Map map, int x, int y, int out[][2]) { // این تابع در هشت جهت دور یک خانه پیمایش انجام میدهد و وقتی به خانه ای میرسد که رنگش با رنگ خانه شورع متفاوت است یا به خانه خالی مرسد متوقف شده و از حلقه وایل خارج میشود و اگر علت توقت ان خانه خالی بوده باشد ان خانه را به عنوان یکی از خانه های مجاز اطراف خانه شروع ذخیره کرده و از ان داخل تابع شو استتوس استفاده میکنیم
	int i = x - 1, j = y - 1, c = 0;
	char turn, _turn;
	if (field[x][y] == 'w') {
		turn = 'w';
		_turn = 'b';
	}
	if (field[x][y] == 'b') {
		turn = 'b';
		_turn = 'w';
	}
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn) {
		i--;
		j--;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i + 1][j + 1] == _turn) {
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x - 1;
	j = y;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn) {
		i--;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i + 1][j] == _turn) {
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x - 1;
	j = y + 1;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn) {
		i--;
		j++;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i + 1][j - 1] == _turn) {
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x;
	j = y - 1;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn) {
		j--;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i][j + 1] == _turn) {
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x;
	j = y + 1;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn) {
		j++;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i][j - 1] == _turn) {
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x + 1;
	j = y - 1;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn) {
		i++;
		j--;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i - 1][j + 1] == _turn) {
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x + 1;
	j = y;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn) {
		i++;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i - 1][j] == _turn) {
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	i = x + 1;
	j = y + 1;
	while (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == _turn) {
		i++;
		j++;
	}
	if (0 <= i && i < map.map_size && 0 <= j && j < map.map_size && field[i][j] == ' ' && field[i - 1][j - 1] == _turn) {
		out[c][0] = i;
		out[c][1] = j;
		c++;
	}
	return c;
}

void show_status(char field[][20], int out[][2], Map map, Player& p1,
	Player& p2) { // این تابع همونطور به کمک تابع سرچ برای تک تک خانه های زمین که مهره ای داخل ان ها هست خانه های مجاز را پیدا کرده و ذخیره میکند و تعداد ان ها را در استراکت هر پلیر میریزد
	int i, j, k, l, c = 0, c2 = 0, flag, pre_out[8][2], pre_out_num, out2[400][2] = { 0 };
	char turn;
	if (map.turn == 1) {
		turn = 'w';
	}
	if (map.turn == 2) {
		turn = 'b';
	}
	for (i = 0; i < map.map_size; i++) {
		for (j = 0; j < map.map_size; j++) {
			if (field[i][j] == 'w' || field[i][j] == 'b') {
				pre_out_num = search(field, map, i, j, pre_out);
				for (k = 0; k < pre_out_num; k++) {
					flag = 0;
					if (field[i][j] == turn) {
						for (l = 0; l < c; l++) {
							if (out[l][0] == pre_out[k][0] && out[l][1] == pre_out[k][1]) {
								flag = 1;
								break;
							}
						}
					}
					else {
						for (l = 0; l < c2; l++) {
							if (out2[l][0] == pre_out[k][0] && out2[l][1] == pre_out[k][1]) {
								flag = 1;
								break;
							}
						}
					}
					if (flag == 0) {
						if (field[i][j] == turn) {
							out[c][0] = pre_out[k][0];
							out[c][1] = pre_out[k][1];
							c++;
						}
						else {
							out2[c2][0] = pre_out[k][0];
							out2[c2][1] = pre_out[k][1];
							c2++;
						}
					}
				}
			}
		}
	}
	if (map.turn == 1) {
		p1.num_choice = c;
		p2.num_choice = c2;
	}
	else {
		p1.num_choice = c2;
		p2.num_choice = c;
	}
	return;
}

int check_ok(int out[], int allowed[][2], int n) { // این تابع از کاربر مختصات ورودی میگیرد و اگر مجاز باشد از تابع خارج میشود خروجی این تابع سه حالت صفر برای خروج از بازی و یک برای ریست کردن بازی و دو برای اجرای راند بعدی بازی میباشد
	int i, flag = 0;
	cin >> out[0];
	cin >> out[1];
	if (out[0] == -1) {
		return 0;
	}
	if (out[0] == -2) {
		return 1;
	}
	for (i = 0; i < n; i++) {
		if (out[0] == allowed[i][0] && out[1] == allowed[i][1]) {
			flag = 1;
			break;
		}
	}
	while (flag == 0) {
		// cout << "Invalid input:" << endl;
		wprintf(L"Invalid input: \n");
		cin >> out[0];
		cin >> out[1];
		for (i = 0; i < n; i++) {
			if (out[0] == allowed[i][0] && out[1] == allowed[i][1]) {
				flag = 1;
				break;
			}
		}
	}
	return 2;
}

void cpu_easy(int out[], int allowed[][2], int n) { // این تابع سی پی یو بازی مباشد و از بین خانه های مجاز یکی را به صورت رندم انتخاب میکند و در ارایه خروجی ذخیره کرده و در تابع ران استفاده میکند
	int x = rand() % n;
	// sleep(3);
	Sleep(3000);
	out[0] = allowed[x][0];
	out[1] = allowed[x][1];
	return;
}

void update_field(char field[][20], int move[], Map map) { // این تابع بعد از اینکه کاربر انتخاب خود را انجام داد یا سی پی یو خانه ای را انخاب کرد زمین را با توجه به انتخاب ها تغییر میدهد الگریمت ان به این صورت است که در هشت جهت خانه تغییر کرده پیمایش میکند و در صورتی که به خانه ای برسد که هم رنگ خودش است و تمام خانه های میانی رنگ مخالف باشند تمام ان ها را همرنگ خود میکند
	int i = move[0], j = move[1], m, n;
	char turn, _turn;
	if (map.turn == 1) {
		turn = 'w';
		_turn = 'b';
	}
	if (map.turn == 2) {
		turn = 'b';
		_turn = 'w';
	}
	field[i][j] = turn;
	m = i - 1;
	n = j - 1;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn) {
		m--;
		n--;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m + 1][n + 1] == _turn) {
		while (m != i || n != j) {
			field[m][n] = turn;
			m++;
			n++;
		}
	}
	m = i - 1;
	n = j;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn) {
		m--;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m + 1][n] == _turn) {
		while (m != i || n != j) {
			field[m][n] = turn;
			m++;
		}
	}
	m = i - 1;
	n = j + 1;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn) {
		m--;
		n++;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m + 1][n - 1] == _turn) {
		while (m != i || n != j) {
			field[m][n] = turn;
			m++;
			n--;
		}
	}
	m = i;
	n = j - 1;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn) {
		n--;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m][n + 1] == _turn) {
		while (m != i || n != j) {
			field[m][n] = turn;
			n++;
		}
	}
	m = i;
	n = j + 1;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn) {
		n++;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m][n - 1] == _turn) {
		while (m != i || n != j) {
			field[m][n] = turn;
			n--;
		}
	}
	m = i + 1;
	n = j - 1;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn) {
		m++;
		n--;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m - 1][n + 1] == _turn) {
		while (m != i || n != j) {
			field[m][n] = turn;
			m--;
			n++;
		}
	}
	m = i + 1;
	n = j;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn) {
		m++;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m - 1][n] == _turn) {
		while (m != i || n != j) {
			field[m][n] = turn;
			m--;
		}
	}
	m = i + 1;
	n = j + 1;
	while (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == _turn) {
		m++;
		n++;
	}
	if (0 <= m && m < map.map_size && 0 <= n && n < map.map_size && field[m][n] == turn && field[m - 1][n - 1] == _turn) {
		while (m != i || n != j) {
			field[m][n] = turn;
			m--;
			n--;
		}
	}



}

void cpu_normal(char field[][20], Map map, int out[], int allowed[][2], int n) { // تابع سی پی یو نرمال یک زمین مجازی برای تست کردن میسازد و بازی را برای هر یک از حالات مجاز اجرا میکند و امتیاز به دست امده را در ارایه کامن ذخیره میکند در اخر مختصات خانه ای را که بیشترین امتیاز را دارد در ارایه خروجی ذخیره میکند و در تابع ران استفاده میشود
	// sleep(3);
	Sleep(3000);
	char test_field[20][20] = { '\0' }, turn; int i, j, k, max, compare[400] = { 0 }, pre = 0, pass;
	turn = map.turn == 1 ? 'w' : 'b';
	for (i = 0; i < map.map_size; i++) {
		for (j = 0; j < map.map_size; j++) {
			if (field[i][j] == turn) {
				pre++;
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
					pass++;
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

void cpu_hard(char field[][20], Map map, int out[], int allowed[][2], int n) { // این تابع برای هر یک از لایه های بازی با توجه به الگوریتم یادگیری ماشین که فایل ان با نام 
// ai_main.cpp
// ذخیره شده است ارزش گذاری میکند یعنی هر مهره مکان خاصی ارزش خاصی دارد
	// sleep(3);
	Sleep(3000);
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

int check_size(char field[][20], Map map, Player p1, Player p2) { // این تابع اتمام بازی را بررسی میکند وقتی که هیچ کدام از بازیکنا انتخابی نداشته باشند بازی تمام میشود توجه کنید که قوتی زمین تمام پر باشد هم بازیکن ها انتخابی ندارند پس مشکلی نیست این تابع همچنین پیام تبریک را چاپ میکند
	int i, j;
	if (p1.num_choice != 0 || p2.num_choice != 0) {
		return 0;
	}
	else {
		if (p1.win_cells > p2.win_cells) {
			// cout << "Congratulations to white player!!!" << endl;
			// cout << "white: " << p1.win_cells << " vs black: " << p2.win_cells << endl;
			wprintf(L"Congratulations to white player!!!\n");
			wprintf(L"white: %d vs black: %d\n", p1.win_cells, p2.win_cells);
		}
		else if (p1.win_cells < p2.win_cells) {
			// cout << "Congratulations to black player!!!" << endl;
			// cout << "white: " << p1.win_cells << " vs black: " << p2.win_cells << endl;
			wprintf(L"Congratulations to black player!!!\n");
			wprintf(L"white: %d vs black: %d\n", p1.win_cells, p2.win_cells);
		}
		system("pause");
		// system("read -p 'Press Enter to continue...' var");
		return 1;
	}
}

int run(char field[][20], Map& map, Player& p1, Player& p2) { // این تابع پیچیده ترین تابع این برنامه از لحاظ تعاملی میباشد تمام بازی ها از طریق این بازی انجام میشود و بسته به حالت های بازیکن ها که در استراکت پلیر ذخیره شده است خانه هایی از کابرگرفته یا با توابع سی پی یو انتخاب میکند و ان ها را با توابع مجاز چک کرده و زمین را اپدیت و پیرینت میکند
	int allowed[400][2] = { 0 }, move[2], i, flag;
	show_status(field, allowed, map, p1, p2);
	system("cls");
	// system("clear");
	for (i = 0; i < (map.turn == 1 ? (p1.num_choice) : (p2.num_choice)); i++) {
		// cout << '(' << allowed[i][0] << ", " << allowed[i][1] << ") ";
		wprintf(L"(%d, %d) ", allowed[i][0], allowed[i][1]);
	}
	// cout << endl
	// 	<< endl;
	wprintf(L"\n\n");
	print(field, map, p1, p2, allowed, map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
	if (check_size(field, map, p1, p2) == 1) {
		return 0;
	}
	if (map.turn == 1 && p1.num_choice == 0) {
		map.turn = 2;
		return 2;
	}
	if (map.turn == 2 && p2.num_choice == 0) {
		map.turn = 1;
		return 2;
	}
	if (p1.mode == 0 && p2.mode == 0) {
		// cout << (map.turn == 1 ? "White" : "Black") << "'s move ('-1 -1' to exit and '-1 0' to reset the field): " << endl << endl;
		wprintf(L"%s's move ('-1 -1' to exit and '-1 0' to reset the field): \n\n", map.turn == 1 ? "White" : "Black");
		flag =
			check_ok(move, allowed,
				map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
	}
	else {
		if ((map.turn == 1 && p1.mode == 0) || (map.turn == 2 && p2.mode == 0)) {
			// cout << "Your's move ('-1 -1' to exit and '-1 0' to reset the field): "
			// 	<< endl
			// 	<< endl;
			wprintf(L"Your's move ('-1 -1' to exit and '-1 0' to reset the field): ");
			flag =
				check_ok(move, allowed,
					map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
		}
		else {
			if (p1.mode == -1 || p2.mode == -1) {
				cpu_easy(move, allowed,
					map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
			}
			else if (p1.mode == -2 || p2.mode == -2) {
				cpu_normal(field, map, move, allowed,
					map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
			}
			else if (p1.mode == -3 || p2.mode == -3) {
				cpu_hard(field, map, move, allowed,
					map.turn == 1 ? (p1.num_choice) : (p2.num_choice));
			}
			flag = 2;
		}
	}
	if (flag == 1) {
		return 1;
	}
	else if (flag == 0) {
		return 0;
	}
	update_field(field, move, map);
	if (map.turn == 1) {
		map.turn = 2;
	}
	else if (map.turn == 2) {
		map.turn = 1;
	}
	return 2;
}

int main() { // تابع اصلی بازی که توابع ران و منو ها داخل ان اجرا میشوند و برای تعامل با کاربر میباشد دارای دو سوییچ برای منو یک و دو میباشد
	char field[20][20] = { '\0' }, wb;
	int exit = 0, flag;
	Map map;
	Player p1, p2;
	srand(time(0));
	map.empty_cells = 60;
	map.map_size = 8;
	map.turn = 1;
	while (exit != 1) {
		switch (menu(map.map_size)) {
		case '1':
			switch (menu2()) {
			case '1':
				p1.mode = 0;
				p2.mode = 0;
				flag = 2;
				while (flag != 0) {
					flag = 2;
					reset(field, map);
					while (flag != 0 && flag != 1) {
						flag = run(field, map, p1, p2);
					}
				}
				break;
			case '2':
				// cout << "Do you want white or black? [w/b] ";
				wprintf(L"Do you want white or black? [w/b] ");
				cin >> wb;
				while (wb != 'w' && wb != 'b') {
					// cout << "Invalid input. w or b? ";
					wprintf(L"Invalid input. w or b? ");
					cin >> wb;
				}
				if (wb == 'w') {
					p1.mode = 0;
					p2.mode = -1;
				}
				else {
					p1.mode = -1;
					p2.mode = 0;
				}
				flag = 2;
				while (flag != 0) {
					flag = 2;
					reset(field, map);
					while (flag != 0 && flag != 1) {
						flag = run(field, map, p1, p2);
					}
				}
				break;
			case '3':
				// cout << "Do you want white or black? [w/b] ";
				wprintf(L"Do you want white or black? [w/b] ");
				cin >> wb;
				while (wb != 'w' && wb != 'b') {
					// cout << "Invalid input. w or b? ";
					wprintf(L"Invalid input. w or b? ");
					cin >> wb;
				}
				if (wb == 'w') {
					p1.mode = 0;
					p2.mode = -2;
				}
				else {
					p1.mode = -2;
					p2.mode = 0;
				}
				flag = 2;
				while (flag != 0) {
					flag = 2;
					reset(field, map);
					while (flag != 0 && flag != 1) {
						flag = run(field, map, p1, p2);
					}
				}
				break;
			case '4':
				// cout << "Do you want white or black? [w/b] ";
				wprintf(L"Do you want white or black? [w/b] ");
				cin >> wb;
				while (wb != 'w' && wb != 'b') {
					// cout << "Invalid input. w or b? ";
					wprintf(L"Invalid input. w or b? ");
					cin >> wb;
				}
				if (wb == 'w') {
					p1.mode = 0;
					p2.mode = -3;
				}
				else {
					p1.mode = -3;
					p2.mode = 0;
				}
				flag = 2;
				while (flag != 0) {
					flag = 2;
					reset(field, map);
					while (flag != 0 && flag != 1) {
						flag = run(field, map, p1, p2);
					}
				}
				break;
			}
			break;
		case '2':
			change_size(map);
			break;
		case '3':
			p1.mode = -1;
			p2.mode = -1;
			flag = 2;
			while (flag != 0) {
				flag = 2;
				reset(field, map);
				while (flag != 0 && flag != 1) {
					flag = run(field, map, p1, p2);
				}
			}
			break;
		case '4':
			exit = 1;
			break;
		}
	}
	return 0;
}
