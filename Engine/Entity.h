#pragma once
#include "Graphics.h"
#include "Map.h"
#include "Animation.h"
#include <vector>

class Entity
{
public:
	Entity( const Vec2f& pos,const Vec2f& vel,const float health,const float speed,const float jumpvel,
		const float fallvelinc,const int width,const int height,const Surface& sprite,Map& map );
	void setDir( const Vec2f& dir,const bool jump );
	void Draw( Graphics& gfx ) const;
	void Tick( const float dt );
private:
	void Update( const float dt );
	void Jump( const float dt );
	void Physiks( const float dt );
public:
	RecI EntityHitBox() const;
private:
	Vec2f ePos;
	Vec2f eVel;
	const float eSpeed;
	const float eJumpVel;
	const float eHealth;
	const int eWidth;
	const int eHeight;
	const float eFallVelInc;
	float eCurrFallVel = 0;
private:
	const Surface eSprite;
	std::vector<Animation> animations;
	Map& map;
};