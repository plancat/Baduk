#pragma once

#include "stdafx.h"

class Egg : public Sprite
{
private:
	Vec2 arrayPosition;
public:
	static Egg* Egg::create();
	Vec2 getArrayPosition();
	void setArrayPosition(Vec2& position);
};