#pragma once
#include "Entity.h"
#include "SurfaceCodex.h"

class Enemy : public Entity
{
public:
	Enemy( const Vec2f& pos );
	void AI( Entity* target,class WorldObject& world );
	void Draw( const Vec2f& pos_c,Graphics& gfx ) const override;
private:
	RecF AttackHB() const;
private:
	const float TrackDistSq = 16.0f * 16.0f;
	const float inRangeSq = 1.0f ;
	const int AttackWidth = 20;
	const int AttackHeight = 20;
};