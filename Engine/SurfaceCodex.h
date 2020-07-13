#pragma once
#include "Surface.h"
#include <string>
#include <vector>
#include <map>
#include <cassert>

class SurfaceCodex
{
public:
	static Surface* Retrieve( const std::wstring& key )
	{
		return get()._Retrieve( key );
	}
	static void* Purge()
	{
		get()._Purge();
	}
private:
	SurfaceCodex() = default;
	~SurfaceCodex()
	{
		for ( auto& e : entrys )
		{
			delete e.second;
		}
	}
	Surface* _Retrieve( const std::wstring& key )
	{
		const auto i = entrys.find( key );
		// not exist
		if ( i == entrys.end() )
		{
			Surface* p = nullptr;
			assert( key.ends_with( L".bmp" ) );
			p = new Surface( key );
			entrys.emplace( key,p );
			return p;
		}
		else
		{
			return i->second;
		}
	}
	void _Purge()
	{
		for ( auto& e : entrys )
		{
			delete e.second;
		}
		entrys.clear();
	}
public:
	static SurfaceCodex& get()
	{
		static SurfaceCodex codex;
		return codex;
	}
private:
	std::map<std::wstring,Surface*> entrys;
};