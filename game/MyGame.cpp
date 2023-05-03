#include "stdafx.h"
#include "MyGame.h"

#pragma warning (disable:4244)

CMyGame::CMyGame(void) :

	world(b2Vec2(0.0f, -5.0f)),

	peggleBall(&world, 400, 500, 24, 24, CColor::Red(), CColor::Black(), 0),
	testPeg(&world, 390, 200, 32, 32, CColor::Green(), CColor::Black(), 0),

	pivot(&world, 800, 936, 194, 194, CColor::Cyan(), CColor::Black(), 0),

	cannon(&world, 800, 840, 32, 32, CColor::Blue(), CColor::Black(), 0),

	background(),
	gameEnd(), 
	backgroundFrame("frame.bmp"),
	pivotGraphic("pivot.bmp")

	
	
{
}

CMyGame::~CMyGame(void)
{
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()

{
	
	if (background.GetX() == 0)
	{
		background.SetX(1600);
	}

	world.Step(1.f / 60.f, 6, 2);

	for (CSprite* p : walls)
		p->Update(GetTime());



	//	for (CSprite* newRamp : ramps)
		//	newRamp->Update(GetTime());

	for (CSprite* newBall : peggleBallList)
	{
		newBall->Update(GetTime());

	}

	//peggleBall.Update(GetTime());
	//testPeg.Update(GetTime());
	pivot.Update(GetTime());
	cannon.Update(GetTime());

	






	for (CSprite* newBall : peggleBallList)
	{
		


		if (newBall->GetY() < -32)
		{
			if (redPegsRemaining <= 0)
			{
				gameState = 2;

			}


			if (ballsRemaining == 0 && redPegsRemaining > 0)
			{
				{
					gameState = 0;

				}
			}



			ballActive = false;
			newBall->Delete();
			newBall->SetY(1000);
			ballCombo = 0;



			for (CSprite* newPegLight : testLight)
			{
				if (newPegLight->GetHealth() == 0 || newPegLight->GetHealth() == 2 || newPegLight->GetHealth() == 4)
				{
					//newPegLight->Delete();

				}


			}

			for (CSprite* newPeg : pegglePegsList)
			{

				if (static_cast<CSpriteBox2DBase*>(newPeg)->GetHealth() == -1)
				{
	
						//static_cast<CSpriteBox2DBase*>(newPeg)->DeleteBody();
					
				}
			}

		}
	}
	
	//pegglePegsList.delete_if(deleted);
	
	for (CSprite* newPegLight : testLight)
	{
		newPegLight->Update(GetTime());
	}
}

void CMyGame::OnDraw(CGraphics* g)
{


	background.Draw(g);

	for (CSprite* p : walls)
		p->Draw(g);


	for (CSprite* newBall : peggleBallList) newBall->Draw(g);

	for (CSprite* newPeg : pegglePegsList) newPeg->Draw(g);

	for (CSprite* newPegLight : testLight) newPegLight->Draw(g);


	g->Blit(CVector(0, 0), backgroundFrame);


	for (CSprite* newPegLight : testLight)
	{
		for (CSprite* newBall : peggleBallList)
		{


			if (newBall->HitTest(newPegLight))
			{
				newBall->SetHealth(0);

				if (newPegLight->GetHealth() == 1)
				{
					ballCombo += 1;
					score += (10 * ballCombo);

					newPegLight->SetHealth(0);


					newPegLight->LoadImageW("pegBlue2.bmp");
					newPegLight->SetImage("pegBlue2.bmp");

					totalPegsRemaining -= 1;
				}
				else if (newPegLight->GetHealth() == 3)
				{
					ballCombo += 1;
					score += (100 * ballCombo);


					newPegLight->SetHealth(2);


					newPegLight->LoadImageW("pegRed1.bmp");
					newPegLight->SetImage("pegRed1.bmp");

					totalPegsRemaining -= 1;
					redPegsRemaining -= 1;
				}
				else if (newPegLight->GetHealth() == 5)
				{
					ballCombo += 1;
					score += (10 * ballCombo);

					newPegLight->SetHealth(4);


					newPegLight->LoadImageW("pegGreen1.bmp");
					newPegLight->SetImage("pegGreen1.bmp");
					ballsRemaining++;

					totalPegsRemaining -= 1;
				}
			}


		}


	}


	//peggleBall.Draw(g);
	//testPeg.Draw(g);

	pivot.Draw(g);
	cannon.Draw(g);


	if (gameState == 1)
	{

		*g << font(28) << color(CColor::Red()) << xy(80, 900) << "Balls Remaining: " << ballsRemaining;
		*g << font(28) << color(CColor::Blue()) << xy(1200, 900) << "Total Remaining: " << totalPegsRemaining;
		*g << font(28) << color(CColor::LightRed()) << xy(1200, 850) << "Red Remaining: " << redPegsRemaining;
		*g << font(28) << color(CColor::Green()) << xy(1000, 900) << "Score: " << score;
		*g << font(28) << color(CColor::Magenta()) << xy(1000, 850) << "Combo: " << ballCombo << "x";
		//*g << font(28) << color(CColor::Red()) << xy(200, 900) << ballActive;
	}


	g->Blit(CVector(703, 839), pivotGraphic);
	if (gameStart == 0)
	{
		menu.Draw(g);
	}

	
		


		

		if (gameState == 2)
		{
			gameEnd.Draw(g);
			*g << font(35) << color(CColor::Black()) << xy(625, 250) << "Thanks for Playing!";
			*g << font(35) << color(CColor::Black()) << xy(575, 650) << "Reset Game to try again";
			*g << font(35) << color(CColor::Magenta()) << xy(725, 300) << "Score: " << score;
			*g << font(35) << color(CColor::DarkGreen()) << xy(725, 700) << "You Win!";
		}
		else if (gameState ==0)
		{	gameEnd.Draw(g);
			*g << font(35) << color(CColor::Black()) << xy(625, 250) << "Thanks for Playing!";
			*g << font(35) << color(CColor::Black()) << xy(575, 650) << "Reset Game to try again";
			*g << font(35) << color(CColor::Magenta()) << xy(725, 300) << "Score: " << score;
			*g << font(35) << color(CColor::Red()) << xy(725, 700) << "You Lose!";
		}
	


		


	}


	

	


/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
	menu.SetPosition(800, 500);
	menu.LoadImageW("menuTest.jpg");
	menu.SetImage("menuTest.jpg");

	gameEnd.LoadImageW("gameEnd.bmp");
	gameEnd.SetImage("gameEnd.bmp");
	gameEnd.SetPosition(800, 500);


	background.LoadImageW("sky.jpg");
	background.SetImage("sky.jpg");
	//background.SetMotion(-100, 0);


	
	ballActive = false;

	pivot.CreateStaticBody();
//peggleBall.CreateDynamicBody(15, 0.5f, 0.8f);
	//testPeg.CreateStaticBody();
	//peggleBall.LoadImageW("peggleBallSmall.bmp");
	//peggleBall.SetImage("peggleBallSmall.bmp");

	
}

// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	StartGame();	// this allows to start the game immediately
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
	
	background.SetPosition(800,500);

	//ballsRemaining = 160;




	
	for (CSprite* p : walls)
	
		delete p;
		walls.clear();

		CSpriteBox2DBase* p;

		p = new CSpriteBox2DRect(&world, 32, 500, 64, 2500, CColor::Yellow(), CColor::Black(), GetTime());
		p->CreateStaticBody();
		walls.push_back(p);

		p = new CSpriteBox2DRect(&world, 1568, 500, 64, 2500, CColor::Yellow(), CColor::Black(), GetTime());
		p->CreateStaticBody();
		
		walls.push_back(p);



		
		for (CSprite* newPeg : pegglePegsList)
			delete newPeg;
		pegglePegsList.clear();
		CSpriteBox2DBase* newPeg;

for (int x = 164; x < (64 * 22); x += 64)
		{

			newPeg = new CSpriteBox2DCircle(&world, x + 8, 200, 32, 32, CColor::Blue(), CColor::Blue(), GetTime());
			newPeg->CreateStaticBody();
			newPeg->SetHealth(1);
			pegglePegsList.push_back(newPeg);

			newPeg = new CSpriteBox2DCircle(&world, 1600 - (x + 8 ), 275, 32, 32, CColor::Blue(), CColor::Blue(), GetTime());
			newPeg->CreateStaticBody();
			newPeg->SetHealth(1);
			pegglePegsList.push_back(newPeg);
			
			newPeg = new CSpriteBox2DCircle(&world, x+8, 350, 32, 32, CColor::Blue(), CColor::Blue(), GetTime());
			newPeg->CreateStaticBody();
			newPeg->SetHealth(1);
			pegglePegsList.push_back(newPeg);

			newPeg = new CSpriteBox2DCircle(&world, 1600 - (x + 8), 425, 32, 32, CColor::Blue(), CColor::Blue(), GetTime());
			newPeg->CreateStaticBody();
			newPeg->SetHealth(1);
			pegglePegsList.push_back(newPeg);

			newPeg = new CSpriteBox2DCircle(&world, x+8, 500, 32, 32, CColor::Blue(), CColor::Blue(), GetTime());
			newPeg->CreateStaticBody();
			newPeg->SetHealth(1);
			pegglePegsList.push_back(newPeg);

			newPeg = new CSpriteBox2DCircle(&world, 1600 - (x + 8), 575, 32, 32, CColor::Blue(), CColor::Blue(), GetTime());
			newPeg->CreateStaticBody();
			newPeg->SetHealth(1);
			pegglePegsList.push_back(newPeg);

			newPeg = new CSpriteBox2DCircle(&world, x+8, 650, 32, 32, CColor::Blue(), CColor::Blue(), GetTime());
			newPeg->CreateStaticBody();
			newPeg->SetHealth(1);
			pegglePegsList.push_back(newPeg);

			newPeg = new CSpriteBox2DCircle(&world, 1600 - (x + 8), 725, 32, 32, CColor::Blue(), CColor::Blue(), GetTime());
			newPeg->CreateStaticBody();
			newPeg->SetHealth(1);
			pegglePegsList.push_back(newPeg);
		}


		for (CSprite* newPegLight : testLight)
		
			delete newPegLight;
			testLight.clear();
			CSprite* newPegLight;



			for (int x = 164; x < (64 * 22); x += 64)
			{

				

				newPegLight = new CSprite(x + 8, 200, spriteSelector(), CColor::Blue(), GetTime());
				newPegLight->SetHealth(spriteHealth);
				testLight.push_back(newPegLight);

				newPegLight = new CSprite(1600 - (x + 8), 275, spriteSelector(), CColor::Blue(), GetTime());
				newPegLight->SetHealth(spriteHealth);
				testLight.push_back(newPegLight);

				newPegLight = new CSprite( x + 8, 350, spriteSelector(), CColor::Blue(), GetTime());
				newPegLight->SetHealth(spriteHealth);
				testLight.push_back(newPegLight);

				newPegLight = new CSprite( 1600 - (x + 8), 425, spriteSelector(), CColor::Blue(), GetTime());
				newPegLight->SetHealth(spriteHealth);
				testLight.push_back(newPegLight);

				newPegLight = new CSprite( x + 8, 500, spriteSelector(), CColor::Blue(), GetTime());
				newPegLight->SetHealth(spriteHealth);
				testLight.push_back(newPegLight);

				newPegLight = new CSprite( 1600 - (x + 8), 575, spriteSelector(), CColor::Blue(), GetTime());
				newPegLight->SetHealth(spriteHealth);
				testLight.push_back(newPegLight);

				newPegLight = new CSprite( x + 8, 650, spriteSelector(), CColor::Blue(), GetTime());
				newPegLight->SetHealth(spriteHealth);
				testLight.push_back(newPegLight);

				newPegLight = new CSprite( 1600 - (x + 8), 725, spriteSelector(), CColor::Blue(), GetTime());
				newPegLight->SetHealth(spriteHealth);
				testLight.push_back(newPegLight);

		}
			redPegsRemaining -= 1;

}

