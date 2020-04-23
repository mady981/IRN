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
	Tile( const Vec2i& tPos,const int& Tdim );
	void Draw( const Vec2i& scrPos,Graphics& gfx ) const;
	RecI TileHitBox() const;
private:
	const RecI TileHB;
	const Vec2i tPos;
	const int* pTileDimantion;
};

class Map
{
public:
	Map();
	std::map<Vec2i,Tile*,customless> getMap() const;
	void Draw( const Vec2i& scrPos,Graphics& gfx ) const;
	bool Collishion( const Vec2i& other,const RecF& rec ) const;
	int getTileDimantion() const;
private:
	std::map<Vec2i,Tile*,customless> mTiles;
	static constexpr int TileDimantion = 16;
};
