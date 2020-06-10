#include "Map.h"
#include <assert.h>

Map::~Map()
{
	//for ( auto& m : mTiles )
	//{
	//	delete m.second;
	//}
}

bool Map::setTile( const Vec2i& pos,const int id )
{
	if ( !mTiles.contains( pos ) )
	{
		if ( id == -1 )
		{
			//delete mTiles.find( pos )->second;
			mTiles.erase( pos );
			return true;
		}
		else
		{
			mTiles.emplace( pos,Tile( pos,id ) );
			return true;
		}
	}
	return false;
}

int Map::getContens( const Vec2i& pos ) const
{
	if ( mTiles.contains( pos ) )
	{
		return mTiles.find( pos )->second.id;
	}
	return -1;
}

void Map::Draw( const Vec2f& pos_c,Graphics& gfx ) const
{
	for ( int my = ( int )pos_c.y - HalfRenderHeight; my <= pos_c.y + HalfRenderHeight; ++my )
	{
		for ( int mx = ( int )pos_c.x - HalfRenderWidth; mx <= pos_c.x + HalfRenderWidth; ++mx )
		{
			auto contens = getContens( { mx,my } );
			if ( contens != -1 )
			{
				mTiles.find( Vec2_{ mx,my } )->second.Draw( pos_c,gfx );
			}
		}
	}
}

bool Map::CollidingWith( const Vec2f& pos,const RecF& rec ) const
{
	for ( int y = -1; y <= 1; ++y )
	{
		for ( int x = -1; x <= 1; ++x )
		{
			if ( mTiles.contains( pos - Vec2i( x,y ) ) )
			{
				if ( mTiles.find( pos - Vec2i( x,y ) )->second.TileHitBox().isOverlappingWith( rec ) )
				{
					return true;
				}
			}
		}
	}
	return false;
}

int Map::Dimantion()
{
	return SurfaceCodex::Retrieve( L"GrassTile.bmp" )->getWidth(); 
}
