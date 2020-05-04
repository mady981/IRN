#pragma once
#include "Graphics.h"
#include "Map.h"
#include "Player.h"
#include "EntityHandle.h"

class Camara
{
public:
	Camara( const Vec2f& cPos,Map& map,Player& Pl,EntityHandle& eh );
	void BindToPlayer( const Vec2f& PlayerPos );
	void HandelImputs( Keyboard& kbd );
	void Move( const Vec2f& dir );
	void Update( float dt );
	void Draw( Graphics& gfx ) const;
private:
	Vec2f cPos;
	Vec2f cVel = { 0.0f,0.0f };
	const float FreeCamMoveSpeed = 10;
	bool FreeCam = false;
private:
	Map& map;
	Player& Pl;
	EntityHandle& eh;
};