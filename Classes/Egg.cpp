#include "Egg.h"

Vec2 Egg::getArrayPosition()
{
	return this->arrayPosition;
}

void Egg::setArrayPosition(Vec2& position)
{
	this->arrayPosition = position;
}

Egg* Egg::create()
{
	Egg *egg = new (std::nothrow) Egg();
	if (egg && egg->init())
	{
		egg->autorelease();
		return egg;
	}
	CC_SAFE_DELETE(egg);
	return nullptr;
}