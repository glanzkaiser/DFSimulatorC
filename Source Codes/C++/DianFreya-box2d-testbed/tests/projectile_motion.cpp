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

class ProjectileMotion: public Test
{
public:

	ProjectileMotion()
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
		
		// Create the ball
		b2CircleShape ballShape;
		ballShape.m_p.SetZero();
		ballShape.m_radius = 0.5f;
		
		b2FixtureDef ballFixtureDef;
		ballFixtureDef.restitution = 0.15f; // the bounciness
		ballFixtureDef.density = 7.3f; // this will affect the ball mass
		ballFixtureDef.friction = 0.1f;
		ballFixtureDef.shape = &ballShape;
		
		b2BodyDef ballBodyDef;
		ballBodyDef.type = b2_dynamicBody;
		ballBodyDef.position.Set(-25.0f, 0.5f);
		// ballBodyDef.angularDamping = 0.2f;

		m_ball = m_world->CreateBody(&ballBodyDef);
		b2Fixture *ballFixture = m_ball->CreateFixture(&ballFixtureDef);	
		
		m_createTime = timer.GetMilliseconds();		
	}
	b2Body* bodylbox;
	b2Body* m_ball;
	
	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_S:
			int theta = 45;
			float v0 = 20.0f;
			m_ball ->SetLinearVelocity(b2Vec2(v0*cos(theta), v0*sin(theta)));
			break;
		}
	}

	void Step(Settings& settings) override
	{	
		b2MassData massData = m_ball->GetMassData();
		
		g_debugDraw.DrawString(5, m_textLine, "Press S to project the ball");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Ball Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		
		b2Vec2 position = m_ball->GetPosition();
		g_debugDraw.DrawString(5, m_textLine, "Ball Position, x = %.6f", position.x);		
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Ball Position, y = %.6f", position.y);
		m_textLine += m_textIncrement;

		b2Vec2 velocity = m_ball->GetLinearVelocity();
		g_debugDraw.DrawString(5, m_textLine, "Ball velocity, x = %.6f", velocity.x);		
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Ball velocity, y = %.6f", velocity.y);
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "create time = %6.2f ms",
			m_createTime);
		m_textLine += m_textIncrement;

		printf("%4.2f %4.2f \n", position.x, position.y);
		//printf("%4.2f %4.2f \n", velocity.x, velocity.y);

		Test::Step(settings);
	}

	static Test* Create()
	{
		return new ProjectileMotion;
	}
	
	float m_createTime;
};

static int testIndex = RegisterTest("Motion in 2D", "Projectile Motion", ProjectileMotion::Create);
