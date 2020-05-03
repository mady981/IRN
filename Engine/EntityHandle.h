#pragma once
#include <vector>
#include "Enemy.h"
#include "Map.h"

class EntityHandle
{
public:
	EntityHandle();
	~EntityHandle();
	void SpawnEnemy( const Vec2f& spawnPos,Map& map );
	void TickEntitys( const float& dt );
public:
	std::vector<Enemy*> Enemys() const;
private:
	std::vector<Enemy*> vEnemys;
};