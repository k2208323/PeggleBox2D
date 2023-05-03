#pragma once

#include "SpriteBox2D.h"

class CMyGame : public CGame
{
	b2World world; 

	CSprite menu;
	CSprite gameEnd;

	CSpriteList walls;
	CSpriteList ramps;

	
	CSpriteList pegglePegsList;
	CSpriteList peggleBallList;

	CSpriteList peggleBallSprite;


	CSpriteBox2DCircle peggleBall;

	CSpriteBox2DCircle testPeg;

	CSpriteBox2DCircle pivot;

	CSpriteBox2DCircle cannon;
	

	CSpriteList testLight;

	int ballsRemaining = 15;

	
	static const int pivotX;
	static const int pivotY;


	const int pivotCentreX = 800;
	const int pivotCentreY = 936;
	const int pivotRadius = 97;

	const int cannonRadius = 16;
	const int ballSpeed = 70;
	const int ballRadius = 12;
	
	bool ballActive = 0;

	int score = 0;
	int ballCombo = 0;


	int totalPegsRemaining = 160;
	int redPegsRemaining = 1;

	string currentSprite;
	int spriteSelect = 0;
	int spriteHealth = 0;

	int testVar = 0;

	int newBallY = 0;

	bool gameStart = 0;


	CSprite background;
	CGraphics backgroundFrame;
	CGraphics pivotGraphic;

	
	
	int gameState = 1;



public:
	CMyGame(void);
	~CMyGame(void);

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);

	char* spriteSelector();
	

};
