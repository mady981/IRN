#pragma once
#include "Colors.h"
#include <string>

class Surface
{
public:
	Surface( const std::wstring& filename );
	Surface( int width,int height );
	Surface( const Surface& rhs );
	~Surface();
	Surface& operator=( const Surface& rhs );
	void PutPixel( int x,int y,Color c );
	Color GetPixel( int x,int y ) const;
	int getWidth() const;
	int getHeight() const;
private:
	Color* pPixel = nullptr;
	int width;
	int height;
};
