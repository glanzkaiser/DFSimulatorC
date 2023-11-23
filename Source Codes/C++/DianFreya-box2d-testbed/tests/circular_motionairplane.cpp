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

class CircularMotionairplane : public Test
{
public:

	CircularMotionairplane()
	{
		m_world->SetGravity(b2Vec2(0.0f,0.0f));
		b2BodyDef bdtrail;
		b2Body* bodytrail = m_world->CreateBody(&bdtrail);
		
		// Create the trail path
		{
			b2CircleShape shape;
			shape.m_radius = 2.1510f;
			shape.m_p.Set(-3.0f, 25.0f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.isSensor = true;
			m_sensor = bodytrail->CreateFixture(&fd);
		}
		// Create shape
		b2Transform xf1;
		xf1.q.Set(1.3496f * b2_pi);  //   rotate the shape 1.3496 pi
		xf1.p = xf1.q.GetXAxis();

		b2Vec2 vertices[3];
		vertices[0] = b2Mul(xf1, b2Vec2(-1.0f, 0.0f));
		vertices[1] = b2Mul(xf1, b2Vec2(1.0f, 0.0f));
		vertices[2] = b2Mul(xf1, b2Vec2(0.0f, 0.5f));
			
		b2PolygonShape poly1;
		poly1.Set(vertices, 3);

		b2FixtureDef sd1;
		sd1.shape = &poly1;
		sd1.density = 200.0f;

		b2Transform xf2;
		xf2.q.Set(-1.3496f * b2_pi); // rotate the shape - 1.3496 pi
		xf2.p = -xf2.q.GetXAxis();

		vertices[0] = b2Mul(xf2, b2Vec2(-1.0f, 0.0f));
		vertices[1] = b2Mul(xf2, b2Vec2(1.0f, 0.0f));
		vertices[2] = b2Mul(xf2, b2Vec2(0.0f, 0.5f));
			
		b2PolygonShape poly2;
		poly2.Set(vertices, 3);

		b2FixtureDef sd2;
		sd2.shape = &poly2;
		sd2.density = 200.0f;

		b2BodyDef bd1;
		bd1.type = b2_dynamicBody;

		bd1.position.Set(-5.1540f, 24.0f);
		bd1.angle = b2_pi;
		bd1.allowSleep = false;
		m_body = m_world->CreateBody(&bd1);
		m_body->CreateFixture(&sd1);
		m_body->CreateFixture(&sd2);
		m_body->SetAngularVelocity(1.0f);  // Counter clockwise movement
		// I Love my Wife!!!
		m_time = 0.0f;	
	}
	b2Body* m_body;
	float m_time;
	b2Fixture* m_sensor;
	void Step(Settings& settings) override
	{
		b2Vec2 v = m_body->GetLinearVelocity();
		float r = 2.1510f;
		float omega = m_body->GetAngularVelocity();
		float angle = m_body->GetAngle();
		b2MassData massData = m_body->GetMassData();
		b2Vec2 position = m_body->GetPosition();
		float sin = sinf(angle);
		float cos = cosf(angle);
		float body_vel = 2.1510f;
		float a = (body_vel*body_vel) / r;
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 

		float ke = 0.5f * massData.mass * b2Dot(v, v) + 0.5f * massData.I * omega * omega;
		
		m_body->SetLinearVelocity(b2Vec2(-body_vel*sinf(angle), body_vel*cosf(angle)));
		
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Airplane position = (%4.1f, %4.1f)", position.x, position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Kinetic energy = %.6f", ke);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Total linear velocity= %.6f", v);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Linear velocity =  (%4.1f, %4.1f)", v.x, v.y);
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
		return new CircularMotionairplane;
	}
	
};

static int testIndex = RegisterTest("Motion in 2D", "Circular Motion for Airplane", CircularMotionairplane::Create);
