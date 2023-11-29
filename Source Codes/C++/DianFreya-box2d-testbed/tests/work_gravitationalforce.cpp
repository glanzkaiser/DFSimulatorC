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
#include <iostream> 
#include "test.h"

class WorkGravitationalforce : public Test
{
public:
	WorkGravitationalforce()
	{
		m_world->SetGravity(b2Vec2(0.0f,-9.8f));
		float L = 10.0f;
		float a = 1.0f;
		float b = 1.5f;
		m_world->SetGravity(b2Vec2(0.0f,-9.8f));
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-46.0f,0.0f), b2Vec2(46.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(0.0f,8.0f), b2Vec2(46.0f, 8.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		{// Create the pulley
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2CircleShape circle;
			circle.m_radius = 1.0f;

			circle.m_p.Set(0.0f,  b + L);  // circle with center of (0,b+L)
			ground->CreateFixture(&circle, 0.0f);
		}
		// Create the triangle
		b2ChainShape chainShape;
		b2Vec2 vertices[] = {b2Vec2(-17.3205,0), b2Vec2(0,0), b2Vec2(0,10)};
		chainShape.CreateLoop(vertices, 3);

		b2FixtureDef groundFixtureDef;
		groundFixtureDef.density = 0;
		groundFixtureDef.shape = &chainShape;

		b2BodyDef groundBodyDef;
		groundBodyDef.type = b2_staticBody;

		b2Body *groundBody = m_world->CreateBody(&groundBodyDef);
		b2Fixture *groundBodyFixture = groundBody->CreateFixture(&groundFixtureDef);

		{
			// Create the sack on a triangle
			b2PolygonShape boxShape;
			boxShape.SetAsBox(a, b); // width and length of the box
			
			b2FixtureDef boxFixtureDef;
			boxFixtureDef.restitution = 0.75f;
			boxFixtureDef.density = 8.334f; // this will affect the box mass
			boxFixtureDef.friction = 0.0f; // frictionless plane
			boxFixtureDef.shape = &boxShape;
			
			b2BodyDef boxBodyDef;
			boxBodyDef.type = b2_dynamicBody;
			boxBodyDef.position.Set(-17.0f, 0.5);
			// boxBodyDef.fixedRotation = true;

			m_boxl = m_world->CreateBody(&boxBodyDef);
			b2Fixture *boxFixture = m_boxl->CreateFixture(&boxFixtureDef);
			
			// Create the box hanging on the right
			b2PolygonShape boxShape2;
			boxShape2.SetAsBox(a, b); // width and length of the box
			
			b2FixtureDef boxFixtureDef2;
			boxFixtureDef2.restitution = 0.75f;
			boxFixtureDef2.density = 16.667f; // this will affect the box mass, mass = density*5.9969
			boxFixtureDef2.friction = 0.3f;
			boxFixtureDef2.shape = &boxShape2;
			
			b2BodyDef boxBodyDef2;
			boxBodyDef2.type = b2_dynamicBody;
			boxBodyDef2.position.Set(3.0f, L);
			// boxBodyDef2.fixedRotation = true;

			m_boxr = m_world->CreateBody(&boxBodyDef2);
			b2Fixture *boxFixture2 = m_boxr->CreateFixture(&boxFixtureDef2);

			// Create the Pulley 
			b2PulleyJointDef pulleyDef;
			b2Vec2 anchor1(-16.0f, 0.5f); // the position of the end string of the left cord to connect to the sack
			b2Vec2 anchor2(2.0f, L); // the position of the end string of the right cord to connect to the right puller
			b2Vec2 groundAnchor1(-1.0f, b + L ); // the string of the cord is tightened at (-1.0f, b+L)
			b2Vec2 groundAnchor2(1.5f,  b + L);  // the string of the cord is tightened at (1.5f, b+L)
			// the last float is the ratio
			pulleyDef.Initialize(m_boxl, m_boxr, groundAnchor1, groundAnchor2, anchor1, anchor2, 1.0f);
			
			m_joint1 = (b2PulleyJoint*)m_world->CreateJoint(&pulleyDef);
		}
	}
	b2Body* m_boxl;
	b2Body* m_boxr;
	float F1 = 50.0f;
	int theta = 30;
	b2PulleyJoint* m_joint1;
	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_D:
			m_boxr->ApplyForceToCenter(b2Vec2(20000.0f, 0.0f), true);			
			break;
		case GLFW_KEY_F:
			m_boxr->SetLinearVelocity(b2Vec2(14.0f, 0.0f));					
			break;
		case GLFW_KEY_G:
			for (int i = 0; i <= 46.0f; ++i)
			{
			m_boxl->ApplyForceToCenter(b2Vec2(F1*i*cosf(theta*DEGTORAD), 0.0f), true);	// resulting in same work for 46 meter displacement		
			}			
			break;
		}
	}
	void Step(Settings& settings) override
	{
		Test::Step(settings);
		b2MassData massData1 = m_boxl->GetMassData();
		b2Vec2 position1 = m_boxl->GetPosition();
		b2Vec2 velocity1 = m_boxl->GetLinearVelocity();
		b2MassData massData2 = m_boxr->GetMassData();
		b2Vec2 position2 = m_boxr->GetPosition();
		b2Vec2 velocity2 = m_boxr->GetLinearVelocity();
		float m1 = massData1.mass;
		float m2 = massData2.mass;
		float g = 9.8f;

		float ke1 = 0.5*m1*((velocity1.x)*(velocity1.x));
		float ke2 = 0.5*m2*((velocity2.x)*(velocity2.x));
		float a = (m2-m1*sinf(30*DEGTORAD))*g / (m1+m2);
		float T = (m1*a) + (m1*g*sinf(30*DEGTORAD));
		
		g_debugDraw.DrawString(5, m_textLine, "Press D to pull the sack with force of 20,000 N");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press F to pull the sack with linear velocity of 14 m/s");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press G to push the sack with force of 50 N");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Left Box position = (%4.1f, %4.1f)", position1.x, position1.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Left Box velocity = (%4.1f, %4.1f)", velocity1.x, velocity1.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Left Box Mass = %.6f", massData1.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Left Box Kinetic Energy = %.6f", ke1);
		m_textLine += m_textIncrement;
		
		g_debugDraw.DrawString(5, m_textLine, "Right Box position = (%4.1f, %4.1f)", position2.x, position2.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Right Box velocity = (%4.1f, %4.1f)", velocity2.x, velocity2.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Right Box Mass = %.6f", massData2.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Right Box Kinetic Energy = %.6f", ke2);
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "Acceleration = %.6f", a);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "The tension of the cord = %.6f", T);
		m_textLine += m_textIncrement;

		float ratio = m_joint1->GetRatio();
		float L = m_joint1->GetCurrentLengthA() + ratio * m_joint1->GetCurrentLengthB();
		g_debugDraw.DrawString(5, m_textLine, "L1 + %4.2f * L2 = %4.2f", (float) ratio, (float) L);
		m_textLine += m_textIncrement;

		printf("%4.2f %4.2f %4.2f %4.2f \n", position1.y, position2.x, ke1, ke2);
	}

	static Test* Create()
	{
		return new WorkGravitationalforce;
	}
};

static int testIndex = RegisterTest("Kinetic Energy and Work", "Gravitational Force", WorkGravitationalforce::Create);
