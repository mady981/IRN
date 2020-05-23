#pragma once
#include "Keyboard.h"
#include "Entity.h"
#include "SurfaceCodex.h"
#include "Map.h"

class Player : public Entity
{
public:
	Player( const Vec2f& pos,Map& map );
	void HandleImtputs( Keyboard& kbd );
	void Draw( const Vec2f& cPos,Graphics& gfx ) const override;
public:
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