// called when Game is Over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
	{
		StopGame();
	}

	if (sym == SDLK_SPACE)
	{
		
		if (gameStart == 0)
		{
			gameStart = 1;
		}
	}
	if (sym == SDLK_F2)
	{
	}
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
	
	
		double angle = atan2(y - pivotCentreY, x - pivotCentreX);

			if (sin(angle) > 0)
			{

				angle = acos(cos(angle));
			}
			



		double cannonCentreX = pivotCentreX + pivotRadius * cos(angle);
		double cannonCentreY = pivotCentreY + pivotRadius * sin(angle);

		cannonCentreX += cannonRadius;
		cannonCentreY += cannonRadius;

		if (cannonCentreY + 8 < 936)
		{
			double dx = cannonCentreX - pivotCentreX;
			double dy = cannonCentreY - pivotCentreY;
			double distance = sqrt(dx * dx + dy * dy);
			double scale = pivotRadius / distance;
			cannonCentreX = (int)(pivotCentreX + dx * scale);
			cannonCentreY = (int)(pivotCentreY + dy * scale);



			cannon.SetPosition(cannonCentreX, cannonCentreY);

		}


}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	{


		// Used to stop shooting inside pivot
		double dx = x - pivotCentreX;
		double dy = y - pivotCentreY;
		double distance = sqrt(dx * dx + dy * dy);
		//


		double angle = atan2(y - cannon.GetY(), x - cannon.GetX());

		int ballCentreX = cannon.GetX() + (cannonRadius - ballRadius) * cos(angle);
		int ballCentreY = cannon.GetY() + (cannonRadius - ballRadius) * sin(angle);

		

	
		int ballVelocityX = ballSpeed * cos(angle);
		int ballVelocityY = ballSpeed * sin(angle);
		
	
		
		if (y <= cannon.GetY()  && distance > pivotRadius && ballActive == false && ballsRemaining>0 && gameStart != 0 && gameState == 1)
		{
			ballActive = true;
			CSpriteBox2DBase* newBall = new CSpriteBox2DCircle(&world, ballCentreX, ballCentreY, 24, 24, CColor::LightGray(), CColor::Black(), 0);
			
			//newBall->LoadImageW("peggleBall.bmp");
			//newBall->SetImage("peggleBall.bmp");
			
			newBall->SetVelocity(ballVelocityX * 20, ballVelocityY * 20);


			newBall->CreateDynamicBody(1, 3, 0.7f);
			

			CSprite* newBallSprite = new CSprite(ballCentreX, ballCentreY, 24, 24, "peggleBallSmall.bmp", CColor::Black(), GetTime());
			peggleBallSprite.push_back(newBallSprite);

			

			peggleBallList.push_back(newBall);

			ballsRemaining -= 1;
			
		}
		
		


	}

	



	


}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
	PauseGame();
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
	




}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}

char* CMyGame::spriteSelector()
{
	spriteSelect = rand() % 160;

	if (spriteSelect >= 0 && spriteSelect <= 1)
	{

		currentSprite = "pegGreen.bmp";
		spriteHealth = 5;
	}
	else if (spriteSelect >= 2 && spriteSelect <= 55)
	{

		currentSprite = "pegRed.bmp";
		redPegsRemaining += 1;
		spriteHealth = 3;
	}
	else if (spriteSelect >55)
	{

		currentSprite = "pegBlue.bmp";
		spriteHealth = 1;
	}
	char* newSprite = currentSprite.data();
	return newSprite;






	
}


