#include "WorldObject.h"

WorldObject::WorldObject( std::vector<Vec2i>& layout,std::optional<Player*> player )
	:
	cam( { 0,0 } ),
	map( layout )
{
	if ( player )
	{
		pl = *player;
	}
	else
	{
		pl = new Player( { 0,0 } );
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
		vEny.emplace_back( Enemy( { 0,0 } ) );
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
