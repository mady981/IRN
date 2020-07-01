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
			Tile()
				:
				pos( 0,0 ),
				id( -1 )
			{}
			Tile( const Vec2i& pos,const int id = -1 )
				:
				pos( pos ),
				id( id )
			{}
			void Init( const Vec2i& _pos,const int _id )
			{
				pos = _pos;
				id = _id;
			}
			RecI TileHitBox() const
			{
				return Rec_<int>(
					pSprite->getRect().WithPosition( pos * Map::Dimantion() )
					);
			}
			void Draw( const Vec2f& cPos,Graphics& gfx ) const
			{
				const Vec2f offset = Vec2f( pos ) - cPos;
				gfx.DrawSprite(
					Vec2_{
						int( offset.x * Map::Dimantion() + gfx.ScreenWidth / 2 ),
						int( offset.y * Map::Dimantion() + gfx.ScreenHeight / 2 ) },
						*pSprite,
						false,
						SpriteEffect::Copy{}
				);
			}
			int getId() const
			{
				return id;
			}
			int setId( int _id )
			{
				id = _id;
			}
		private:
			Vec2i pos;
			int id;
			const Surface* pSprite = SurfaceCodex::Retrieve( L"GrassTile.bmp" );
		};
	public:
		Chunk( const Vec2_<int>& chunk_pos )
			:
			chunk_pos( chunk_pos ),
			tile( 256 )
		{
			for ( int t = 0; t < 256; ++t )
			{
				tile.emplace( tile.begin() + t,Tile( Vec2_<int>{ t % ChunkDimantion,t / ChunkDimantion } + chunk_pos * ChunkDimantion,-1 ) );
			}
		}
		std::vector<Tile> tile;
		Vec2_<int> chunk_pos;
		bool isActive = false;
	};
