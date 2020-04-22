#pragma once
#include "Graphics.h"
#include <map>

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
	Tile( const Vec2i& tPos,const int& Tdim )
		:
		tPos( tPos ),
		TileDimantion( &Tdim )
	{}
	void Draw( const Vec2i& scrPos,Graphics& gfx ) const;
	RecI TileHitBox() const;
private:
	const Vec2i tPos;
	const int* TileDimantion;
};

class Map
{
public:
	Map()
	{
		for ( int x = 0; x < 20; ++x )
		{
			mTiles.emplace( Vec2i( x,0 ),new Tile( Vec2i( x,0 ),TileDimantion ) );
		}
		mTiles.emplace( Vec2i( 0,1 ),new Tile( Vec2i( 0,1 ),TileDimantion ) );
		mTiles.emplace( Vec2i( -1,-1 ),new Tile( Vec2i( -1,-1 ),TileDimantion ) );
	}
	std::map<Vec2i,Tile*,customless> getMap() const;
	void Draw( const Vec2i& scrPos,Graphics& gfx ) const;
	int getTileDimantion() const;
private:
	std::map<Vec2i,Tile*,customless> mTiles;
	static constexpr int TileDimantion = 16;
};
