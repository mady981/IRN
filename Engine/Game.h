/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "WorldObject.h"
#include "FrameTimer.h"
#include "Text.h"
#include "SurfaceCodex.h"
#include <vector>
#include <random>
#include "Bencher.h"

class Game
{
private:
    enum class GameState
    {
        InMenue,
        InGame1,
        InGame2
    };
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
    ~Game();
	void Go();
private:
    void HandleWorldObject();
	void ComposeFrame();
	void UpdateModel();
private:
	MainWindow& wnd;
	Graphics gfx;
    std::mt19937 rng;
    WorldObject* pWorld = nullptr;
    FrameTimer ft;
    Text text = Text( 32,4,SurfaceCodex::Retrieve( L"../Engine/Sprite/FontSheet16x18.bmp" ) );
    Bencher bench;
private:
    GameState g_state = GameState::InMenue;
    bool ispresst = false;
    std::vector<Vec2i> layout1;
    std::vector<Vec2i> layout2;
    RecI World1SelectionHitBox = RecI( { 100 - 2,200 - 2 },text.getGlythWidth() * 7,text.getGlythHeight() );
    RecI World2SelectionHitBox = RecI( { 100 - 2,300 - 2 },text.getGlythWidth() * 7,text.getGlythHeight() );
};