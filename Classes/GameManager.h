#include "stdafx.h"

#define MAX_Y 19
#define MAX_X 19

class Egg;
class GameManager
{
private:
	// ���� ���� �迭
	// 0 ����ִ�.
	// 1 ��
	// 2 ������
	EggColor gameBoard[MAX_Y][MAX_X];
	// ----------------- [�θ� ���]
	Node* ownerLayer;
	// ------------------ [Function]
	void BoardInitialize();
	// ��� �Լ� -> (�迭 x,�迭 y,���� ��)
	int EggListCheck(int nX, int nY, int X, int Y);
public:
	void Initialize(Node* parent);
	// ���� ������ -> �迭 ��
	Vec2 MapToArray(const Vec2& target);
	// �迭 �� -> ���� ������
	Vec2 ArrayToMap(const Vec2& target);
	// �ٵϵ��� �߰��Ѵ�.
	int AddEgg(Vec2& position,EggColor& eggColor);
};