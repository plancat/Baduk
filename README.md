# Baduk
Cocos2D Baduk Game

> 재귀함수를 익힐 수 있고 간단한 승패를 낼 수 있는 바둑게임입니다.

## 중요 코드
``` C++
int GameManager::EggListCheck(int nX, int nY, int X, int Y)
{
	int nNextX = nX + X;
	int nNextY = nY + Y;

	if (nNextX < 0 || nNextX >= MAX_Y || nNextY < 0 || nNextY >= MAX_Y)
		return 0;        
	if (gameBoard[nY][nX] != gameBoard[nNextY][nNextX])
		return 0;

	return 1 + EggListCheck(nNextX, nNextY, X, Y);
}
```