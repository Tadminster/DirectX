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
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
