#pragma once
#include "Surface.h"
#include <string>
#include <vector>

class SurfaceCodex
{
public:
	class Entry
	{
	public:
		Entry( const std::wstring& key,Surface* pSurface )
			:
			key( key ),
			pSurface( pSurface )
		{}
		std::wstring key;
		Surface* pSurface;
	};
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
			delete e.pSurface;
		}
	}
	Surface* _Retrieve( const std::wstring& key )
	{
		const auto i = std::find_if( entrys.begin(),entrys.end(),
			[&key]( const Entry& e )
			{
				return key == e.key;
			}
		);
		// not exist
		if ( i == entrys.end() )
		{
			auto p = new Surface( L"../Engine/Sprite/" + key );
			entrys.emplace_back( key,p );
			return p;
		}
		else
		{
			return i->pSurface;
		}
	}
	void _Purge()
	{
		for ( auto& e : entrys )
		{
			delete e.pSurface;
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
	std::vector<Entry> entrys;
};