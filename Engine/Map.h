#pragma once
#include "Graphics.h"
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
		const Vec2i pos;
		const int id;
		static constexpr int TileDimantion = 16;
		const RecI TileHitBox = RecI(
			pos.x * TileDimantion,
			pos.x * TileDimantion + TileDimantion,
			pos.y * TileDimantion,
			pos.y * TileDimantion + TileDimantion
		);
	};
public:
	Map()
	{
		//mTiles.emplace( Vec2i( 0,0 ),new Tile( Vec2i( 0,0 ),1 ) );
		//mTiles.emplace( Vec2i( 1,0 ),new Tile( Vec2i( 1,0 ),1 ) );
		//mTiles.emplace( Vec2i( 2,1 ),new Tile( Vec2i( 2,1 ),1 ) );
		//mTiles.emplace( Vec2i( -1,-1 ),new Tile( Vec2i( -1,-1 ),1 ) );
		for ( int p = 0; p < 100; ++p )
		{
			mTiles.emplace( Vec2i( p,p ),new Tile( Vec2i( p,p ),1 ) );
		}
	}
	~Map();
	bool setTile( const Vec2i& pos,const int id = 0 );
	int getContens( const Vec2i& pos );
	bool Collision( const Vec2f& pos,const RecF& rec ) const;
	int getTileDim() const;
private:
	std::map<Vec2i,Tile*> mTiles;
};
