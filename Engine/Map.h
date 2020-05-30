#pragma once
#include "Graphics.h"
#include "SpriteEffect.h"
#include "SurfaceCodex.h"
#include <map>

class Map
{
private:
	class Tile
	{
	public:
		Tile( const Vec2i& pos,const int id )
			:
			pos( pos ),
			id( id )
		{}
		RecI TileHitBox() const
		{
			return RecI(
				pSprite->getRect<int>().WithPosition( pos * Dimantion() )
			);
		}
		void Draw( const Vec2f& cPos,Graphics& gfx )
		{
			const Vec2f offset = Vec2f( pos ) - cPos;
			gfx.DrawSprite(
				int( offset.x * Dimantion() + gfx.ScreenWidth / 2 ),
				int( offset.y * Dimantion() + gfx.ScreenHeight / 2 ),
				*pSprite,
				false,
				SpriteEffect::Chroma{ Colors::Magenta }
			);
		}
		const Vec2i pos;
		const int id;
		const Surface* pSprite = SurfaceCodex::Retrieve( L"GrassTile.bmp" );
	};
public:
	Map()
	{
		for ( int x = -20; x < 10; ++x )
		{
			mTiles.emplace( Vec2i( x,0 ),new Tile( Vec2i( x,0 ),1 ) );
		}
		for ( int p = 10; p < 30; ++p )
		{
			mTiles.emplace( Vec2i( p,-p + 10 ),new Tile( Vec2i( p,-p + 10 ),1 ) );
		}
		for ( int x = -25; x < -15; ++x )
		{
			mTiles.emplace( Vec2i( x,-5 ),new Tile( Vec2i( x,-5 ),1 ) );
		}
	}
	bool setTile( const Vec2i& pos,const int id = 0 );
	int getContens( const Vec2i& pos ) const;
	void Draw( const Vec2f& pos_c,Graphics& gfx ) const;
	bool CollidingWith( const Vec2f& pos,const RecF& rec ) const;
	static int Dimantion();
private:
	std::map<Vec2i,Tile*> mTiles;
	const int HalfRenderHeight = Graphics::ScreenHeight / SurfaceCodex::Retrieve( L"GrassTile.bmp" )->getHeight() / 2 + 1;
	const int HalfRenderWidth = Graphics::ScreenWidth / SurfaceCodex::Retrieve( L"GrassTile.bmp" )->getWidth() / 2 + 1;
};
