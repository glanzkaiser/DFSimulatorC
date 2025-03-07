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

#include "settings.h"
#include "test.h"
#include "imgui/imgui.h"
#include <iostream> 

class SpeedDeamplifier : public Test
{
public:
	SpeedDeamplifier()
	{
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-96.0f, 0.0f), b2Vec2(-96.0f, 46.0f));
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
			shape.SetTwoSided(b2Vec2(-96.0f, 0.0f), b2Vec2(46.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		
			// Create the box as the movable object with friction 0
			b2PolygonShape boxShape;
			boxShape.SetAsBox(0.5f, 0.5f);
			
			b2FixtureDef boxFixtureDef;
			boxFixtureDef.restitution = 0.75f;
			boxFixtureDef.density = 2.4f; // this will affect the box mass
			boxFixtureDef.friction = 0.0f;
			boxFixtureDef.shape = &boxShape;
			
			b2BodyDef boxBodyDef;
			boxBodyDef.type = b2_dynamicBody;
			boxBodyDef.position.Set(0.0f, 0.5f);

			m_box = m_world->CreateBody(&boxBodyDef);
			b2Fixture *boxFixture = m_box->CreateFixture(&boxFixtureDef);
	
			// Create the box 2 with friction 0.0
			b2PolygonShape boxShape2;
			boxShape2.SetAsBox(1.0f, 1.0f);
			
			b2FixtureDef boxFixtureDef2;
			boxFixtureDef2.restitution = 0.75f;
			boxFixtureDef2.density = 1.2f; // this will affect the box mass
			boxFixtureDef2.friction = 0.0f;
			boxFixtureDef2.shape = &boxShape2;
			
			b2BodyDef boxBodyDef2;
			boxBodyDef2.type = b2_dynamicBody;
			boxBodyDef2.position.Set(5.0f, 0.5f);

			m_box2 = m_world->CreateBody(&boxBodyDef2);
			b2Fixture *boxFixture2 = m_box2->CreateFixture(&boxFixtureDef2);

			// Create the box 3 with friction 0.0
			b2PolygonShape boxShape3;
			boxShape3.SetAsBox(2.0f, 2.0f);
			
			b2FixtureDef boxFixtureDef3;
			boxFixtureDef3.restitution = 0.75f;
			boxFixtureDef3.density = 0.6f; // this will affect the box mass
			boxFixtureDef3.friction = 0.0f;
			boxFixtureDef3.shape = &boxShape3;
			
			b2BodyDef boxBodyDef3;
			boxBodyDef3.type = b2_dynamicBody;
			boxBodyDef3.position.Set(10.0f, 0.5f);

			m_box3 = m_world->CreateBody(&boxBodyDef3);
			b2Fixture *boxFixture3 = m_box3->CreateFixture(&boxFixtureDef3);
			m_time = 0.0f;	
	}
	b2Body* m_box;
	b2Body* m_box2;
	b2Body* m_box3;
	float m_time;

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_D:
			m_box->SetLinearVelocity(b2Vec2(4.0f, 0.0f));		
			break;
		case GLFW_KEY_G:
			m_box->ApplyForceToCenter(b2Vec2(500.0f, 0.0f), true);			
			break;
		}
	}
	void Step(Settings& settings) override
	{		
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		b2MassData massData1 = m_box->GetMassData();
		b2MassData massData2 = m_box2->GetMassData();
		b2MassData massData3 = m_box3->GetMassData();
		b2Vec2 position1 = m_box->GetPosition();
		b2Vec2 position2 = m_box2->GetPosition();
		b2Vec2 position3 = m_box3->GetPosition();
		b2Vec2 velocity1 = m_box->GetLinearVelocity();
		b2Vec2 velocity2 = m_box2->GetLinearVelocity();
		b2Vec2 velocity3 = m_box3->GetLinearVelocity();
		
		g_debugDraw.DrawString(5, m_textLine, "Press D to set the box velocity into 4 m/s");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press G to move the box with Force of 500 N");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box 1 position = (%4.1f, %4.1f)", position1.x, position1.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box 1 velocity = (%4.1f, %4.1f)", velocity1.x, velocity1.y);
		m_textLine += m_textIncrement;
		
		g_debugDraw.DrawString(5, m_textLine, "Box 2 position = (%4.1f, %4.1f)", position2.x, position2.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box 2 velocity = (%4.1f, %4.1f)", velocity2.x, velocity2.y);
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "Box 3 position = (%4.1f, %4.1f)", position3.x, position3.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box 3 velocity = (%4.1f, %4.1f)", velocity3.x, velocity3.y);
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "Box 1 Mass = %4.2f", massData1.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box 2 Mass = %4.2f", massData2.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box 3 Mass = %4.2f", massData3.mass);
		m_textLine += m_textIncrement;
		Test::Step(settings);
		
		printf("%4.2f %4.2f %4.2f %4.2f %4.2f %4.2f \n", position1.x, position2.x, position3.x, velocity1.x, velocity2.x, velocity3.x);	
	}
	static Test* Create()
	{
		return new SpeedDeamplifier;
	}
	
};

static int testIndex = RegisterTest("Center of Mass", "Speed Deamplifier", SpeedDeamplifier::Create);
