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
	// ---------------- [ ��ġ ������ �ʱ�ȭ ]
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	// ---------------- [ ���콺�� �����϶� ĳġ�ϴ� �̺�Ʈ ]
	auto MoveMouse = EventListenerMouse::create();
	MoveMouse->onMouseMove = CC_CALLBACK_1(Game::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(MoveMouse, this);

	// ���� ���带 �׸���.
	Sprite* gameBoard = Sprite::create("board.png");
	gameBoard->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
	this->addChild(gameBoard, Board_tag);

	// ������� �ٵϵ� ����
	moveEgg = Egg::create();
	moveEgg->setScale(0.35);
	moveEgg->setOpacity(100);
	moveEgg->setTexture("black.png");
	this->addChild(moveEgg, Egg_tag + 1);

	// ---------------- [ ���� ���� & ���� �Ŵ��� ]
	Layer* test = Layer::create();
	test->setContentSize(Size(480, 480));
	test->setPosition(Vec2(15.4, 15.4));
	this->addChild(test, Board_tag);

	// ---------------- [ ���� �Ŵ��� ����]
	// ---------------- Initialize()�� ȣ���ϰ�
	// ---------------- ��ġ�ϴ� ������ AddEgg(Vec2& )�� ȣ��
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
	// �ٵϵ��� �߰��Ѵ�.
	int egg_state = gameManager->AddEgg(touch->getLocation(), eggColor);

	// 0 �ٵϵ��� ���� ����
	// 1 �ٵϵ��� ���������� ����
	// 5 ��� �ٵϵ��� �̱�
	// 6 ���
	switch (egg_state)
	{
	case 0:
		break;
	case 1:
		// ���� ��ü
		ChangeColor();
		break;
	case 5:{
		// Ŭ���� ������
		// �¸��� Label�� ����Ѵ�.
		Label* label = Label::create("", "Arial", 45, Size::ZERO);
		label->setPosition(Vec2(WIDTH / 2, HEIGHT / 2));
		this->addChild(label, UI_tag);
		label->runAction(Sequence::create(
			FadeOut::create(2.0f),
			CallFunc::create([=]()
		{
			// ȭ�� ��ȯ
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

// --------------------------------[���� �����̴� �Լ�]
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

// --------------------------------[���� �ٲ�]
void Game::ChangeColor()
{
	// ���� �ٲٱ�
	if (eggColor == EggColor::BLACK)
		eggColor = EggColor::WHITE;
	else
		eggColor = EggColor::BLACK;
}