#include "stdafx.h"
#include "Ob_movable.h"

Ob_movable::Ob_movable()
{
	this->scale = Vector2(100.f, 100.f);
	this->SetWorldPos(Vector2(0.f, 0.f));
}
