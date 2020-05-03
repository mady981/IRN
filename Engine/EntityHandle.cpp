#include "EntityHandle.h"
#include <assert.h>

EntityHandle::EntityHandle()
{
}

EntityHandle::~EntityHandle()
{
	for ( auto e : vEnemys )
	{
		assert( e != nullptr );
		delete e;
	}
}

void EntityHandle::SpawnEnemy( const Vec2f& spawnPos,Map& map )
{
	if ( vEnemys.size() < vEnemys.max_size() )
	{
		vEnemys.emplace_back( new Enemy( spawnPos,map ) );
	}
}

void EntityHandle::TickEntitys( const float& dt )
{
	for ( auto e : vEnemys )
	{
		e->Tick( dt );
	}
}

std::vector<Enemy*> EntityHandle::Enemys() const
{
	return vEnemys;
}
