#pragma once

namespace MorMath
{
	template<typename T>
	T sqr( T num )
	{
		return num * num;
	}
	template<typename T>
	T abs( T num )
	{
		return num < 0 ? -num : num;
	}
	template<typename T>
	T one( T num )
	{
		return num / abs( num );
	}
}