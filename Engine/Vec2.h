#pragma once

template<typename T>
class Vec2_
{
public:
	Vec2_( T x_in,T y_in )
		:
		x( x_in ),
		y( y_in )
	{
	}
	Vec2_ operator+( const Vec2_& rhs ) const
	{
		return Vec2_( x + rhs.x,y + rhs.y );
	}
	Vec2_& operator+=( const Vec2_& rhs )
	{
		return *this = *this + rhs;
	}
	Vec2_ operator-( const Vec2_& rhs ) const
	{
		return Vec2_( x - rhs.x,y - rhs.y );
	}
	Vec2_& operator-=( const Vec2_& rhs )
	{
		return *this = *this - rhs;
	}
	Vec2_ operator*( T rhs ) const
	{
		return Vec2_( x * rhs,y * rhs );
	}
	Vec2_& operator*=( T rhs )
	{
		return *this = *this * rhs;
	}
	Vec2_ operator/( T rhs ) const
	{
		return Vec2_( x / rhs,y / rhs );
	}
	Vec2_& operator/=( T rhs )
	{
		return *this = *this / rhs;
	}
	bool operator==( const Vec2_& rhs ) const
	{
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=( const Vec2_& rhs ) const
	{
		return !( *this == rhs );
	}
	T getLength() const
	{
		return std::sqrt( getLengthSq() );
	}
	T getLengthSq() const
	{
		return x * x + y * y;
	}
	Vec2_& Nomalize()
	{
		return *this = getNomalize();
	}
	Vec2_ getNomalize() const
	{
		const T len = getLengthSq();
		if ( len != 0.0f )
		{
			return *this * ( 1.0f / len );
		}
		return *this;
	}
public:
	T x;
	T y;
};

typedef Vec2_<int> Vec2i;
typedef Vec2_<float> Vec2f;
