/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once
#include "ChiliWin.h"
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "Vec2.h"
#include "Rec.h"
#include "Surface.h"

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( int x,int y,Color c );
	Color getPixel( int x,int y );
	void DrawRec( int x0,int y0,int x1,int y1,Color c );
	void DrawRecDim( const Vec2i& pos,int width,int height,Color c )
	{
		DrawRec( pos.x,pos.y,pos.x + width,pos.y + height,c );
	}
	void DrawRecDimClip( Vec2i pos,int width,int height,Color c );
	void DrawRecOutline( const RecI& src,int thikness,Color c );
	void DrawOutline( const Vec2i& pos,const int& width,const int& height,const int& thikness,Color c )
	{
		DrawRecOutline( RecI( pos.x,pos.x + width,pos.y,pos.y + height ),thikness,c );
	}
	template<typename E>
	void DrawSprite( Vec2i pos,const Surface& s,bool mirrow,E effect )
	{
		DrawSprite( pos,{ 0,s.getWidth(),0,s.getHeight() },s,mirrow,effect );
	}
	template<typename E>
	void DrawSprite( Vec2i pos,RecI srcRect,const Surface& s,bool mirrow,E effect )
	{
		DrawSprite( pos,srcRect,Screen,s,mirrow,effect );
	}
	template<typename E>
	void DrawSprite( Vec2i pos,RecI srcRect,const RecI& clip,const Surface& s,bool mirrow,E effect )
	{
		if ( pos.x < clip.left )
		{
			srcRect.left += clip.left - pos.x;
			pos.x = clip.left;
		}
		else if ( pos.x + srcRect.getWidth() >= clip.right )
		{
			srcRect.right -= pos.x + srcRect.getWidth() - clip.right;
		}
		if ( pos.y < clip.top )
		{
			srcRect.top -= pos.y - clip.top;
			pos.y = clip.top;
		}
		else if ( pos.y + srcRect.getHeight() >= clip.bottem )
		{
			srcRect.bottem -= pos.y + srcRect.getHeight() - clip.bottem;
		}
		if ( !mirrow )
		{
			for ( int sy = srcRect.top; sy < srcRect.bottem; ++sy )
			{
				for ( int sx = srcRect.left; sx < srcRect.right; ++sx )
				{
					effect(
						s.GetPixel( sx,sy ),
						pos.x + sx - srcRect.left,
						pos.y + sy - srcRect.top,
						*this
					);
				}
			}
		}
		else
		{
			const int offset = srcRect.left + srcRect.right - 1;
			for ( int sy = srcRect.top; sy < srcRect.bottem; ++sy )
			{
				for ( int sx = srcRect.left; sx < srcRect.right; ++sx )
				{
					effect(
						s.GetPixel( offset - sx,sy ),
						pos.x + sx - srcRect.left,
						pos.y + sy - srcRect.top,
						*this
					);
				}
			}
		}
	}
	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
	Rec_<int> Screen = { 0,ScreenWidth,0,ScreenHeight };
};

#include "SpriteEffect.h"

#ifndef GOD_GRAPHICS
extern template
void Graphics::DrawSprite<SpriteEffect::Copy>( Vec2i pos,RecI srcRect,const RecI& clip,const Surface& s,bool mirrow,SpriteEffect::Copy );
extern template
void Graphics::DrawSprite<SpriteEffect::Chroma>( Vec2i pos,RecI srcRect,const RecI& clip,const Surface& s,bool mirrow,SpriteEffect::Chroma );
extern template
void Graphics::DrawSprite<SpriteEffect::Substitution>( Vec2i pos,RecI srcRect,const RecI& clip,const Surface& s,bool mirrow,SpriteEffect::Substitution );
#endif // !GOD_GRAPHICS 
