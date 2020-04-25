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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
    Pl( { 3,-6 },map ),
    cam( { 3,-6 },map,Pl )
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
    if ( wnd.kbd.KeyIsPressed( VK_UP ) )
    {
        dir.y -= 1.0;
    }
    if ( wnd.kbd.KeyIsPressed( VK_DOWN ) )
    {
        dir.y += 1.0f;
    }
    if ( wnd.kbd.KeyIsPressed( VK_LEFT ) )
    {
        dir.x -= 1.0f;
    }
    if ( wnd.kbd.KeyIsPressed( VK_RIGHT ) )
    {
        dir.x += 1.0f;
    }
    if ( wnd.kbd.KeyIsPressed( VK_SPACE ) )
    {
        jump = true;
    }
    if ( wnd.kbd.KeyIsPressed( 'W' ) )
    {
        cdir.y -= 1.0;
    }
    if ( wnd.kbd.KeyIsPressed( 'S' ) )
    {
        cdir.y += 1.0f;
    }
    if ( wnd.kbd.KeyIsPressed( 'A' ) )
    {
        cdir.x -= 1.0f;
    }
    if ( wnd.kbd.KeyIsPressed( 'D' ) )
    {
        cdir.x += 1.0f;
    }
    Pl.setDir( dir,jump );
    Pl.Tick( dt );
    cam.Move( cdir );
    cam.Update( dt );
}

void Game::ComposeFrame()
{
    gfx.PutPixel( gfx.ScreenWidth / 2,gfx.ScreenHeight / 2,Colors::Blue );
    cam.Draw( gfx );
}
