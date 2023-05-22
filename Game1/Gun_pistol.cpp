#include "stdafx.h"
#include "Gun_pistol.h"
#include "Bullet_proto.h"
#include "Player.h"

Gun_pistol::Gun_pistol() 
    : name("����"), damage(15), ammo_max(9999), ammo_current(this->ammo_max), ammo_speed(400.f),
    fire_rate(4.f), range(800.f) 
{
    this->scale.x = 20.f;
    this->scale.y = 10.f;
}

bool Gun_pistol::Fire(class Player* shooter)
{

    float currentTime = TIMER->GetWorldTime();
    float elapsedTime = currentTime - lastShotTime;

    if (this->ammo_current > 0 && elapsedTime >= this->timeSinceLastTime)
    {
        // �ѱ� ��ġ ���
        Vector2 muzzle = Vector2(this->GetWorldPos() + shooter->GetRight() * scale.x);
        // ź�� ���(�÷��̾ �ٶ󺸴� ����)
        // float rotation_z{ atan2f(shooter->get_right().y, shooter->get_right().x) };

        // ź����
        const Bullet_proto bullet
        (
            muzzle,
            shooter->GetRight(),
            this->ammo_speed * DELTA,
            this->range,
            shooter->charge_current * 5.f
        );
        //���Ϳ� ź push
        bullets.push_back(bullet);
        //ź ���� ����
        this->ammo_current = max(this->ammo_current - 1, 0);

        // ���Ӱ��
        this->lastShotTime = currentTime;
        this->timeSinceLastTime = 1.0f / this->fire_rate;
    }

	return false;
}

void Gun_pistol::Update_Bullets()
{
    for (auto& ammo : this->bullets)
    {
        // ź�� ��ġ �̵�
        // ammo.pos += Vector2(cosf(ammo.rotation.z), sinf(ammo.rotation.z)) * (ammo.speed);
        // ammo.pos += Vector2(0, ammo.gravity_sin);
        // ammo.gravity_sin += ammo.gravity_cos * DELTA;

        ammo.gravityForce += 500.0f * DELTA;

        Vector2 velocity = (ammo.shooting_Dir * ammo.pressPower
            + ammo.gravityDir * ammo.gravityForce);
        ammo.MoveWorldPos(velocity * DELTA);

        // ź�� �� ���� �������
        int map_side{ 10 };
        // x��
        if (ammo.GetLocalPos().x < 0 + map_side)
        {
            ammo.SetWorldPosX(0 + map_side);
            ammo.reflection_y();
            // ammo.rotation.z = atan2f(ammo.get_right().y, -ammo.get_right().x);
        }
        else if (ammo.GetLocalPos().x > 800 - map_side)
        {
            ammo.SetWorldPosX(800 - map_side);
            ammo.reflection_y();
            // ammo.rotation.z = atan2f(ammo.get_right().y, -ammo.get_right().x);
        }
        // y��
        if (ammo.GetLocalPos().y < 0 + map_side)
        {
            ammo.SetWorldPosY(0 + map_side);
            ammo.reflection_x();
            // ammo.rotation.z = atan2f(-ammo.get_right().y, ammo.get_right().x);
        }
        else if (ammo.GetLocalPos().y > 800 - map_side)
        {
            ammo.SetWorldPosY(800 - map_side - 5);
            ammo.reflection_x();
            // ammo.rotation.z = atan2f(-ammo.get_right().y, ammo.get_right().x);
        }

        // ź�� ���� ������Ʈ
        ammo.Update();

        // ź�� ü���� 0�̸� ����
        // if (ammo.Hp == 0) ammo.traveledDistance = range;
    }


    // ź�� ��Ÿ��� �������
    bullets.erase(
        std::remove_if
        (
            bullets.begin(),
            bullets.end(),
            [](const Bullet_proto& b
                ) { return b.hasTraveledTooFar(); }),
        bullets.end()
    );
}

void Gun_pistol::Render_Bullets()
{
    for (auto& ammo : this->bullets)
        ammo.Render();
}
