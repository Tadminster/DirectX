#pragma once
class Player : public ObCircle
{
public:
	int score;

public:
	Player();
	virtual ~Player();
	void Init(Vector2 spawn, bool isLeft);
	void Control(Vector2 arrow);
	void Update() override;
	void Render() override;
};

