#pragma once
#include "Entity.h"
#include "SurfaceCodex.h"

class Enemy : public Entity
{
public:
	Enemy( const Vec2f& pos,Map& map,const float& TrackDist = 16.0f,const float& inRange = 1.0f,const int& AttackWidth = 20,const int& AttackHeight = 20 );
	void AI( Entity& target );
	void Draw( const Vec2f& pos_c,Graphics& gfx ) const override;
private:
	RecF AttackHB() const;
private:
	Vec2f facing;
	const float TrackDistSq;
	const float inRangeSq;
	const int AttackWidth;
	const int AttackHeight;
};