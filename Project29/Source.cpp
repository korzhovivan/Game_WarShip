#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <time.h>
#include <string.h>
using namespace std;

//Prototypes
int random(int min, int max);						// рандом
int** CreatMap(const int width, const int height);	// создание карты(массив)
void DeleteArray(int **arr, int height);			// удаление масива
void ShowConsoleCursor(bool showFlag);				// удаление курсора
int MenuNavigation();								// навигация в меню
int SettingsNavigation(int two_players);			//навигация в найстройках
void InitArray(int **arr, const int width, const int height, int min, int max);
void UpdateMapMy(int **arr);
void UpdateMapEnemy(int **arr, int **show);
void UpdateGame(int **enemy, int **my, int** show);
void AddSingleShip(int **arr);
void SetZoneNeatShip(int **arr);
void AddShip(int **arr, int size);
void SetShipsRandom(int **arr);
int CountLenght(const char* str);
int getYfromCoordinate(char*coordinate);
int getXfromCoordinate(char*coordinate);
void AddShipManual(int **arr, int size);
void StringToUpper(char* str);
void ManualSetShipsScenary(int**arr);
void Exeption();
void MyShoot(int **enemy, int** show, int** my);
void SetZoneAfterDie(int **arr, int** show);
void Success();
void BotShoot(int **enemy, int** show, int** my);
void SetZoneAfterDieForMy(int **arr);
int WinOrNo(int** my, int** enemy);
bool CleverShoot(int **enemy, int** show, int** my, int &miss);


/*-------------------------------------------------------------------------------------------------------*/
											/*MAIN*/
/*-------------------------------------------------------------------------------------------------------*/

int main()
{
	srand(time(NULL));
	//setlocale(LC_ALL, "Russian"); // русский язык
	/***********************Размер консоли и удаление курсора*/
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 500, 300, TRUE); // 800 width, 100 height
	ShowConsoleCursor(false);
	/**********************************************************************/

	//Map var
	int map_size = 12;
	int **enemy = CreatMap(map_size, map_size);
	int **my = CreatMap(map_size, map_size);
	int **showEnemy = CreatMap(map_size, map_size);


	//settings var
	int randomSetShips = 1;

	int j = 10;
	for (int i = 1; i < 300; i++)
	{
		MoveWindow(console, r.left, r.top, 500, i, TRUE);
		Sleep(1);
	}
	MoveWindow(console, r.left, r.top, 500, 300, TRUE);
	system("cls");
	cout << "\n\n\n\n\n\n========================================================\n";
	cout << "\t\tWELCOME IN WAR SHIPS\n";
	cout << "========================================================\n";
	Sleep(2500);
	system("cls");


navigation:
	int choose = MenuNavigation();


	/*-------------------------------------------------------------------------------------------------------*/
												/*ИГРА*/
	/*-------------------------------------------------------------------------------------------------------*/
	if (choose == 49)
	{
		InitArray(enemy, map_size, map_size, 0, 1);
		InitArray(my, map_size, map_size, 0, 1);
		InitArray(showEnemy, map_size, map_size, 0, 1);

		MoveWindow(console, r.left, r.top, 500, 750, TRUE);


		//Растановка кораликов
		if (randomSetShips == 1)
		{
			SetShipsRandom(my);
			SetShipsRandom(enemy);
		}
		else
		{
			SetShipsRandom(enemy);
			ManualSetShipsScenary(my);
		}

		//Игра
		while (true)
		{
			UpdateGame(enemy, my, showEnemy);

			MyShoot(enemy, showEnemy, my);
			if (WinOrNo(my, enemy) == 1)
			{
				cout << "You WIN !!!\n";
				Sleep(5000);
				goto navigation;
			}
			SetZoneAfterDie(enemy, showEnemy);
			UpdateGame(enemy, my, showEnemy);

			Sleep(1000);
			BotShoot(enemy, showEnemy, my);
			if (WinOrNo(my, enemy) == -1)
			{
				cout << "You LOSE !!!\n";
				Sleep(5000);
				goto navigation;
			}

		}
	}
	/*-------------------------------------------------------------------------------------------------------*/
	/*-------------------------------------------------------------------------------------------------------*/
	/*-------------------------------------------------------------------------------------------------------*/


	if (choose == 50) //настройки
	{
		randomSetShips = SettingsNavigation(randomSetShips);
		system("cls");
		goto navigation;
	}
	if (choose == 51) //выход
	{
		return 0;
	}
	system("pause");
	return 0;
}



