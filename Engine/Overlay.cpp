#include "Overlay.h"

Overlay::Overlay( Graphics& gfx )
	:
	gfx( gfx )
{
}

void Overlay::DrawHealBar( const float& hp,const int& maxhp ) const
{
	gfx.DrawRecDim( HPBarPos, int( hp ),HPBarHeight,HPColor );
	gfx.DrawOutline( HPBarPos,maxhp,HPBarHeight,2,Colors::LightGray );
}
