#include "Surface.h"

void Surface::PutPixel( int x,int y,Color c )
{
	assert( x >= 0 );
	assert( x < width );
	assert( y >= 0 );
	assert( y < height );
	pixel.data()[y * width + x] = c;
}

Color Surface::GetPixel( int x,int y ) const
{
	assert( x >= 0 );
	assert( x < width );
	assert( y >= 0 );
	assert( y < height );
	return pixel.data()[y * width + x];
}

void Surface::Fill( Color c )
{
	std::fill( pixel.begin(),pixel.end(),c );
}