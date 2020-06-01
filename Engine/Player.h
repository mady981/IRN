#pragma once
#include "Keyboard.h"
#include "Entity.h"
#include "SurfaceCodex.h"
#include "Map.h"
#include "Text.h"

class Player : public Entity
{
public:
	Player( const Vec2f& pos );
	void HandleImputs( Keyboard& kbd,class WorldObject& world );
	void Draw( const Vec2f& pos_c,Graphics& gfx ) const override;
private:
	static constexpr int HPBarHeight = 10;
	static constexpr int HpBarWidth = 150;
	Text text = Text( 32,4,SurfaceCodex::Retrieve( L"FontSheet16x18.bmp" ) );
	/*********************TestFunctions Begin****************************/
public:
	void debugSetPlayer( const Vec2f& debugpos,float fallvel )
	{
		pos = debugpos;
		currFallSpeed = fallvel;
	}
	void healPlayer( int heal )
	{
		if ( ( HitPoints += heal ) > maxHitPoints )
		{
			HitPoints = maxHitPoints;
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
