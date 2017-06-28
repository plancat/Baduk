#include "stdafx.h"

#define MAX_Y 19
#define MAX_X 19

class Egg;
class GameManager
{
private:
	// 게임 보드 배열
	// 0 비어있다.
	// 1 흰돌
	// 2 검은돌
	EggColor gameBoard[MAX_Y][MAX_X];
	// ----------------- [부모 노드]
	Node* ownerLayer;
	// ------------------ [Function]
	void BoardInitialize();
	// 재귀 함수 -> (배열 x,배열 y,더할 값)
	int EggListCheck(int nX, int nY, int X, int Y);
public:
	void Initialize(Node* parent);
	// 실제 포지션 -> 배열 값
	Vec2 MapToArray(const Vec2& target);
	// 배열 값 -> 실제 포지션
	Vec2 ArrayToMap(const Vec2& target);
	// 바둑돌을 추가한다.
	int AddEgg(Vec2& position,EggColor& eggColor);
};