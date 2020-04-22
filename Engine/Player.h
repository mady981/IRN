#pragma once
#include "Graphics.h"
#include "Map.h"

class Player
{
public:
	Player( const Vec2f& pos );
	void setDir( const Vec2f& dir,const bool jump );
	void Draw( Graphics& gfx ) const;
	void Tick( const float& dt );
private:
	void Update( const float dt );
	void Jump( const float dt );
	void Physiks( const float dt );
public:
	RecF PlayerHitBox() const;
	Vec2i PlayerPos() const;
private:
	Vec2f pos;
	Vec2f vel = { 0,0 };
	float currfvel = 0;
	float jvel = 0;
	static constexpr float fvelinc = 300.0f;
	static constexpr float jumpspeed = 160.0f;
	static constexpr float speed = 120.0f;
private:
	Map map;
};