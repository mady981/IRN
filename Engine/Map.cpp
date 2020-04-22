#include "Map.h"
#include <assert.h>

void Tile::Draw( const Vec2i& scrPos,Graphics& gfx ) const
{
	gfx.DrawRecDimClip( ( tPos * *TileDimantion ) - scrPos,*TileDimantion - 1,*TileDimantion - 1,Colors::Green );
}

RecI Tile::TileHitBox() const
{
	return RecI( tPos.x,tPos.x + *TileDimantion,tPos.y,tPos.y + *TileDimantion );
}

std::map<Vec2i,Tile*,customless> Map::getMap() const
{
	return mTiles;
}

void Map::Draw( const Vec2i& scrPos,Graphics& gfx ) const
{
	for ( auto t : mTiles )
	{
		t.second->Draw( scrPos,gfx );
	}
}

int Map::getTileDimantion() const
{
	return TileDimantion;
}
