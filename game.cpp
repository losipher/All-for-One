
#include "sprite.h"
#include "game.h"


//background image


//sprite handler
LPD3DXSPRITE sprite_handler;


//ball sprite
LPDIRECT3DTEXTURE9 enemy_image;
sprite enemy;

LPDIRECT3DTEXTURE9 hero_image;
sprite hero;

LPDIRECT3DTEXTURE9 laser_image;
sprite laser[25];

LPDIRECT3DTEXTURE9 back1;
sprite space1;

LPDIRECT3DTEXTURE9 back2;
sprite space2;

LPDIRECT3DTEXTURE9 enemy_image2;
sprite enemy2;

LPDIRECT3DTEXTURE9 enemy_image3;
sprite enemy3;

LPDIRECT3DTEXTURE9 enemy_laser;
sprite enemyLaser;

LPDIRECT3DTEXTURE9 enemy_image4;
LPDIRECT3DTEXTURE9 enemy_image5;
sprite enemy4, enemy5;

LPDIRECT3DTEXTURE9 boss_image;
sprite boss;


CSound *backgroundMusic;
CSound *laserSound;
CSound *explosion;

long start = GetTickCount();
HRESULT result;

//************************************************************************************

sprite LaserSprite[10];

//************************************************************************************


int Game_Init(HWND hwnd)
{
	srand(time(NULL));

	if (!Init_Mouse(hwnd))
	{
		MessageBox(hwnd, "Error initializing the mouse", "Error", MB_OK);
		return 0;
	}

	if (!Init_Keyboard(hwnd))
	{
		MessageBox(hwnd, "Error initializing the keyboard", "Error", MB_OK);
		return 0;
	}

	result = D3DXCreateSprite(d3ddev, &sprite_handler);
	if (result != D3D_OK)
		return 0;

	back1 = LoadTexture("space.bmp",D3DCOLOR_XRGB(255,0,255));
	back2 = LoadTexture("space2.bmp", D3DCOLOR_XRGB(255,0,255));
	enemy_image = LoadTexture("enemy.bmp", D3DCOLOR_XRGB(255,255,255));
	hero_image = LoadTexture("hero.bmp", D3DCOLOR_XRGB(255,255,255));
	laser_image = LoadTexture("laser.bmp", D3DCOLOR_XRGB(255,255,255));
	enemy_image2 = LoadTexture("enemy2.bmp", D3DCOLOR_XRGB(255,255,255));
	enemy_image3 = LoadTexture("enemy3.bmp", D3DCOLOR_XRGB(255,255,255));
	enemy_laser = LoadTexture("enemyLaser.bmp", D3DCOLOR_XRGB(255,255,255));
	enemy_image4 = LoadTexture("enemy4.bmp", D3DCOLOR_XRGB(255,255,255));
	enemy_image5 = LoadTexture("enemy4.bmp", D3DCOLOR_XRGB(255,255,255));
	boss_image = LoadTexture("boss.bmp", D3DCOLOR_XRGB(0,0,0));



	hero.setX(285);
	hero.setY(380);
	hero.setWidth(73);
	hero.setHeight(74);
	hero.setMoveX(12);

	enemy.setX(500);
	enemy.setY(-50);
	enemy.setWidth(48);
	enemy.setHeight(49);
	enemy.setMoveX(0);
	enemy.setMoveY(5);

	space1.setX(0);
	space1.setY(0);

	space2.setX(0);
	space2.setY(-480);

	enemy2.setX(50);
	enemy2.setY(-100);
	enemy2.setWidth(67);
	enemy2.setHeight(58);
	enemy2.setMoveY(0);
	enemy2.setMoveX(0);

	enemy3.setX(285);
	enemy3.setY(-270);
	enemy3.setWidth(70);
	enemy3.setHeight(89);
	enemy3.setMoveX(0);
	enemy3.setMoveY(0);

	enemy4.setX(0);
	enemy4.setY(-100);
	enemy4.setWidth(54);
	enemy4.setHeight(63);
	enemy4.setMoveX(0);
	enemy4.setMoveY(0);

	enemy5.setX(586);
	enemy5.setY(-100);
	enemy5.setWidth(54);
	enemy5.setHeight(63);
	enemy5.setMoveX(0);
	enemy5.setMoveY(0);

	boss.setX(195);
	boss.setY(-160);
	boss.setWidth(250);
	boss.setHeight(151);
	boss.setMoveX(0);
	boss.setMoveY(0);


	enemyLaser.setX(0);
	enemyLaser.setY(0);



	backgroundMusic = LoadSound("theme.wav");
	laserSound = LoadSound("laser.wav");
	explosion = LoadSound("explosion.wav");

	return 1;
}

