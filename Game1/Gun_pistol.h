#pragma once
class Gun_pistol : public ObRect
{
public:
	Vector2			pos;

	std::string		name;
	
	int				ammo_current;
	int				ammo_max;
	int				damage;
	float			range;
	float			ammo_speed;
	float			fire_rate;

	float			lastShotTime;
	float			timeSinceLastTime;

	std::vector<class Bullet_proto> bullets;

	Gun_pistol();

	bool			Fire(class Player* shooter);
	virtual void	Update_Bullets();
	virtual void	Render_Bullets();

};

