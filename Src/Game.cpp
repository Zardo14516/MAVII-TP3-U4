#include "Game.h"
#include <iostream>


Game::Game(int ancho, int alto, std::string titulo)
{
 
    wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
    wnd->setVisible(true);
    fps = 60;
    wnd->setFramerateLimit(fps);
    frameTime = 3.0f / fps;
    SetZoom(); 
    InitPhysics(); 
    b2Vec2 cannonPosition(10.0f, 90.0f);
    cannon = new Cannon(phyWorld, cannonPosition);

}


void Game::Loop()
{
    while (wnd->isOpen())
    {
        wnd->clear(clearColor);
        DoEvents(); 
        CheckCollitions(); 
        UpdatePhysics(); 
        DrawGame();
        wnd->display();
    }
}
void Game::UpdatePhysics()
{
    phyWorld->Step(frameTime, 8, 8); 
    phyWorld->ClearForces(); 
    phyWorld->DebugDraw(); 


}

void Game::DrawGame()
{

}

void Game::DoEvents()
{
    Event evt;
    while (wnd->pollEvent(evt))
    {
        switch (evt.type)
        {
        case Event::Closed:
            wnd->close();
            break;
        case Event::MouseButtonPressed:
            if (evt.mouseButton.button == Mouse::Left)
            {
                b2Vec2 target(evt.mouseButton.x, evt.mouseButton.y);
                cannon->AimAt(target);
                auto [direction, force] = cannon->Fire(target);
                b2Vec2 cannonPosition = cannon->GetBase()->GetWorldCenter();
                Ragdoll ragdoll(phyWorld, cannonPosition, direction, force);
                ragdolls.push_back(ragdoll);
            }
            break;
        }
    }
}

void Game::CheckCollitions()
{

}

void Game::SetZoom()
{
    View camara;
    camara.setSize(100.0f, 100.0f);
    camara.setCenter(50.0f, 50.0f);
    wnd->setView(camara);
}



Game::~Game(void)
{
   
}