#include <iostream>
#include <conio.h>
#include <Windows.h>

#define MAP_SIZE 100
#define PLAYER	'@'
#define PORTAL	'P'
#define COIN	'c'
#define EMPTY	' '
#define HEALTH  'H'
#define TRAP    '0'
#define ENEMY   'E'
#define BOSS    'B'
#define SHOP    'S'

struct Character
{
	int x, y;
};

char map[MAP_SIZE][MAP_SIZE];
Character player = { 1, 1 };
int level = 0;
int coins = 0;
int health_player = 3;
int damage = 1;
int health_enemy = 0;
char shop;
int wsword = 0;
int isword = 0;
int bow = 0;
int sp = 0;
int heal = 0;
bool tr = true;

void START()
{
	int YN = 0;
	printf("							        ����������\n");
	printf("������� 0 ����� ���������� ��������, ������� 1 ���� �� ������ ������ ��������\n");
	printf("(����� ���� ��������� ��������, �������� ������� �� ���� �����!)\n");
	scanf_s("%i", &YN);
	switch (YN)
	{
	case 1:
		printf("����� ������� ���� � ��� ����������� ������ ���� ������� ���������� ���� �� ��������� ����������\n");
		printf("����� ������ ����������� ������� W A S D\n");
		printf("����� ������������ �������� \"@\"\n");
		printf("������ ������������ �������� \"c\"\n");
		printf("������� �� ��������� ������� ������������ �������� \"P\"\n");
		printf("����� ���� ����� � �������, �� ��� ��� ���������!\n");
		printf("����� ������������ �������� \"E\", � ��� ��� ������� ��������� ���������� �����\n");
		printf("������� ������������ �������� \"H\", ��� �������� ��� 1 �����, ����� �� ��������� � ��� ����� 5 ������, �� ������������ �� ������ ������ �� 3\n");
		printf("������ �� ������ ��������� � ��������, ������� ������������ �������� \"S\"\n");
	case 0:
		break;
	}
	system("pause");
	system("cls");
}

int readMap(const char filename[])
{
	FILE* file;
	if (fopen_s(&file, filename, "rt") != 0)
	{
		printf("�� ���������� ������� ���� �����.\n");
		system("pause");
		return 1;
	}

	for (int y = 0; y < 20; y++)
		fgets(map[y], MAP_SIZE, file);

	fclose(file);
	return 0;
}

bool canGoTo(int x, int y)
{
	if (map[y][x] == EMPTY ||
		map[y][x] == PORTAL ||
		map[y][x] == COIN ||
		map[y][x] == HEALTH ||
		map[y][x] == TRAP ||
		map[y][x] == ENEMY ||
		map[y][x] == BOSS ||
		map[y][x] == SHOP
		) return true;
	else return false;
}

void printMap()
{
	printf("������� �������: %i\n", level);
	printf("������: %i\n", health_player);
	printf("� ��� �����: %i\n\n", coins);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			if (x == player.x && y == player.y)
				printf("%c", PLAYER);
			else
				printf("%c", map[y][x]);
		}
		printf("\n");
	}
}

