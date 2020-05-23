#include "Map.h"
#include <assert.h>

bool Map::setTile( const Vec2i& pos,const int id )
{
	if ( !mTiles.contains( pos ) )
	{
		if ( id == -1 )
		{
			delete mTiles.find( pos )->second;
			mTiles.erase( pos );
			return true;
		}
		else
		{
			mTiles.emplace( pos,new Tile( pos,id ) );
			return true;
		}
	}
	return false;
}

int Map::getContens( const Vec2i& pos )
{
	if ( mTiles.contains( pos ) )
	{
		return mTiles.find( pos )->second->id;
	}
	return -1;
}

bool Map::CollidingWith( const Vec2f& pos,const RecF& rec ) const
{
	for ( int y = -1; y <= 1; ++y )
	{
		for ( int x = -1; x <= 1; ++x )
		{
			if ( mTiles.contains( pos - Vec2i( x,y ) ) )
			{
				if ( mTiles.find( pos - Vec2i( x,y ) )->second->TileHitBox().isOverlappingWith( rec ) )
				{
					return true;
				}
			}
		}
	}
	return false;
}

const Surface* Map::TileSprite() const
{
	return mTiles.begin()->second->pSprite;
}

std::map<Vec2i,Map::Tile*> Map::Tiles() const
{
	return mTiles;
}
