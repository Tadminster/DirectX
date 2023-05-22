#include "stdafx.h"
#include "Bullet_proto.h"

// obj_weapon_bullet::obj_weapon_bullet(Vector2 pos, float speed, float range, float rotation_z, float charging_scale)
Bullet_proto::Bullet_proto(Vector2 pos, Vector2 direction, float speed, float range, float charge)
    : speed(speed), range(range), traveledDistance(0.f), Damage(5), Pos_Initial(pos), Hp(1), pressPower(charge)
{
    // ź�� ������ġ
    this->SetLocalPosX(pos.x);
    this->SetLocalPosY(pos.y);

    // ź�� ũ��
    this->scale.x = 5.f;
    this->scale.y = 5.f;

    // ź�� ����
    // this->rotation.z = rotation_z;
    this->shooting_Dir = direction;

    // �߷�
    this->gravityDir = DOWN;
    this->gravityForce = 0.0f;

    this->pivot = OFFSET_L;
    this->hasAxis = false;
}

void Bullet_proto::Update()
{
    this->scale.x = 5.f;
    this->scale.y = 3.f;

    ObRect::Update();

    // ź�� �̵��� �Ÿ� ���
    this->Pos_Current.x += speed;
    this->Pos_Current.y += speed;
    traveledDistance += std::sqrt(std::pow(speed, 2) + std::pow(speed, 2));
}

void Bullet_proto::Render()
{
    ObRect::Render();
}

bool Bullet_proto::hasIntersect(class GameObject* target)
{
    
    
    Vector2 temp_vector
    (
        target->GetWorldPos().x - this->GetWorldPos().x, 
        target->GetWorldPos().y - this->GetWorldPos().y
    );
    float distance = sqrt(pow((temp_vector.x), 2) + pow((temp_vector.y), 2));
    float radius_sum = target->scale.x + this->scale.x;
    float radius_diff = abs(target->scale.x - this->scale.x);
    if (distance <= radius_sum)
    {
        return true;
    }
    return false;
}

void Bullet_proto::reflection_y()
{
    shooting_Dir.x = -shooting_Dir.x;

    /*Vector2 dir =
        Vector2(cosf(rotation.z), sinf(rotation.z));
    rotation.z = atan2f(dir.y, -dir.x);*/

    pressPower *= 0.7f;
    gravityForce *= 0.7f;
}

void Bullet_proto::reflection_x()
{
    shooting_Dir.y = -shooting_Dir.y;
    gravityForce = -gravityForce;

    //Vector2 dir =
    //	Vector2(cosf(rotation.z), sinf(rotation.z));
    //rotation.z = atan2f(-dir.y, dir.x);

    pressPower *= 0.7f;
    gravityForce *= 0.7f;
}