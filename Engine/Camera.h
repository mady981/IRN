#pragma once
#include "Graphics.h"
#include "Keyboard.h"

class Camera
{
public:
	Camera( const Vec2f& cPos );
	void BindToPlayer( const Vec2f& PlayerPos );
	void HandleImputs( Keyboard& kbd,class WorldObject& world );
	void Move( const Vec2f& dir );
	void Update( float dt );
	Vec2f cPos_get() const;
private:
	Vec2f cPos;
	Vec2f cVel = { 0.0f,0.0f };
	const float FreeCamMoveSpeed = 10;
	bool FreeCam = false;
};