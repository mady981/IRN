#pragma once
#include "Graphics.h"
#include "SpriteEffect.h"
#include "SurfaceCodex.h"
#include <map>
#include "Vec2.h"
#include <random>

class Map
{
private:
	class Chunk
	{
	public:
		class Tile
		{
		public:
			Tile();
			Tile( const Vec2i& pos,const int id = -1 );
			void Init( const Vec2i& _pos,const int _id );
			RecI TileHitBox() const;
			void Draw( const Vec2f& cPos,Graphics& gfx ) const;
			int getId() const;
			void setId( int _id );
			Vec2i getPos() const;
		private:
			Vec2i pos;
			int id;
			const Surface* pSprite = SurfaceCodex::Retrieve( L"GrassTile.bmp" );
		};
	public:
		Chunk( const Vec2_<int>& chunk_pos );
		std::vector<Tile> tiles;
		Vec2_<int> chunk_pos;
		bool isActive = false;
	};
public:
	void GenerateChunk( const Vec2_<int>& chunk_pos );
	bool setTile( const Vec2i& pos,const int id );
	void setTile_GenChunk( const Vec2i& pos,const int id );
	int getContens( const Vec2i& pos ) const;
	void Draw( const Vec2f& cPos,Graphics& gfx ) const;
	bool CollidingWith( const Vec2f& pos,const RecF& rec ) const;
	static int Dimantion();
	void setShowTileHitBox( bool in )
	{
		ShowTileHitBox = in;
		//ShowTileHitBox ? ShowTileHitBox = false : ShowTileHitBox = true;
	}
public:
	std::mt19937 rng = std::mt19937( std::random_device()( ) );
	static constexpr int ChunkDimantion = 16;
	std::map<Vec2_<int>,Chunk> chunks;
	const int HalfRenderHeight = Graphics::ScreenHeight / SurfaceCodex::Retrieve( L"GrassTile.bmp" )->getHeight() / 2 + 1;
	const int HalfRenderWidth = Graphics::ScreenWidth / SurfaceCodex::Retrieve( L"GrassTile.bmp" )->getWidth() / 2 + 1;
	bool ShowTileHitBox = false;
};