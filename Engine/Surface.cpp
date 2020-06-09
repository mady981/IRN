#include "Surface.h"
#include "ChiliWin.h"
#include <fstream>

Surface::Surface( const std::wstring& filename )
{
	std::ifstream file( filename,std::ios::binary );
	BITMAPFILEHEADER bmfileheader;
	file.read( reinterpret_cast< char* >( &bmfileheader ),sizeof( bmfileheader ) );
	BITMAPINFOHEADER bminfoheader;
	file.read( reinterpret_cast< char* >( &bminfoheader ),sizeof( bminfoheader ) );
	assert( bminfoheader.biBitCount == 24 || bminfoheader.biBitCount == 32 );
	assert( bminfoheader.biCompression == BI_RGB );
	const bool is32 = bminfoheader.biBitCount == 32;
	width = bminfoheader.biWidth;
	int yStart;
	int yEnd;
	int dy;
	if ( bminfoheader.biHeight < 0 )
	{
		height = -bminfoheader.biHeight;
		yStart = 0;
		yEnd = height;
		dy = 1;
	}
	else
	{
		height = bminfoheader.biHeight;
		yStart = height - 1;
		yEnd = -1;
		dy = -1;
	}
	pixel.resize( (size_t)width * (size_t)height );
	file.seekg( bmfileheader.bfOffBits );
	const int padding = ( 4 - ( width * 3 ) % 4 ) % 4;
	for ( int y = yStart; y != yEnd; y += dy )
	{
		for ( int x = 0; x < width; ++x )
		{
			PutPixel( x,y,Color( file.get(),file.get(),file.get() ) );
			if ( is32 )
			{
				file.seekg( 1,std::ios::cur );
			}
		}
		if ( !is32 )
		{
			file.seekg( padding,std::ios::cur );
		}
	}
}

Surface::Surface( int width,int height )
	:
	width( width ),
	height( height ),
	pixel( (size_t)width * (size_t)height )
{
}

int Surface::getWidth() const
{
	return width;
}

int Surface::getHeight() const
{
	return height;
}

Rec_<int> Surface::getRect() const
{
	return Rec_<int>( 0,width,0,height );
}

const Color* Surface::Date()
{
	return pixel.data();
}