public:
	void GenerateChunk( const Vec2_<int>& chunk_pos )
	{
		bool reverse = false;
		Vec2_<int> start_pos;
		std::map<Vec2_<int>,Chunk>::iterator c;
		for ( int x = -1; x <= 1; x += 2 )
		{
			bool brk = false;
			Vec2_ tc = chunk_pos + Vec2_{ x,0 };
			c = chunks.find( tc );
			if ( c != chunks.end() )
			{
				rngpos = false;
				for ( int sy = 0; sy < 16; ++sy )
				{
					int sx = x < 0 ? 15 : 0;
					if ( c->second.tile.data()[sy * ChunkDimantion + sx].getId() != -1 )
					{
						if ( x > 0 )
						{
							reverse = true;
						}
						start_pos = { -1,sy };
						brk = true;
						break;
					}
				}
			}
			if ( brk )
			{
				break;
			}
		}
		if ( c == chunks.end() )
		{
			std::uniform_int_distribution<int> syDist( 0,15 );
			start_pos = { -1,syDist( rng ) };
			rngpos = true;
		}
		std::vector<Vec2_<int>> filler;
		chunks.emplace( chunk_pos,Chunk( chunk_pos ) );
		std::uniform_int_distribution<int> yDist( 0,15 );
		Vec2_<float> pos[16];
		for ( int x = 3; x < ChunkDimantion; x += 4 )
		{
			pos[x] = Vec2_<int>{ x,yDist( rng ) };
		}
		for ( int i = 0; i < 4; ++i )
		{
			Vec2_<int> dxy;
			if ( i == 0 )
			{
				dxy = pos[3] - start_pos;
			}
			else
			{
				dxy = pos[i * 4 + 3] - pos[i * 4 - 1];
			}
			float m = 0.0f;
			if ( dxy.y != 0 )
			{
				m = (float)dxy.y / (float)dxy.x;
			}
			for ( int n = i * 4; n < dxy.x + i * 4; ++n )
			{
				Vec2_<float> refrence;
				if ( n == 0 )
				{
					refrence = start_pos;
				}
				else
				{
					refrence = pos[n - 1];
				}
				pos[n] = refrence + Vec2_{ 1.0f,m };
				for ( int f = 1; f < std::abs( (int)refrence.y - (int)pos[n].y ); ++f )
				{
					if ( m > 0 )
					{
						filler.emplace_back( Vec2_{ refrence.x,refrence.y + f } );
					}
					else
					{
						filler.emplace_back( Vec2_{ pos[n].x,pos[n].y + f } );
					}
				}
			}
		}
		for ( const auto& p : pos )
		{
			Vec2_<int> ipos = p;
			if ( reverse )
			{
				ipos.x = 15 - (int)p.x;
			}
			else
			{
				ipos = p;
			}
			chunks.find( chunk_pos )->second.tile[ipos.get1D( ChunkDimantion )].Init( p + chunk_pos * ChunkDimantion,1 );
		}
		for ( auto& fill : filler )
		{
			if ( reverse )
			{
				fill.x = 15 - fill.x;
			}
			chunks.find( chunk_pos )->second.tile[fill.get1D( ChunkDimantion )].Init( fill + chunk_pos * ChunkDimantion,1 );
		}
		rev = reverse;
	}
	bool setTile( const Vec2i& pos,const int id = 0 )
	{
		const auto i = chunks.find( pos / ChunkDimantion );
		if ( i != chunks.end() )
		{
			Vec2_<int> chunk_tile_pos = Vec2_{ pos.x - ( pos.x / ChunkDimantion ),pos.y - ( pos.y / ChunkDimantion ) }.getAbs();
			i->second.tile.data()[chunk_tile_pos.get1D( ChunkDimantion )].setId( -1 );
			return true;
		}
		return false;
	}
	int getContens( const Vec2i& pos ) const
	{
		const auto i = chunks.find( ( Vec2_<float>( pos ) / (float)ChunkDimantion ).Castfloat2int() );
		if ( i != chunks.end() )
		{
			Vec2_<int> chunk_tile_pos = Vec2_{ pos.x - ( pos.x / ChunkDimantion ) * ChunkDimantion,pos.y - ( pos.y / ChunkDimantion ) * ChunkDimantion }.getAbs();
			return i->second.tile.data()[chunk_tile_pos.get1D( ChunkDimantion )].getId();
		}
		return -1;
	}
	void Draw( const Vec2f& cPos,Graphics& gfx ) const
	{
		for ( int my = (int)cPos.y - HalfRenderHeight; my <= (int)cPos.y + HalfRenderHeight; ++my )
		{
			for ( int mx = (int)cPos.x - HalfRenderWidth; mx <= (int)cPos.x + HalfRenderWidth; ++mx )
			{
				Vec2_<int> chunkPos = ( Vec2_{ (float)mx,(float)my } / (float)ChunkDimantion ).Castfloat2int();
				const auto i = chunks.find( chunkPos );
				if ( i != chunks.end() /*&& i->second.isActive*/ )
				{
					Vec2_<int> chunk_tile_pos = Vec2_{ mx - ( mx / ChunkDimantion ) * ChunkDimantion,my - ( my / ChunkDimantion ) * ChunkDimantion }.getAbs();
					//Vec2_<int> tilepos = { mx,my };
					const auto d = i->second.tile.data()[chunk_tile_pos.get1D(ChunkDimantion)];
					if ( d.getId() != -1 )
					{
						d.Draw( cPos,gfx );
					}
				}
			}
		}
	}
	bool CollidingWith( const Vec2f& pos,const RecF& rec ) const
	{
		for ( int y = -1; y <= 1; ++y )
		{
			for ( int x = -1; x <= 1; ++x )
			{
				Vec2_<int> chunkPos = Vec2_<float>{ ( pos + Vec2_{ (float)x,(float)y } ) / ChunkDimantion }.Castfloat2int();
				const auto i = chunks.find( chunkPos );
				if ( i != chunks.end() )
				{
					Vec2_<int> chunk_tile_pos = Vec2_{ (int)pos.x - ( (int)pos.x / ChunkDimantion ) * ChunkDimantion + x,(int)pos.y - ( (int)pos.y / ChunkDimantion ) * ChunkDimantion + y }.getAbs();
					//Vec2_<int> tilepos = { (int)pos.x + x,(int)pos.y + y };
					const auto t = i->second.tile.data()[chunk_tile_pos.get1D( ChunkDimantion )];
					if ( t.getId() != -1 )
					{
						if ( t.TileHitBox().isCollidingWith( rec ) )
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	static int Dimantion()
	{
		return ChunkDimantion;
	}
public:
	std::mt19937 rng = std::mt19937( std::random_device()( ) );
	static constexpr int ChunkDimantion = 16;
	std::map<Vec2_<int>,Chunk> chunks;
	bool rngpos = false;
	bool rev;
	const int HalfRenderHeight = Graphics::ScreenHeight / SurfaceCodex::Retrieve( L"GrassTile.bmp" )->getHeight() / 2 + 1;
	const int HalfRenderWidth = Graphics::ScreenWidth / SurfaceCodex::Retrieve( L"GrassTile.bmp" )->getWidth() / 2 + 1;
};