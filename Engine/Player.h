#pragma once
#include "Keyboard.h"
#include "Entity.h"
#include "SurfaceCodex.h"
#include "Map.h"

class Player : public Entity
{
public:
	Player( const Vec2f& pos,Map& map );
	void HandleImputs( Keyboard& kbd );
	void Draw( const Vec2f& pos_c,Graphics& gfx ) const override;
private:
	static constexpr int HPBarHeight = 10;
	static constexpr int HpBarWidth = 150;
	/*********************TestFunctions Begin****************************/
public:
	void debugSetPlayer( const Vec2f& debugpos,float fallvel )
	{
		pos = debugpos;
		currFallSpeed = fallvel;
	}
	void healPlayer( int heal )
	{
		if ( ( hitpoints += heal ) > maxHitPoints )
		{
			hitpoints = maxHitPoints;
		}
	}
	void incMaxHP( int inc )
	{
		maxHitPoints += inc;
	}
	void decMaxHP( int dec )
	{
		maxHitPoints -= dec;
	}
	float oldy = 0;
	bool ispresst = false;
	/*********************TestFunctions End****************************/
};
