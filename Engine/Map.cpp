#include "Map.h"
#include "Text.h"

void Map::GenerateChunk( const Vec2_<int>& chunk_pos )
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
			for ( int sy = 0; sy < 16; ++sy )
			{
				int sx = x < 0 ? 15 : 0;
				if ( c->second.tiles.data()[sy * ChunkDimantion + sx].getId() != -1 )
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
		chunks.find( chunk_pos )->second.tiles[ipos.get1D( ChunkDimantion )].Init( p + chunk_pos * ChunkDimantion,1 );
	}
	for ( auto& fill : filler )
	{
		if ( reverse )
		{
			fill.x = 15 - fill.x;
		}
		chunks.find( chunk_pos )->second.tiles[fill.get1D( ChunkDimantion )].Init( fill + chunk_pos * ChunkDimantion,1 );
	}
}

bool Map::setTile( const Vec2i& pos,const int id )
{
	const auto i = chunks.find( pos / ChunkDimantion );
	if ( i != chunks.end() )
	{
		Vec2_<int> chunk_tile_pos = Vec2_{ pos.x - ( pos.x / ChunkDimantion ),pos.y - ( pos.y / ChunkDimantion ) }.getAbs();
		i->second.tiles.data()[chunk_tile_pos.get1D( ChunkDimantion )].setId( id );
		return true;
	}
	return false;
}

void Map::setTile_GenChunk( const Vec2i& pos,const int id )
{
	auto i = chunks.find( pos / ChunkDimantion );
	if ( i == chunks.end() )
	{
		chunks.emplace( pos / ChunkDimantion,Chunk( pos / ChunkDimantion ) );
		i = chunks.find( pos / ChunkDimantion );
	}
	Vec2_<int> chunk_tile_pos = Vec2_{ pos.x - ( pos.x / ChunkDimantion ),pos.y - ( pos.y / ChunkDimantion ) }.getAbs();
	i->second.tiles.data()[chunk_tile_pos.get1D( ChunkDimantion )].setId( id );
}

int Map::getContens( const Vec2i& pos ) const
{
	const auto i = chunks.find( ( Vec2_<float>( pos ) / (float)ChunkDimantion ).Castfloat2int() );
	if ( i != chunks.end() )
	{
		Vec2_<int> chunk_tile_pos = Vec2_{ pos.x - ( pos.x / ChunkDimantion ) * ChunkDimantion,pos.y - ( pos.y / ChunkDimantion ) * ChunkDimantion }.getAbs();
		return i->second.tiles.data()[chunk_tile_pos.get1D( ChunkDimantion )].getId();
	}
	return -1;
}

void Map::Draw( const Vec2f& cPos,Graphics& gfx ) const
{
	int HalfChunkRenderWidth = 2;
	int HalfChunkRenderHeight = 2;
	for ( int cy = -HalfChunkRenderHeight; cy <= HalfChunkRenderHeight; ++cy )
	{
		for ( int cx = -HalfChunkRenderWidth; cx <= HalfChunkRenderWidth; ++cx )
		{
			Vec2_<int> chunkPos = ( ( cPos / (float)ChunkDimantion + Vec2_{ (float)cx,(float)cy } ) ).Castfloat2int();
			const auto i = chunks.find( chunkPos );
			if ( i != chunks.end() /*&& i->second.isActive*/ )
			{
				//Vec2_<int> chunk_tile_pos = Vec2_{ mx - ( mx / ChunkDimantion ) * ChunkDimantion,my - ( my / ChunkDimantion ) * ChunkDimantion }.getAbs();
				////Vec2_<int> tilepos = { mx,my };
				//const auto d = i->second.tiles.data()[chunk_tile_pos.get1D( ChunkDimantion )];
				//if ( d.getId() != -1 )
				//{
				//	d.Draw( cPos,gfx );
				//}
				for ( const auto& t : i->second.tiles )
				{
					if ( t.getId() != -1 )
					{
						t.Draw( cPos,gfx );
					}
				}
			}
		}
	}
	if ( ShowTileHitBox )
	{
		for ( const auto& c : chunks )
		{
			for ( const auto& t : c.second.tiles )
			{
				if ( t.getId() != -1 )
				{
					const Vec2f offset = Vec2f( t.getPos() ) - cPos;
					gfx.DrawOutline(
						Vec2_{
							int( offset.x * Map::Dimantion() + gfx.ScreenWidth / 2 ),
							int( offset.y * Map::Dimantion() + gfx.ScreenHeight / 2 )
						},
						16,16,0,Colors::Green
					);
				}
			}
		}
	}
}

bool Map::CollidingWith( const Vec2f& pos,const RecF& rec ) const
{
	for ( int y = -1; y <= 1; ++y )
	{
		for ( int x = -1; x <= 1; ++x )
		{
			Vec2_<int> chunkPos = Vec2_<float>{ ( pos + Vec2_{ (float)x,(float)y } ) / ChunkDimantion }.Castfloat2int();
			const auto i = chunks.find( chunkPos );
			if ( i != chunks.end() )
			{
				Vec2_<int> chunk_tile_pos = Vec2_{ (int)pos.x - chunkPos.x * ChunkDimantion + x,(int)pos.y - chunkPos.y * ChunkDimantion + y }.getAbs();
				//Vec2_<int> tilepos = { (int)pos.x + x,(int)pos.y + y };
				const auto t = i->second.tiles.data()[chunk_tile_pos.get1D( ChunkDimantion )];
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

int Map::Dimantion()
{
	return ChunkDimantion;
}

Map::Chunk::Chunk( const Vec2_<int>& chunk_pos )
	:
	chunk_pos( chunk_pos ),
	tiles( 256 )
{
	std::generate( tiles.begin(),tiles.end(),[val = 0,chunk_pos]() mutable
	{
		Vec2i pos = Vec2i{ val % ChunkDimantion,val / ChunkDimantion } + chunk_pos * ChunkDimantion;
		++val;
		return Tile( pos,-1 );
	} );
}

Map::Chunk::Tile::Tile()
	:
	pos( 0,0 ),
	id( -1 )
{}

Map::Chunk::Tile::Tile( const Vec2i & pos,const int id )
	:
	pos( pos ),
	id( id )
{}

void Map::Chunk::Tile::Init( const Vec2i & _pos,const int _id )
{
	pos = _pos;
	id = _id;
}

RecI Map::Chunk::Tile::TileHitBox() const
{
	return Rec_<int>(
		pSprite->getRect().WithPosition( pos * Map::Dimantion() )
		);
}

void Map::Chunk::Tile::Draw( const Vec2f& cPos,Graphics& gfx ) const
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
	//Text::DrawNumber_( pos.x,
	//	{ int( offset.x * Map::Dimantion() + gfx.ScreenWidth / 2 ),
	//	int( offset.y * Map::Dimantion() + gfx.ScreenHeight / 2 ) },
	//	gfx
	//);
	//Text::DrawNumber_( pos.y,
	//	{ int( offset.x * Map::Dimantion() + gfx.ScreenWidth / 2 ),
	//	int( offset.y * Map::Dimantion() + gfx.ScreenHeight / 2 ) },
	//	gfx
	//);
}

int Map::Chunk::Tile::getId() const
{
	return id;
}

void Map::Chunk::Tile::setId( int _id )
{
	id = _id;
}

Vec2i Map::Chunk::Tile::getPos() const
{
	return pos;
}
