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

class BaseballBasketball: public Test
{
public:

	BaseballBasketball()
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
			shapeTop.SetTwoSided(b2Vec2(-40.0f, 60.0f), b2Vec2(30.0f, 60.0f));
			ground->CreateFixture(&shapeTop, 0.0f);

			b2EdgeShape shapeLeft;
			shapeLeft.SetTwoSided(b2Vec2(-40.0f, 0.0f), b2Vec2(-40.0f, 60.0f));
			ground->CreateFixture(&shapeLeft, 0.0f);
			
			b2EdgeShape shapeRight;
			shapeRight.SetTwoSided(b2Vec2(30.0f, 0.0f), b2Vec2(30.0f, 60.0f));
			ground->CreateFixture(&shapeRight, 0.0f);
		}

		// Create the basketball
		b2CircleShape ballShape;
		ballShape.m_p.SetZero();
		ballShape.m_radius = 1.5f;
		
		b2FixtureDef ballFixtureDef;
		ballFixtureDef.restitution = 0.75f; // the bounciness
		ballFixtureDef.density = 0.09f; // this will affect the ball mass
		ballFixtureDef.friction = 0.1f;
		ballFixtureDef.shape = &ballShape;
		
		b2BodyDef ballBodyDef;
		ballBodyDef.type = b2_dynamicBody;
		ballBodyDef.position.Set(0.0f, 25.0f);
		// ballBodyDef.angularDamping = 0.2f;

		m_ball = m_world->CreateBody(&ballBodyDef);
		b2Fixture *ballFixture = m_ball->CreateFixture(&ballFixtureDef);		

		// Create the baseball
		b2CircleShape ballShape2;
		ballShape2.m_p.SetZero();
		ballShape2.m_radius = 0.5f;
		
		b2FixtureDef ballFixtureDef2;
		ballFixtureDef2.restitution = 0.75f; // the bounciness
		ballFixtureDef2.density = 0.27f; // this will affect the ball mass
		ballFixtureDef2.friction = 0.1f;
		ballFixtureDef2.shape = &ballShape2;
		
		b2BodyDef ballBodyDef2;
		ballBodyDef2.type = b2_dynamicBody;
		ballBodyDef2.position.Set(0.0f, 30.0f);
		// ballBodyDef2.angularDamping = 0.2f;

		m_ball2 = m_world->CreateBody(&ballBodyDef2);
		b2Fixture *ballFixture2 = m_ball2->CreateFixture(&ballFixtureDef2);	
	
		m_createTime = timer.GetMilliseconds();		
		m_time = 0.0f;
	}
	b2Body* bodylbox;
	b2Body* m_ball;
	b2Body* m_ball2;
	float m_time;

	void Step(Settings& settings) override
	{	
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %4.2f", m_time);
		m_textLine += m_textIncrement;
		
		b2MassData massData2 = m_ball2->GetMassData();
		b2Vec2 position2 = m_ball2->GetPosition();
		
		g_debugDraw.DrawString(5, m_textLine, "Baseball Mass = %.6f", massData2.mass);
		m_textLine += m_textIncrement;		
		g_debugDraw.DrawString(5, m_textLine, "Baseball Position = (%4.2f, %4.2f)", position2.x, position2.y);
		m_textLine += m_textIncrement;

		b2MassData massData = m_ball->GetMassData();
		b2Vec2 position = m_ball->GetPosition();

		g_debugDraw.DrawString(5, m_textLine, "Basketball Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Basketball Position = (%4.2f, %4.2f)", position.x, position.y);
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "create time = %6.2f ms",
			m_createTime);
		m_textLine += m_textIncrement;

		printf("%4.2f %4.2f \n", position2.y, position.y);

		Test::Step(settings);
	}

	static Test* Create()
	{
		return new BaseballBasketball;
		
	}
	
	float m_createTime;
};

static int testIndex = RegisterTest("Center of Mass", "Baseball Basketball", BaseballBasketball::Create);
