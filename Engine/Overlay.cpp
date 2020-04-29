#include "Overlay.h"

Overlay::Overlay( Graphics& gfx )
	:
	gfx( gfx )
{
}

void Overlay::DrawHealBar( const float& hp ) const
{
	gfx.DrawRecDim( HPBarPos, int( hp * 1.5f ),HPBarHeight,HPColor );
	gfx.DrawOutline( HPBarPos,HPBarWidht,HPBarHeight,2,Colors::LightGray );
}
