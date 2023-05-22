#pragma once
class Player : public ObRect
{
public:

	// 플레이어 능력치
	int		speed;
	int		score;
	float	jump_power;
	float	jump_startPoint;
	float	charge_current;

	class Gun_pistol* pistol;

	// 플레이어 상태
	int		hand;
	bool	jump_status;

public:
	Player();
	virtual ~Player();
	void Init(Vector2 spawn, bool isLeft);
	void Control();
	void Control(Vector2 arrow);
	void Update() override;
	void Render() override;
};

