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
	printf("							        ПОДЗЕМЕЛЬЕ\n");
	printf("Нажмите 0 чтобы пропустить обучение, нажмите 1 если вы хотите пройти обучение\n");
	printf("(Чтобы игра нормально работала, откройте консоль на весь экран!)\n");
	scanf_s("%i", &YN);
	switch (YN)
	{
	case 1:
		printf("Перед началом игры у вас обязательно должен быть включен английский язык на раскладке клавиатуры\n");
		printf("Чтобы ходить используйте клавиши W A S D\n");
		printf("Игрок обозначается символом \"@\"\n");
		printf("Монеты обозначаются символом \"c\"\n");
		printf("Порталы на следующий уровень обозначаются символом \"P\"\n");
		printf("Также есть стены и ловушки, ну там сам разберёшся!\n");
		printf("Враги обозначаются символом \"E\", с них вам выпадет некоторое количество монет\n");
		printf("Аптечки обозначаются символом \"H\", они добавять вам 1 жизнь, когда вы появитесь у вас будет 5 жизней, но восстановить вы можете только до 3\n");
		printf("Монеты ты можешь потратить в магазине, который обозначается символом \"S\"\n");
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
		printf("Не получилось открыть файл карты.\n");
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
	printf("Текущий уровень: %i\n", level);
	printf("Жизней: %i\n", health_player);
	printf("У вас монет: %i\n\n", coins);

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
		printf("Вы встретили врага, у него 3 жизни\n");
		printf("Нажимайте ПРОБЕЛ чтобы атаковать\n");
		while (cool == true)
		{
			if (damage >= 3)
			{
				cr = _getch();
				switch (cr)
				{
				case ' ':
					printf("Вы убили врага с одного удара и получили 3 монеты\n");
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
					printf("Вы сняли врагу 1 жизнь\n");
					health_enemy--;
				}
				if (i == 2 || i == 4 || i == 6 || i == 8 || i == 10)
				{
					printf("Враг ударил вас и снял вам 1 жизнь\n");
					health_player--;
				}
				if (health_player == 0)
				{
					printf("Вы умерли в сражении и потеряли %i монет\n", coins);
					return 0;
				}
				if (health_enemy <= 0)
				{
					printf("Вы убили врага, и получили 3 монеты\n");
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
		printf("Вы встретили врага, у него 4 жизни\n");
		printf("Нажимайте ПРОБЕЛ чтобы атаковать\n");
		while (cool == true)
		{
			i++;
			if (damage >= 4)
			{
				cr = _getch();
				switch (cr)
				{
				case ' ':
					printf("Вы убили врага с одного удара и получили 3 монеты\n");
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
				printf("Вы сняли врагу %i жизни/жизней\n", damage);
				health_enemy -= damage;
				if (i == 1 || i == 4 || i == 6 || i == 9)
				{
					printf("Враг ударил вас и снял вам 1 жизнь\n");
					health_player--;
				}
				if (health_player == 0)
				{
					printf("Вы умерли в сражении и потеряли %i монет\n", coins);
					system("pause");
					return 0;
				}
				if (health_enemy <= 0)
				{
					printf("Вы убили врага, и получили 3 монеты\n");
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
		printf("Вы встретили врага, у него 5 жизней\n");
		printf("Нажимайте ПРОБЕЛ чтобы атаковать\n");
		while (cool == true)
		{
			i++;
			if (damage >= 5)
			{
				cr = _getch();
				switch (cr)
				{
				case ' ':
					printf("Вы убили врага с одного удара и получили 4 монеты\n");
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
				printf("Вы сняли врагу %i жизни/жизней\n", damage);
				health_enemy -= damage;
				if (i == 1 || i == 4 || i == 6 || i == 9)
				{
					printf("Враг ударил вас и снял вам 1 жизнь\n");
					health_player--;
				}
				if (health_player == 0)
				{
					printf("Вы умерли в сражении и потеряли %i монет\n", coins);
					system("pause");
					return 0;
				}
				if (health_enemy <= 0)
				{
					printf("Вы убили врага, и получили 4 монеты\n");
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
		printf("Вы встретили врага, у него 6 жизней\n");
		printf("Нажимайте ПРОБЕЛ чтобы атаковать\n");
		while (cool == true)
		{
			i++;
			if (damage >= 6)
			{
				cr = _getch();
				switch (cr)
				{
				case ' ':
					printf("Вы убили врага с одного удара и получили 4 монеты\n");
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
				printf("Вы сняли врагу %i жизни/жизней\n", damage);
				health_enemy -= damage;
				if (i == 1 || i == 5 || i == 7 || i == 10)
				{
					printf("Враг ударил вас и снял вам 1 жизнь\n");
					health_player--;
				}
				if (health_player == 0)
				{
					printf("Вы умерли в сражении и потеряли %i монет\n", coins);
					system("pause");
					return 0;
				}
				if (health_enemy <= 0)
				{
					printf("Вы убили врага, и получили 4 монеты\n");
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
		printf("Вы встретили врага, у него 8 жизней\n");
		printf("Нажимайте ПРОБЕЛ чтобы атаковать\n");
		while (cool == true)
		{
			i++;
			if (damage >= 8)
			{
				cr = _getch();
				switch (cr)
				{
				case ' ':
					printf("Вы убили врага с одного удара и получили 5 монет\n");
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
				printf("Вы сняли врагу %i жизни/жизней\n", damage);
				health_enemy -= damage;
				if (i == 1 || i == 5 || i == 7 || i == 10 || i == 14)
				{
					printf("Враг ударил вас и снял вам 1 жизнь\n");
					health_player--;
				}
				if (health_player == 0)
				{
					printf("Вы умерли в сражении и потеряли %i монет\n", coins);
					system("pause");
					return 0;
				}
				if (health_enemy <= 0)
				{
					printf("Вы убили врага, и получили 5 монет\n");
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
		printf("Вы встретили врага, у него 11 жизней\n");
		printf("Нажимайте ПРОБЕЛ чтобы атаковать\n");
		while (cool == true)
		{
			i++;
			if (damage >= 11)
			{
				cr = _getch();
				switch (cr)
				{
				case ' ':
					printf("Вы убили врага с одного удара и получили 5 монет\n");
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
				printf("Вы сняли врагу %i жизни/жизней\n", damage);
				health_enemy -= damage;
				if (i == 1 || i == 5 || i == 7 || i == 10 || i == 14 || i == 17)
				{
					printf("Враг ударил вас и снял вам 1 жизнь\n");
					health_player--;
				}
				if (health_player == 0)
				{
					printf("Вы умерли в сражении и потеряли %i монет\n", coins);
					system("pause");
					return 0;
				}
				if (health_enemy <= 0)
				{
					printf("Вы убили врага, и получили 5 монет\n");
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
			printf("У вас 1 монета\n");
		if (coins > 1 && coins < 5)
			printf("У вас %i монеты\n", coins);
		if (coins >= 5)
			printf("У вас %i монет\n", coins);
		printf("Нажмите 1 для того чтобы осмотреть деревянный мечь\nНажмите 2 чтобы осмотреть железный мечь\nНажмите 3 чтобы осмотреть лук\nНажмите 4 для того чтобы осмотреть супер-оружие\nНажмите 5 для того чтобы осмотреть аптечку\nНажмите 0 чтобы выйти\n");
		
		shop = _getch();
		switch (shop)
		{
		case '1':
			printf("Деревянный мечь\nУрон: 3\nСтоимость: 8 монет\n\n");
			printf("Нажмите 1 чтобы купить\nНажмите 0 чтобы выйти\n");
			scanf_s("%i", &wsword);
			if (wsword == 0)
				break;
				switch (wsword)
				{
				case 1:
					if (coins < 8)
					{
						printf("У вас не достатачно монет\n");
						break;
					}
					printf("Вы купили деревянный мечь, ваш урон увеличен до 3\n");
					coins -= 8;
					damage = 3;
					break;
				}
				if (wsword == 1)
					break;
		case '2':
			printf("Железный мечь\nУрон: 5\nСтоимость: 15 монет\n\n");
			printf("Нажмите 1 чтобы купить\nНажмите 0 чтобы выйти\n");
			scanf_s("%i", &isword);
			if (isword == 0)
				break;
			switch (isword)
			{
			case 1:
				if (coins < 15)
				{
					printf("У вас не достатачно монет\n");
					break;
				}
				printf("Вы купили железный мечь, ваш урон увеличен до 5\n");
				coins -= 15;
				damage = 5;
				break;
			}
			if (isword == 1)
				break;
		case '3':
			printf("Лук\nУрон: 7\nСтоимость: 25 монеты\n\n");
			printf("Нажмите 1 чтобы купить\nНажмите 0 чтобы выйти\n");
			scanf_s("%i", &bow);
			if (bow == 0)
				break;
			switch (bow)
			{
			case 1:
				if (coins < 25)
				{
					printf("У вас не достатачно монет\n");
					break;
				}
				printf("Вы купили лук, ваш урон увеличен до 7\n");
				coins -= 25;
				damage = 7;
				break;
			}
			if (bow == 1)
				break;
		case '4':
			printf("Супер-оружие\nУрон: 10\nСтоимость: 50 монет\n\n");
			printf("Нажмите 1 чтобы купить\nНажмите 0 чтобы выйти\n");
			scanf_s("%i", &sp);
			if (sp == 0)
				break;
			switch (sp)
			{
			case 1:
				if (coins < 50)
				{
					printf("У вас не достатачно монет\n");
					break;
				}
				printf("Вы купили супер-оружие, ваш урон увеличен до 10\n");
				coins -= 50;
				damage = 10;
				break;
			}
			if (sp == 1)
				break;
		case '5':
			printf("Аптечка\nЖизни: +1\nСтоимость: 10 монет\n\n");
			printf("Нажмите 1 чтобы купить\nНажмите 0 чтобы выйти\n");
			scanf_s("%i", &heal);
			if (heal == 0)
				break;
			switch (heal)
			{
			case 1:
				if (coins < 10)
				{
					printf("У вас не достатачно монет\n");
					break;
				}
				printf("Вы купили апттечку, ваши жизни увеличены на 1\n");
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

	printf("Ты не победишь меня, ты слишком слаб!\n");
	Sleep(3000);
	printf("У боcса 3 фазы:\nПервая фаза, у него 50 жизней, и он бьёт тебя после каждого твоего 3 удара\nВторая фаза, у босса 25 жизней, и он бьёт тебя каждый твой удар\nФинальная фаза у босса 100 жизней и он бьёт тебя каждый твой 5 удар\nУдачи!\n\n");
	if (damage >= 10)
		printf("Хорошо что я купил супер-оружие!\n\n");
	else
		printf("\"Почему я не купил супер-оружие!?\" - спросил ты сам у себя\n\n");

	Sleep(5000);
	printf("ДЕРИТЕСЬ!!!\n");
	health_boss = 50;
	while (boss1 == true)
	{ 
		atb = _getch();
		switch (atb)
		{
		case ' ':
			printf("Вы нанесли боссу %i урона\n", damage);
			health_boss -= damage;
			if (i == 3 || i == 6 || i == 9 || i == 12 || i == 15)
			{
				printf("Босс снёс вам 1 жизнь\n");
				health_player--;
			}
			if (health_boss <= 0)
			{
				printf("ПЕРВАЯ ФАЗА ОКОНЧЕНА, ЖИЗНИ ВОССТАНОВЛЕНЫ, ПЕРЕХОДИМ КO BTOPOЙ ФАЗЕ\n");
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
			printf("Вы нанесли боссу %i урона\n", damage);
			health_boss -= damage;
			if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8)
			{
				printf("Босс снёс вам 1 жизнь\n");
				health_player--;
			}
			if (health_boss <= 0)
			{
				printf("ВТОРАЯ ФАЗА ОКОНЧЕНА, ЖИЗНИ ВОССТАНОВЛЕНЫ, ПЕРЕХОДИМ К ФИНАЛЬНОЙ ФАЗЕ\n");
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
			printf("Вы нанесли боссу %i урона\n", damage);
			health_boss -= damage;
			if (i == 5 || i == 10 || i == 15 || i == 20 || i == 25 || i == 30 || i == 35)
			{
				printf("Босс снёс вам 1 жизнь\n");
				health_player--;
			}
			if (health_boss <= 0)
			{
				printf("Вы победили босса!!!\n");
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
			printf("Вы проиграли\n");
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
	printf("СПАСИБО ЗА ИГРУ!!!");
	system("pause");
	return 0;
}