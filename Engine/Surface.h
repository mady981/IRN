#pragma once
#include "Colors.h"
#include "Rec.h"
#include <vector>
#include <string>

class Surface
{
public:
	Surface() = default;
	Surface( const std::wstring& filename );
	Surface( int width,int height );
	Surface( const Surface& ) = default;
	Surface& operator=( const Surface& ) = default;
	void PutPixel( int x,int y,Color c );
	Color GetPixel( int x,int y ) const;
	int getWidth() const;
	int getHeight() const;
	template<typename T>
	Rec_<T> getRect() const
	{
		return { ( T )0,( T )width,( T )0,( T )height };
	}
private:
	std::vector<Color> vPixel;
	int width;
	int height;
};
