#pragma once
#include "Graphics.h"
#include "Map.h"
#include "Player.h"
#include "SpriteCodex.h"

class Camara
{
public:
	Camara( const Vec2f& cPos,Map& map,Player& Pl );
	void Move( const Vec2f& dir );
	void Update( float dt );
	void Draw( Graphics& gfx ) const;
private:
	Vec2f cPos;
	Vec2f cVel = { 0.0f,0.0f };
	Map& map;
	Player& Pl;
	SpriteCodex sc;
};