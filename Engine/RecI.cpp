#include "RecI.h"

RecI::RecI( int left_in,int right_in,int top_in,int bottem_in )
	:
	left( left_in ),
	right( right_in ),
	top( top_in ),
	bottem( bottem_in )
{
}

RecI::RecI( const Vec2i& topleft,const Vec2i& bottemright )
	:
	RecI( topleft.x,bottemright.x,topleft.y,bottemright.y )
{
}

RecI::RecI( const Vec2i& topleft,int width,int height )
	:
	RecI( topleft,topleft + Vec2i( width,height ) )
{
}

bool RecI::isOverlappingWith( const RecI& other ) const
{
	return right > other.left && left < other.right
		&& bottem > other.top && top < other.bottem;
}

bool RecI::isOverlappingWith( const Vec2i& other ) const
{
	return right > other.x && left < other.x
		&& bottem > other.y && top < other.y;
}

RecI RecI::fromCenter( const Vec2i& center,int width,int height )
{
	const Vec2i half( width / 2,height / 2 );
	return RecI( center - half,center + half );
}
