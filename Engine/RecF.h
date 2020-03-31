#pragma once
#include "Vec2f.h"
#include "RecI.h"

class RecF
{
public:
	RecF() = default;
	RecF( float left_in,float right_in,float top_in,float bottem_in );
	RecF( const Vec2f& topleft,const Vec2f& bottemright );
	RecF( const Vec2f& topleft,float width,float height );
	bool isOverlappingWith( const RecF& other ) const;
	bool isOverlappingWith( const Vec2f& other ) const;
	static RecF fromCenter( const Vec2f & center,float width,float height );
	operator RecI() const;
public:
	float left;
	float right;
	float top;
	float bottem;
};
