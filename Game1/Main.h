#pragma once

class Main : public Scene
{
private:
	class Player* player[2];
	class Player* goalpost[2];
	class Ball* ball;

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
