#pragma once
#include "Graphics.h"
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
				pos.x * pSprite->getWidth(),
				pos.x * pSprite->getWidth() + pSprite->getWidth(),
				pos.y * pSprite->getHeight(),
				pos.y * pSprite->getHeight() + pSprite->getHeight()
			);
		}
		void Draw( const Vec2f& cPos,Graphics& gfx )
		{
			const Vec2f offset = Vec2f( pos ) - cPos;
			gfx.DrawSprite(
				int( offset.x * pSprite->getWidth() + gfx.ScreenWidth / 2 ),
				int( offset.y * pSprite->getHeight() + gfx.ScreenHeight / 2 ),
				*pSprite,
				false
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
	int getContens( const Vec2i& pos );
	bool CollidingWith( const Vec2f& pos,const RecF& rec ) const;
	const Surface* TileSprite() const;
	std::map<Vec2i,Tile*> Tiles() const;
private:
	std::map<Vec2i,Tile*> mTiles;
};
