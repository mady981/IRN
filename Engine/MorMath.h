#pragma once

namespace MorMath
{
	template<typename T>
	T sqr( T num_in )
	{
		return num_in * num_in;
	}
	template<typename T>
	T abs( T num_in )
	{
		return num_in < 0 ? -num_in : num_in;
	}
	template<typename T>
	T one( T num_in )
	{
		return num_in / abs( num_in );
	}
}