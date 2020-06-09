#define GOD_GRAPHICS
#include "Graphics.h"

void Graphics::BeginFrame()
{
	// clear the sysbuffer
	memset( pSysBuffer,0u,sizeof( Color ) * Graphics::ScreenHeight * Graphics::ScreenWidth );
}

void Graphics::PutPixel( int x,int y,Color c )
{
	assert( x >= 0 );
	assert( x < int( Graphics::ScreenWidth ) );
	assert( y >= 0 );
	assert( y < int( Graphics::ScreenHeight ) );
	pSysBuffer[Graphics::ScreenWidth * y + x] = c;
}

Color Graphics::getPixel( int x,int y )
{
	assert( x >= 0 );
	assert( x < int( Graphics::ScreenWidth ) );
	assert( y >= 0 );
	assert( y < int( Graphics::ScreenHeight ) );
	return pSysBuffer[Graphics::ScreenWidth * y + x];
}

void Dummy( Graphics& gfx )
{
	gfx.DrawSprite( Vec2_{ 0,0 },Rec_{ 0,0,0,0 },Rec_{ 0,0,0,0 },Surface{},false,SpriteEffect::Copy{} );
	gfx.DrawSprite( Vec2_{ 0,0 },Rec_{ 0,0,0,0 },Rec_{ 0,0,0,0 },Surface{},false,SpriteEffect::Chroma{ Colors::Black } );
	gfx.DrawSprite( Vec2_{ 0,0 },Rec_{ 0,0,0,0 },Rec_{ 0,0,0,0 },Surface{},false,SpriteEffect::Substitution{ Colors::Black,Colors::Black } );
}