int Enemy()
{
	int i = 0;
	bool cool = true;
	char at;
	char cr;

	if (level == 1)
	{
		health_enemy = 3;
		printf("�� ��������� �����, � ���� 3 �����\n");
		printf("��������� ������ ����� ���������\n");
		while (cool == true)
		{
			if (damage >= 3)
			{
				cr = _getch();
				switch (cr)
				{
				case ' ':
					printf("�� ����� ����� � ������ ����� � �������� 3 ������\n");
					coins += 3;
					cool = false;
					break;
				}
			}
			if (damage >= 3)
				break;
			at = _getch();
			switch (at)
			{
			case ' ':
				i++;
				if (damage == 1)
				{
					printf("�� ����� ����� 1 �����\n");
					health_enemy--;
				}
				if (i == 2 || i == 4 || i == 6 || i == 8 || i == 10)
				{
					printf("���� ������ ��� � ���� ��� 1 �����\n");
					health_player--;
				}
				if (health_player == 0)
				{
					printf("�� ������ � �������� � �������� %i �����\n", coins);
					return 0;
				}
				if (health_enemy <= 0)
				{
					printf("�� ����� �����, � �������� 3 ������\n");
					coins += 3;
					cool = false;
					system("pause");
					break;
				}
			}
		}
	}
	if (level == 2)
	{
		i = 0;
		cool = true;
		health_enemy = 4;
		printf("�� ��������� �����, � ���� 4 �����\n");
		printf("��������� ������ ����� ���������\n");
		while (cool == true)
		{
			i++;
			if (damage >= 4)
			{
				cr = _getch();
				switch (cr)
				{
				case ' ':
					printf("�� ����� ����� � ������ ����� � �������� 3 ������\n");
					coins += 3;
					cool = false;
					break;
				}
			}
			if (damage >= 4)
				break;
			at = _getch();
			switch (at)
			{
			case ' ':
				printf("�� ����� ����� %i �����/������\n", damage);
				health_enemy -= damage;
				if (i == 1 || i == 4 || i == 6 || i == 9)
				{
					printf("���� ������ ��� � ���� ��� 1 �����\n");
					health_player--;
				}
				if (health_player == 0)
				{
					printf("�� ������ � �������� � �������� %i �����\n", coins);
					system("pause");
					return 0;
				}
				if (health_enemy <= 0)
				{
					printf("�� ����� �����, � �������� 3 ������\n");
					coins += 3;
					cool = false;
					system("pause");
					break;
				}
			}
		}
	}
	if (level == 3)
	{
		i = 0;
		cool = true;
		health_enemy = 5;
		printf("�� ��������� �����, � ���� 5 ������\n");
		printf("��������� ������ ����� ���������\n");
		while (cool == true)
		{
			i++;
			if (damage >= 5)
			{
				cr = _getch();
				switch (cr)
				{
				case ' ':
					printf("�� ����� ����� � ������ ����� � �������� 4 ������\n");
					coins += 4;
					cool = false;
					break;
				}
			}
			if (damage >= 5)
				break;
			at = _getch();
			switch (at)
			{
			case ' ':
				printf("�� ����� ����� %i �����/������\n", damage);
				health_enemy -= damage;
				if (i == 1 || i == 4 || i == 6 || i == 9)
				{
					printf("���� ������ ��� � ���� ��� 1 �����\n");
					health_player--;
				}
				if (health_player == 0)
				{
					printf("�� ������ � �������� � �������� %i �����\n", coins);
					system("pause");
					return 0;
				}
				if (health_enemy <= 0)
				{
					printf("�� ����� �����, � �������� 4 ������\n");
					coins += 4;
					cool = false;
					system("pause");
					break;
				}
			}
		}
	}
	if (level == 4)
	{
		i = 0;
		cool = true;
		health_enemy = 6;
		printf("�� ��������� �����, � ���� 6 ������\n");
		printf("��������� ������ ����� ���������\n");
		while (cool == true)
		{
			i++;
			if (damage >= 6)
			{
				cr = _getch();
				switch (cr)
				{
				case ' ':
					printf("�� ����� ����� � ������ ����� � �������� 4 ������\n");
					coins += 4;
					cool = false;
					break;
				}
			}
			if (damage >= 6)
				break;
			at = _getch();
			switch (at)
			{
			case ' ':
				printf("�� ����� ����� %i �����/������\n", damage);
				health_enemy -= damage;
				if (i == 1 || i == 5 || i == 7 || i == 10)
				{
					printf("���� ������ ��� � ���� ��� 1 �����\n");
					health_player--;
				}
				if (health_player == 0)
				{
					printf("�� ������ � �������� � �������� %i �����\n", coins);
					system("pause");
					return 0;
				}
				if (health_enemy <= 0)
				{
					printf("�� ����� �����, � �������� 4 ������\n");
					coins += 4;
					cool = false;
					system("pause");
					break;
				}
			}
		}
	}
	if (level == 5)
	{
		i = 0;
		cool = true;
		health_enemy = 8;
		printf("�� ��������� �����, � ���� 8 ������\n");
		printf("��������� ������ ����� ���������\n");
		while (cool == true)
		{
			i++;
			if (damage >= 8)
			{
				cr = _getch();
				switch (cr)
				{
				case ' ':
					printf("�� ����� ����� � ������ ����� � �������� 5 �����\n");
					coins += 5;
					cool = false;
					break;
				}
			}
			if (damage >= 8)
				break;
			at = _getch();
			switch (at)
			{
			case ' ':
				printf("�� ����� ����� %i �����/������\n", damage);
				health_enemy -= damage;
				if (i == 1 || i == 5 || i == 7 || i == 10 || i == 14)
				{
					printf("���� ������ ��� � ���� ��� 1 �����\n");
					health_player--;
				}
				if (health_player == 0)
				{
					printf("�� ������ � �������� � �������� %i �����\n", coins);
					system("pause");
					return 0;
				}
				if (health_enemy <= 0)
				{
					printf("�� ����� �����, � �������� 5 �����\n");
					coins += 5;
					cool = false;
					system("pause");
					break;
				}
			}
		}
	}
	if (level == 6)
	{
		i = 0;
		cool = true;
		health_enemy = 11;
		printf("�� ��������� �����, � ���� 11 ������\n");
		printf("��������� ������ ����� ���������\n");
		while (cool == true)
		{
			i++;
			if (damage >= 11)
			{
				cr = _getch();
				switch (cr)
				{
				case ' ':
					printf("�� ����� ����� � ������ ����� � �������� 5 �����\n");
					coins += 5;
					cool = false;
					break;
				}
			}
			if (damage >= 11)
				break;
			at = _getch();
			switch (at)
			{
			case ' ':
				printf("�� ����� ����� %i �����/������\n", damage);
				health_enemy -= damage;
				if (i == 1 || i == 5 || i == 7 || i == 10 || i == 14 || i == 17)
				{
					printf("���� ������ ��� � ���� ��� 1 �����\n");
					health_player--;
				}
				if (health_player == 0)
				{
					printf("�� ������ � �������� � �������� %i �����\n", coins);
					system("pause");
					return 0;
				}
				if (health_enemy <= 0)
				{
					printf("�� ����� �����, � �������� 5 �����\n");
					coins += 5;
					cool = false;
					system("pause");
					break;
				}
			}
		}
	}
	return 0;
}

