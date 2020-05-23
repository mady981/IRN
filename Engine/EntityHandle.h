#pragma once
#include <vector>
#include "Enemy.h"
#include "Map.h"

class EntityHandle
{
public:
	EntityHandle() = default;
	~EntityHandle();
	void SpawnEnemy( const Vec2f& spawnPos,Map& map );
	void HandleEntitys( const float& dt,Entity& target );
public:
	std::vector<Enemy*> Enemys() const;
private:
	std::vector<Enemy*> vEnemys;
};