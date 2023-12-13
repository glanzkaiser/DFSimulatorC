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
#include "test.h"

class ConveyorBelt : public Test
{
public:

	ConveyorBelt()
	{
		// Ground
		{
			b2BodyDef bd;
			b2Body* ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-20.0f, 0.0f), b2Vec2(108.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}

		// First Horizontal Platform
		{
			b2BodyDef bd;
			bd.position.Set(-9.0f, 4.6f);
			b2Body* body = m_world->CreateBody(&bd);

			b2PolygonShape shape;
			shape.SetAsBox(10.0f, 0.5f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.friction = 0.1f;
			m_platform = body->CreateFixture(&fd);
		}
		// Second Horizontal Platform
		{
			b2BodyDef bd;
			bd.position.Set(33.650578f, 8.5f);
			b2Body* body = m_world->CreateBody(&bd);

			b2PolygonShape shape;
			shape.SetAsBox(10.0f, 0.5f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.friction = 0.1f;
			m_platform4 = body->CreateFixture(&fd);
		}
		// Third Horizontal Platform
		{
			b2BodyDef bd;
			bd.position.Set(75.650578f, 4.6f);
			b2Body* body = m_world->CreateBody(&bd);

			b2PolygonShape shape;
			shape.SetAsBox(10.0f, 0.5f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.friction = 0.1f;
			m_platform5 = body->CreateFixture(&fd);
		}
		
		// The first incline
		{
			b2ChainShape chainShape;
			b2Vec2 vertices[] = {b2Vec2(1,5), b2Vec2(23.650578,5), b2Vec2(23.650578,8.9939)};
			chainShape.CreateLoop(vertices, 3);

			b2FixtureDef groundFixtureDef;
			groundFixtureDef.density = 0;
			groundFixtureDef.friction = 0.1f;
			groundFixtureDef.shape = &chainShape;

			b2BodyDef groundBodyDef;
			groundBodyDef.type = b2_staticBody;

			b2Body *groundBody = m_world->CreateBody(&groundBodyDef);
			m_platform2 = groundBody->CreateFixture(&groundFixtureDef);
		}
		// The decline triangle
		{
			b2ChainShape chainShape;
			b2Vec2 vertices[] = {b2Vec2(43.6,5), b2Vec2(66.250578,5), b2Vec2(43.6,8.9939)};
			chainShape.CreateLoop(vertices, 3);

			b2FixtureDef groundFixtureDef;
			groundFixtureDef.density = 0;
			groundFixtureDef.friction = 0.1f;
			groundFixtureDef.shape = &chainShape;

			b2BodyDef groundBodyDef;
			groundBodyDef.type = b2_staticBody;

			b2Body *groundBody = m_world->CreateBody(&groundBodyDef);
			m_platform3 = groundBody->CreateFixture(&groundFixtureDef);
		}
		// Boxes
		for (int32 i = 0; i < 5; ++i)
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-10.0f + 2.0f * i, 7.0f);
			body = m_world->CreateBody(&bd);

			b2PolygonShape shape;
			shape.SetAsBox(0.5f, 0.5f);
			b2FixtureDef boxFixtureDef1;
			boxFixtureDef1.restitution = 0.0f;
			boxFixtureDef1.density = 2.0f; // this will affect the mass
			boxFixtureDef1.friction = 0.5f;
			boxFixtureDef1.shape = &shape;
			b2Fixture *boxFixture1 = body->CreateFixture(&boxFixtureDef1);
			
		}
		m_time = 0.0f;
	}
	b2Body* body;
	b2Fixture* m_platform;
	b2Fixture* m_platform2;
	b2Fixture* m_platform3;
	b2Fixture* m_platform4;
	b2Fixture* m_platform5;
	float m_time;
	bool m_fixed_camera;
	
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override
	{
		Test::PreSolve(contact, oldManifold);

		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA == m_platform)
		{
			contact->SetTangentSpeed(5.0f);
		}

		if (fixtureB == m_platform)
		{
			contact->SetTangentSpeed(-5.0f);
		}

		if (fixtureA == m_platform2)
		{
			contact->SetTangentSpeed(5.0f);
		}
		if (fixtureB == m_platform2)
		{
			contact->SetTangentSpeed(-5.0f);
		}
		
		if (fixtureA == m_platform3)
		{
			contact->SetTangentSpeed(5.0f);
		}
		if (fixtureB == m_platform3)
		{
			contact->SetTangentSpeed(-5.0f);
		}

		if (fixtureA == m_platform4)
		{
			contact->SetTangentSpeed(5.0f);
		}
		if (fixtureB == m_platform4)
		{
			contact->SetTangentSpeed(-5.0f);
		}

		if (fixtureA == m_platform5)
		{
			contact->SetTangentSpeed(0.0f);
		}
		if (fixtureB == m_platform5)
		{
			contact->SetTangentSpeed(0.0f);
		}
		
	}
	void Keyboard(int key) override
	{
		switch (key)
		{
			case GLFW_KEY_C:
			m_fixed_camera = !m_fixed_camera;
			if(m_fixed_camera)
			{
				g_camera.m_center = b2Vec2(3.0f, 10.0f);
				g_camera.m_zoom = 1.7f; // zoom out camera
			}
			break;
		}
	}
	void Step(Settings& settings) override
	{
		Test::Step(settings);
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		b2MassData massData1 = body->GetMassData();
		b2Vec2 position1 = body->GetPosition();
		b2Vec2 velocity1 = body->GetLinearVelocity();
		float m = massData1.mass;
		float g = 9.8f;
		float v = 0.5;
		float P1 = m*g*cos(80*DEGTORAD)*v;
		float P2 = m*g*cos(90*DEGTORAD)*v;
		float P3 = m*g*cos(100*DEGTORAD)*v;

		g_debugDraw.DrawString(5, m_textLine, "Press C = Camera fixed/tracking");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box position = (%4.1f, %4.1f)", position1.x, position1.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box velocity = (%4.1f, %4.1f)", velocity1.x, velocity1.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box Mass = %4.2f", massData1.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Power at First Inclination = %4.2f", P1);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Power at Horizontal Platform = %4.2f", P2);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Power at Downward Inclination = %4.2f", P3);
		m_textLine += m_textIncrement;

		if(!m_fixed_camera)
		{
			g_camera.m_center = body->GetPosition();
			g_camera.m_zoom = 1.7f; // zoom out camera
		}
	}

	static Test* Create()
	{
		return new ConveyorBelt;
	}

	
};

static int testIndex = RegisterTest("Kinetic Energy and Work", "Conveyor Belt", ConveyorBelt::Create);
