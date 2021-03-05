#include <iostream>
#include <string>
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

struct Player
{
	string name = "";
	int HP = 0;
	int input = 0;
};

int main()
{
	//게임 시작
	//가위바위보 시작
	int level = 0;
	Player player;
	int monsterNum = 0;
	int monsterInput = 0;
	int coin = 0;
	int playerPosX = 0;
	int playerPosY = 0;
	int monsterPosX = 0;
	int monsterPosY = 0;
	int count = 0;
	int monsterCount = 0;

	srand(time(NULL));

	cout << "영웅은 절차적 게임에 온 것을 환영합니다! 빠밤" << endl;
	cout << "게임을 시작하겠습니다." << endl;

	cout << endl;

	cout << "영웅의 이름을 입력해 주세요. : ";
	cin >> player.name;

	cout << endl;

	while (true) //난이도 체크
	{
		cout << "난이도를 선택해 주세요 :" << endl;
		cout << "1. Easy   2. Normal   3. Hard " << endl;
		cin >> level;

		cout << endl;

		if (level == 1)
		{
			player.HP = 100;
			monsterNum = 3;
			cout << "난이도를 " << level << "로 선택하였습니다." << endl;
			cout << "HP " << player.HP << "을 획득하였습니다." << endl;
			cout << "처치해야 할 몬스터는 " << monsterNum << "마리 입니다." << endl;
			cout << "몬스터는 첫번째 판에만 나타납니다." << endl;
			system("PAUSE");
			break;
		}
		if (level == 2)
		{
			player.HP = 80;
			monsterNum = 4;
			cout << "난이도를 " << level << "로 선택하였습니다." << endl;
			cout << "HP " << player.HP << "을 획득하였습니다." << endl;
			cout << "처치해야 할 몬스터는 " << monsterNum << "마리 입니다." << endl;
			cout << "몬스터는 첫번째 판에만 나타납니다." << endl;
			system("PAUSE");
			break;
		}
		if (level == 3)
		{
			player.HP = 70;
			monsterNum = 5;
			cout << "난이도를 " << level << "로 선택하였습니다." << endl;
			cout << "HP " << player.HP << "을 획득하였습니다." << endl;
			cout << "처치해야 할 몬스터는 " << monsterNum << "마리 입니다." << endl;
			cout << "몬스터는 첫번째 판에만 나타납니다." << endl;
			system("PAUSE");
			break;
		}
		else
		{
			cout << "잘못된 숫자를 입력하셨습니다. 다시 입력해 주세요 용사님!" << endl;
			cout << endl;
		}
	}

	cout << endl;

	while (true) //맵짜기
	{
		if (monsterNum == 0)
		{
			cout << player.name << " 용사님의 완승! 몬스터가 전부 처치되었어요!!" << endl;
			cout << " -게임 종료- ";
			break;
		}

		//맵 데이터
		char map[10][10];

		for (int i = 0; i < 10; i++) //i는 y축 (열)
		{
			for (int j = 0; j < 10; j++) //j는 x축 (행)
			{
				map[i][j] = '#';
			}
		}

		//플레이어 정보 적용
		map[playerPosY][playerPosX] = 'H';

		monsterPosX = (rand() % 99 + 1) % 10;
		monsterPosY = (rand() % 99 + 1) / 10;
		map[monsterPosY][monsterPosX] = 'M';
		monsterCount++;

		while (true)
		{
			//몬스터 정보
			if (monsterCount == 0)
			{
				monsterPosX = (rand() % 99 + 1) % 10;
				monsterPosY = (rand() % 99 + 1) / 10;
				map[monsterPosY][monsterPosX] = 'M';
				monsterCount++;
			}

			if (monsterNum == 0)
				break;
			if (player.HP == 0)
				break;

			system("cls");
			//맵 출력
			for (int i = 0; i < 10; i++) //i는 y축 (열)
			{
				for (int j = 0; j < 10; j++) //j는 x축 (행)
				{
					cout << map[i][j];
				}
				cout << endl;
			}

			map[playerPosY][playerPosX] = '#';

			int inputKey = _getch();

			switch (inputKey)
			{
			case 'w': case 'W':
				if (playerPosY != 0)
					playerPosY--;
				break;
			case 's': case 'S':
				if (playerPosY != 9)
					playerPosY++;
				break;
			case 'a': case 'A':
				if (playerPosX != 0)
					playerPosX--;
				break;
			case 'd': case 'D':
				if (playerPosX != 9)
					playerPosX++;
				break;
			}

			map[playerPosY][playerPosX] = 'H';

			if (map[playerPosY][playerPosX] == map[monsterPosY][monsterPosX])
			{
				cout << endl;
				cout << endl;

				cout << "몬스터가 나타났다!!!!" << endl;
				cout << endl;

				while (true)
				{
					cout << endl;
					cout << endl;

					cout << "가위, 바위, 보 중 하나를 입력해 주세요. : " << endl;
					cout << "1. 가위   2. 바위     3. 보" << endl;
					cout << endl;

					int comNum = rand() % 3 + 1;
					int shop = 0;
					int potion = 0;

					while (true)
					{
						cin >> player.input;

						if (player.input == 1)
						{
							cout << player.name << " 용사님은 가위를 선택하였습니다." << endl;
							break;
						}
						if (player.input == 2)
						{
							cout << player.name << " 용사님은 바위를 선택하였습니다." << endl;
							break;
						}
						if (player.input == 3)
						{
							cout << player.name << " 용사님은 보를 선택하였습니다." << endl;
							break;
						}
						else
						{
							cout << "잘못된 숫자를 입력하셨습니다. 다시 입력해 주세요 용사님!" << endl;
							cout << endl;
						}
					}

						if (comNum == 1)
						{
							cout << "몬스터는  가위를 선택하였습니다." << endl;
						}
						if (comNum == 2)
						{
							cout << "몬스터는  바위를 선택하였습니다." << endl;
						}
						if (comNum == 3)
						{
							cout << "몬스터는  보를 선택하였습니다." << endl;
						}

						if (player.input == comNum)
						{
							cout << "앗 비겼어요! 이대로 한 판 더!" << endl;
						}
						cout << endl;

						if ((player.input - comNum == -1) || (player.input - comNum == 2))
						{
							cout << "끄앙 졌음 ㅠㅠ" << endl;
							cout << "체력이 -10 되었습니다 ㅠㅠ" << endl;
							player.HP = player.HP - 10;

							if (player.HP == 0)
							{
								cout << player.name << " 용사님..사망하셨습니다. 기도합시다." << endl;
								cout << "다음 판에서 만나요." << endl;
								break;
							}

							cout << "현재 체력은 " << player.HP << "입니다." << endl;
							cout << "보유하고 계신 금화는 " << coin << "입니다," << endl;
						}
						cout << endl;

						if ((player.input - comNum == -2) || (player.input - comNum == 1))
						{
							cout << player.input << " 용사님의 승리!" << endl;
							cout << "금화가 +10 되었습니다! " << endl;
							coin += 10;
							monsterNum -= 1;
							cout << endl;

							cout << "현재 체력은 " << player.HP << "입니다." << endl;
							cout << "보유하고 계신 금화는 " << coin << "입니다." << endl;
							cout << "남은 몬스터 수는 " << monsterNum << "입니다." << endl;

							cout << endl;
							cout << endl;

							cout << "상점은 몬스터를 처치할 때 마다 방문할 수 있습니다!" << endl;
							cout << "1. 네! 갈게요.             2. 아뇨, 이번엔 가지 않을게요." << endl;

							cin >> shop;


							system("cls");

							if (shop == 1)// 상점입장
							{
								cout << "[용감한 상점 입장]" << endl;
								cout << "용감한 상점에 온 것을 환영한다네." << endl;
								cout << "난 주인장 한용감이야. 이름만큼 한용감 하지. 구매할 수 있는 목록을 보여줄테니 잘 봐봐." << endl;
								cout << endl;
								cout << "1. 기본 포션 (10 코인) : HP가 10 증가한다." << endl;
								cout << "2. 고급 포션 (15 코인) : HP가 20 증가한다." << endl;
								cout << "3. 존좋 포션 (40 코인) : HP가 모두 증가한다." << endl;
								cout << "4. 프리미엄 포션 (20 코인) : HP가 30 증가한다." << endl;
								cout << "5. 내키는 게 없군요. 그냥 갈래요." << endl;

								cout << endl;
								cout << endl;

								cout << "자네 상태는 [ HP :" << player.HP << " ], [ 금화 : " << coin << " ] 라네. 마음에 드는 게 있어?" << endl;
								cin >> potion;

								if (potion == 1)
								{
									player.HP += 10;
									coin -= 10;

									cout << "체력이 " << player.HP << "되었습니다." << endl;
									cout << "[한용감] 좋아. 좋은 걸 구매했군. 그럼 또 보게." << endl;
									cout << endl;
									cout << endl;
									system("PAUSE");
								}
								if (potion == 2)
								{
									player.HP += 20;
									coin -= 15;

									cout << "체력이 " << player.HP << "되었습니다.";
									cout << "[한용감] 좋아. 좋은 걸 구매했군. 그럼 또 보게." << endl;
									cout << endl;
									cout << endl;
									system("PAUSE");
								}
								if (potion == 3)
								{
									player.HP = 100;
									coin -= 40;

									cout << "체력이 " << player.HP << "되었습니다.";
									cout << "[한용감] 좋아. 좋은 걸 구매했군. 그럼 또 보게." << endl;
									cout << endl;
									cout << endl;
								}
								if (potion == 4)
								{
									player.HP += 30;
									coin -= 20;

									cout << "체력이 " << player.HP << "되었습니다.";
									cout << "[한용감] 좋아. 좋은 걸 구매했군. 그럼 또 보게." << endl;
									cout << endl;
									cout << endl;
									system("PAUSE");
								}
								if (potion == 5)
								{
									cout << "아무것도 구매하지 않아 상태에 변함이 없습니다." << endl;
									cout << "[한용감] 아무것도 사지 않았네. 자네도 용감하군..그럼 또 보게." << endl;
									cout << endl;
									cout << endl;
									system("PAUSE");
								}
							}
							else
							{
								cout << "상점을 들리지 않으셨습니다. 다시 몬스터를 잡으러 갑니다!" << endl;
								cout << endl;
								cout << endl;
								system("PAUSE");
							}
							cout << endl;
							break;
						}
				}	
			}
		}
	}

}