/*-------------------------------------------------------------------------------------------------------*/
											/*Функции*/
/*-------------------------------------------------------------------------------------------------------*/



int random(int min, int max) {
	return min + rand() % max;
}
int** CreatMap(const int width, const int height) {
	int **arr = new int*[height];
	for (int i = 0; i < height; i++)
	{
		*(arr + i) = new int[width];
	}
	return arr;
}
void DeleteArray(int **arr, int height) {
	for (int i = 0; i < height; i++)
	{
		delete[] * (arr + i);
	}
	delete[] arr;
}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}
int MenuNavigation() {
	char choose;
	cout << "\n\n\n";
	cout << "=========================MENU============================";
	cout << "\n\n\n";
	cout << "\t\t\t";
	cout << "1. PLAY";
	cout << "\n\n\n";
	cout << "\t\t\t";
	cout << "2. SETTINGS";
	cout << "\n\n\n";
	cout << "\t\t\t";
	cout << "3. EXIT";
	cout << "\n\n\n";
	cout << "=========================================================";
	do
	{
		choose = _getch();
	} while (choose != 49 && choose != 50 && choose != 51);

	return choose;
}
int SettingsNavigation(int randomSetShips) {
	int random_set = randomSetShips;
	int choose;

	char*str1 = new char[50];
	char*str2 = new char[50];

	if (randomSetShips == 0)
	{
		strcpy(str1, "1. MANUAL SET SHIPS\t(activated)");
		strcpy(str2, "2. RANDOM");
	}
	else
	{
		strcpy(str1, "1. MANUAL SET SHIPS");
		strcpy(str2, "2. RANDOM\t\t(activated)");
	}
	system("cls");
	cout << "\n";
	cout << "=======================SETTINGS==========================";
	cout << "\n\n\n";
	cout << "\t\t";
	cout << str1;
	cout << "\n\n\n";
	cout << "\t\t";
	cout << str2;
	cout << "\n\n\n";
	cout << "=========================================================";
	do
	{
		choose = _getch();
	} while (choose != 49 && choose != 50 && choose != 27);
	if (choose == 50)
	{
		random_set = 1;

	}
	if (choose == 49)
	{
		random_set = 0;

	}
	return random_set;
	delete[] str1;
	delete[] str2;
	system("cls");
}
void InitArray(int **arr, const int width, const int height, int min, int max) {
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			*(*(arr + i) + j) = random(min, max);
		}
	}
}
void UpdateMapMy(int **arr) {
	cout << "  | A |" << " B |" << " C |" << " D |" << " E |" << " F |" << " G |" << " H |" << " I |" << " J |\n";
	cout << "-------------------------------------------\n";

	for (int i = 1; i < 11; i++)
	{
		if (i == 10)
		{
			cout << i << "| ";
		}
		else
		{
			cout << i << " | ";
		}

		for (int j = 1; j < 11; j++)
		{
			switch (arr[i][j])
			{
			case 0:cout << "."; break;			// пусто(море)
			case 1:cout << char(254); break;    // часть корабля(254)
			case 2:cout << "O"; break;	     	// выстрел
			case 3:cout << char(149); break;	// раненный корабль
			case 6:cout << char(149); break;	// убитый корабль
			case 10:cout << "."; break;         // недоступное для установки корабля
			}

			if (j == 10)
			{

				cout << " |";
			}
			else
			{
				cout << "   ";
			}

		}
		cout << "\n";
	}
	cout << "-------------------------------------------\n";
}
void UpdateMapEnemy(int **arr, int **show) {
	cout << "  | A |" << " B |" << " C |" << " D |" << " E |" << " F |" << " G |" << " H |" << " I |" << " J |\n";
	cout << "-------------------------------------------\n";

	for (int i = 1; i < 11; i++)
	{
		if (i == 10)
		{
			cout << i << "| ";
		}
		else
		{
			cout << i << " | ";
		}

		for (int j = 1; j < 11; j++)
		{
			if (show[i][j] == 1)
			{
				switch (arr[i][j])
				{
				case 0:cout << ".";   break;        // пусто(море)
				case 1:cout << char(254); break;    // часть корабля
				case 2:cout << "O"; break;	     	// выстрел
				case 3:cout << char(149); break;			// раненный корабль
				case 6:cout << char(149); break;			//убитый
				//case 10:cout << "-"; break;         // недоступное для установки корабля
				}
			}
			else
			{
				cout << ".";;
			}
			if (j == 10)
			{

				cout << " |";
			}
			else
			{
				cout << "   ";
			}
		}
		cout << "\n";
	}
	cout << "-------------------------------------------\n";
}
void UpdateGame(int **enemy, int **my, int** show) {

	system("cls");
	cout << "\t\tENEMY MAP\n\n\n";
	UpdateMapEnemy(enemy, show);
	cout << "\n\n\n\n";
	cout << "\t\tMY MAP\n\n\n";
	UpdateMapMy(my);
}
void AddSingleShip(int **arr) {

	while (true)
	{
		// координаты корабля
		int x = random(1, 10);
		int y = random(1, 10);

		if (arr[x][y] != 1 && arr[x][y] != 10) //если не на дургом корабле или на недоступной зоне
		{
			arr[x][y] = 1; // установка корабля

			SetZoneNeatShip(arr);
			break;
		}
	}
}
void AddShip(int **arr, int size) {

	int direct;
	int x;
	int y;
	int counter = 1;
	int result_direct;
	int x_res;
	int y_res;
	int set = 0;

	while (set != 1) {


		direct = random(1, 4);
		x = random(1, 10);
		y = random(1, 10);
		counter = 1;

		if (arr[x][y] != 1 && arr[x][y] != 10) {
			switch (direct)
			{
			case 1:
				for (int i = 1; i < size; i++)
				{
					if (y - i == 0)
					{
						break;
					}
					if (arr[x][y - i] != 1 && arr[x][y - i] != 10)
					{

						counter++;
						if (counter == size)
						{
							result_direct = direct;
							x_res = x;
							y_res = y;
							set = 1;
						}
					}
				}
				break;
			case 2:
				for (int i = 1; i < size; i++)
				{
					if (x - i == 0)
					{
						break;
					}
					if (arr[x - i][y] != 1 && arr[x - i][y] != 10)
					{

						counter++;
						if (counter == size)
						{
							result_direct = direct;
							x_res = x;
							y_res = y;
							set = 1;
						}
					}
				}
				break;
			case 3:
				for (int i = 1; i < size; i++)
				{
					if (y + i == 11)
					{
						break;
					}
					if (arr[x][y + i] != 1 && arr[x][y + i] != 10)
					{
						counter++;
						if (counter == size)
						{
							result_direct = direct;
							x_res = x;
							y_res = y;
							set = 1;
						}
					}
				}
				break;
			case 4:
				for (int i = 1; i < size; i++)
				{
					if (x + i == 11)
					{
						break;
					}
					if (arr[x + i][y] != 1 && arr[x + i][y] != 10)
					{
						counter++;
						if (counter == size)
						{
							result_direct = direct;
							x_res = x;
							y_res = y;
							set = 1;
						}
					}
				}
				break;
			} // конец switch
		}
	}

	arr[x_res][y_res] = 1;
	if (x_res > 0 && x_res < 11 && y_res > 0 && y_res < 11)
	{
		switch (result_direct)
		{
		case 1:
			for (int i = 1; i < size; i++) {
				arr[x][y - i] = 1;
			}
			break;

		case 2:
			for (int i = 1; i < size; i++) {
				arr[x - i][y] = 1;
			}
			break;
		case 3:
			for (int i = 1; i < size; i++) {
				arr[x][y + i] = 1;
			}
			break;
		case 4:
			for (int i = 1; i < size; i++) {
				arr[x + i][y] = 1;
			}
			break;
		}
	}
	SetZoneNeatShip(arr);
}
void SetZoneNeatShip(int **arr) {
	for (int x = 1; x < 11; x++)
	{
		for (int y = 1; y < 11; y++)
		{
			if (arr[x][y] == 1)
			{
				if (arr[x][y + 1] != 1)
				{
					arr[x][y + 1] = 10;
				}
				if (arr[x][y - 1] != 1)
				{
					arr[x][y - 1] = 10;
				}
				if (arr[x - 1][y] != 1)
				{
					arr[x - 1][y] = 10;
				}
				if (arr[x + 1][y] != 1)
				{
					arr[x + 1][y] = 10;
				}
				arr[x - 1][y - 1] = 10;
				arr[x - 1][y + 1] = 10;
				arr[x + 1][y + 1] = 10;
				arr[x + 1][y - 1] = 10;
			}
		}
	}
}
void SetShipsRandom(int **arr) {
	AddShip(arr, 4);
	AddShip(arr, 3);
	AddShip(arr, 3);
	AddShip(arr, 2);
	AddShip(arr, 2);
	AddShip(arr, 2);
	AddSingleShip(arr);
	AddSingleShip(arr);
	AddSingleShip(arr);
	AddSingleShip(arr);
	/*4-палубный(1шт),3-палубный(2шт),2-палубный(3шт),1-палубный(4шт)*/
}
void AddShipManual(int **arr, int size) {

	int direct;
	int x;
	int y;
	int counter = 1;
	int set = 0;
	char *coordinate = new char[10];

	while (set != 1) {
		counter = 1;
		int goodInput = 0;
		system("cls");
		cout << "=======================MANUAL==========================\n\n\n";
		UpdateMapMy(arr);
		cout << "\n\n";
		if (size == 1)
		{
			cout << "Set single(1) ship:\n";
		}
		if (size == 2)
		{
			cout << "Set double(2) ship:\n\n";
		}
		if (size == 3)
		{
			cout << "Set triaple(3) ship:\n\n";
		}
		if (size == 4)
		{
			cout << "Set quadruple(4) ship:\n";
		}

		cout << "Input coordinate: ";

		do
		{
			gets_s(coordinate, 10);

			int ansi = int(coordinate[0]);
			int length = CountLenght(coordinate);

			if (length > 1 && length < 4 && ((ansi < 107 && ansi > 96) || (ansi > 64 && ansi < 75)))
			{
				if (int(coordinate[1]) > 48 && int(coordinate[1]) < 58)
				{
					x = getYfromCoordinate(coordinate);
					y = getXfromCoordinate(coordinate);
					goodInput = 1;

				}
				else
				{
					Exeption();
					cout << "Enter one more:(1) ";
				}
			}
			/*else
			{
				Exeption();
				cout << "Enter one more:(2) ";
			}*/
		} while (goodInput == 0);

		if (arr[x][y] != 1 && arr[x][y] != 10)
		{
			if (size == 1)
			{
				arr[x][y] = 1;
				SetZoneNeatShip(arr);
				break;
			}
		}

		cout << "Enter direct: (1-left,2-top,3-right,4-bottom):  ";
		goodInput = 0;
		do
		{
			cin >> direct;
			if (direct > 0 && direct < 5)
			{
				goodInput = 1;
			}
			else
			{
				Exeption();
				cout << "Enter one more:(3) ";
			}

		} while (goodInput == 0);


		if (arr[x][y] != 1 && arr[x][y] != 10) {
			switch (direct)
			{
			case 1:
				for (int i = 1; i < size; i++)
				{
					if (y - i == 0)
					{
						Exeption();
						break;

					}
					if (arr[x][y - i] != 1 && arr[x][y - i] != 10)
					{

						counter++;
						if (counter == size)
						{
							set = 1;
						}
					}
				}
				break;
			case 2:
				for (int i = 1; i < size; i++)
				{
					if (x - i == 0)
					{
						Exeption();
						break;

					}
					if (arr[x - i][y] != 1 && arr[x - i][y] != 10)
					{

						counter++;
						if (counter == size)
						{
							set = 1;
						}
					}
				}
				break;
			case 3:
				for (int i = 1; i < size; i++)
				{
					if (y + i == 11)
					{
						Exeption();
						break;
					}
					if (arr[x][y + i] != 1 && arr[x][y + i] != 10)
					{
						counter++;
						if (counter == size)
						{
							set = 1;
						}
					}
				}
				break;
			case 4:
				for (int i = 1; i < size; i++)
				{
					if (x + i == 11)
					{
						Exeption();
						break;
					}
					if (arr[x + i][y] != 1 && arr[x + i][y] != 10)
					{
						counter++;
						if (counter == size)
						{
							set = 1;
						}
					}
				}
				break;
			} // конец switch
		}
		else
		{
			Exeption();
		}
	}

	arr[x][y] = 1;

	if (size != 1) {
		if (x > 0 && x < 11 && y > 0 && y < 11)
		{
			switch (direct)
			{
			case 1:
				for (int i = 1; i < size; i++) {
					arr[x][y - i] = 1;
				}
				break;
			case 2:
				for (int i = 1; i < size; i++) {
					arr[x - i][y] = 1;
				}
				break;
			case 3:
				for (int i = 1; i < size; i++) {
					arr[x][y + i] = 1;
				}
				break;
			case 4:
				for (int i = 1; i < size; i++) {
					arr[x + i][y] = 1;
				}
				break;
			}
		}
	}
	SetZoneNeatShip(arr);
}
int CountLenght(const char* str) {
	int lenght = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		lenght++;
	}
	return lenght;
}
int getXfromCoordinate(char*coordinate) {
	int x;
	switch (toupper(coordinate[0]))
	{
	case 'A': x = 1; break;
	case 'B': x = 2; break;
	case 'C': x = 3; break;
	case 'D': x = 4; break;
	case 'E': x = 5; break;
	case 'F': x = 6; break;
	case 'G': x = 7; break;
	case 'H': x = 8; break;
	case 'I': x = 9; break;
	case 'J': x = 10; break;
	}
	return x;
}
int getYfromCoordinate(char*coordinate) {
	int y;
	if (CountLenght(coordinate) == 2)
	{
		switch (coordinate[1])
		{
		case '1': y = 1; break;
		case '2': y = 2; break;
		case '3': y = 3; break;
		case '4': y = 4; break;
		case '5': y = 5; break;
		case '6': y = 6; break;
		case '7': y = 7; break;
		case '8': y = 8; break;
		case '9': y = 9; break;
		}
		return y;
	}
	else
	{
		return 10;
	}

}
void StringToUpper(char* str) {
	for (int i = 0; i < CountLenght(str); i++)
	{
		*(str + i) = toupper(*(str + i));
	}
}
void ManualSetShipsScenary(int**arr) {
	AddShipManual(arr, 4);
	AddShipManual(arr, 3);
	AddShipManual(arr, 3);
	AddShipManual(arr, 2);
	AddShipManual(arr, 2);
	AddShipManual(arr, 2);
	AddShipManual(arr, 1);
	AddShipManual(arr, 1);
	AddShipManual(arr, 1);
	AddShipManual(arr, 1);
}
void Exeption() {
	system("color 40");
	Sleep(300);
	system("color 07");
}
void Success() {
	system("color 20");
	Sleep(150);
	system("color 07");
}
void MyShoot(int **enemy, int** show, int** my) {
	char *coordinate = new char[10];
	int goodInput = 0;
	int miss = 0;
	cout << "Input coordinate: ";
	int x, y;

	while (miss == 0)
	{
		do
		{
			gets_s(coordinate, 10);
			goodInput = 0;
			int ansi = int(coordinate[0]);
			int length = CountLenght(coordinate);

			if (length > 1 && length < 4 && ((ansi < 107 && ansi > 96) || (ansi > 64 && ansi < 75)))
			{
				if (int(coordinate[1]) > 48 && int(coordinate[1]) < 58)
				{
					x = getYfromCoordinate(coordinate);
					y = getXfromCoordinate(coordinate);
					if (show[x][y] == 0)
					{
						goodInput = 1;
					}
					else
					{
						cout << "You shoot here before!!!\n";
						cout << "Enter one more: ";
						Exeption();
					}
				}
				else
				{
					cout << "Enter one more: ";
					Exeption();
				}
			}
			else
			{
				cout << "Enter one more: ";
				Exeption();
			}
		} while (goodInput == 0);

		show[x][y] = 1;
		if (enemy[x][y] == 1)
		{
			enemy[x][y] = 3;
			SetZoneAfterDie(enemy, show);
			UpdateGame(enemy, my, show);
			if (WinOrNo(my, enemy) == 1) {
				break;
			}
			cout << "You damage him ))). Shoot one more: ";
			//Success();
		}
		else
		{
			miss = 1;
			enemy[x][y] = 2;
		}
	}
}
void SetZoneAfterDie(int **arr, int** show) {
	int die = 0;

	for (int i = 0; i < 10; i++)
	{
		die = 0;
		for (int x = 1; x < 11; x++)
		{
			for (int y = 1; y < 11; y++)
			{
				if (arr[x][y] == 3)
				{
					if (arr[x][y + 1] != 1)
					{
						die++;
					}
					if (arr[x][y - 1] != 1)
					{
						die++;
					}
					if (arr[x - 1][y] != 1)
					{
						die++;
					}
					if (arr[x + 1][y] != 1)
					{
						die++;
					}
					if (die == 4)
					{
						arr[x][y] = 6;
					}
				}
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int x = 1; x < 11; x++)
		{
			for (int y = 1; y < 11; y++)
			{
				if (arr[x][y] == 3)
				{
					if (arr[x][y + 1] == 6)
					{
						arr[x][y + 1] = 3;
					}
					if (arr[x][y - 1] == 6)
					{
						arr[x][y - 1] = 3;
					}
					if (arr[x - 1][y] == 6)
					{
						arr[x - 1][y] = 3;
					}
					if (arr[x + 1][y] == 6)
					{
						arr[x + 1][y] = 3;
					}

				}
			}
		}
	}


	for (int x = 1; x < 11; x++)
	{
		for (int y = 1; y < 11; y++)
		{
			if (arr[x][y] == 6)
			{
				if (arr[x][y + 1] != 3 && arr[x][y + 1] != 6)
				{
					show[x][y + 1] = 1;
					arr[x][y + 1] = 2;
				}
				if (arr[x][y - 1] != 3 && arr[x][y - 1] != 6)
				{
					arr[x][y - 1] = 2;
					show[x][y - 1] = 1;
				}
				if (arr[x - 1][y] != 3 && arr[x - 1][y] != 6)
				{
					arr[x - 1][y] = 2;
					show[x - 1][y] = 1;
				}
				if (arr[x + 1][y] != 3 && arr[x + 1][y] != 6)
				{
					arr[x + 1][y] = 2;
					show[x + 1][y] = 1;
				}
				arr[x - 1][y - 1] = 2;
				arr[x - 1][y + 1] = 2;
				arr[x + 1][y + 1] = 2;
				arr[x + 1][y - 1] = 2;

				show[x - 1][y - 1] = 1;
				show[x - 1][y + 1] = 1;
				show[x + 1][y + 1] = 1;
				show[x + 1][y - 1] = 1;

			}
		}
	}
}
void BotShoot(int **enemy, int** show, int** my) {
	int x;
	int y;
	int miss = 0;

	while (miss == 0) {

		do
		{
			x = random(1, 10);
			y = random(1, 10);

		} while (my[x][y] == 2 || my[x][y] == 3);

		if (my[x][y] == 1)
		{
			my[x][y] = 3;
			SetZoneAfterDieForMy(my);
			UpdateGame(enemy, my, show);
			if (WinOrNo(my, enemy) == -1) {
				break;
			}
			cout << "You are damaged!!!\n";
			Sleep(1000);
		}
		if (my[x][y] == 0)
		{
			miss = 1;
			my[x][y] = 2;
		}

	}
}
void SetZoneAfterDieForMy(int **arr) {
	int die = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int x = 1; x < 11; x++)
		{
			for (int y = 1; y < 11; y++)
			{
				if (arr[x][y] == 3)
				{
					die = 0;
					if (arr[x][y + 1] != 1)
					{
						die++;
					}
					if (arr[x][y - 1] != 1)
					{
						die++;
					}
					if (arr[x - 1][y] != 1)
					{
						die++;
					}
					if (arr[x + 1][y] != 1)
					{
						die++;
					}
					if (die == 4)
					{
						arr[x][y] = 6;
					}
				}
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int x = 1; x < 11; x++)
		{
			for (int y = 1; y < 11; y++)
			{
				if (arr[x][y] == 3)
				{
					if (arr[x][y + 1] == 6)
					{
						arr[x][y + 1] = 3;
					}
					if (arr[x][y - 1] == 6)
					{
						arr[x][y - 1] = 3;
					}
					if (arr[x - 1][y] == 6)
					{
						arr[x - 1][y] = 3;
					}
					if (arr[x + 1][y] == 6)
					{
						arr[x + 1][y] = 3;
					}

				}
			}
		}
	}


	for (int x = 1; x < 11; x++)
	{
		for (int y = 1; y < 11; y++)
		{
			if (arr[x][y] == 6)
			{
				if (arr[x][y + 1] != 3 && arr[x][y + 1] != 6)
				{

					arr[x][y + 1] = 2;
				}
				if (arr[x][y - 1] != 3 && arr[x][y - 1] != 6)
				{
					arr[x][y - 1] = 2;
				}
				if (arr[x - 1][y] != 3 && arr[x - 1][y] != 6)
				{
					arr[x - 1][y] = 2;
				}
				if (arr[x + 1][y] != 3 && arr[x + 1][y] != 6)
				{
					arr[x + 1][y] = 2;
				}
				arr[x - 1][y - 1] = 2;
				arr[x - 1][y + 1] = 2;
				arr[x + 1][y + 1] = 2;
				arr[x + 1][y - 1] = 2;
			}
		}
	}

}
int WinOrNo(int** my, int** enemy) {
	int my_ships = 0;
	int enemy_ships = 0;

	for (int x = 1; x < 11; x++)
	{
		for (int y = 1; y < 11; y++)
		{
			if (my[x][y] == 1)
			{
				my_ships++;
				break;
			}

			if (enemy[x][y] == 1)
			{
				enemy_ships++;
				break;
			}
		}
	}
	if (my_ships == 0)
	{
		return -1;
	}
	if (enemy_ships == 0)
	{
		return 1;
	}
	return 0;
}
