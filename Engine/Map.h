#pragma once
#include "Graphics.h"
#include <map>
#include <vector>

struct customless
{
	bool operator()( const Vec2i& a,const Vec2i& b ) const
	{
		return a.y == b.y ? a.x < b.x : a.y < b.y;
	}
};

class Tile
{
public:
	Tile( const Vec2i& pos,const int id )
		:
		pos( pos ),
		id( id )
	{}
	const Vec2i pos;
	const int id;
	static constexpr int TileDimantion = 16;
	const RecI TileHitBox = RecI( pos.x,pos.x + TileDimantion,pos.y,pos.y + TileDimantion );
};

class Map
{
public:
	Map()
	{
		mTiles.emplace( Vec2i( 0,0 ),new Tile( Vec2i( 0,0 ),1 ) );
		mTiles.emplace( Vec2i( 1,0 ),new Tile( Vec2i( 1,0 ),1 ) );
		mTiles.emplace( Vec2i( 2,1 ),new Tile( Vec2i( 2,1 ),1 ) );
		mTiles.emplace( Vec2i( -1,-1 ),new Tile( Vec2i( -1,-1 ),1 ) );
	}
	bool setTile( const Vec2i& pos,const int id = 0 );
	int getContens( const Vec2i& pos );
	bool Collision( const Vec2f& pos,const RecF& rec ) const;
private:
	std::map<Vec2i,Tile*,customless> mTiles;
};
