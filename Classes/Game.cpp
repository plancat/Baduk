#include "stdafx.h"
#include "GameManager.h"
#include "Egg.h"

Game::Game()
{

}

Game::~Game()
{

}

Scene* Game::createScene()
{
	auto scene = Scene::create();
	auto layer = Game::create();
	scene->addChild(layer);
	return scene;
}

bool Game::init()
{
	if (!Layer::init())
		return false;
	// ---------------- [ 터치 리스너 초기화 ]
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	// ---------------- [ 마우스가 움직일때 캐치하는 이벤트 ]
	auto MoveMouse = EventListenerMouse::create();
	MoveMouse->onMouseMove = CC_CALLBACK_1(Game::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(MoveMouse, this);

	// 게임 보드를 그린다.
	Sprite* gameBoard = Sprite::create("board.png");
	gameBoard->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
	this->addChild(gameBoard, Board_tag);

	// 따라오는 바둑돌 생성
	moveEgg = Egg::create();
	moveEgg->setScale(0.35);
	moveEgg->setOpacity(100);
	moveEgg->setTexture("black.png");
	this->addChild(moveEgg, Egg_tag + 1);

	// ---------------- [ 게임 보드 & 게임 매니저 ]
	Layer* test = Layer::create();
	test->setContentSize(Size(480, 480));
	test->setPosition(Vec2(15.4, 15.4));
	this->addChild(test, Board_tag);

	// ---------------- [ 게임 매니저 생성]
	// ---------------- Initialize()를 호출하고
	// ---------------- 터치하는 곳에서 AddEgg(Vec2& )를 호출
	gameManager = new GameManager();
	gameManager->Initialize(test);
	eggColor = EggColor::BLACK;

	// ---------------- [ Game Start ]
	Label* label = Label::create("GameStart", "Arial", 45, Size::ZERO);
	label->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
	this->addChild(label, UI_tag);

	label->runAction(Sequence::create(FadeOut::create(1.5f), RemoveSelf::create(), nullptr));
	return true;
}
bool Game::onTouchBegan(Touch *touch, Event *unused_event){
	return true;
}
void Game::onTouchEnded(Touch *touch, Event *unused_event)
{
	// 바둑돌을 추가한다.
	int egg_state = gameManager->AddEgg(touch->getLocation(), eggColor);

	// 0 바둑돌을 넣지 못함
	// 1 바둑돌을 성공적으로 넣음
	// 5 어떠한 바둑돌이 이김
	// 6 장목
	switch (egg_state)
	{
	case 0:
		break;
	case 1:
		// 색상 교체
		ChangeColor();
		break;
	case 5:{
		// 클리어 했을시
		// 승리자 Label을 출력한다.
		Label* label = Label::create("", "Arial", 45, Size::ZERO);
		label->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
		this->addChild(label, UI_tag);
		label->runAction(Sequence::create(
			FadeOut::create(2.0f),
			CallFunc::create([=]()
		{
			// 화면 전환
			Director::getInstance()->replaceScene(Game::createScene());
		}), nullptr));

		label->setString(eggColor == EggColor::BLACK ? "BLACK WIN" : "WHITE WIN");
		}
		break;
	case 6:{
		Label* label = Label::create("Jang Mok", "Arial", 30, Size::ZERO);
		label->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
		this->addChild(label, UI_tag);
		label->runAction(Sequence::create(FadeOut::create(1.0f), RemoveSelf::create(), nullptr));
		}
		break;
	}
}

// --------------------------------[따라 움직이는 함수]
void Game::onMouseMove(Event* event)
{
	//log("MouseMove");
	if (eggColor == EggColor::BLACK)
		moveEgg->setTexture("black.png");
	else
		moveEgg->setTexture("white.png");

	auto mE = static_cast<EventMouse*>(event);
	Vec2 pt = Vec2(mE->getCursorX(), mE->getCursorY());

	moveEgg->setArrayPosition(gameManager->MapToArray(pt));
	moveEgg->setPosition(gameManager->ArrayToMap(moveEgg->getArrayPosition()) + Vec2(15, 15));
}

// --------------------------------[색상 바꿈]
void Game::ChangeColor()
{
	// 색상 바꾸기
	if (eggColor == EggColor::BLACK)
		eggColor = EggColor::WHITE;
	else
		eggColor = EggColor::BLACK;
}