#pragma once
#include "Graphics.h"
#include "Rec.h"
#include "Vec2.h"
#include "Surface.h"
#include <string>
#include "SpriteEffect.h"

class Text
{
public:
	Text( const int Rows,const int Collums,const Surface* font,Color chroma = Colors::Black )
		:
		font( font ),
		chroma( chroma ),
		CharWidth( font->getWidth() / Rows ),
		CharHeight( font->getHeight() / Collums )
	{}
	void DrawText( const std::string& text,const Vec2i& pos,Graphics& gfx ) const
	{
		int currletter = 0;
		for ( auto c : text )
		{
			gfx.DrawSprite( pos.x + currletter * CharWidth,pos.y,CharMaping( c ),*font,false,SpriteEffect::Chroma( chroma ) );
			++currletter;
		}
	}
	void DrawText( const std::string& text,int x,int y,Graphics& gfx ) const
	{
		DrawText( text,Vec2i( x,y ),gfx );
	}
	int getGlythWidth() const
	{
		return ( int )CharWidth;
	}
	int getGlythHeight() const
	{
		return ( int )CharHeight;
	}
private:
	RecI CharMaping( char c ) const
	{
		const char y = c / ( font->getWidth() / CharWidth );
		const char x = c % ( font->getWidth() / CharWidth );
		return RecI( x * CharWidth,( x + 1 ) * CharWidth,y * CharHeight,( y + 1 ) * CharHeight );
	}
private:
	const Surface* font;
	const Color chroma;
	const char CharHeight;
	const char CharWidth;
};