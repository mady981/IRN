#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "Rec.h"
#include "Vec2.h"
#include "FrameTimer.h"
#include <vector>

class Animation
{
public:
	Animation( int x,int y,int width,int height,float holdtime,int animations,const Surface& sprite,Color chroma = Colors::Magenta );
	void Update( float dt );
	void Draw( const Vec2i& pos,Graphics& gfx ) const;
private:
	void Advance();
private:
	Color chroma;
	const Surface& sprite;
	std::vector<RecI> frame;
	float HoldTime;
	float CurrTime = 0;
	int CurrAnimation = 0;
};