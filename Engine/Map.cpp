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

bool Map::Collision( const Vec2f& pos,const RecF& rec ) const
{
	if ( mTiles.contains( pos.getRound() ) )
	{
		return mTiles.find( pos.getRound() )->second->TileHitBox.isOverlappingWith( rec );
	}
	return false;
}
