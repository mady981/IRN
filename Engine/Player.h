#pragma once
#include "Graphics.h"
#include "Map.h"

class Player
{
public:
	Player( const Vec2f& pos,Map& map );
	void setDir( const Vec2f& dir,const bool jump );
	void Tick( const float& dt );
	RecF PlHitBox() const;
	Vec2f PlPos() const;
	int PlWidth() const;
	int PlHeight() const;
private:
	void Update( const float dt );
	void Jump( const float dt );
	void Physiks( const float dt );
public:
private:
	Vec2f pos;
	Vec2f vel = { 0,0 };
	float currfvel = 0;
	float jvel = 0;
	static constexpr float fvelinc = 45.0f;
	static constexpr float jumpspeed = 20.0f;
	static constexpr float speed = 10.0f;
private:
	static constexpr int PlayerWidth = 16;
	static constexpr int PlayerHeight = 24;
private:
	Map& map;
};