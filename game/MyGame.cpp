#include "stdafx.h"
#include "MyGame.h"

#pragma warning (disable:4244)

CMyGame::CMyGame(void) :
	world(b2Vec2(0.0f, -10.0f)),
	m_ground(&world, 512, 0, 2000, 200, CColor::Black(), 0),
	m_marble(&world, X_SLING, Y_SLING, 30, 30, CColor::Red(), CColor::Black(), 0),
	m_background("back.jpg")
{
	m_bAiming = false;
}

CMyGame::~CMyGame(void)
{
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	world.Step(1.0f / 60.0f, 6, 2);

	m_ground.Update(GetTime());
	for (CSprite *p : m_house)
		p->Update(GetTime());
	m_marble.Update(GetTime());
}

void CMyGame::OnDraw(CGraphics* g)
{
	g->Blit(CVector(0, 0), m_background);
	for (CSprite *p : m_house)
		p->Draw(g);
	m_marble.Draw(g);
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}

// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	StartGame();	// this allows to start the game immediately
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
	m_ground.CreateStaticBody();

	for (CSprite *p : m_house)
		delete p;
	m_house.clear();
	
	CSpriteBox2DBase *p;
	p = new CSpriteBox2DRect(&world, 775, 175, 20, 150, CColor::Black(128), CColor::Black(), GetTime());
	p->CreateDynamicBody();
	m_house.push_back(p);
	p = new CSpriteBox2DRect(&world, 925, 175, 20, 150, CColor::Black(128), CColor::Black(), GetTime());
	p->CreateDynamicBody();
	m_house.push_back(p);
	p = new CSpriteBox2DRect(&world, 850, 260, 154, 20, CColor::Black(128), CColor::Black(), GetTime());
	p->CreateDynamicBody();
	m_house.push_back(p);
	p = new CSpriteBox2DRect(&world, 810, 320, 20, 100, CColor::Black(128), CColor::Black(), GetTime());
	p->CreateDynamicBody();
	m_house.push_back(p);
	p = new CSpriteBox2DRect(&world, 890, 320, 20, 100, CColor::Black(128), CColor::Black(), GetTime());
	p->CreateDynamicBody();
	m_house.push_back(p);
	p = new CSpriteBox2DRect(&world, 850, 380, 100, 20, CColor::Black(128), CColor::Black(), GetTime());
	p->CreateDynamicBody();
	m_house.push_back(p);
	p = new CSpriteBox2DRect(&world, 850, 415, 50, 50, CColor::Black(128), CColor::Black(), GetTime());
	p->CreateDynamicBody();
	m_house.push_back(p);
	p = new CSpriteBox2DCircle(&world, 850, 300, 40, 40, CColor::Green(), CColor::Black(), GetTime());
	p->CreateDynamicBody();
	m_house.push_back(p);

	m_marble.DeleteBody();
	m_marble.SetVelocity(0, 0);
	m_marble.SetPivotFromCenter(0, 0);
	m_marble.SetPosition(X_SLING, Y_SLING);
	m_bAiming = false;
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
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
	if (m_bAiming == true)
	{
		m_marble.SetPosition(x, y);
	}
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	if (m_marble.HitTest(x, y))
	{
		m_bAiming = true;
		m_marble.SetPivot(x, y);
	}
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
	if (m_bAiming)
	{
		m_marble.SetPosition(x, y);
		m_bAiming = false;

		double fx = X_SLING - x;
		double fy = Y_SLING - y;

		m_marble.SetVelocity(10 * fx, 10 * fy);

		m_marble.CreateDynamicBody(15, 0.5f, 0.3f);
		m_marble.GetBody()->SetAngularDamping(100);
	}
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
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
