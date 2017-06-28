#include "GameManager.h"
#include "Egg.h"

void GameManager::Initialize(Node* parent)
{
	// �θ� ����
	ownerLayer = parent;
	this->BoardInitialize();
}

Vec2 GameManager::MapToArray(const Vec2& target)
{
	int xpos = target.x / 26;
	int ypos = target.y / 26;

	if (xpos >= 18)
		xpos = 18;
	if (ypos >= 18)
		ypos = 18;

	//log("X : %d, Y : %d", xpos, ypos);
	return Vec2(xpos, ypos);
}

Vec2 GameManager::ArrayToMap(const Vec2& target)
{
	int xpos = target.x * 26;
	int ypos = target.y * 26;
	//log("X : %d, Y : %d", xpos, ypos);
	return Vec2(xpos, ypos);
}

void GameManager::BoardInitialize()
{
	for (int i = 0; i < MAX_Y; i++)
		for (int j = 0; j < MAX_X; j++)
			gameBoard[i][j] = EggColor::NONE;
}

int GameManager::AddEgg(Vec2& position, EggColor& eggColor)
{
	//---------------------
	// 0 = �ٵϵ� ���� ����
	// 1 = �ٵϵ� ���� ����
	// 3 = 33 �ݼ�, ���� X
	// 5 = �¸�
	// 6 = ���, ���� X
	//---------------------

	// �ٵε� ����
	Egg* egg = Egg::create();
	egg->setTexture(eggColor == EggColor::WHITE ? "white.png" : "black.png");
	egg->setScale(0.35);
	egg->setArrayPosition(MapToArray(position));

	// �̹� ���ڸ��� ���� �ִٸ�
	if (gameBoard[(int)egg->getArrayPosition().y][(int)egg->getArrayPosition().x] != EggColor::NONE)
		return 0;
	else{
		// �� �߰�
		egg->setPosition(ArrayToMap(egg->getArrayPosition()));
		gameBoard[(int)egg->getArrayPosition().y][(int)egg->getArrayPosition().x] = eggColor;
		ownerLayer->addChild(egg, Egg_tag);

		// �迭 ��
		int arrX = egg->getArrayPosition().x;
		int arrY = egg->getArrayPosition().y;

		// ------------------------------- [ 33 �ݼ� �˻�]
		//int _vertical   = EggListCheck(arrX, arrY, 1, 0)  + EggListCheck(arrX, arrY, -1, 0)  + 1;
		//int _horizontal = EggListCheck(arrX, arrY, 0, 1)  + EggListCheck(arrX, arrY, 0, -1)  + 1;
		//int _diag       = EggListCheck(arrX, arrY, 1, 1)  + EggListCheck(arrX, arrY, -1, -1) + 1;
		//int _diag2      = EggListCheck(arrX, arrY, -1,1)  + EggListCheck(arrX, arrY, 1, -1)  + 1;
		
		
		// ------------------------------- [ �� 5�� �˻� , ���]
		std::vector<Vec2> direction = {
			Vec2(0, 1),
			Vec2(1, 1),
			Vec2(1, 0),
			Vec2(1, -1)
		};

		for (Vec2 nextDir : direction) {
			// ������ �˻�
			int right = EggListCheck(arrX, arrY, nextDir.x, nextDir.y);
			// ���� �˻�
			int left = EggListCheck(arrX, arrY, (-1 * nextDir.x), (-1 * nextDir.y));
			// �ڽ��� �����ϰ� �˻��߱� ������ 1�� ���Ѵ�.
			int number = left + right + 1;
			// �� ������ 5���϶�
			if (number == 5)
				return 5;
			
			// �� ������ ����϶�
			// �Ͼᵹ�̳� �������̳� -> �Ͼᵹ �¸�
			else if (number >= 6){
				//�ش� ����� ���� �����Ѵ�.
				//gameBoard[(int)egg->getArrayPosition().y][(int)egg->getArrayPosition().x] = EggColor::NONE;
				// ownerLayer->removeChild(egg);
				return eggColor == EggColor::WHITE ? 5 : 6;
			}
		}
	}
	return 1;
}

int GameManager::EggListCheck(int nX, int nY, int X, int Y)
{
	int nNextX = nX + X;
	int nNextY = nY + Y;

	// üũ�� ������ �Ѿ����
	if (nNextX < 0 || nNextX >= MAX_Y || nNextY < 0 || nNextY >= MAX_Y)
		return 0;
	// ���� �ٵϵ��� �� -> �ٸ���
	if (gameBoard[nY][nX] != gameBoard[nNextY][nNextX])
		return 0;
	// ����ġ�� �д�. �ڽ��� ������ �ٵϵ��� �˻��Ѵ�.
	return 1 + EggListCheck(nNextX, nNextY, X, Y);
}
