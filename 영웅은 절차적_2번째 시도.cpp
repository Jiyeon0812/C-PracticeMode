#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <conio.h>

using namespace std;

/* 실습: 영웅은 절차적
	1) 텍스트로 진행되는 게임
	2) 게임이 시작되면 영웅의 이름과 난이도를 입력
	3) 난이도에 따라서 영웅의 HP / 만나게 되는 몬스터의 숫자가 변동 //난이도는 랜덤?
	4) 몬스터를 잡으면 랜덤하게 돈을 획득한다. ( 0 ~ 100 ) //돈 랜덤하게 생성
	5) 몬스터를 잡으면 던전을 계속 탐험할지 상점을 들를지 결정한다.
	6) 상점에 들릴 경우, 돈을 소모해서 HP를 회복할 수 있다.
	6_1) HP나 돈에 따라 전체회복, +10, +20, +30 차등 회복할 수 있다.
	7) HP가 0이 되면 게임오버
	8) 몬스터를 모두 잡으면 게임클리어

	0) 게임 전투 방식
	0_1) 가위바위보 (비기면 승패가 정해질 때까지 반복)
	0_2) 졌을 때만 영웅 HP가 줄어든다.
	0_3) 몬스터는 한 번 지면 바로 죽음

	1) 우선순위
	1_1) 가위바위보 순서도 먼저 만들기
	1_2) 그 다음에 짜기
*/

struct Hero
{
    string name = "";
    int hp = 0;
    int gold = 0;
    int posX = 0;
    int posY = 0;
	int heroInput = 0;
	bool isUSeShop = 0;
};

struct Monster
{
	string name[3] = { "요정", "도깨비", "대박거인" };
	int gold = 0;
	int attack = 0;
	int posX = 0;
	int posY = 0;
	int monsterInput = 0;
	string battle[3] = { "가위" , "바위", "보" };
};

struct MonsterGroup
{
	Monster monster[3];
};

struct Difficulty
{
	int heroHP[3] = { 100, 80, 50 };
	int monsterattack[3] = { 10, 15, 20 };
	int level = 0;
	int monsterNum[3] = { 3, 4, 5 };
	string name[3] = { "쉬움", "보통", "어려움" };
};

struct ShopItems
{
	int num = 0;
	int gold[3] = {10, 15, 20};
	int HP[3] = {10, 20, 25};
	string name[3] = {"기본 포션", "고급 포션", "프리미엄 포션"};
};

struct Exit
{
	int posX = 0;
	int posY = 0;
};

