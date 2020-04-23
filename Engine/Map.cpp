#include "Map.h"
#include <assert.h>

Tile::Tile( const Vec2i& tPos,const int& Tdim )
	:
	tPos( tPos ),
	pTileDimantion( &Tdim ),
	TileHB( RecI( tPos.x* Tdim,tPos.x* Tdim + Tdim,tPos.y* Tdim,tPos.y* Tdim + Tdim ) )
{
}

void Tile::Draw( const Vec2i& scrPos,Graphics& gfx ) const
{
	gfx.DrawRecDimClip( ( tPos * *pTileDimantion ) - scrPos,*pTileDimantion - 1,*pTileDimantion - 1,Colors::Green );
}

RecI Tile::TileHitBox() const
{
	return TileHB;
}

Map::Map()
{
	for ( int x = 2; x < 20; ++x )
	{
		mTiles.emplace( Vec2i( x,0 ),new Tile( Vec2i( x,0 ),TileDimantion ) );
	}
	mTiles.emplace( Vec2i( 0,1 ),new Tile( Vec2i( 0,1 ),TileDimantion ) );
	mTiles.emplace( Vec2i( -1,-1 ),new Tile( Vec2i( -1,-1 ),TileDimantion ) );
	mTiles.emplace( Vec2i( -2,-2 ),new Tile( Vec2i( -2,-2 ),TileDimantion ) );
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

bool Map::Collishion( const Vec2i& other,const RecF& rec ) const
{
	// check if target exists
	for ( int x = -1; x <= 1; ++x )
	{
		if ( mTiles.contains( other + Vec2i( x,0 ) ) )
		{
			if ( mTiles.find( other + Vec2i( x,0 ) )->second->TileHitBox().isOverlappingWith( rec ) )
			{
				return true;
			}
		}
	}
	return false;
}

int Map::getTileDimantion() const
{
	return TileDimantion;
}
