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

class KineticenergyWork : public Test
{
public:
	KineticenergyWork()
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
			// Create the cutting tool going to positive x axis
			b2PolygonShape boxShape;
			boxShape.SetAsBox(0.5f, 0.5f);
			
			b2FixtureDef boxFixtureDef;
			boxFixtureDef.restitution = 0.75f;
			boxFixtureDef.density = 230.0f; // this will affect the box mass
			boxFixtureDef.friction = 0.0f; // frictionless
			boxFixtureDef.shape = &boxShape;
			
			b2BodyDef boxBodyDef;
			boxBodyDef.type = b2_dynamicBody;
			boxBodyDef.position.Set(-23.0f, 0.5f);

			m_box = m_world->CreateBody(&boxBodyDef);
			b2Fixture *boxFixture = m_box->CreateFixture(&boxFixtureDef);
			//m_box->SetLinearVelocity(b2Vec2(40.8f, 0.0f));
		
			m_time = 0.0f;	
	}
	b2Body* m_box;
	float m_time;
	float F1 = 30.0f;
	float F2 = 24.0f;
	float d = 46.0f;
	int theta = 30;
	int theta2 = 33;
	
	float fsum = F1*d*cosf(theta*DEGTORAD) + F2*d*cosf(theta2*DEGTORAD);
	float vf = sqrt(2*fsum/230);
	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_D:
			for (int i = 0; i <= 46.0f; ++i)
			{
			//m_box->ApplyForceToCenter(b2Vec2(2121.0f, 0.0f), true);			
			m_box->ApplyForceToCenter(b2Vec2(F1*i*cosf(theta*DEGTORAD) + F2*i*cosf(theta2*DEGTORAD), 0.0f), true);	// resulting in same work for 46 meter displacement		
			}			
			break;
		case GLFW_KEY_F:
			m_box->SetLinearVelocity(b2Vec2(vf, 0.0f));					
			break;
		case GLFW_KEY_G:
			b2Vec2 f = m_box->GetWorldVector(b2Vec2(2121.0f, 0.0f));
			b2Vec2 p = m_box->GetWorldPoint(b2Vec2(2121.0f, 0.0f));
			m_box->ApplyForce(f, p, true);				
			break;
		}
	}
	void Step(Settings& settings) override
	{		
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		b2MassData massData = m_box->GetMassData();
		b2Vec2 position = m_box->GetPosition();
		b2Vec2 velocity = m_box->GetLinearVelocity();
		
		g_debugDraw.DrawString(5, m_textLine, "Press D to make the cutting tool move toward positive x axis with force");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press F to make the cutting tool move toward positive x axis with constant velocity");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Cutting tool position = (%4.1f, %4.1f)", position.x, position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Cutting tool velocity = (%4.1f, %4.1f)", velocity.x, velocity.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Work done to move the cutting tool 46 meter = %.4f", fsum);
		m_textLine += m_textIncrement;
				
		g_debugDraw.DrawString(5, m_textLine, "Cutting tool Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		
		Test::Step(settings);
		
		printf("%4.2f %4.2f  \n", position.x, position.y);	
	}
	static Test* Create()
	{
		return new KineticenergyWork;
	}
	
};

static int testIndex = RegisterTest("Kinetic Energy and Work", "Kinetic Energy: Work", KineticenergyWork::Create);
