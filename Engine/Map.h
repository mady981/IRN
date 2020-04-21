#pragma once
#include "Graphics.h"
#include <map>

class Map
{
private:
	class Tile
	{
	public:
		Tile( const Vec2i& pos,int blockid );
		void Draw( Graphics& gfx ) const;
	private:
		Vec2i pos;
		int blockid;
	};
public:
	Map();
	void Render( const Vec2i& Plpos,Graphics& gfx );
	void Draw( Graphics& gfx );
public:
	static constexpr int ChunkDimantion = 16;
	static constexpr int BlockDimantion = 16;
private:
	struct customless
	{
		bool operator()( const Vec2i& a,const Vec2i& b ) const
		{
			return ( a.y * Map::ChunkDimantion + a.x ) < ( b.y * Map::ChunkDimantion + b.x );
		}
	};
	std::map<Vec2i,Tile*,customless> pMap;
	std::map<int,Tile*> rtiles;
};
