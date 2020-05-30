#pragma once
#include "Graphics.h"

namespace SpriteEffect
{
	class Copy
	{
	public:
		void operator()( Color cSrc,int xDest,int yDest,Graphics& gfx ) const
		{
			gfx.PutPixel( xDest,yDest,cSrc );
		}
	};

	class Chroma
	{
	public:
		Chroma( Color c )
			:
			chroma( c )
		{}
		void operator()( Color cSrc,int xDest,int yDest,Graphics& gfx ) const
		{
			if ( cSrc != chroma )
			{
				gfx.PutPixel( xDest,yDest,cSrc );
			}
		}
	private:
		Color chroma;
	};

	class Alpha
	{
	public:
		Alpha( float a,Color c = Colors::Magenta )
			:
			alpha( a ),
			chroma( c )
		{}
		void operator()( Color cSrc,int xDest,int yDest,Graphics& gfx ) const
		{
			if ( cSrc != chroma )
			{
				Color cGet = gfx.getPixel( xDest,yDest );
				gfx.PutPixel(
					xDest,
					yDest,
					Color(
						unsigned char( ( float )cSrc.GetR() * alpha + ( float )cGet.GetR() * ( 1 - alpha ) ),
						unsigned char( ( float )cSrc.GetG() * alpha + ( float )cGet.GetG() * ( 1 - alpha ) ),
						unsigned char( ( float )cSrc.GetB() * alpha + ( float )cGet.GetB() * ( 1 - alpha ) )
					)
				);
			}
		}
	private:
		float alpha;
		Color chroma;
	};

	class Substitution
	{
	public:
		Substitution( Color s,Color c = Colors::Magenta )
			:
			sub( s ),
			chroma( c )
		{}
		void operator()( Color cSrc,int xDest,int yDest,Graphics& gfx ) const
		{
			if ( cSrc != chroma )
			{
				gfx.PutPixel( xDest,yDest,sub );
			}
		}
	private:
		Color sub;
		Color chroma;
	};
}