#pragma once
#include "Entity.h"
#include "Surface.h"
#include "Map.h"

class Player : public Entity
{
public:
	Player( const Vec2f& pos,Map& map );
	float MaxHitPoints() const;
	/*********************TestFunctions Begin****************************/
public:
	void debugSetPlayer( const Vec2f& debugpos,float fallvel )
	{
		pos = debugpos;
		currFallSpeed = fallvel;
	}
	void healPlayer( float heal )
	{
		if ( ( hitpoints += heal ) > maxHitPoints )
		{
			hitpoints = maxHitPoints;
		}
	}
	void incMaxHP( float inc )
	{
		maxHitPoints += inc;
	}
	void decMaxHP( float dec )
	{
		maxHitPoints -= dec;
	}
	float oldy = 0;
	/*********************TestFunctions End****************************/
};
