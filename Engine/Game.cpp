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
    cam( { 0,0 },map,Pl,eh ),
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

    //Player
    Pl.HandleImtputs( wnd.kbd );
    Pl.Tick( dt );

    //Camera
    cam.HandelImputs( wnd.kbd );
    //FreeCam controlls
    cam.Update( dt );

    //Enemy
    eh.HandleEntitys( dt,Pl );

    /*------Test Code Begin---------------------*/
    if ( wnd.kbd.KeyIsPressed( 'R' ) )
    {
        Pl.debugSetPlayer( { 0,-1 },0.0f );
    }
    if ( wnd.kbd.KeyIsPressed( 'J' ) && !ispresst )
    {
        std::uniform_real_distribution<float> rDamage( 0.0f,10.0f );
        Pl.TakeDamage( rDamage( rng ) );
        ispresst = true;
    }
    else if ( wnd.kbd.KeyIsPressed( 'H' ) && !ispresst )
    {
        Pl.healPlayer( 100.0f );
        ispresst = true;
    }
    if ( wnd.kbd.KeyIsPressed( 'O' ) && !ispresst )
    {
        Pl.incMaxHP( 20 );
        ispresst = true;
    }
    if ( wnd.kbd.KeyIsPressed( 'L' ) && !ispresst )
    {
        Pl.decMaxHP( 20 );
        ispresst = true;
    }
    if ( wnd.kbd.KeyIsPressed( 'I' ) && !ispresst )
    {
        eh.SpawnEnemy( { 0,0 },map );
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
    cam.Draw( gfx );
    ol.DrawHealBar( Pl.HitPoints(),( int )Pl.MaxHitPoints() );
    text.DrawText( "IRN",gfx.ScreenWidth / 2 - ( text.getGlythWidth() * 3 ) / 2,10,gfx );
}
