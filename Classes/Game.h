#pragma once
#include "stdafx.h"

class GameManager;
class Egg;
class Game : public Layer
{
private:
	// 게임 매니저
	// Map -> Array
	// Array -> Map
	GameManager* gameManager;
	EggColor eggColor;
	Egg* moveEgg;
public:
	Game();
	~Game();

	bool onTouchBegan(Touch *touch, Event *unused_event) override;
	void onTouchEnded(Touch *touch, Event *unused_event) override;
	void onMouseMove(Event* event);

	void ChangeColor();

    static Scene* createScene();
    bool init();
	CREATE_FUNC(Game);
};