/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
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
    Pl( { 0,0 },map ),
    cam( { 0,0 },map,Pl ),
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
    dt = ft.Duration();
    Vec2f dir = { 0.0f,0.0f };
    Vec2f cdir = { 0.0f,0.0f };
    bool jump = false;
    if ( wnd.kbd.KeyIsPressed( VK_SPACE ) )
    {
        jump = true;
    }
    if ( wnd.kbd.KeyIsPressed( 'W' ) )
    {
        dir.y -= 1.0;
    }
    if ( wnd.kbd.KeyIsPressed( 'S' ) )
    {
        dir.y += 1.0f;
    }
    if ( wnd.kbd.KeyIsPressed( 'A' ) )
    {
        dir.x -= 1.0f;
    }
    if ( wnd.kbd.KeyIsPressed( 'D' ) )
    {
        dir.x += 1.0f;
    }
    Pl.setDir( dir,jump );
    Pl.Tick( dt );
    if ( !FreeCam )
    {
        if ( wnd.kbd.KeyIsPressed( 'M' ) )
        {
            FreeCam = true;
        }
        cam.BindToPlayer( Pl.PlPos() );
    }
    //FreeCam controlls
    else
    {
        if ( wnd.kbd.KeyIsPressed( 'P' ) )
        {
            FreeCam = false;
        }
        if ( wnd.kbd.KeyIsPressed( VK_UP ) )
        {
            cdir.y -= 1.0;
        }
        if ( wnd.kbd.KeyIsPressed( VK_DOWN ) )
        {
            cdir.y += 1.0f;
        }
        if ( wnd.kbd.KeyIsPressed( VK_LEFT ) )
        {
            cdir.x -= 1.0f;
        }
        if ( wnd.kbd.KeyIsPressed( VK_RIGHT ) )
        {
            cdir.x += 1.0f;
        }
        cam.Move( cdir );
        cam.Update( dt );
    }

    /*------Test Code---------------------*/
    if ( wnd.kbd.KeyIsPressed( 'R' ) )
    {
        Pl.debugSetPlayer( { 0,-1 },0.0f );
    }
    if ( wnd.kbd.KeyIsPressed( 'J' ) && !ispresst )
    {
        std::uniform_real_distribution<float> rDamage( 0.0f,10.0f );
        Pl.PlDamage( rDamage( rng ) );
        ispresst = true;
    }
    else if ( wnd.kbd.KeyIsPressed( 'H' ) && !ispresst )
    {
        Pl.healPlayer( 100.0f );
        ispresst = true;
    }
    const Keyboard::Event e = wnd.kbd.ReadKey();
    if ( e.IsRelease() )
    {
        ispresst = false;
    }
    DBOUT( Pl.getPlHP() );
    DBOUT( "\n" );
    /*------Test Code---------------------*/
}

void Game::ComposeFrame()
{
    gfx.PutPixel( gfx.ScreenWidth / 2,gfx.ScreenHeight / 2,Colors::Blue );
    cam.Draw( gfx );
    ol.DrawHealBar( Pl.getPlHP() );
    text.DrawText( "IRN",gfx.ScreenWidth / 2 - ( text.getGlythWidth() * 3 ) / 2,10,gfx );
}
