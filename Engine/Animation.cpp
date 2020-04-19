#include "Animation.h"

Animation::Animation( int x,int y,int width,int height,float holdtime,int animations,const Surface& sprite,Color chroma )
	:
	sprite( sprite ),
	HoldTime( holdtime ),
	chroma( chroma )

{
	for ( int i = 0; i < animations; ++i )
	{
		frame.emplace_back( x + i * width,x + ( i + 1 ) * width,y,y + height );
	}
}

void Animation::Update( float dt )
{
	CurrTime += dt;
	while ( CurrTime >= HoldTime )
	{
		Advance();
		CurrTime -= HoldTime;
	}
}

void Animation::Draw( const Vec2i& pos,Graphics& gfx ) const
{
	gfx.DrawSprite( pos.x,pos.y,frame[CurrAnimation],sprite );
}

void Animation::Advance()
{
	if ( ++CurrAnimation >= frame.size() )
	{
		CurrAnimation = 0;
	}
}
