// MIT License

// Copyright (c) 2019 Erin Catto

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#define DEGTORAD 0.0174532925199432957f
#include "settings.h"
#include "test.h"
#include "imgui/imgui.h"
#include <iostream> 

class FrictionalForces : public Test
{
public:
	FrictionalForces()
	{
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-46.0f, 0.0f), b2Vec2(-46.0f, 46.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(46.0f, 0.0f), b2Vec2(46.0f, 46.0f));
			ground->CreateFixture(&shape, 0.0f);
		}		
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-46.0f, 0.0f), b2Vec2(46.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
			// Create the box as the movable object with friction 0.3
			b2PolygonShape boxShape;
			boxShape.SetAsBox(0.5f, 0.5f);
			
			b2FixtureDef boxFixtureDef;
			boxFixtureDef.restitution = 0.75f;
			boxFixtureDef.density = 3.3f; // this will affect the box mass
			boxFixtureDef.friction = 0.3f;
			boxFixtureDef.shape = &boxShape;
			
			b2BodyDef boxBodyDef;
			boxBodyDef.type = b2_dynamicBody;
			boxBodyDef.position.Set(5.0f, 0.5f);

			m_box = m_world->CreateBody(&boxBodyDef);
			b2Fixture *boxFixture = m_box->CreateFixture(&boxFixtureDef);
	
			m_time = 0.0f;	
	}
	b2Body* m_box;
	float m_time;
	float F = 50.0f;
	int theta = 30;
	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_A:
			m_box->ApplyForceToCenter(b2Vec2(F*cosf(theta*DEGTORAD), F*sinf(theta*DEGTORAD)), true);			
			break;
		case GLFW_KEY_S:
			m_box->ApplyForceToCenter(b2Vec2(50.0f, 0.0f), true);					
			break;
		case GLFW_KEY_D:
			m_box->ApplyForceToCenter(b2Vec2(100.0f, 0.0f), true);			
			break;
		case GLFW_KEY_F:
			m_box->ApplyForceToCenter(b2Vec2(150.0f, 0.0f), true);					
			break;
		case GLFW_KEY_G:
			m_box->ApplyForceToCenter(b2Vec2(250.0f, 0.0f), true);			
			break;
		}
	}
	void Step(Settings& settings) override
	{		
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		b2MassData massData = m_box->GetMassData();
		b2Vec2 position = m_box->GetPosition();
		b2Vec2 velocity1 = m_box->GetLinearVelocity();
		float m = massData.mass;
		float fs_max = (0.3 * m * 9.8) + (F*sinf(theta*DEGTORAD));

		g_debugDraw.DrawString(5, m_textLine, "Press A to push the box with magnitude 50 N at a downward angle of 30 degree");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press S, D, F, G to push the box with magnitude 50 N, 100 N, 150 N, 250 N respectively, with direction toward positive x axis");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "The maximum static frictional force (f_{s,max})= %.6f", fs_max);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box 1 position = (%4.1f, %4.1f)", position.x, position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box 1 velocity = (%4.1f, %4.1f)", velocity1.x, velocity1.y);
		m_textLine += m_textIncrement;
		
		g_debugDraw.DrawString(5, m_textLine, "Box Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		Test::Step(settings);
		
		printf("%4.2f %4.2f \n", velocity1.x, velocity1.y);	
	}
	static Test* Create()
	{
		return new FrictionalForces;
	}
	
};

static int testIndex = RegisterTest("Force and Motion", "Frictional Forces", FrictionalForces::Create);
