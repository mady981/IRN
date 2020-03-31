#include "RecF.h"

RecF::RecF( float left_in,float right_in,float top_in,float bottem_in )
	:
	left( left_in ),
	right( right_in ),
	top( top_in ),
	bottem( bottem_in )
{
}

RecF::RecF( const Vec2f& topleft,const Vec2f& bottemright )
	:
	RecF( topleft.x,bottemright.x,topleft.y,bottemright.y )
{
}

RecF::RecF( const Vec2f& topleft,float width,float height )
	:
	RecF( topleft,topleft + Vec2f( width,height ) )
{
}

bool RecF::isOverlappingWith( const RecF& other ) const
{
	return right > other.left && left < other.right
		&& bottem > other.top && top < other.bottem;
}

bool RecF::isOverlappingWith( const Vec2f& other ) const
{
	return right > other.x && left < other.x
		&& bottem > other.y && top < other.y;
}

RecF RecF::fromCenter( const Vec2f& center,float width,float height )
{
	const Vec2f half( width / 2.0f,height / 2.0f );
	return RecF( center - half,center + half );
}

RecF::operator RecI() const
{
	return{ int( left ),int( right ),int( top ),int( bottem ) };
}
