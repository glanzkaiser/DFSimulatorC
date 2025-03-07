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

class ElasticCollisionSteelBall : public Test
{
public:

	ElasticCollisionSteelBall()
	{
		b2Body* b1;
		{
			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-9990.0f, 24.2f), b2Vec2(9990.0f, 24.2f));

			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
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

		// Create the steel block as the movable object with friction 0
		b2PolygonShape boxShape;
		boxShape.SetAsBox(0.5f, 0.5f);
			
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.restitution = 0.75f;
		boxFixtureDef.density = 2.5f; // this will affect the block mass
		boxFixtureDef.friction = 0.0f;
		boxFixtureDef.shape = &boxShape;
			
		b2BodyDef boxBodyDef;
		boxBodyDef.type = b2_dynamicBody;
		boxBodyDef.position.Set(0.0f, 24.5f);

		m_box = m_world->CreateBody(&boxBodyDef);
		b2Fixture *boxFixture = m_box->CreateFixture(&boxFixtureDef);

		// Create the pendulum steel ball
		b2RevoluteJointDef jd;
		b2Vec2 anchor;

		b2CircleShape ballShape;
		ballShape.m_p.SetZero();
		ballShape.m_radius = 0.5f;
		
		b2FixtureDef ballFixtureDef;
		ballFixtureDef.restitution = 0.75f;
		ballFixtureDef.density = 0.64f; // this will affect the ball mass
		ballFixtureDef.friction = 0.0f;
		ballFixtureDef.shape = &ballShape;
		
		b2BodyDef ballBodyDef;
		ballBodyDef.type = b2_dynamicBody;
		ballBodyDef.position.Set(-11.0f, 36.0f);
		// ballBodyDef.angularDamping = 0.2f;

		m_ball = m_world->CreateBody(&ballBodyDef);
		b2Fixture *ballFixture = m_ball->CreateFixture(&ballFixtureDef);	
		
		// Create the anchor and connect it to the ball
		anchor.Set(0.0f, 36.0f); // x and y axis position for the Pendulum anchor
		jd.Initialize(b2, m_ball, anchor);
		//jd.collideConnected = true;
		m_world->CreateJoint(&jd); // Create the Pendulum anchor
	}
	b2Body* m_box;

	float m_time;

	void Step(Settings& settings) override
	{
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		b2MassData massDataBlock = m_box->GetMassData();
		b2Vec2 positionBlock = m_box->GetPosition();
		b2Vec2 v_block = m_box->GetLinearVelocity();
		
		b2Vec2 v = m_ball->GetLinearVelocity();
		float omega = m_ball->GetAngularVelocity();
		float angle = m_ball->GetAngle();
		b2MassData massData = m_ball->GetMassData();
		b2Vec2 position = m_ball->GetPosition();

		float ke = 0.5f * massData.mass * b2Dot(v, v) + 0.5f * massData.I * omega * omega;

		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		
		g_debugDraw.DrawString(5, m_textLine, "Steel Ball position, x = (%4.2f, %4.2f)", position.x, position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Steel Ball velocity, v = (%4.2f, %4.2f)", v.x, v.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Steel Ball Linear velocity = %.6f", v);
		m_textLine += m_textIncrement;		
		g_debugDraw.DrawString(5, m_textLine, "Stell Ball Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Steel Ball Kinetic energy = %.6f", ke);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Steel Ball Angle (in degrees) = %.6f", angle*RADTODEG);
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "Steel Block position = (%4.2f, %4.2f)", positionBlock.x, positionBlock.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Steel Block velocity = (%4.2f, %4.2f)", v_block.x, v_block.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Stell Block Mass = %.6f", massDataBlock.mass);
		m_textLine += m_textIncrement;
		
		// Print the result in every time step then plot it into graph with either gnuplot or anything

		printf("%4.2f %4.2f %4.2f %4.2f %4.2f %4.2f %4.2f\n", position.x, position.y, angle*RADTODEG, positionBlock.x, positionBlock.y, v_block.x, v_block.y);
		//std::ofstream MyFile("/root/output.txt"); ;
		//MyFile << angle << "  " << position.x << "  " << position.y;
			
		Test::Step(settings);
	}
	
	static Test* Create()
	{
		return new ElasticCollisionSteelBall;
	}
	
	b2Body* m_ball;
};

static int testIndex = RegisterTest("Center of Mass", "Elastic Collision Steel Ball", ElasticCollisionSteelBall::Create);
