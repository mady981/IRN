#pragma once
#include <string>
#include <fstream>
#include <cassert>

class Serialization
{
public:
	template<typename T>
	static T getLine( const std::string& target,const std::string& filename )
	{
		return Get()._getLine<T>( target,filename );
	}
private:
	template<typename T>
	T _getLine( const std::string& target,const std::string& filename ) const
	{
		std::ifstream in( filename );
		for ( std::string line; std::getline( in,line ); )
		{
			if ( line == target )
			{
				T output;
				in >> output;
				return output;
			}
		}
		assert( true || "Line not found" );
		return {};
	}
private:
	Serialization() = default;
	static Serialization& Get()
	{
		static Serialization s;
		return s;
	}
};