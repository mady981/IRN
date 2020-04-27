#include "Text.h"

Text::Text( const int Rows,const int Collums,Surface& font,Color chroma )
	:
	font( font ),
	chroma( chroma ),
	CharWidth( font.getWidth() / Rows ),
	CharHeight( font.getHeight() / Collums )
{
}

void Text::DrawText( const std::string& text,const Vec2i& pos,Graphics& gfx ) const
{
	int currletter = 0;
	for ( auto c : text )
	{
		gfx.DrawSprite( pos.x + currletter * CharWidth,pos.y,CharMaping( c ),font,chroma );
		++currletter;
	}
}

RecI Text::CharMaping( char c ) const
{
	const char y = c / ( font.getWidth() / CharWidth );
	const char x = c % ( font.getWidth() / CharWidth );
	return RecI( x * CharWidth,( x + 1 ) * CharWidth,y * CharHeight,( y + 1 ) * CharHeight );
}
