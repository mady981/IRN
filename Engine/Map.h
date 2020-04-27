#pragma once
#include "Graphics.h"
#include <map>

class Map
{
private:
	class Tile
	{
	public:
		Tile( const Vec2i& pos,const int id,const Surface& pSprite )
			:
			pos( pos ),
			id( id ),
			pSprite( pSprite )
		{}
		RecI TileHitBox() const
		{
			return RecI(
				pos.x * pSprite.getWidth(),
				pos.x * pSprite.getWidth() + pSprite.getWidth(),
				pos.y * pSprite.getHeight(),
				pos.y * pSprite.getHeight() + pSprite.getHeight()
			);
		}
		const Vec2i pos;
		const int id;
		const Surface& pSprite;
	};
public:
	Map()
	{
		for ( int x = -20; x < 10; ++x )
		{
			mTiles.emplace( Vec2i( x,0 ),new Tile( Vec2i( x,0 ),1,*pSprite ) );
		}
		for ( int p = 10; p < 30; ++p )
		{
			mTiles.emplace( Vec2i( p,-p + 10 ),new Tile( Vec2i( p,-p + 10 ),1,*pSprite ) );
		}
		for ( int x = -25; x < -15; ++x )
		{
			mTiles.emplace( Vec2i( x,-5 ),new Tile( Vec2i( x,-5 ),1,*pSprite ) );
		}
	}
	~Map();
	bool setTile( const Vec2i& pos,const int id = 0 );
	int getContens( const Vec2i& pos );
	bool Collision( const Vec2f& pos,const RecF& rec ) const;
	Surface* TileSprite() const;
private:
	std::map<Vec2i,Tile*> mTiles;
	Surface* pSprite = new Surface( L"../Engine/Sprite/GrassTile.bmp" );
};
