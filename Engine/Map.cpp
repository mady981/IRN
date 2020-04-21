#include "Map.h"

Map::Tile::Tile( const Vec2i& pos,int blockid )
	:
	pos( pos ),
	blockid( blockid )
{
}

void Map::Tile::Draw( Graphics& gfx ) const
{
	gfx.DrawRecDimClip( pos,Map::BlockDimantion,Map::BlockDimantion,Color( blockid * 255,255,0 ) );
}

Map::Map()
{
	for ( int y = 0; y < 2; ++y )
	{
		for ( int x = 0; x < 100; ++x )
		{
			pMap.insert( { Vec2i( x,y ),new Tile( Vec2i( x,y ),y ) } );
		}
	}
}

void Map::Render( const Vec2i& Plpos,Graphics& gfx )
{
	for ( int y = Plpos.y - ( ( gfx.ScreenHeight / 2 ) / BlockDimantion ); y < Plpos.y + ( ( gfx.ScreenHeight / 2 ) / BlockDimantion ); ++y )
	{
		for ( int x = Plpos.y - ( ( gfx.ScreenWidth / 2 ) / BlockDimantion ); x < Plpos.y + ( ( gfx.ScreenWidth / 2 ) / BlockDimantion ); ++x )
		{
			rtiles.insert( { ( y * ChunkDimantion + x ),pMap.find( Vec2i( x,y ) )->second } );
		}
	}
}

void Map::Draw( Graphics& gfx )
{
	for ( int t = 0; t < rtiles.size(); ++t )
	{
		rtiles[t]->Draw( gfx );
	}
}
