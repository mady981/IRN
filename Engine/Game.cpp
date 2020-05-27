/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 planetChili.net <http://www.planetchili.net>							  *
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
#include "MainWindow.h"
#include "Game.h"

#include <iostream>
#include <sstream>

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
    pl( { 0,0 },map ),
    cam( { 0,0 },pl ),
    ol( gfx )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
#ifdef NDEBUG
    const auto dt = ft.Duration();
#else
    const auto dt = 1.0f / 60.0f;
#endif // NDEBUG

    //player
    pl.HandleImtputs( wnd.kbd );
    pl.Tick( dt );

    //Camera
    cam.HandelImputs( wnd.kbd );
    //FreeCam controlls
    cam.Update( dt );

    //Enemy
    for ( auto& e : vEny )
    {
        e.AI( pl );
        e.Tick( dt );
    }

    /*------Test Code Begin---------------------*/
    if ( wnd.kbd.KeyIsPressed( 'I' ) && !ispresst )
    {
        vEny.emplace_back( Enemy( { 0,0 },map ) );
        ispresst = true;
    }
    const Keyboard::Event e = wnd.kbd.ReadKey();
    if ( e.IsRelease() )
    {
        ispresst = false;
    }
    /*------Test Code End---------------------*/
}

void Game::ComposeFrame()
{
    gfx.PutPixel( gfx.ScreenWidth / 2,gfx.ScreenHeight / 2,Colors::Blue );
    map.Draw( cam.cPos_get(),gfx );
    pl.Draw( cam.cPos_get(),gfx );
    for ( const auto& e : vEny )
    {
        e.Draw( cam.cPos_get(),gfx );
    }
    ol.DrawHealBar( pl.HitPoints(),( int )pl.MaxHitPoints() );
    text.DrawText( "IRN",gfx.ScreenWidth / 2 - ( text.getGlythWidth() * 3 ) / 2,10,gfx );
}
