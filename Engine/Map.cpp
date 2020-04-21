#include "Map.h"
#include <assert.h>

Map::Tile::Tile( const Vec2i& pos,int blockid )
	:
	pos( pos ),
	blockid( blockid )
{
}

void Map::Tile::Draw( Graphics& gfx ) const
{
	gfx.DrawRecDimClip( pos * BlockDimantion,Map::BlockDimantion - 1,Map::BlockDimantion - 1,Color( 0,255,0 ) );
}

Map::Map()
{
	for ( int y = 0; y < ChunkDimantion; ++y )
	{
		for ( int x = 0; x < ChunkDimantion; ++x )
		{
			pMap.insert( { Vec2i( x,y ),new Tile( Vec2i( x,y ),-1 ) } );
		}
	}
}

void Map::Render( const Vec2i& Plpos,Graphics& gfx )
{
	int t = 0;
	rtiles.clear();
	for ( int y = Plpos.y - ( ( gfx.ScreenHeight / 2 ) / BlockDimantion ); y < Plpos.y + ( ( gfx.ScreenHeight / 2 ) / BlockDimantion ); ++y )
	{
		for ( int x = Plpos.x - ( ( gfx.ScreenWidth / 2 ) / BlockDimantion ); x < Plpos.x + ( ( gfx.ScreenWidth / 2 ) / BlockDimantion ); ++x )
		{
			if ( pMap.contains( Vec2i( x,y ) ) )
			{
				rtiles.insert( { ( t ),pMap.find( Vec2i( x,y ) )->second } );
				++t;
			}
		}
	}
}

void Map::Draw( Graphics& gfx )
{
	for ( int t = 0; t < rtiles.size(); ++t )
	{
		rtiles.find( t )->second->Draw( gfx );
	}
}