int Shop()
{
	bool sh = true;
	while (sh == true)
	{
		system("cls");
		if (coins == 1)
			printf("� ��� 1 ������\n");
		if (coins > 1 && coins < 5)
			printf("� ��� %i ������\n", coins);
		if (coins >= 5)
			printf("� ��� %i �����\n", coins);
		printf("������� 1 ��� ���� ����� ��������� ���������� ����\n������� 2 ����� ��������� �������� ����\n������� 3 ����� ��������� ���\n������� 4 ��� ���� ����� ��������� �����-������\n������� 5 ��� ���� ����� ��������� �������\n������� 0 ����� �����\n");
		
		shop = _getch();
		switch (shop)
		{
		case '1':
			printf("���������� ����\n����: 3\n���������: 8 �����\n\n");
			printf("������� 1 ����� ������\n������� 0 ����� �����\n");
			scanf_s("%i", &wsword);
			if (wsword == 0)
				break;
				switch (wsword)
				{
				case 1:
					if (coins < 8)
					{
						printf("� ��� �� ���������� �����\n");
						break;
					}
					printf("�� ������ ���������� ����, ��� ���� �������� �� 3\n");
					coins -= 8;
					damage = 3;
					break;
				}
				if (wsword == 1)
					break;
		case '2':
			printf("�������� ����\n����: 5\n���������: 15 �����\n\n");
			printf("������� 1 ����� ������\n������� 0 ����� �����\n");
			scanf_s("%i", &isword);
			if (isword == 0)
				break;
			switch (isword)
			{
			case 1:
				if (coins < 15)
				{
					printf("� ��� �� ���������� �����\n");
					break;
				}
				printf("�� ������ �������� ����, ��� ���� �������� �� 5\n");
				coins -= 15;
				damage = 5;
				break;
			}
			if (isword == 1)
				break;
		case '3':
			printf("���\n����: 7\n���������: 25 ������\n\n");
			printf("������� 1 ����� ������\n������� 0 ����� �����\n");
			scanf_s("%i", &bow);
			if (bow == 0)
				break;
			switch (bow)
			{
			case 1:
				if (coins < 25)
				{
					printf("� ��� �� ���������� �����\n");
					break;
				}
				printf("�� ������ ���, ��� ���� �������� �� 7\n");
				coins -= 25;
				damage = 7;
				break;
			}
			if (bow == 1)
				break;
		case '4':
			printf("�����-������\n����: 10\n���������: 50 �����\n\n");
			printf("������� 1 ����� ������\n������� 0 ����� �����\n");
			scanf_s("%i", &sp);
			if (sp == 0)
				break;
			switch (sp)
			{
			case 1:
				if (coins < 50)
				{
					printf("� ��� �� ���������� �����\n");
					break;
				}
				printf("�� ������ �����-������, ��� ���� �������� �� 10\n");
				coins -= 50;
				damage = 10;
				break;
			}
			if (sp == 1)
				break;
		case '5':
			printf("�������\n�����: +1\n���������: 10 �����\n\n");
			printf("������� 1 ����� ������\n������� 0 ����� �����\n");
			scanf_s("%i", &heal);
			if (heal == 0)
				break;
			switch (heal)
			{
			case 1:
				if (coins < 10)
				{
					printf("� ��� �� ���������� �����\n");
					break;
				}
				printf("�� ������ ��������, ���� ����� ��������� �� 1\n");
				coins -= 10;
				health_player++;
				break;
			}
			if (heal == 1)
				break;
		case '0':
			sh = false;
			break;
		default:
			sh = false;
			break;
		}
	}
	return 0;
}

