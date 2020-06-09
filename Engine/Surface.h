#pragma once
#include "Colors.h"
#include "Rec.h"
#include <vector>
#include <string>
#include <cassert>

class Surface
{
public:
	Surface() = default;
	Surface( const std::wstring& filename );
	Surface( int width,int height );
	void PutPixel( int x,int y,Color c );
	Color GetPixel( int x,int y ) const;
	int getWidth() const;
	int getHeight() const;
	Rec_<int> getRect() const;
	const Color* Date();
	void Fill( Color c );
private:
	std::vector<Color> pixel;
	int width;
	int height;
};
