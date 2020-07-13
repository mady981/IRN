#include "WorldObject.h"

WorldObject::WorldObject( Player* player )
	:
	cam( { 0,0 } )
{
	for ( int i = -3; i <= 3; ++i ) { map.GenerateChunk( Vec2_{ i,0 } ); }
	//for ( int i = -32; i < 32; ++i ) { map.setTile_GenChunk( Vec2_{ i,0 },1 ); }
	if ( player )
	{
		pl = player;
	}
	else
	{
		pl = new Player( { 0.5f,0.0f } );
	}
}

WorldObject::~WorldObject()
{
}

void WorldObject::Tick( float dt )
{
	cam.Update( dt );
	pl->Tick( dt,*this );
	for ( auto& e : vEny )
	{
		e.Tick( dt,*this );
		e.AI( pl,*this );
	}
}

void WorldObject::HandleImputs( Keyboard& kbd )
{
	pl->HandleImputs( kbd,*this );
	cam.HandleImputs( kbd,*this );
	if ( kbd.KeyIsPressed( 'I' ) )
	{
		vEny.emplace_back( Enemy( { 0.5f,0.0f } ) );
	}
	if ( kbd.KeyIsPressed( 'B' ) )
	{
		map.setShowTileHitBox( true );
	}
	if ( kbd.KeyIsPressed( '0' ) )
	{
		map.setShowTileHitBox( false );
	}
}

void WorldObject::Draw( Graphics& gfx ) const
{
	const auto cpos = cam.cPos_get();
	map.Draw( cpos,gfx );
	pl->Draw( cpos,gfx );
	for ( auto& e : vEny )
	{
		e.Draw( cpos,gfx );
	}
}

void WorldObject::DeletePlayer()
{
	delete pl;
}

Player* WorldObject::getPl()
{
	return pl;
}

Map* WorldObject::getMap()
{
	return &map;
}
