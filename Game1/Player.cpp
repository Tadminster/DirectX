#include "stdafx.h"
#include "Player.h"

Player::Player()
{
    hasAxis = true;
    scale.x = 300.0f;
    scale.y = 300.0f;
    
    score = 0;
}

Player::~Player()
{
}

void Player::Init(Vector2 spawn, bool isLeft)
{
    SetWorldPosX(spawn.x);
    SetWorldPosY(spawn.y);
    rotation.y = isLeft ? PI : 0.0f;
}

void Player::Control(Vector2 arrow)
{
    MoveWorldPos(arrow * DELTA * 250);
}

void Player::Update()
{
    ObCircle::Update();
}

void Player::Render()
{
    ObCircle::Render();
}

