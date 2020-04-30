#pragma once
#include "Graphics.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"

class Camara
{
public:
	Camara( const Vec2f& cPos,Map& map,Player& Pl,Enemy& eny );
	void BindToPlayer( const Vec2f& PlayerPos );
	void Move( const Vec2f& dir );
	void Update( float dt );
	void Draw( Graphics& gfx ) const;
private:
	Vec2f cPos;
	Vec2f cVel = { 0.0f,0.0f };
	Map& map;
	Player& Pl;
	Enemy& eny;
};