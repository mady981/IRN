#pragma once
#include "Graphics.h"
#include "Rec.h"
#include "Vec2.h"
#include "Surface.h"
#include <string>

class Text
{
public:
	Text( const int Rows,const int Collums,Surface& font,Color chroma = Colors::Black );
	void DrawText( const std::string& text,const Vec2i& pos,Graphics& gfx ) const;
private:
	RecI CharMaping( char c ) const;
private:
	Surface font;
	const Color chroma;
	const char CharHeight;
	const char CharWidth;
};