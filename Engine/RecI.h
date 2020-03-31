#pragma once
#include "Vec2i.h"

class RecI
{
public:
	RecI() = default;
	RecI( int left_in,int right_in,int top_in,int bottem_in );
	RecI( const Vec2i& topleft,const Vec2i& bottemright );
	RecI( const Vec2i& topleft,int width,int height );
	bool isOverlappingWith( const RecI& other ) const;
	bool isOverlappingWith( const Vec2i& other ) const;
	static RecI fromCenter( const Vec2i& center,int width,int height );
public:
	int left;
	int right;
	int top;
	int bottem;
};
