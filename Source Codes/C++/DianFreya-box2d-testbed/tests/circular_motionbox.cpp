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

class CircularMotionbox : public Test
{
public:

	CircularMotionbox()
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
		// Create the box
		b2PolygonShape boxShape;
		boxShape.SetAsBox(0.5f, 0.5f);
			
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.restitution = 0.75f;
		boxFixtureDef.density = 3.3f; // this will affect the box mass
		boxFixtureDef.friction = 0.3f;
		boxFixtureDef.shape = &boxShape;
			
		b2BodyDef boxBodyDef;
		boxBodyDef.type = b2_dynamicBody;
		boxBodyDef.position.Set(0.0f, 25.0f);

		m_box = m_world->CreateBody(&boxBodyDef);
		b2Fixture *boxFixture = m_box->CreateFixture(&boxFixtureDef);
		m_box->SetAngularVelocity(1.0f); // has to be set to 1 to make it rotating and revolving
		
		// I Love my Wife!!!
		m_time = 0.0f;	
	}
	b2Body* m_box;
	b2Body* m_body;
	float m_time;
	b2Fixture* m_sensor;
	void Step(Settings& settings) override
	{
		b2Vec2 v = m_box->GetLinearVelocity();
		float r = 3.0f;
		float omega = m_box->GetAngularVelocity();
		float angle = m_box->GetAngle();
		b2MassData massData = m_box->GetMassData();
		b2Vec2 position = m_box->GetPosition();
		float sin = sinf(angle);
		float cos = cosf(angle);
		float box_vel = 3.0f;
		float a = (box_vel*box_vel) / r;
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 

		float ke = 0.5f * massData.mass * b2Dot(v, v) + 0.5f * massData.I * omega * omega;
		
		m_box->SetLinearVelocity(b2Vec2(-box_vel*sinf(angle), box_vel*cosf(angle)));
		
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box position = (%4.1f, %4.1f)", position.x, position.y);
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
		return new CircularMotionbox;
	}
	
};

static int testIndex = RegisterTest("Motion in 2D", "Circular Motion for Box", CircularMotionbox::Create);