int Collision(int tempX1, int tempY1, int tempWidth1, int tempHeight1,
			  int tempX2, int tempY2, int tempWidth2, int tempHeight2)
{

	RECT rect1;
	rect1.left = tempX1 + 1;
	rect1.top = tempY1 + 1;
	rect1.right = tempX1 + tempWidth1 - 1;
	rect1.bottom = tempY1 + tempHeight1 - 1;

	RECT rect2;
	rect2.left = tempX2 + 1;
	rect2.top = tempY2 + 1;
	rect2.right = tempX2 + tempWidth2 - 1;
	rect2.bottom = tempY2 + tempHeight2 - 1;

	RECT dest;
	return IntersectRect(&dest, &rect1, &rect2);
}




void Game_Run(HWND hwnd)
{
	static int heroX = hero.getX();
	static int heroY = hero.getY();
	static int heroHeight = hero.getHeight();
	static int heroWidth = hero.getWidth();
	static int heroMoveX = hero.getMoveX();

	static int enemyX = enemy.getX();
	static int enemyY = enemy.getY();
	static int enemyMoveX = enemy.getMoveX();
	static int enemyMoveY = enemy.getMoveY();
	static int enemyWidth = enemy.getWidth();
	static int enemyHeight = enemy.getHeight();
	static int enemyFrame = 0;
	static bool destroyed = false;
	static bool destroyed2 = false;

	static int enemy2X = enemy2.getX();
	static int enemy2Y = enemy2.getY();
	static int enemy2Width = enemy2.getWidth();
	static int enemy2Height = enemy2.getHeight();
	static int enemy2MoveY = enemy2.getMoveY();
	static int enemy2MoveX = enemy2.getMoveX();
	static int enemy3X = enemy3.getX();
	static int enemy3Y = enemy3.getY();
	static int enemy3Width = enemy3.getWidth();
	static int enemy3Height = enemy3.getHeight();
	static int enemy3MoveX = enemy3.getMoveX();
	static int enemy3MoveY = enemy3.getMoveY();
	static bool destroyed3 = false, enemyFire = false, heroDestroyed = false, heroDestroyed2;

	static int enemy4X = enemy4.getX();
	static int enemy4Y = enemy4.getY();
	static int enemy4Width = enemy4.getWidth();
	static int enemy4Height = enemy4.getHeight();
	static int enemy4MoveX = enemy4.getMoveX();
	static int enemy4MoveY = enemy4.getMoveY();

	static int enemy5X = enemy5.getX();
	static int enemy5Y = enemy5.getY();
	static int enemy5Width = enemy5.getWidth();
	static int enemy5Height = enemy5.getHeight();
	static int enemy5MoveX = enemy5.getMoveX();
	static int enemy5MoveY = enemy5.getMoveY();

	static bool destroyed4 = false, destroyed5 = false;


	static int space1X = space1.getX();
	static int space1Y = space1.getY();

	static int space2X = space2.getX();
	static int space2Y = space2.getY();
	static int lasNum = 0;
	static int laserX = 0, laserY = 0;
	static int laserNum = 0;
	static int laserWidth = 13;
	static int laserHeight = 46;

	static int enemyLaserW = 13;
	static int enemyLaserH = 46;
	static int enemyLaserX = enemyLaser.getX();
	static int enemyLaserY = enemyLaser.getY();
	static bool enemyShoot = false;

	static int bossX = boss.getX();
	static int bossY = boss.getY();
	static int bossWidth = boss.getWidth();
	static int bossHeight = boss.getHeight();
	static int bossMoveX = boss.getMoveX();
	static int bossMoveY = boss.getMoveY();
	static bool bossDestroyed = false;
	static int bossHitPoints = 10;


	//*************************************************************************************
	static bool Shoot = false;
	//*************************************************************************************


	LoopSound(backgroundMusic);
	//ball position vector
	D3DXVECTOR3 position(0,0,0);   

	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;

	//update mouse and keyboard
	Poll_Mouse();
	Poll_Keyboard();

	if (enemyFrame > 7)
	{
		if (destroyed)
		{
            enemyX = 700;
			enemyMoveX = 0;
			enemyMoveY = 0;
			enemyFrame =0;
			destroyed = false;
		}
		if (destroyed2)
		{
			enemy2X = 700;
			enemyFrame = 0;
			destroyed2 = false;
		}
		if (destroyed3)
		{
			enemy3X = 700;
			enemyFrame = 0;
			enemy3MoveX = 0;
			enemy3MoveY = 0;
		}
		if (destroyed4)
		{
			enemy4X = 700;
			enemyY = -100;
			enemyFrame = 0;
			enemy4MoveX = 0;
			enemy4MoveY = 0;
		}
		if (destroyed5)
		{
			enemy5X = 700;
			enemy5Y = -100;
			enemyFrame = 0;
			enemy5MoveX = 0;
			enemy5MoveY = 0;
		}
		if (bossDestroyed)
		{
			bossX = 700;
			bossY = -100;
			enemyFrame = 0;
			bossMoveX = 0;
			bossMoveY = 0;

			MessageBox(hwnd, "You Win!", "Game Over!", MB_OK);
			PostMessage(hwnd, WM_DESTROY, 0,0);
		}
		if (heroDestroyed)
		{
			MessageBox(hwnd, "You Lose!", "GameOver", MB_OK);
			PostMessage(hwnd, WM_DESTROY, 0, 0);
		}
	}

	if (GetTickCount() - start >= 30)
	{
		start = GetTickCount();

		space1Y += 3;
		space2Y += 3;

		if (space2Y == 0)
			space1Y = -480;

		if (space1Y == 0)
			space2Y = -480;

		if (enemyY == 100)
		{
			enemyMoveY = 5;
			enemyMoveX = 5;
		}
		if (!destroyed3)
		{
		
			if (enemy3Y >= 200 && enemy3MoveX == 0)
			{
				enemy3MoveX = 4;
				enemy3MoveY = 0;
			}
	
		
			if (enemy3X >= 540 - 89)
				enemy3MoveX = -4;

			if (enemy3X <= 100)
				enemy3MoveX = 4;
		}


		if (Key_Down(DIK_LEFT))
			heroX -= heroMoveX;


		if (Key_Down(DIK_RIGHT))
			heroX += heroMoveX;
		//*********************************************************************************************************
		if (Key_Down(DIK_SPACE) && Shoot == false)
		{
			PlaySound(laserSound);
			laserX = heroX + 30;
			laserY = heroY - 32;
			Shoot = true;
		}

		if (!enemyShoot && enemy3Y >= 200 && enemy3X != 650)
		{
			PlaySound(laserSound);
			enemyLaserX = enemy3X + 30;
			enemyLaserY = enemy3Y ;
			enemyShoot = true;
		}
		if (!enemyShoot && bossY >= 50 && !bossDestroyed)
		{
			PlaySound(laserSound);
			enemyLaserX = bossX + 120;
			enemyLaserY = bossY + 110;
			enemyShoot = true;
		}

		if (heroX > SCREEN_WIDTH - (heroWidth))
			heroX = SCREEN_WIDTH - (heroWidth);
		else if (heroX < 0)
			heroX = 0;

		if (Collision(enemyX, enemyY - enemyHeight, enemyWidth, enemyHeight, laserX, laserY, laserWidth, laserHeight))
		{
 			PlaySound(explosion);
			enemy_image = LoadTexture("explosion.bmp", D3DCOLOR_XRGB(0,0,0));
			destroyed = true;
			enemy2MoveY = 5;
		}
		if (Collision(enemy2X, enemy2Y - enemy2Height, enemy2Width, enemy2Height, laserX, laserY, laserWidth, laserHeight))
		{
			PlaySound(explosion);
			enemy_image2 = LoadTexture("explosion.bmp", D3DCOLOR_XRGB(0,0,0));
			destroyed2 = true;
			enemy3MoveY = 4;
		}
		if(Collision(enemy3X, enemy3Y - enemy3Height, enemy3Width, enemy3Height, laserX, laserY, laserWidth, laserHeight))
		{
			PlaySound(explosion);
			enemy_image3 = LoadTexture("explosion.bmp", D3DCOLOR_XRGB(0,0,0));
			destroyed3 = true;
			enemy4MoveY = 5;
			enemy5MoveY = 5;
		}
		if (Collision(heroX, heroY, heroWidth, heroHeight, enemyLaserX, enemyLaserY, enemyLaserW, enemyLaserH))
		{
			PlaySound(explosion);
			hero_image = LoadTexture("explosion.bmp", D3DCOLOR_XRGB(0,0,0));
			heroDestroyed = true;
		}
		if (Collision(heroX, heroY, heroWidth, heroHeight, enemyX, enemyY, enemyWidth, enemyHeight))
		{
			PlaySound(explosion);
			hero_image = LoadTexture("explosion.bmp", D3DCOLOR_XRGB(0,0,0));
			enemy_image = LoadTexture("explosion.bmp", D3DCOLOR_XRGB(0,0,0));
			heroDestroyed = true;
		}
		if (Collision(heroX, heroY, heroWidth, heroHeight, enemy2X, enemy2Y, enemy2Width, enemy2Height))
		{
			PlaySound(explosion);
			hero_image = LoadTexture("explosion.bmp", D3DCOLOR_XRGB(0,0,0));
			enemy_image = LoadTexture("explosion.bmp", D3DCOLOR_XRGB(0,0,0));
			heroDestroyed = true;
		}
		if (Collision(enemy4X, enemy4Y, enemy4Width, enemy4Height, laserX, laserY, laserWidth, laserHeight))
		{
			PlaySound(explosion);
			enemy_image4 = LoadTexture("explosion.bmp", D3DCOLOR_XRGB(0,0,0));
			destroyed4 = true;
		}
		if (Collision(enemy5X, enemy5Y, enemy5Width, enemy5Height, laserX, laserY, laserWidth, laserHeight))
		{
			PlaySound(explosion);
			enemy_image5 = LoadTexture("explosion.bmp", D3DCOLOR_XRGB(0,0,0));
			destroyed5 = true;
		}
		if (Collision(laserX, laserY, laserWidth, laserHeight, bossX, bossY, bossWidth, bossHeight))
		{
			bossHitPoints -= 1;
			laserY = 0;
		}

		if (bossHitPoints <= 0)
		{
			PlaySound(explosion);
			boss_image = LoadTexture("explosion2.bmp", D3DCOLOR_XRGB(0,0,0));
			bossDestroyed = true;
		}

		if (enemy4X == 700 && enemy5X == 700 && destroyed5 == true)
		{
			bossMoveY = 2;
			destroyed5 = false;
		}


		enemyY += enemyMoveY;
		enemyX -= enemyMoveX;

		if (enemy2Y == 100)
		{
			enemy2MoveY = 5;
			enemy2MoveX = 5;
		}
		if (enemy4X == 0 && enemy4Y == 0)
		{
			enemy4MoveY = 0;
			enemy4MoveX = 5;
		}
		if (enemy5Y == 0 && enemy5X == 586)
		{
			enemy5MoveY = 0;
			enemy5MoveX = 5;
		}
		if (enemy4X >= 320 - enemy4Width - 5)
		{
			enemy4MoveX = 0;
			enemy4MoveY = 5;
		}
		if (enemy5X <= 320 + 5)
		{
			enemy5MoveX = 0;
			enemy5MoveY = 5;
		}
		if (enemy4Y >= 180 && enemy4X >= 300 - enemy4Width )
		{
			enemy4MoveY = 0;
			enemy4MoveX = -5;
		}
		if (enemy4X <= 0 && enemy4Y >= 180)
			enemy4MoveX = 5;
		if (enemy5Y >= 180 && enemy5X == 321)
		{
			enemy5MoveY = 0;
			enemy5MoveX = -5;
		}
		if (enemy5X >= 640 - enemy5Width && enemy5Y >= 180)
			enemy5MoveX = 5;

		if (bossY >= 50 && bossMoveX == 0)
		{
			bossMoveY = 0;
			bossMoveX = 2;
		}
		if (bossX <= 0)
			bossMoveX = 2;
		if (bossX > 640 - bossWidth)
			bossMoveX = -2;

		enemy2Y += enemy2MoveY;
		enemy2X += enemy2MoveX;

		enemy3Y += enemy3MoveY;
		enemy3X += enemy3MoveX;

		bossY += bossMoveY;
		bossX += bossMoveX;

		heroX += Mouse_X();
		if (destroyed || destroyed2 || destroyed3 || destroyed3 || heroDestroyed || destroyed4 || destroyed5 || bossDestroyed)
			enemyFrame++;

		if (enemyLaserY >= 480 + enemyLaserH)
			enemyShoot = false;

		enemy4Y += enemy4MoveY;
		enemy4X += enemy4MoveX;
		enemy5Y += enemy5MoveY;
		enemy5X -= enemy5MoveX;

	}


	//start rendering
	if (d3ddev->BeginScene())
	{

		LoopSound(backgroundMusic);
		d3ddev->StretchRect(NULL, NULL, backbuffer, NULL, D3DTEXF_NONE);

		//start sprite handler
		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);


		position.x = (float)0;
		position.y = (float)space1Y;
		sprite_handler->Draw(
			back1,
			NULL,
			NULL,
			&position,
			D3DCOLOR_XRGB(255,255,255));

		position.x = (float)0;
		position.y = (float)space2Y;
		sprite_handler->Draw(
			back2,
			NULL,
			NULL,
			&position,
			D3DCOLOR_XRGB(255,255,255));

		RECT srcRect2;
		srcRect2.left = 0;
		srcRect2.top = 0;
		srcRect2.right = enemy2Width;
		srcRect2.top = enemy2Height;
		int colums2 = 7;
		position.x = (float)enemy2X;
		position.y = (float)enemy2Y;
		if (destroyed2 || heroDestroyed)
		{
			srcRect2.left = (enemyFrame % colums2) * 66;
			srcRect2.top = (enemyFrame / colums2) * 67;
			srcRect2.right = srcRect2.left + 66;
			srcRect2.bottom = srcRect2.top + 67;
			position.y -= enemy2Height;
		}
		
		sprite_handler->Draw(
			enemy_image2,
			&srcRect2,
			NULL,
			&position,
			D3DCOLOR_XRGB(255,255,255));

		RECT srcRect;
		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.right = enemyWidth;
		srcRect.top = enemyHeight;
		int colums = 7;
		position.x = (float)enemyX;
		position.y = (float)enemyY;
		if (destroyed || heroDestroyed)
		{
			srcRect.left = (enemyFrame % colums) * 66;
			srcRect.top = (enemyFrame / colums) * 67;
			srcRect.right = srcRect.left + 66;
			srcRect.bottom = srcRect.top + 67;
			position.y -= enemyHeight;
		}
		//draw the ball
		
		sprite_handler->Draw(
			enemy_image, 
			&srcRect,
			NULL,
			&position,
			D3DCOLOR_XRGB(255,255,255));

			
		RECT srcRect3;
		srcRect3.left = 0;
		srcRect3.top = 0;
		srcRect3.right = enemy3Width;
		srcRect3.top = enemy3Height;
		int colums3 = 7;
		position.x = (float)enemy3X;
		position.y = (float)enemy3Y;
		if (destroyed3)
		{
			srcRect3.left = (enemyFrame % colums3) * 66;
			srcRect3.top = (enemyFrame / colums3) * 67;
			srcRect3.right = srcRect3.left + 66;
			srcRect3.bottom = srcRect3.top + 67;
			position.y -= enemy3Height;
		}
		sprite_handler->Draw(
			enemy_image3,
			&srcRect3,
			NULL,
			&position,
			D3DCOLOR_XRGB(255,255,255));

		RECT srcRect4;
		srcRect4.left = 0;
		srcRect4.top = 0;
		srcRect4.right = heroWidth;
		srcRect4.top = heroHeight;
		int colums4 = 7;
		position.x = (float)heroX;
		position.y = (float)heroY + heroHeight;
		if (heroDestroyed)
		{
			srcRect4.left = (enemyFrame % colums4) * 66;
			srcRect4.top = (enemyFrame / colums4) * 67;
			srcRect4.right = srcRect4.left + 66;
			srcRect4.bottom = srcRect4.top + 67;
			position.y -= heroHeight;
		}
		sprite_handler->Draw(
			hero_image,
			&srcRect4,
			NULL,
			&position,
			D3DCOLOR_XRGB(255,255,255));
		//*****************************************************************************************************
		if (Shoot && laserY != 0 )
		{		
			laserY--;
			position.x = (float)laserX;
			position.y = (float)laserY;
			sprite_handler->Draw(
				laser_image,
				NULL,
				NULL,
				&position,
				D3DCOLOR_XRGB(255,255,255));		
		}
		if (laserY == 0 )
		{
			laserX = heroX + 25;
			laserY = heroY - 32;
			Shoot = false;
		}
		if(enemyShoot)
		{
			enemyLaserY++;
			position.x = (float)enemyLaserX;
			position.y = (float)enemyLaserY;
			sprite_handler->Draw(
				enemy_laser,
				NULL,
				NULL,
				&position,
				D3DCOLOR_XRGB(255,255,255));
		}
		RECT srcRect5;
		srcRect5.left = 0;
		srcRect5.top = 0;
		srcRect5.right = enemy4Width;
		srcRect5.top = enemy4Height;
		int colums5 = 7;
		position.x = (float)enemy4X;
		position.y = (float)enemy4Y + enemy4Height;
		if (destroyed4)
		{
			srcRect5.left = (enemyFrame % colums5) * 66;
			srcRect5.top = (enemyFrame / colums5) * 67;
			srcRect5.right = srcRect5.left + 66;
			srcRect5.bottom = srcRect5.top + 67;
		}
		sprite_handler->Draw(
			enemy_image4,
			&srcRect5,
			NULL,
			&position,
			D3DCOLOR_XRGB(255,255,255));

		RECT srcRect6;
		srcRect6.left = 0;
		srcRect6.top = 0;
		srcRect6.right = enemy5Width;
		srcRect6.top = enemy5Height;
		int colums6 = 7;
		position.x = (float)enemy5X;
		position.y = (float)enemy5Y + enemy5Height;
		if (destroyed5)
		{
			srcRect6.left = (enemyFrame % colums6) * 66;
			srcRect6.top = (enemyFrame / colums6) * 67;
			srcRect6.right = srcRect6.left + 66;
			srcRect6.bottom = srcRect6.top + 67;
			
		}
		sprite_handler->Draw(
			enemy_image5,
			&srcRect6,
			NULL,
			&position,
			D3DCOLOR_XRGB(255,255,255));

		RECT srcRect7;
		srcRect7.left = 0;
		srcRect7.top = 0;
		srcRect7.right = bossWidth;
		srcRect7.top = bossHeight;
		int colums7 = 7;
		position.x = (float)bossX;
		position.y = (float)bossY + bossHeight;
		if (bossDestroyed)
		{
			srcRect7.left = (enemyFrame % colums7) * 132;
			srcRect7.top = (enemyFrame / colums7) * 134;
			srcRect7.right = srcRect7.left + 132;
			srcRect7.bottom = srcRect7.top + 134;
			position.y -= bossHeight;
			
		}
		sprite_handler->Draw(
			boss_image,
			&srcRect7,
			NULL,
			&position,
			D3DCOLOR_XRGB(255,255,255));
		//***************************************************************************************************		
		sprite_handler->End();

		//stop rendering
		d3ddev->EndScene();
	}

	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);

	//check for mouse button (to exit program)
	if (Mouse_Button(0))
		PostMessage(hwnd, WM_DESTROY, 0, 0);

	//check for escape key (to exit program)
	if (Key_Down(DIK_ESCAPE))
		PostMessage(hwnd, WM_DESTROY, 0, 0);
}

//frees memory and cleans up before the game ends
void Game_End(HWND hwnd)
{

	if (enemy_image != NULL)
		enemy_image->Release();
	if (enemy_image2 != NULL)
		enemy_image2->Release();
	if (enemy_image3 != NULL)
		enemy_image3->Release();
	if (laser_image != NULL)
		laser_image->Release();
	if (enemy_laser != NULL)
		enemy_laser->Release();
	if (back2 != NULL)
		back2->Release();

	if (hero_image != NULL)
		hero_image->Release();

	if (back1 != NULL)
		back1->Release();

	if (sprite_handler != NULL)
		sprite_handler->Release();

	//if (sound_bounce != NULL)
	//    delete sound_bounce;

	//if (sound_hit != NULL)
	//    delete sound_hit;


}

