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

// ./testbed > /root/circularoutput.txt
// close the testbed to record the result see it at /root/circularoutput.txt

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#include "test.h"
#include <fstream> 

class CircularMotion : public Test
{
public:

	CircularMotion()
	{
		m_world->SetGravity(b2Vec2(0.0f,0.0f));
		b2BodyDef bd;
		b2Body* ground = m_world->CreateBody(&bd);
		b2Body* b1;
		{
			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));

			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
		}
		// Create the trail path
		{
			b2CircleShape shape;
			shape.m_radius = 3.0f;
			shape.m_p.Set(-3.0f, 25.0f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.isSensor = true;
			m_sensor = ground->CreateFixture(&fd);
		}

		// Create the ball
		b2CircleShape ballShape;
		ballShape.m_p.SetZero();
		ballShape.m_radius = 0.5f;
		
		b2FixtureDef ballFixtureDef;
		ballFixtureDef.restitution = 0.75f;
		ballFixtureDef.density = 3.3f; // this will affect the ball mass
		ballFixtureDef.friction = 0.1f;
		ballFixtureDef.shape = &ballShape;
		
		b2BodyDef ballBodyDef;
		ballBodyDef.type = b2_dynamicBody;
		ballBodyDef.position.Set(0.0f, 25.0f);
		
		m_ball = m_world->CreateBody(&ballBodyDef);
		b2Fixture *ballFixture = m_ball->CreateFixture(&ballFixtureDef);	
		m_ball->SetAngularVelocity(1.0f);
		
		// I Love my Wife!!!
		m_time = 0.0f;	
	}
	b2Body* m_ball;
	float m_time;
	b2Fixture* m_sensor;
	void Step(Settings& settings) override
	{
		b2Vec2 v = m_ball->GetLinearVelocity();
		float r = 3.0f;
		float omega = m_ball->GetAngularVelocity();
		float angle = m_ball->GetAngle();
		b2MassData massData = m_ball->GetMassData();
		b2Vec2 position = m_ball->GetPosition();
		float sin = sinf(angle);
		float cos = cosf(angle);
		float ball_vel = 3.0f;
		float a = (ball_vel*ball_vel) / r;
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 

		float ke = 0.5f * massData.mass * b2Dot(v, v) + 0.5f * massData.I * omega * omega;
		
		m_ball->SetLinearVelocity(b2Vec2(-ball_vel*sinf(angle), ball_vel*cosf(angle)));
		
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Ball position, x = %.6f", position.x);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Ball position, y = %.6f", position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Kinetic energy = %.6f", ke);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Linear velocity = %.6f", v);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Linear velocity, x = %.6f", v.x);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Linear velocity, y = %.6f", v.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Acceleration, a = %.6f", a);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Angle (in degrees) = %.6f", angle*RADTODEG);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "sin (angle) = %.6f", sin);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "cos (angle) = %.6f", cos);
		m_textLine += m_textIncrement;
		// Print the result in every time step then plot it into graph with either gnuplot or anything

		printf("%4.2f %4.2f %4.2f %4.2f %4.2f %4.2f %4.2f\n", position.x, position.y, angle*RADTODEG, v.x, v.y, sin, cos);
			
		Test::Step(settings);
	}
	
	static Test* Create()
	{
		return new CircularMotion;
	}
	
};

static int testIndex = RegisterTest("Motion in 2D", "Circular Motion", CircularMotion::Create);
