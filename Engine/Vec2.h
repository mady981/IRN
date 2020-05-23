#pragma once
#include <compare>

template<typename T>
class Vec2_
{
public:
	Vec2_() = default;
	Vec2_( T x_in,T y_in )
		:
		x( x_in ),
		y( y_in )
	{
	}
	template<typename S>
	Vec2_( const Vec2_<S>& src )
		:
		x( ( T )src.x ),
		y( ( T )src.y )
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
	auto operator<=>( const Vec2_& ) const = default;
	Vec2_& Round()
	{
		return *this = getRound();
	}
	Vec2_ getRound() const
	{
		return { ( T )round( x ),( T )round( y ) };
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
		if ( len != ( T )0 )
		{
			return *this * ( ( T )1 / len );
		}
		return *this;
	}
	Vec2_& SetOne()
	{
		return *this = getSetOne();
	}
	Vec2_ getSetOne() const
	{
		T x1 = x;
		T y1 = y;
		if ( x != 0 )
		{
			x1 /= std::abs( x );
		}
		if ( y != 0 )
		{
			y1 /= std::abs( y );
		}
		return { x1,y1 };
	}
public:
	T x;
	T y;
};

typedef Vec2_<int> Vec2i;
typedef Vec2_<float> Vec2f;
