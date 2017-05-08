#define _USE_MATH_DEFINES
#include "SceneGraphApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Utility.h>
#include "Node.h"
#include "SpriteNode.h"
#include "Tank.h"
#include <math.h>

SceneGraphApp::SceneGraphApp() {
}

SceneGraphApp::~SceneGraphApp() {
}

bool SceneGraphApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_wallPaper = new aie::Texture("./sceneGraph/textures/wallpaper.png");
	m_tankTracks = new aie::Texture("./sceneGraph/textures/tankTracks.png");


	m_tank = new Tank();
	m_tank->Translate(Vector2<float>(300, 300));
	m_nodes.push_back(m_tank);

	return true;
}

void SceneGraphApp::shutdown() {

	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++) {
		delete (*iter);
	}
	m_nodes.clear();
	
	delete m_font;
	delete m_2dRenderer;
	delete m_wallPaper;
	delete m_tankTracks;
}

void SceneGraphApp::update(float deltaTime) {
	static float sDx, sDy;
	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	int mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);

	Vector2<float> tankPos = m_tank->GetGlobalPosition();
	
	// grab the position of the tank and make it a vector
	Vector2<float> mouse = Vector2<float>((float)mouseX, (float)mouseY) - tankPos;

	// calculate angle from vector (the vector from the tank to the mouse)
	float rads = atan2f(mouse.y, mouse.x);

	// move towards the mouse
	float speed = 0.2f;
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		m_tank->SetBaseRotate(rads);
		float bRads = m_tank->GetBaseRotate();
		m_tank->SetTurretRotate(bRads); 

		float dx = (mouseX - tankPos.x) * speed*deltaTime;
		float dy = (mouseY - tankPos.y) * speed*deltaTime;
		m_tank->Translate({ dx, dy });

		if (abs(sDx - tankPos.x) + abs(sDy - tankPos.y) > 5) {
			TankTracks tt;

			tt.pt = m_tank->GetLocalPosition();
			tt.rotate = m_tank->GetBaseRotate();
			tt.time = 0.0f;

			m_tracks.push_back(tt);
			sDx = tankPos.x;
			sDy = tankPos.y;
		}
	} else {
		// the turret only follows the tank
		m_tank->SetTurretRotate(rads); 
	}

	// clear 'old' tank tracks - first update the timing
	for (auto iter = m_tracks.begin(); iter != m_tracks.end(); ++iter) {
		iter->time += deltaTime;
	}
	// then erase the ones that have been around a while counting backwards
	for (unsigned int k = m_tracks.size(); k--;) {
		if (m_tracks[k].time >= 5.0f) {
			m_tracks.erase(m_tracks.begin()+k);
		}
	}

	// iterator way for counting backwards
	//for (auto iter = m_tracks.end(); iter != m_tracks.begin(); /* Do nothing */)
	//{
	//	--iter; // Unfortunately, you now need this here
	//	/* Do work */
	//}

	// change the location of the tank or rotation your choice
	//if (input->isKeyDown(aie::INPUT_KEY_W))
	//	m_tank->Translate({ 0.f, .1f });
	//if (input->isKeyDown(aie::INPUT_KEY_A))
	//	m_tank->Translate({ -.1f, 0.f });
	//if (input->isKeyDown(aie::INPUT_KEY_S))
	//	m_tank->Translate({ 0.f, -.1f });
	//if (input->isKeyDown(aie::INPUT_KEY_D))
	//	m_tank->Translate({ .1f, 0.f });

	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++)
	{
		(*iter)->Update(deltaTime);
	}
}

void SceneGraphApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_2dRenderer->drawSprite(m_wallPaper, (float)getWindowWidth() / 2, (float)getWindowHeight() / 2, 0, 0, 0, 5.f);

	m_2dRenderer->setRenderColour(0xffffff40);
	for (auto iter = m_tracks.begin(); iter != m_tracks.end(); ++iter) {
		m_2dRenderer->drawSprite(m_tankTracks, iter->pt.x, iter->pt.y, (float)m_tankTracks->getWidth(), (float)m_tankTracks->getHeight(), iter->rotate, 2.f);
	}
	m_2dRenderer->setRenderColour(0xffffffff);

	// loop through the collection of nodes and render everything
	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++) {
		(*iter)->Render(m_2dRenderer);
	}

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}