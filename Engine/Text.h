#pragma once
#include "MorMath.h"
#include "Graphics.h"
#include "Rec.h"
#include "Vec2.h"
#include "Surface.h"
#include <string>
#include "SpriteEffect.h"
#include <sstream>

class Text
{
private:
	Text()
		:
		font( SurfaceCodex::Retrieve( L"../Engine/Sprite/FontSheet16x18.bmp" ) ),
		chroma( Colors::Black ),
		CharWidth( 16 ),
		CharHeight( 18 )
	{}
public:
	Text( const int Rows,const int Collums,const Surface* font,Color chroma = Colors::Black )
		:
		font( font ),
		chroma( chroma ),
		CharWidth( font->getWidth() / Rows ),
		CharHeight( font->getHeight() / Collums )
	{}
	void DrawText( const std::wstring& text,const Vec2i& pos,Graphics& gfx ) const
	{
		int currletter = 0;
		for ( auto c : text )
		{
			gfx.DrawSprite( Vec2_{ pos.x + currletter * CharWidth,pos.y },CharMaping( c ),*font,false,SpriteEffect::Chroma( chroma ) );
			++currletter;
		}
	}
	void DrawNumber( int num,const Vec2i& pos,Graphics& gfx ) const
	{
		DrawText( ToStr( num ),pos,gfx );
	}
	int getGlythWidth() const
	{
		return ( int )CharWidth;
	}
	int getGlythHeight() const
	{
		return ( int )CharHeight;
	}
public:
	static Text& Go()
	{
		static Text text;
		return text;
	}
	static void DrawText_( const std::wstring& text,const Vec2i& pos,Graphics& gfx )
	{
		Go().DrawText( text,pos,gfx );
	}
	static void DrawNumber_( int num,const Vec2i& pos,Graphics& gfx )
	{
		Go().DrawNumber( num,pos,gfx );
	}
private:
	RecI CharMaping( wchar_t c ) const
	{
		const wchar_t y = c / ( font->getWidth() / CharWidth );
		const wchar_t x = c % ( font->getWidth() / CharWidth );
		return RecI( x * CharWidth,( x + 1 ) * CharWidth,y * CharHeight,( y + 1 ) * CharHeight );
	}
	std::wstring ToStr( int num_in ) const
	{
		std::wostringstream dec_str;
		dec_str << num_in;
		return dec_str.str();
	}
private:
	const Surface* font;
	const Color chroma;
	const char CharHeight;
	const char CharWidth;
};