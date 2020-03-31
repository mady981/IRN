#pragma once
#include "Vec2i.h"

class Vec2f
{
public:
	Vec2f() = default;
	Vec2f( float x_in , float y_in );
	Vec2f operator+( const Vec2f& rhs ) const;
	Vec2f& operator+=( const Vec2f& rhs );
	Vec2f operator-( const Vec2f& rhs ) const;
	Vec2f& operator-=( const Vec2f& rhs );
	Vec2f operator*( float rhs ) const;
	Vec2f& operator*=( float rhs );
	Vec2f operator/( float rhs ) const;
	Vec2f& operator/=( float rhs );
	bool operator==( const Vec2f& rhs ) const;
	bool operator!=( const Vec2f& rhs ) const;
	float getLength() const;
	float getLengthSq() const;
	Vec2f& Nomalize();
	Vec2f getNomalize() const;
	operator Vec2i() const;
public:
	float x;
	float y;
};

