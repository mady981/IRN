#pragma once

class Vec2i
{
public:
	Vec2i() = default;
	Vec2i( int x_in,int y_in );
	Vec2i operator+( const Vec2i& rhs ) const;
	Vec2i& operator+=( const Vec2i& rhs );
	Vec2i operator-( const Vec2i& rhs ) const;
	Vec2i& operator-=( const Vec2i& rhs );
	Vec2i operator*( int rhs ) const;
	Vec2i& operator*=( int rhs );
	Vec2i operator/( int rhs ) const;
	Vec2i& operator/=( int rhs );
	bool operator==( const Vec2i& rhs ) const;
	bool operator!=( const Vec2i& rhs ) const;
	float getLength() const;
	float getLengthSq() const;
	Vec2i& Nomalize();
	Vec2i getNomalize() const;
public:
	int x;
	int y;
};
