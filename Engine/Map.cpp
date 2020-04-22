#include "Map.h"
#include <assert.h>

void Tile::Draw( const Vec2i& scrPos,Graphics& gfx )
{
	gfx.DrawRecDimClip( ( tPos * *TileDimantion ) - scrPos,*TileDimantion - 1,*TileDimantion - 1,Colors::Green );
}

std::map<Vec2i,Tile*,customless> Map::getMap() const
{
	return mTiles;
}

void Map::Draw( const Vec2i& scrPos,Graphics& gfx )
{
	for ( auto t : mTiles )
	{
		t.second->Draw( scrPos,gfx );
	}
}
