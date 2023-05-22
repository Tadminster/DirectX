#pragma once

class Bullet_proto : public ObRect
{
protected:

public:
    Vector2         Pos_Current;            // ���� ��ġ(local)
    Vector2         Pos_Initial;            // ó�� �߻�� ��ġ
    int             Hp;                     // ü��
    Vector2         shooting_Dir;           // ����
    float           speed;                  // �ӵ�
    int             Damage;                 // ���ݷ�
    float           range;                  // �����Ÿ�
    float           traveledDistance;       // �̵��Ÿ�
    float           pressPower;                 // ����

    Vector2         gravityDir;             // �߷� ����
    float           gravityForce;           // �߷� ��
    float           gravityWeight;          // �߷� ����ġ

public:
    Bullet_proto(Vector2 pos, Vector2 direction, float speed, float range, float charge);

    virtual void Update() override;
    virtual void Render() override;

    /* ź�� �̵��� �Ÿ��� range�� �Ѿ����� Ȯ�� */
    bool hasTraveledTooFar() const { return traveledDistance >= range; }
    bool hasIntersect(class GameObject* target);

    void reflection_y();
    void reflection_x();
};

