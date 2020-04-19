#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include "Animation.h"
#include "Surface.h"
#include <vector>

class Character
{
private:
	enum class Sequence
	{
		WalkingLeft,
		WalkingRight,
		WalkingUp,
		WalkingDown,
		StandingLeft,
		StandingRight,
		StandingUp,
		StandingDown,
		Count
	};
public:
	Character( const int width,const int height,const float holdtime,const int nanimations,const Vec2f& pos,const float speed,const Surface& sprite );
	void SetDirection( Vec2f& dir );
	void Update( float dt );
	void Draw( Graphics& gfx ) const;
private:
	const float speed;
	Vec2f pos;
	Vec2f vel = { 0.0f,0.0f };
	Surface sprite;
	std::vector<Animation> animations;
	Sequence CurrAniation = Sequence::StandingDown;
};