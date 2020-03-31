#include "Vec2f.h"
#include <cmath>

Vec2f::Vec2f(float x_in, float y_in)
	:
	x( x_in ),
	y( y_in )
{
}

Vec2f Vec2f::operator+(const Vec2f& rhs) const
{
	return Vec2f( x + rhs.x , y + rhs.y );
}

Vec2f& Vec2f::operator+=(const Vec2f& rhs)
{
	return *this = *this + rhs;
}

Vec2f Vec2f::operator-( const Vec2f& rhs ) const
{
	return Vec2f( x - rhs.x,y - rhs.y );
}

Vec2f& Vec2f::operator-=( const Vec2f& rhs )
{
	return *this = *this - rhs;
}

Vec2f Vec2f::operator*(float rhs) const
{
	return Vec2f( x * rhs , y * rhs );
}

Vec2f& Vec2f::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Vec2f Vec2f::operator/( float rhs ) const
{
	return Vec2f( x / rhs,y / rhs );
}

Vec2f& Vec2f::operator/=( float rhs )
{
	return *this = *this / rhs;
}

bool Vec2f::operator==( const Vec2f& rhs ) const
{
	return x == rhs.x && y == rhs.y;
}

bool Vec2f::operator!=( const Vec2f& rhs ) const
{
	return !( *this == rhs );
}

float Vec2f::getLength() const
{
	return std::sqrt( getLengthSq() );
}

float Vec2f::getLengthSq() const
{
	return x * x + y * y;
}

Vec2f& Vec2f::Nomalize()
{
	return *this = getNomalize();
}

Vec2f Vec2f::getNomalize() const
{
	const float len = getLengthSq();
	if ( len != 0.0f )
	{
		return *this * (1.0f / len);
	}
	return *this;
}

Vec2f::operator Vec2i() const
{
	return{ int( x ),int( y ) };
}
