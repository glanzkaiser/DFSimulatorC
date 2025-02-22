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

#include "test.h"
#include <iostream> 

class CenterofMassThreeParticles: public Test
{
public:

	CenterofMassThreeParticles()
	{
		m_world->SetGravity(b2Vec2(0.0f,-9.8f));
		b2Timer timer;
		// Perimeter Ground body
		{
			b2BodyDef bd;
			b2Body* ground = m_world->CreateBody(&bd);

			b2EdgeShape shapeGround;
			shapeGround.SetTwoSided(b2Vec2(-40.0f, 0.0f), b2Vec2(30.0f, 0.0f));
			ground->CreateFixture(&shapeGround, 0.0f);
			
			b2EdgeShape shapeTop;
			shapeTop.SetTwoSided(b2Vec2(-40.0f, 30.0f), b2Vec2(30.0f, 30.0f));
			ground->CreateFixture(&shapeTop, 0.0f);

			b2EdgeShape shapeLeft;
			shapeLeft.SetTwoSided(b2Vec2(-40.0f, 0.0f), b2Vec2(-40.0f, 30.0f));
			ground->CreateFixture(&shapeLeft, 0.0f);
			
			b2EdgeShape shapeRight;
			shapeRight.SetTwoSided(b2Vec2(30.0f, 0.0f), b2Vec2(30.0f, 30.0f));
			ground->CreateFixture(&shapeRight, 0.0f);
		}

		// Create the first particle
		b2CircleShape ballShape;
		ballShape.m_p.SetZero();
		ballShape.m_radius = 0.5f;
		
		b2FixtureDef ballFixtureDef;
		ballFixtureDef.restitution = 0.75f; // the bounciness
		ballFixtureDef.density = 3.3f; // this will affect the ball mass
		ballFixtureDef.friction = 0.1f;
		ballFixtureDef.shape = &ballShape;
		
		b2BodyDef ballBodyDef;
		ballBodyDef.type = b2_dynamicBody;
		ballBodyDef.position.Set(-10.0f, 25.0f);
		// ballBodyDef.angularDamping = 0.2f;

		m_ball = m_world->CreateBody(&ballBodyDef);
		b2Fixture *ballFixture = m_ball->CreateFixture(&ballFixtureDef);	
		
		// Create the second particle
		b2CircleShape ballShape2;
		ballShape2.m_p.SetZero();
		ballShape2.m_radius = 0.5f;
		
		b2FixtureDef ballFixtureDef2;
		ballFixtureDef2.restitution = 0.75f; // the bounciness
		ballFixtureDef2.density = 7.3f; // this will affect the ball mass
		ballFixtureDef2.friction = 0.1f;
		ballFixtureDef2.shape = &ballShape2;
		
		b2BodyDef ballBodyDef2;
		ballBodyDef2.type = b2_dynamicBody;
		ballBodyDef2.position.Set(0.0f, 25.0f);
		// ballBodyDef2.angularDamping = 0.2f;

		m_ball2 = m_world->CreateBody(&ballBodyDef2);
		b2Fixture *ballFixture2 = m_ball2->CreateFixture(&ballFixtureDef2);	

		// Create the third particle
		b2CircleShape ballShape3;
		ballShape3.m_p.SetZero();
		ballShape3.m_radius = 1.5f;
		
		b2FixtureDef ballFixtureDef3;
		ballFixtureDef3.restitution = 0.45f; // the bounciness
		ballFixtureDef3.density = 2.3f; // this will affect the ball mass
		ballFixtureDef3.friction = 0.1f;
		ballFixtureDef3.shape = &ballShape2;
		
		b2BodyDef ballBodyDef3;
		ballBodyDef3.type = b2_dynamicBody;
		ballBodyDef3.position.Set(20.0f, 25.0f);
		// ballBodyDef3.angularDamping = 0.2f;

		m_ball3 = m_world->CreateBody(&ballBodyDef3);
		b2Fixture *ballFixture3 = m_ball3->CreateFixture(&ballFixtureDef3);	
				
		m_createTime = timer.GetMilliseconds();		
	}
	b2Body* bodylbox;
	b2Body* m_ball;
	b2Body* m_ball2;
	b2Body* m_ball3;
	
	void Step(Settings& settings) override
	{	
		b2MassData massData = m_ball->GetMassData();
		b2Vec2 position = m_ball->GetPosition();
		b2MassData massData2 = m_ball2->GetMassData();
		b2Vec2 position2 = m_ball2->GetPosition();
		b2MassData massData3 = m_ball3->GetMassData();
		b2Vec2 position3 = m_ball3->GetPosition();
		
		float xcom = (1/(massData.mass+massData2.mass+massData3.mass)) * (massData.mass*position.x + massData2.mass*position2.x + massData3.mass*position3.x);
		float ycom = (1/(massData.mass+massData2.mass+massData3.mass)) * (massData.mass*position.y + massData2.mass*position2.y + massData3.mass*position3.y);

		g_debugDraw.DrawString(5, m_textLine, "First Particle Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "First Particle Position, x = %.6f", position.x);		
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "First Particle Position, y = %.6f", position.y);
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "Second Particle Mass = %.6f", massData2.mass);
		m_textLine += m_textIncrement;		
		g_debugDraw.DrawString(5, m_textLine, "Second Particle Position, x = %.6f", position2.x);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Second Particle Position, y = %.6f", position2.y);
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "Third Particle Mass = %.6f", massData3.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Third Particle Position, x = %.6f", position3.x);		
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Third Particle Position, y = %.6f", position3.y);
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "x_{com} = %.6f", xcom);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "y_{com} = %.6f", ycom);
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "create time = %6.2f ms", m_createTime);
		m_textLine += m_textIncrement;

		printf("%4.2f %4.2f \n", xcom, ycom);

		Test::Step(settings);
	}

	static Test* Create()
	{
		return new CenterofMassThreeParticles;
		
	}
	
	float m_createTime;
};

static int testIndex = RegisterTest("Center of Mass", "Three Particles", CenterofMassThreeParticles::Create);
