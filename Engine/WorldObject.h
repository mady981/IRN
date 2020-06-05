#pragma once
#include "Graphics.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Camera.h"
#include <vector>
#include <string>

class WorldObject
{
public:
	WorldObject( std::vector<Vec2i>& layout,Player* player );
	~WorldObject();
	void Tick( float dt );
	void HandleImputs( Keyboard& kbd );
	void Draw( Graphics& gfx ) const;
	void DeletePlayer();
	Player* getPl();
	Map* getMap();
private:
	Player* pl;
	std::vector<Enemy> vEny;
	Map map;
	Camera cam;
};