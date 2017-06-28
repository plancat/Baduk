#include "GameManager.h"
#include "Egg.h"

void GameManager::Initialize(Node* parent)
{
	// 부모 설정
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
	// 0 = 바둑돌 놓기 실패
	// 1 = 바둑돌 놓기 성공
	// 3 = 33 금수, 놓기 X
	// 5 = 승리
	// 6 = 장목, 놓기 X
	//---------------------

	// 바두돌 생성
	Egg* egg = Egg::create();
	egg->setTexture(eggColor == EggColor::WHITE ? "white.png" : "black.png");
	egg->setScale(0.35);
	egg->setArrayPosition(MapToArray(position));

	// 이미 그자리에 돌이 있다면
	if (gameBoard[(int)egg->getArrayPosition().y][(int)egg->getArrayPosition().x] != EggColor::NONE)
		return 0;
	else{
		// 돌 추가
		egg->setPosition(ArrayToMap(egg->getArrayPosition()));
		gameBoard[(int)egg->getArrayPosition().y][(int)egg->getArrayPosition().x] = eggColor;
		ownerLayer->addChild(egg, Egg_tag);

		// 배열 값
		int arrX = egg->getArrayPosition().x;
		int arrY = egg->getArrayPosition().y;

		// ------------------------------- [ 33 금수 검사]
		//int _vertical   = EggListCheck(arrX, arrY, 1, 0)  + EggListCheck(arrX, arrY, -1, 0)  + 1;
		//int _horizontal = EggListCheck(arrX, arrY, 0, 1)  + EggListCheck(arrX, arrY, 0, -1)  + 1;
		//int _diag       = EggListCheck(arrX, arrY, 1, 1)  + EggListCheck(arrX, arrY, -1, -1) + 1;
		//int _diag2      = EggListCheck(arrX, arrY, -1,1)  + EggListCheck(arrX, arrY, 1, -1)  + 1;
		
		
		// ------------------------------- [ 돌 5개 검사 , 장목]
		std::vector<Vec2> direction = {
			Vec2(0, 1),
			Vec2(1, 1),
			Vec2(1, 0),
			Vec2(1, -1)
		};

		for (Vec2 nextDir : direction) {
			// 오른쪽 검사
			int right = EggListCheck(arrX, arrY, nextDir.x, nextDir.y);
			// 왼쪽 검사
			int left = EggListCheck(arrX, arrY, (-1 * nextDir.x), (-1 * nextDir.y));
			// 자신을 제외하고 검사했기 때문에 1을 더한다.
			int number = left + right + 1;
			// 돌 개수가 5개일때
			if (number == 5)
				return 5;
			
			// 돌 개수가 장목일때
			// 하얀돌이냐 검은돌이냐 -> 하얀돌 승리
			else if (number >= 6){
				//해당 장목의 돌을 삭제한다.
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

	// 체크할 범위를 넘어갔을때
	if (nNextX < 0 || nNextX >= MAX_Y || nNextY < 0 || nNextY >= MAX_Y)
		return 0;
	// 다음 바둑돌과 비교 -> 다를때
	if (gameBoard[nY][nX] != gameBoard[nNextY][nNextX])
		return 0;
	// 가중치를 둔다. 자신을 제외한 바둑돌을 검사한다.
	return 1 + EggListCheck(nNextX, nNextY, X, Y);
}
