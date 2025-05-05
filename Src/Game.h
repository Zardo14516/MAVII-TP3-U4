#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Ragdoll.h"
#include <list>
#include "Canon.h"
#include "Box2DHelper.h"


using namespace sf;
class Game
{
private:
	// Propiedades de la ventana
	int alto;
	int ancho;
	RenderWindow *wnd;
	Color clearColor;

	// Objetos de box2d
	b2World *phyWorld;
	SFMLRenderer *debugRender;

	//tiempo de frame
	float frameTime;
	int fps;

	
	std::vector<Ragdoll> ragdolls;



	

public:

	Cannon* cannon;

	Game(int ancho, int alto,std::string titulo);
	void CheckCollitions();
	~Game(void);

	void InitPhysics()
	{

		phyWorld = new b2World(b2Vec2(0.0f, 9.8f));


		debugRender = new SFMLRenderer(wnd);
		debugRender->SetFlags(UINT_MAX);
		phyWorld->SetDebugDraw(debugRender);


		b2Body* groundBody = Box2DHelper::CreateComplexRectangularStaticBody(phyWorld, 100, 10, 5);
		groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

		b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
		leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

		b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
		rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

		b2Body* TopWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
		TopWallBody->SetTransform(b2Vec2(50.f, 0.0f), 0.0f);

		b2Body* Obst1 = Box2DHelper::CreateRectangularStaticBody(phyWorld, 5, 10);
		Obst1->SetTransform(b2Vec2(40.f, 40.0f), 0.0f);

		b2Body* Obst2 = Box2DHelper::CreateRectangularKinematicBody(phyWorld, 5, 10);
		Obst2->SetTransform(b2Vec2(60.f, 60.0f), 0.0f);
	}

	void Loop();
	void DrawGame();
	void UpdatePhysics();
	void DoEvents();
	void SetZoom();
};

