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
				pos.x * ( 2 * pSprite.getWidth() ),
				pos.y * pSprite.getHeight(),
				pos.y * ( 2 * pSprite.getHeight() )
			);
		}
		const Vec2i pos;
		const int id;
		const Surface& pSprite;
	};
public:
	Map()
	{
		//mTiles.emplace( Vec2i( 0,0 ),new Tile( Vec2i( 0,0 ),1 ) );
		//mTiles.emplace( Vec2i( 1,0 ),new Tile( Vec2i( 1,0 ),1 ) );
		//mTiles.emplace( Vec2i( 2,1 ),new Tile( Vec2i( 2,1 ),1 ) );
		//mTiles.emplace( Vec2i( -1,-1 ),new Tile( Vec2i( -1,-1 ),1 ) );
		for ( int x = 0; x < 100; ++x )
		{
			mTiles.emplace( Vec2i( x,0 ),new Tile( Vec2i( x,0 ),1,*pSprite ) );
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