int main()
{
	Hero hero;
	Difficulty difficulty;
	Monster monster;
	MonsterGroup monsterGroup;

	srand((unsigned)time(NULL));

	//게임 시작 안내

	cout << "			##================================================##" << endl;
	cout << "			||                                                ||" << endl;
	cout << "			||                                                ||" << endl;
	cout << "			||                                                ||" << endl;
	cout << "			||               영 웅 은 절 차 적                ||" << endl;
	cout << "			||                                                ||" << endl;
	cout << "			||                                                ||" << endl;
	cout << "			||                                                ||" << endl;
	cout << "			##================================================##" << endl;





	cout << endl;
	cout << endl;
	cout << endl;

	cout << "	                               어서오세요 영웅님.. ";

	cout << endl;
	cout << endl;
	cout << endl;

	cout << "	                           영웅님의 이름을 입력해 주세요.. ";
	cin >> hero.name;

	cout << endl;

	cout << "	                               반갑습니다 " << hero.name << "님.. ";

	cout << endl;
	cout << endl;

	while (1)
	{
		cout << "	                               난이도를 선택해 주세요. ";

		cout << endl;
		cout << endl;

		cout << "	                               0. 쉬움    1. 보통    2. 어려움 ";
		cin >> difficulty.level;
		cout << endl;

		cout << endl;
		cout << endl;

		//난이도에 따라 영웅 hp,  몬스터 공격력, 몬스터 종류 정하기
			if (difficulty.level == 0 || difficulty.level == 1 || difficulty.level == 2)
			{
				hero.hp = difficulty.heroHP[difficulty.level];
				monster.attack = difficulty.monsterattack[difficulty.level];
				break;
			}
			else
			{
				cout << "				잘못 입력하셨습니다. 보기 내의 숫자를 골라주세요. " << endl;
				cout << endl;
				cout << endl;
			}
	}

	cout << endl;

	cout << "					" << difficulty.name[difficulty.level] << "을 택하셨군요.	" << endl;
	cout << "					영웅님은 " << monster.name[difficulty.level] << " " << difficulty.monsterNum[difficulty.level] << "마리를 처치하셔야 합니다." << endl;
	cout << "					게임을 시작하도록 하겠습니다.. " << endl;
	system("PAUSE");

	//맵 데이터 저장 [10][10]
	char map[10][10];

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			map[i][j] = '*';
		}
	}

	//탈출구 정보
	Exit exit;
	exit.posX = rand() % 10;
	exit.posY = 9;

	map[exit.posY][exit.posX] = 'E';

	//몬스터 정보
	monster.posX = (rand() % 99 + 1) % 10;
	monster.posY = (rand() % 99 + 1) / 10;
	map[monster.posY][monster.posX] = 'M';
	int battleCount = difficulty.monsterNum[difficulty.level];

	//상점 아이템 정보
	ShopItems shoptItems;
	
	//게임 시작
	while (1)
	{
		system("cls");

		cout << "몬스터는 지도상에 표기되지 않습니다." << endl;
		cout << "E 는 탈출구 입니다. 게임을 종료하길 원하실 경우 이동해 주세요." << endl;
		cout << "영웅이 움직이지 않을 경우 한영키를 변경해 주세요." << endl;

		cout << endl;
		cout << endl;

		//맵 출력, 플레이어 및 몬스터 배치
		for (int i = 0; i < 10; i++)	
		{
			for (int j = 0; j < 10; j++)	
			{
				if (i == hero.posY && j == hero.posX) cout << "H";
				else if (map[i][j] == 'M' && map[i][j] != map[exit.posY][exit.posX]) cout << "*";
				else cout << map[i][j];
			}
			cout << endl;
		}

		monster.gold = rand() % 100 + 1;

		//플레이어 이동 정보
		int inputKey = _getch();

		switch (inputKey)
		{
		case 'w': case 'W':
			if (hero.posY != 0)
				hero.posY--;
			break;
		case 's': case 'S':
			if (hero.posY != 9)
				hero.posY++;
			break;
		case 'a': case 'A':
			if (hero.posX != 0)
				hero.posX--;
			break;
		case 'd': case 'D':
			if (hero.posX != 9)
				hero.posX++;
		}

		if (map[hero.posY][hero.posX] == 'E')
		{
			cout << endl;
			cout << endl;
			// 탈출
			cout << "---------------------------------------------------------------------" << endl;
			cout << "     #####     #####      #####         #        #####     #####     " << endl;
			cout << "     #         #          #            # #       #   #     #         " << endl;
			cout << "     ###       #####      #           #   #      #####     ###       " << endl;
			cout << "     #             #      #           #####      #         #         " << endl;
			cout << "     #             #      #           #   #      #         #         " << endl;
			cout << "     #####     #####      #####       #   #      #         #####     " << endl;
			cout << "---------------------------------------------------------------------" << endl;
			cout << "       탈출하였으므로 게임을 종료합니다. 안녕히 가세요!" << endl;
			
			system("PAUSE");
			break;
		}
		else if (map[hero.posY][hero.posX] == 'M')
		{
			//몬스터 만남
			cout << endl;
			cout << endl;

			cout << monster.name[difficulty.level] << "(이)가 나타났다!!!!!!!!!!!!!!!" << endl;

			cout << endl;
			cout << endl;

			cout << monster.name[difficulty.level] << "를 처치하기 위해 가위바위보를 해야 합니다." << endl;

			cout << endl;

			while (1) //가위바위보 예외처리
			{
				cout << "가위, 바위, 보 중 하나를 선택해 주세요." << endl;
				cout << "1. 가위          2. 바위           3. 보" << endl;
				cin >> hero.heroInput;

				cout << endl;
				cout << endl;

				if (hero.heroInput < 0 || hero.heroInput > 3)
				{
					cout << "잘못 입력하였습니다. 다시 선택해 주세요!" << endl;
					cout << endl;
				}
				else
				{
					break;
				}
			}

			monster.monsterInput = rand() % 3 + 1;

			while (monster.monsterInput == hero.heroInput)
			{
				//무승부
				cout << hero.name << "님의 선택 : " << monster.battle[hero.heroInput - 1] << endl;
				cout << monster.name[difficulty.level] << "의 선택 : " << monster.battle[monster.monsterInput - 1] << endl;
				
				cout << endl;

				cout << "무승부 입니다! 한 번 더 진행해 주세요." << endl;

				cout << endl;
				cout << endl;

				cout << "가위, 바위, 보 중 하나를 선택해 주세요." << endl;
				cout << "1. 가위          2. 바위           3. 보" << endl;
				cin >> hero.heroInput;

				cout << endl;
				cout << endl;

				monster.monsterInput = rand() % 3 + 1;
			}

			if ((hero.heroInput - monster.monsterInput == -2) || (hero.heroInput - monster.monsterInput == 1))
			{
				//승리
				cout << hero.name << "님의 선택 : " << monster.battle[hero.heroInput - 1] << endl;
				cout << monster.name[difficulty.level] << "의 선택 : " << monster.battle[monster.monsterInput - 1] << endl;
				
				cout << endl;
				cout << endl;

				cout << "##================================================##" << endl;
				cout << "||                                                ||" << endl;
				cout << "||                     승리!                      ||" << endl;
				cout << "||                     (유후!)                      ||" << endl;
				cout << "##================================================##" << endl;

				cout << endl;
				cout << endl;

				cout << monster.name[difficulty.level] << "(을)를 처치하였습니다!" << endl;
				cout << monster.gold << " 골드를 획득하였습니다." << endl;
				hero.gold += monster.gold;

				cout << endl;
				cout << endl; 

				cout << "현재 " << hero.name << "님은 [ HP : " << hero.hp << " ], [ Gold : " << hero.gold << " ] 를 보유하고 있습니다." << endl;
				battleCount--;
				cout << "남은 " << monster.name[difficulty.level] << "은(는) " << battleCount << "마리 입니다. " << endl;

				cout << endl;
				cout << endl;
			}
			else
			{
				//패배
				cout << endl;
				cout << endl;

				cout << hero.name << "님의 선택 : " << monster.battle[hero.heroInput - 1] << endl;
				cout << monster.name[difficulty.level] << "의 선택 : " << monster.battle[monster.monsterInput - 1] << endl;

				cout << "##================================================##" << endl;
				cout << "||                                                ||" << endl;
				cout << "||                     패배!                      ||" << endl;
				cout << "||                                                ||" << endl;
				cout << "##================================================##" << endl;

				hero.hp -= monster.attack;
				
				cout << "영웅님의 HP가 -" << monster.attack << " 줄었습니다. ㅠㅠ.." << endl;
				cout << "현재 영웅님의 HP는 " << hero.hp << "입니다." << endl;
				cout << "남은 " << monster.name[difficulty.level] << "은(는) " << battleCount << "마리 입니다. " << endl;

				cout << endl;
				cout << endl;
			}

			if (battleCount == 0)
			{
				cout << "You WIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
				cout << "몬스터를 전부 처치하였습니다! 영웅님. 게임을 종료합니다. 고생하셨습니다!" << endl;
				system("PAUSE");
				break;
			}

			if (hero.hp == 0)
			{
				cout << "---------------------------------------------------------------------" << endl;
				cout << "        #   #    ###    #     #       #####    #####   #####         " << endl;
				cout << "        #   #   #   #   #     #       #    #     #     #             " << endl;
				cout << "         # #   #     #  #     #       #     #    #     ###           " << endl;
				cout << "          #    #     #  #     #       #     #    #     #             " << endl;
				cout << "          #     #   #   #     #       #    #     #     #             " << endl;
				cout << "          #      ###     #####        #####    #####   #####         " << endl;
				cout << "---------------------------------------------------------------------" << endl;
				system("PAUSE");
				break;
			}

			cout << "상점으로 이동하시겠습니까?" << endl;

			cout << endl;
			cout << endl;

			cout << "1. 상점으로 이동할게요.     0. 아뇨, 필요 없어요." << endl;
			cin >> hero.isUSeShop;

			if (hero.isUSeShop == 1)
			{
				cout << "상점으로 이동합니다.." << endl;
				system("PAUSE");

				while (1)
				{
					system("cls");
					cout << endl;
					cout << endl;

					cout << "[용감한 상점 입장]" << endl;
					cout << "용감한 상점에 온 것을 환영한다네." << endl;
					cout << "난 주인장 한용감이야. 이름만큼 한용감 하지. 구매할 수 있는 목록을 보여줄테니 잘 봐봐." << endl;
					cout << endl;

					for (int i = 0; i < 3; i++)
					{
						cout << i + 1 << ". " << shoptItems.name[i] << " : HP를 " << shoptItems.HP[i] << "회복시켜 준다. [ " << shoptItems.gold[i] << " Gold] 필요" << endl;
					}
					cout << "4. 존좋포션 : HP를 100% 회복시켜 준다. [ 30 Gold ] 필요" << endl;
					cout << "5. 상점 나가기." << endl;

					cout << "현재 " << hero.name << "님은 [ HP : " << hero.hp << " ], [ Gold : " << hero.gold << " ] 를 보유하고 있습니다." << endl;

					cout << endl;
					cout << endl;

					cout << "어떤 것을 구매하시겠어요? ";
					cin >> shoptItems.num;

					cout << endl;
					cout << endl;

					if (shoptItems.num == 5)
					{
						cout << "[한용감] 충분한가 보구만. 행운을 빌겠네. 또 보게나.." << endl;
						cout << "게임으로 다시 돌아갑니다." << endl;
						system("PAUSE");
						break;
					}
					else if ((shoptItems.num) == 1 || (shoptItems.num) == 2 || (shoptItems.num) == 3)
					{
						if (hero.gold >= shoptItems.gold[shoptItems.num - 1])
						{
							if (hero.hp < difficulty.heroHP[difficulty.level])
							{
								cout << shoptItems.name[shoptItems.num - 1] << "을 선택하셨습니다." << endl;

								hero.hp += shoptItems.HP[shoptItems.num - 1];
								hero.gold -= shoptItems.gold[shoptItems.num - 1];

								cout << "[HP : " << hero.hp << "], [Gold : " << hero.gold << "] 가 되었습니다." << endl;

								cout << endl;

								cout << "[한용감] 좋은 아이템을 구매했구만. 아이템 구매는 한 번만 가능하다네. 행운을 빌겠네. 또 보게나..." << endl;
								system("PAUSE");
							}
							break;
						}
						else if (hero.gold < shoptItems.gold[shoptItems.num - 1])
						{
							cout << "[한용감] 자네 골드가 부족하구만. 몬스터를 더 잡고 오게나.." << endl;
							cout << "상점을 떠납니다. " << endl;
							system("PAUSE");
							break;
						}
						else if (hero.hp >= difficulty.heroHP[difficulty.level])
						{
							cout << "[한용감] 자네 HP가 이미 최대치이군. 그럼 더 이상 구매할 수 없어. 다시 돌아가게나.." << endl;
							cout << "상점을 떠납니다. " << endl;
							system("PAUSE");
							break;
						}
					}
					else if (shoptItems.num == 4)
					{
						if (hero.gold >= shoptItems.gold[shoptItems.num - 1])
						{
							cout << "존좋 포션을 선택하셨습니다." << endl;
							cout << "HP가 최대가 됩니다." << endl;
							hero.hp = difficulty.heroHP[difficulty.level];
							hero.gold -= 30;

							cout << "[HP : " << hero.hp << "], [Gold : " << hero.gold << "] 가 되었습니다." << endl;

							cout << endl;

							cout << "[한용감] 좋은 아이템을 구매했구만. 아이템 구매는 한 번만 가능하다네. 행운을 빌겠네. 또 보게나..." << endl;
							system("PAUSE");
							break;
						}
						else if (hero.gold < shoptItems.gold[shoptItems.num - 1])
						{
							cout << "[한용감] 자네 골드가 부족하구만. 몬스터를 더 잡고 오게나.." << endl;
							cout << "상점을 떠납니다. " << endl;
							system("PAUSE");
							break;
						}
					}
					else
					{
						cout << "잘못 입력하였습니다. 다시 선택해 주세요." << endl;
					}

				}
			}
			else
			{
				cout << "상점을 방문하지 않습니다. 게임으로 다시 돌아갑니다." << endl;
				system("PAUSE");
				//break;
			}
			//상점 끝
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (i == hero.posY && j == hero.posX) cout << "H";
					else if (map[i][j] == 'M' && map[i][j] != map[exit.posY][exit.posX]) cout << "*";
					else cout << map[i][j];
				}
				cout << endl;
			}
		}
	 }
}
