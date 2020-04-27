#pragma once
#include "Graphics.h"
#include "Map.h"
#include "Surface.h"

class Player
{
public:
	Player( const Vec2f& pos,Map& map );
	~Player();
	void setDir( const Vec2f& dir,const bool jump );
	void Tick( const float& dt );
	void PlDamage( const float damage );
public:
	RecF PlHitBox() const;
	Vec2f PlPos() const;
	Surface* PlSprite() const;
	float getPlHP() const;
private:
	void Update( const float dt );
	void Jump( const float dt );
	void Physiks( const float dt );
private:
	Vec2f pos;
	Vec2f vel = { 0,0 };
	float currfvel = 0;
	float jvel = 0;
	static constexpr float fvelinc = 45.0f;
	static constexpr float jumpspeed = 20.0f;
	static constexpr float speed = 10.0f;
	static constexpr float maxhp = 100.0f;
	float currhp = maxhp;
	bool isAlive = true;
private:
	Map& map;
	Surface* pSprite = new Surface( L"../Engine/Sprite/Player.bmp" );
public:
	void debugSetPlayer( const Vec2f& debugpos,float fallvel )
	{
		pos = debugpos;
		currfvel = fallvel;
	}
	void healPlayer( float heal )
	{
		if ( currhp < maxhp )
		{
			currhp += heal;
		}
		else
		{
			currhp = maxhp;
		}
	}
	float oldy = 0;
};
