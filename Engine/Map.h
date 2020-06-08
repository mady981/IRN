#pragma once
#include "Graphics.h"
#include "SpriteEffect.h"
#include "SurfaceCodex.h"
#include <map>

class Map
{
private:
	class Tile
	{
	public:
		Tile( const Vec2i& pos,const int id )
			:
			pos( pos ),
			id( id )
		{}
		RecI TileHitBox() const
		{
			return RecI(
				pSprite->getRect<int>().WithPosition( pos * Dimantion() )
			);
		}
		void Draw( const Vec2f& cPos,Graphics& gfx )
		{
			const Vec2f offset = Vec2f( pos ) - cPos;
			gfx.DrawSprite(
				int( offset.x * Dimantion() + gfx.ScreenWidth / 2 ),
				int( offset.y * Dimantion() + gfx.ScreenHeight / 2 ),
				*pSprite,
				false,
				SpriteEffect::Copy{}
			);
		}
		const Vec2i pos;
		const int id;
		const Surface* pSprite = SurfaceCodex::Retrieve( L"GrassTile.bmp" );
	};
public:
	Map( std::vector<Vec2i>& layout )
	{
		for ( auto l : layout )
		{
			mTiles.emplace( l,new Tile( l,1 ) );
		}
	}
	~Map();
	bool setTile( const Vec2i& pos,const int id = 0 );
	int getContens( const Vec2i& pos ) const;
	void Draw( const Vec2f& pos_c,Graphics& gfx ) const;
	bool CollidingWith( const Vec2f& pos,const RecF& rec ) const;
	static int Dimantion();
private:
	std::map<Vec2i,Tile*> mTiles;
	const int HalfRenderHeight = Graphics::ScreenHeight / SurfaceCodex::Retrieve( L"GrassTile.bmp" )->getHeight() / 2 + 1;
	const int HalfRenderWidth = Graphics::ScreenWidth / SurfaceCodex::Retrieve( L"GrassTile.bmp" )->getWidth() / 2 + 1;
};
