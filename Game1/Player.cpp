#include "stdafx.h"
#include "Player.h"
#include "Gun_pistol.h"

Player::Player()
{
    this->hand = 0;
    this->speed = 250;
    this->jump_power = 150.f;
    this->jump_startPoint = this->GetWorldPos().y;
    this->jump_status = false;

    hasAxis = true;
    scale.x = 30.f;
    scale.y = 50.f;
    
    score = 0;

    pistol = new Gun_pistol();
    pistol->SetParentRT(*this);
}

Player::~Player()
{
    delete pistol;
}

void Player::Init(Vector2 spawn, bool isLeft)
{
    SetWorldPosX(spawn.x);
    SetWorldPosY(spawn.y);
    rotation.y = isLeft ? PI : 0.0f;
}

void Player::Control()
{
    if (jump_status && this->GetWorldPos().y < jump_startPoint + this->jump_power)
    {
        this->MoveWorldPos(UP * DELTA * this->speed * 2.f);
        if (this->GetWorldPos().y +5.f >= jump_startPoint + this->jump_power)
            jump_status = false;
    }
    // 이동
    //if (INPUT->KeyPress('W'))
    //    this->MoveWorldPos(UP * DELTA * this->speed);
    //if (INPUT->KeyPress('S'))
    //    this->MoveWorldPos(DOWN * DELTA * this->speed);
    if (INPUT->KeyPress('A'))
        this->MoveWorldPos(LEFT * DELTA * this->speed);
    if (INPUT->KeyPress('D'))
        this->MoveWorldPos(RIGHT * DELTA * this->speed);
    // 점프
    if (INPUT->KeyPress(VK_SPACE) && this->GetWorldPos().y <= FLOOR)
    {
        this->jump_startPoint = this->GetWorldPos().y;
        this->jump_status = true;
    }

    // 격발
    if (INPUT->KeyPress(VK_LBUTTON))
    {
        if (this->hand == 1)
            pistol->Fire(this);
    }

    // 무기 스왑
    if (INPUT->KeyDown('1'))
        this->hand == 1;
}

void Player::Control(Vector2 arrow)
{
    MoveWorldPos(arrow * DELTA * this->speed);
}

void Player::Update()
{
    // 중력
    if (this->GetWorldPos().y > -app.GetHalfHeight() + this->scale.y)
        this->MoveWorldPos(DOWN * DELTA * 200.f);

    //ObCircle::Update();
    ObRect::Update();

    // 총기가 마우스 방향으로 바라보게
    Vector2 mouse_point(INPUT->GetWorldMousePos() - this->pistol->GetWorldPos());
    pistol->rotation.z = atan2f(mouse_point.y, mouse_point.x);
    this->pistol->Update();
    this->pistol->Update_Bullets();
}

void Player::Render()
{
    //ObCircle::Render();
    ObRect::Render();
    this->pistol->Render();
    this->pistol->Render_Bullets();
}

