#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "vector_2.h"
#include "edge.h"
#include "graph.h"
#include "node.h"

#include <queue>

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Texture*		m_face;

	std::queue<node<vector_2>*>	m_selection_queue;

	graph<vector_2>*	m_graph;


	float m_timer;
};