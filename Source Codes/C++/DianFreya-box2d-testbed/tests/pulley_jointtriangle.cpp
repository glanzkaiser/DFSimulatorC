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

class PulleyJointTriangle : public Test
{
public:
	PulleyJointTriangle()
	{
		m_world->SetGravity(b2Vec2(0.0f,-9.8f));
		float L = 10.0f;
		float a = 1.0f;
		float b = 1.5f;
		
		b2Body* ground = NULL;
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
			// Create the box on a triangle
			b2PolygonShape boxShape;
			boxShape.SetAsBox(a, b); // width and length of the box
			
			b2FixtureDef boxFixtureDef;
			boxFixtureDef.restitution = 0.75f;
			boxFixtureDef.density = 0.616985f; // this will affect the box mass
			boxFixtureDef.friction = 0.0f; // frictionless plane
			boxFixtureDef.shape = &boxShape;
			
			b2BodyDef boxBodyDef;
			boxBodyDef.type = b2_dynamicBody;
			boxBodyDef.position.Set(-3.0f, L);
			// boxBodyDef.fixedRotation = true;

			m_boxl = m_world->CreateBody(&boxBodyDef);
			b2Fixture *boxFixture = m_boxl->CreateFixture(&boxFixtureDef);
			
			// Create the box hanging on the right
			b2PolygonShape boxShape2;
			boxShape2.SetAsBox(a, b); // width and length of the box
			
			b2FixtureDef boxFixtureDef2;
			boxFixtureDef2.restitution = 0.75f;
			boxFixtureDef2.density = 0.3835f; // this will affect the box mass, mass = density*5.9969
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
			b2Vec2 anchor1(-3.0f, L-1.5f); // the position of the end string of the left cord is (-3.0f, L-1.5)
			b2Vec2 anchor2(2.0f, L); // the position of the end string of the right cord is (2.0f, L)
			b2Vec2 groundAnchor1(-1.0f, b + L ); // the string of the cord is tightened at (-1.0f, b+L)
			b2Vec2 groundAnchor2(1.5f,  b + L);  // the string of the cord is tightened at (1.5f, b+L)
			// the last float is the ratio
			pulleyDef.Initialize(m_boxl, m_boxr, groundAnchor1, groundAnchor2, anchor1, anchor2, 1.0f);
			
			m_joint1 = (b2PulleyJoint*)m_world->CreateJoint(&pulleyDef);
		}
	}
	b2Body* m_boxl;
	b2Body* m_boxr;
	b2PulleyJoint* m_joint1;

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
		
		float a = (m2-m1*sinf(30*DEGTORAD))*g / (m1+m2);
		float T = (m1*a) + (m1*g*sinf(30*DEGTORAD));
		
		g_debugDraw.DrawString(5, m_textLine, "Left Box position = (%4.1f, %4.1f)", position1.x, position1.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Left Box velocity = (%4.1f, %4.1f)", velocity1.x, velocity1.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Left Box Mass = %.6f", massData1.mass);
		m_textLine += m_textIncrement;
		
		g_debugDraw.DrawString(5, m_textLine, "Right Box position = (%4.1f, %4.1f)", position2.x, position2.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Right Box velocity = (%4.1f, %4.1f)", velocity2.x, velocity2.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Right Box Mass = %.6f", massData2.mass);
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "Acceleration = %.6f", a);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "The tension of the cord = %.6f", T);
		m_textLine += m_textIncrement;

		float ratio = m_joint1->GetRatio();
		float L = m_joint1->GetCurrentLengthA() + ratio * m_joint1->GetCurrentLengthB();
		g_debugDraw.DrawString(5, m_textLine, "L1 + %4.2f * L2 = %4.2f", (float) ratio, (float) L);
		m_textLine += m_textIncrement;
	}

	static Test* Create()
	{
		return new PulleyJointTriangle;
	}
};

static int testIndex = RegisterTest("Force and Motion", "Pulley Tension 1", PulleyJointTriangle::Create);
