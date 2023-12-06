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

// ./testbed > /root/output.txt
// close the testbed to record the result see it at /root/output.txt

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#include "test.h"
#include <fstream> 

class CratePendulum : public Test
{
public:

	CratePendulum()
	{
		b2Body* b1;
		{
			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));

			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
		}
		// the two blocks below for creating boxes are only for sweetener.
		{
			b2PolygonShape shape;
			shape.SetAsBox(7.0f, 0.25f, b2Vec2_zero, 0.7f); // Gradient is 0.7

			b2BodyDef bd;
			bd.position.Set(6.0f, 6.0f);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&shape, 0.0f);
		}
		{
			b2PolygonShape shape;
			shape.SetAsBox(7.0f, 0.25f, b2Vec2_zero, -0.7f); // Gradient is -0.7

			b2BodyDef bd;
			bd.position.Set(-6.0f, 6.0f);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&shape, 0.0f);
		}

		b2Body* b2; // the hanging bar for the pendulum
		{
			b2PolygonShape shape;
			shape.SetAsBox(7.25f, 0.25f);

			b2BodyDef bd;
			bd.position.Set(0.0f, 37.0f);
			b2 = m_world->CreateBody(&bd);
			b2->CreateFixture(&shape, 0.0f);
		}

		b2RevoluteJointDef jd;
		b2Vec2 anchor;

		// Create the pendulum ball
		b2PolygonShape boxShape1;
		boxShape1.SetAsBox(1.0f, 0.5f); 

		b2FixtureDef boxFixtureDef1;
		boxFixtureDef1.restitution = 0.75f;
		boxFixtureDef1.density = 115.0f; // this will affect the left elevator mass
		boxFixtureDef1.friction = 0.3f;
		boxFixtureDef1.shape = &boxShape1;
			
		b2BodyDef boxBodyDef1;
		boxBodyDef1.type = b2_dynamicBody;
		boxBodyDef1.position.Set(0.0f, 24.0f);
		// boxBodyDef2.fixedRotation = true;
		// boxBodyDef1.angularDamping = 0.2f;

		m_box = m_world->CreateBody(&boxBodyDef1);
		b2Fixture *boxFixture1 = m_box->CreateFixture(&boxFixtureDef1);
		
		// Create the anchor and connect it to the crate
		anchor.Set(0.0f, 36.0f); // x and y axis position for the Pendulum anchor
		jd.Initialize(b2, m_box, anchor);
		//jd.collideConnected = true;
		m_world->CreateJoint(&jd); // Create the Pendulum anchor

		m_time = 0.0f;
	}
	b2Body* m_box;
	float m_time;

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_S:
			m_box->SetTransform(b2Vec2(4.0f, 24.0f),0); // warp or teleport it to move with displacement of 4
			break;
		case GLFW_KEY_T:
			m_time = 0.0f;
			break;
		}
	}
	void Step(Settings& settings) override
	{
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		b2Vec2 v = m_box->GetLinearVelocity();
		float omega = m_box->GetAngularVelocity();
		float angle = m_box->GetAngle();
		b2MassData massData = m_box->GetMassData();
		b2Vec2 position = m_box->GetPosition();
		float m = massData.mass;
		float g = 9.8f;
		float L = 12.0f;
		float d = 4.0f;
		float theta = asin(d/L);		
		float T = (m*g)/(cos(theta));
		float F = T*sin(theta);
		float ke = 0.5f * massData.mass * b2Dot(v, v) + 0.5f * massData.I * omega * omega;

		g_debugDraw.DrawString(5, m_textLine, "Press S to apply force 10,000 N to positive x axis");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press T to reset time");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Ball position, x,y =( %4.1f, %4.1f)", position.x, position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Mass = %4.1f", massData.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Theta = %4.2f", theta*RADTODEG);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Rope tension = %4.2f", T);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Pushing Force = %4.2f", F);
		m_textLine += m_textIncrement;
		
		g_debugDraw.DrawString(5, m_textLine, "Kinetic energy = %4.1f", ke);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Linear velocity = %4.1f", v);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Angle (in degrees) = %4.1f", angle*RADTODEG);
		m_textLine += m_textIncrement;
		// Print the result in every time step then plot it into graph with either gnuplot or anything

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle*RADTODEG);
		//std::ofstream MyFile("/root/output.txt"); ;
		//MyFile << angle << "  " << position.x << "  " << position.y;
			
		Test::Step(settings);
	}
	
	static Test* Create()
	{
		return new CratePendulum;
	}
	
};

static int testIndex = RegisterTest("Kinetic Energy and Work", "Crate Pendulum", CratePendulum::Create);