int Boss()
{
	int i = 0;
	char atb;
	bool boss1 = true;
	bool boss2 = true;
	bool boss3 = true;
	int health_boss = 50;

	printf("�� �� �������� ����, �� ������� ����!\n");
	Sleep(3000);
	printf("� ��c�� 3 ����:\n������ ����, � ���� 50 ������, � �� ���� ���� ����� ������� ������ 3 �����\n������ ����, � ����� 25 ������, � �� ���� ���� ������ ���� ����\n��������� ���� � ����� 100 ������ � �� ���� ���� ������ ���� 5 ����\n�����!\n\n");
	if (damage >= 10)
		printf("������ ��� � ����� �����-������!\n\n");
	else
		printf("\"������ � �� ����� �����-������!?\" - ������� �� ��� � ����\n\n");

	Sleep(5000);
	printf("��������!!!\n");
	health_boss = 50;
	while (boss1 == true)
	{ 
		atb = _getch();
		switch (atb)
		{
		case ' ':
			printf("�� ������� ����� %i �����\n", damage);
			health_boss -= damage;
			if (i == 3 || i == 6 || i == 9 || i == 12 || i == 15)
			{
				printf("���� ��� ��� 1 �����\n");
				health_player--;
			}
			if (health_boss <= 0)
			{
				printf("������ ���� ��������, ����� �������������, ��������� �O BTOPO� ����\n");
				health_player = 5;
				boss1 = false;
			}
			i++;
		}
	}
	health_boss = 25;
	while (boss2 == true)
	{
		atb = _getch();
		switch (atb)
		{
		case ' ':
			printf("�� ������� ����� %i �����\n", damage);
			health_boss -= damage;
			if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8)
			{
				printf("���� ��� ��� 1 �����\n");
				health_player--;
			}
			if (health_boss <= 0)
			{
				printf("������ ���� ��������, ����� �������������, ��������� � ��������� ����\n");
				health_player = 5;
				boss2 = false;
			}
			i++;
		}
	}
	health_boss = 100;
	while (boss3 == true)
	{
		atb = _getch();
		switch (atb)
		{
		case ' ':
			printf("�� ������� ����� %i �����\n", damage);
			health_boss -= damage;
			if (i == 5 || i == 10 || i == 15 || i == 20 || i == 25 || i == 30 || i == 35)
			{
				printf("���� ��� ��� 1 �����\n");
				health_player--;
			}
			if (health_boss <= 0)
			{
				printf("�� �������� �����!!!\n");
				boss3 = false;
				system("pause");
				break;
			}
			i++;
		}
	}
	return 0;
}

int goNextLevel()
{
	level++;

	switch (level)
	{
	case 1:
		if (readMap("level1.txt") != 0) return 1;
		player = { 1, 1 };
		break;
	case 2:
		if (readMap("level2.txt") != 0) return 1;
		player = { 18, 18 };
		break;
	case 3:
		if (readMap("level3.txt") != 0) return 1;
		player = { 1, 1 };
		break;
	case 4:
		if (readMap("level4.txt") != 0) return 1;
		player = { 15, 15 };
		break;
	case 5:
		if (readMap("level5.txt") != 0) return 1;
		player = { 9, 9 };
		break;
	case 6:
		if (readMap("level6.txt") != 0) return 1;
		player = { 1, 1 };
		break;
	}
	return 0;
}

int checkAction()
{
	switch (map[player.y][player.x])
	{
	case EMPTY:
		break;
	case PORTAL:
		if (goNextLevel() != 0)
			return 1;
		break;
	case COIN:
		coins++;
		map[player.y][player.x] = EMPTY;
		break;
	case HEALTH:
		if (health_player < 3)
		{
			health_player++;
			map[player.y][player.x] = EMPTY;
		}
		break;
	case TRAP:
		health_player--;
		map[player.y][player.x] = EMPTY;
		break;
	case ENEMY:
		Enemy();
		map[player.y][player.x] = EMPTY;
		break;
	case BOSS:
		Boss();
		map[player.y][player.x] = EMPTY;
		tr = false;
		break;
	case SHOP:
		Shop();
		break;
	}
	return 0;
}

int main()
{
	system("chcp 1251");
	system("cls");

	level = 0;
	coins = 0;
	health_player = 5;

	START();

	if (goNextLevel() != 0)
		return 1;

	char key;

	while (tr == true)
	{
		system("cls");
		if (health_player == 0)
		{
			printf("�� ���������\n");
			system("pause");
			return 0;
		}
		printMap();

		key = _getch();
		switch (key)
		{
		case 'w':
			if (canGoTo(player.x, player.y - 1))
				player.y--;
			break;

		case 's':
			if (canGoTo(player.x, player.y + 1))
				player.y++;
			break;

		case 'd':
			if (canGoTo(player.x + 1, player.y))
				player.x++;
			break;

		case 'a':
			if (canGoTo(player.x - 1, player.y))
				player.x--;
			break;
		}

		if (checkAction() != 0)
			return 1;
	}
	system("cls");
	printf("������� �� ����!!!");
	system("pause");
	return 0;
}