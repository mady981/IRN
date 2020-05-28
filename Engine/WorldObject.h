#pragma once
#include "Graphics.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Camera.h"
#include <vector>

class WorldObject
{
public:
	WorldObject();
	void Tick( float dt );
	void HandleImputs( Keyboard& kbd );
	void Draw( Graphics& gfx ) const;
private:
	Player pl;
	std::vector<Enemy> vEny;
	Map map;
	Camera cam;
};