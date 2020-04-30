#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy( const Vec2f& pos,const float& TrackDist,const float& inRange,const int& AttackWidth,const int& AttackHeight,Map& map );
	void AI( Entity& target );
	Vec2f Facing() const override;
private:
	RecF AttackHB() const;
private:
	Vec2f facing;
	const float TrackDistSq;
	const float inRangeSq;
	const int AttackWidth;
	const int AttackHeight;
};