// Beginning Game Programming
// Chapter 10
// Paddle_Game program header file


#ifndef _GAME_H
#define _GAME_H 1

//windows/directx headers
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9core.h>
#include <dxerr.h>
#include <dsound.h>
#include <dinput.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//framework-specific headers
#include "dxgraphics.h"
#include "dxaudio.h"
#include "dxinput.h"

//application title
#define APPTITLE "Paddle_Game"

//screen setup
#define FULLSCREEN 0       //0 = windowed, 1 = fullscreen
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//function prototypes
int Game_Init(HWND);
void Game_Run(HWND);
void Game_End(HWND);



#endif

