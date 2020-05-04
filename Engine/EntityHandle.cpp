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

void EntityHandle::HandleEntitys( const float& dt,Entity& target )
{
	for ( auto e : vEnemys )
	{
		e->Tick( dt );
		e->AI( target );
	}
}

std::vector<Enemy*> EntityHandle::Enemys() const
{
	return vEnemys;
}
