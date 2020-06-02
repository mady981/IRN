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
	template<typename T>
	T exp( T base_in,T expo_in )
	{
		auto base = 1;
		for ( auto n = 0; n < expo_in; ++n )
		{
			base *= base_in;
		}
		return base;
	}
}