#pragma once
#include "Surface.h"

class SpriteCodex
{
public:
	SpriteCodex() = default;
	~SpriteCodex()
	{
		delete pPlayer;
		delete pGrassTile;
	}
	Surface& PLayerSprite() const
	{
		return *pPlayer;
	}
	Surface& GrassTileSprite() const
	{
		return *pGrassTile;
	}
private:
	Surface* pPlayer = new Surface( L"../Engine/Sprite/Player.bmp" );
	Surface* pGrassTile = new Surface( L"../Engine/Sprite/GrassTile.bmp" );
};