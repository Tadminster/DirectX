#pragma once
#define number_star 500

class Main : public Scene
{
private:
	// ����
	class ObStar* bg_star[number_star];
	class Ob_floor* floor;

	// �÷��̾�
	class Player* player;
	class Gun_pistol* pistol;

	//class Ball* ball;
	//class Player* goalpost[2];

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
