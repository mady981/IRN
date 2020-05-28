#include "WorldObject.h"

WorldObject::WorldObject()
	:
	pl( { 0,0 },map ),
	cam( { 0,0 },pl )
{}

void WorldObject::Tick( float dt )
{
	cam.Update( dt );
	pl.Tick( dt );
	for ( auto& e : vEny )
	{
		e.Tick( dt );
		e.AI( pl );
	}
}

void WorldObject::HandleImputs( Keyboard& kbd )
{
	pl.HandleImputs( kbd );
	cam.HandleImputs( kbd );
}

void WorldObject::Draw( Graphics& gfx ) const
{
	const auto cpos = cam.cPos_get();
	map.Draw( cpos,gfx );
	pl.Draw( cpos,gfx );
	for ( auto& e : vEny )
	{
		e.Draw( cpos,gfx );
	}
}
