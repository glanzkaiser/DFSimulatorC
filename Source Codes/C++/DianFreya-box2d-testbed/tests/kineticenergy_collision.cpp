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

#include "settings.h"
#include "test.h"
#include "imgui/imgui.h"
#include <iostream> 

class KineticenergyCollision : public Test
{
public:
	KineticenergyCollision()
	{
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-46.0f, 0.0f), b2Vec2(-46.0f, 46.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(46.0f, 0.0f), b2Vec2(46.0f, 46.0f));
			ground->CreateFixture(&shape, 0.0f);
		}		
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-46.0f, 0.0f), b2Vec2(46.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
			// Create the middle train body 
			b2BodyDef bd1;
			bd1.type = b2_dynamicBody;
			bd1.angularDamping = 0.1f;

			bd1.position.Set(1.0f, 0.5f);
			b2Body* springbox = m_world->CreateBody(&bd1);

			b2PolygonShape shape1;
			shape1.SetAsBox(0.5f, 0.5f);
			springbox->CreateFixture(&shape1, 5.0f);
			// Create the last train body 
			b2BodyDef bd2;
			bd2.type = b2_dynamicBody;
			bd2.angularDamping = 0.1f;

			bd2.position.Set(-1.0f, 0.5f);
			b2Body* springbox2 = m_world->CreateBody(&bd2);

			b2PolygonShape shape2;
			shape2.SetAsBox(0.5f, 0.5f);
			springbox2->CreateFixture(&shape2, 5.0f);
			
			// Create the first train / the head as the movable object going to positive x axis
			b2PolygonShape boxShape;
			boxShape.SetAsBox(0.5f, 0.5f);
			
			b2FixtureDef boxFixtureDef;
			boxFixtureDef.restitution = 0.75f;
			boxFixtureDef.density = 122000.0f; // this will affect the box mass
			boxFixtureDef.friction = 0.1f;
			boxFixtureDef.shape = &boxShape;
			
			b2BodyDef boxBodyDef;
			boxBodyDef.type = b2_dynamicBody;
			boxBodyDef.position.Set(3.0f, 0.5f);

			m_box = m_world->CreateBody(&boxBodyDef);
			b2Fixture *boxFixture = m_box->CreateFixture(&boxFixtureDef);
			m_box->SetLinearVelocity(b2Vec2(40.8f, 0.0f));
		
			// Make a distance joint for the head train with the middle train		
			m_hertz = 1.0f;
			m_dampingRatio = 0.1f;

			b2DistanceJointDef jd;
			jd.Initialize(springbox, m_box, b2Vec2(1.0f, 0.5f), boxBodyDef.position);			
			jd.collideConnected = true; // In this case we decide to allow the bodies to collide.
			m_length = jd.length;
			m_minLength = 2.0f;
			m_maxLength = 2.0f;
			b2LinearStiffness(jd.stiffness, jd.damping, m_hertz, m_dampingRatio, jd.bodyA, jd.bodyB);
			
			m_joint = (b2DistanceJoint*)m_world->CreateJoint(&jd);
			m_joint->SetMinLength(m_minLength);
			m_joint->SetMaxLength(m_maxLength);

			// Create distance joint / chain that connect the last train to the middle
			b2DistanceJointDef jd2;
			jd2.Initialize(springbox, springbox2, b2Vec2(1.0f, 0.5f), bd2.position);			
			jd2.collideConnected = true; // In this case we decide to allow the bodies to collide.
			m_length = jd2.length;
			m_minLength = 2.0f;
			m_maxLength = 2.0f;
			b2LinearStiffness(jd2.stiffness, jd2.damping, m_hertz, m_dampingRatio, jd2.bodyA, jd2.bodyB);
			m_joint2 = (b2DistanceJoint*)m_world->CreateJoint(&jd2);
			m_joint2->SetMinLength(m_minLength);
			m_joint2->SetMaxLength(m_maxLength);
		
			// For the second train going toward negative x axis
			// Create the middle train body 
			b2BodyDef bd3;
			bd3.type = b2_dynamicBody;
			bd3.angularDamping = 0.1f;

			bd3.position.Set(31.0f, 0.5f);
			b2Body* springbox3 = m_world->CreateBody(&bd3);

			b2PolygonShape shape3;
			shape3.SetAsBox(0.5f, 0.5f);
			springbox3->CreateFixture(&shape3, 5.0f);
			// Create the last train body 
			b2BodyDef bd4;
			bd4.type = b2_dynamicBody;
			bd4.angularDamping = 0.1f;

			bd4.position.Set(29.0f, 0.5f);
			b2Body* springbox4 = m_world->CreateBody(&bd4);

			b2PolygonShape shape4;
			shape4.SetAsBox(0.5f, 0.5f);
			springbox4->CreateFixture(&shape4, 5.0f);
			
			// Create the first train / the head 
			b2PolygonShape boxShape2;
			boxShape2.SetAsBox(0.5f, 0.5f);
			
			b2FixtureDef boxFixtureDef2;
			boxFixtureDef2.restitution = 0.75f;
			boxFixtureDef2.density = 122000.0f; // this will affect the box mass
			boxFixtureDef2.friction = 0.1f;
			boxFixtureDef2.shape = &boxShape2;
			
			b2BodyDef boxBodyDef2;
			boxBodyDef2.type = b2_dynamicBody;
			boxBodyDef2.position.Set(33.0f, 0.5f);

			m_box2 = m_world->CreateBody(&boxBodyDef2);
			b2Fixture *box2Fixture = m_box2->CreateFixture(&boxFixtureDef2);
			m_box2->SetLinearVelocity(b2Vec2(-40.8f, 0.0f));
			
			// Make a distance joint for the head train with the middle train	
			m_hertz = 1.0f;
			m_dampingRatio = 0.1f;

			b2DistanceJointDef jd3;
			jd3.Initialize(springbox3, m_box2, b2Vec2(31.0f, 0.5f), boxBodyDef2.position);			
			jd3.collideConnected = true; // In this case we decide to allow the bodies to collide.
			m_length = jd3.length;
			m_minLength = 2.0f;
			m_maxLength = 2.0f;
			b2LinearStiffness(jd3.stiffness, jd3.damping, m_hertz, m_dampingRatio, jd3.bodyA, jd3.bodyB);
			
			m_joint3 = (b2DistanceJoint*)m_world->CreateJoint(&jd3);
			m_joint3->SetMinLength(m_minLength);
			m_joint3->SetMaxLength(m_maxLength);

			// Make a distance joint that connect the last train to the middle
			b2DistanceJointDef jd4;
			jd4.Initialize(springbox3, springbox4, b2Vec2(31.0f, 0.5f), bd4.position);			
			jd4.collideConnected = true; // In this case we decide to allow the bodies to collide.
			m_length = jd4.length;
			m_minLength = 2.0f;
			m_maxLength = 0.0f;
			b2LinearStiffness(jd4.stiffness, jd4.damping, m_hertz, m_dampingRatio, jd4.bodyA, jd4.bodyB);
			m_joint4 = (b2DistanceJoint*)m_world->CreateJoint(&jd4);
			m_joint4->SetMinLength(m_minLength);
			m_joint4->SetMaxLength(m_maxLength);

			m_time = 0.0f;	
	}
	b2Body* m_box;
	b2Body* m_box2;
	b2DistanceJoint* m_joint;
	b2DistanceJoint* m_joint2;
	b2DistanceJoint* m_joint3;
	b2DistanceJoint* m_joint4;
	float m_length;
	float m_minLength;
	float m_maxLength;
	float m_hertz;
	float m_dampingRatio;
	float m_time;
	float F = 50.0f;
	int theta = 30;
	
	void Step(Settings& settings) override
	{		
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		b2MassData massData = m_box->GetMassData();
		b2MassData massData2 = m_box2->GetMassData();
		b2Vec2 position = m_box->GetPosition();
		b2Vec2 position2 = m_box2->GetPosition();
		b2Vec2 velocity = m_box->GetLinearVelocity();
		b2Vec2 velocity2 = m_box2->GetLinearVelocity();
		
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Train 1 position = (%4.1f, %4.1f)", position.x, position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Train 2 position = (%4.1f, %4.1f)", position2.x, position2.y);
		m_textLine += m_textIncrement;
		
		g_debugDraw.DrawString(5, m_textLine, "Train 1 velocity = (%4.1f, %4.1f)", velocity.x, velocity.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Train 2 velocity = (%4.1f, %4.1f)", velocity2.x, velocity2.y);
		m_textLine += m_textIncrement;
		
		g_debugDraw.DrawString(5, m_textLine, "Train 1 Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Train 2 Mass = %.6f", massData2.mass);
		m_textLine += m_textIncrement;

		Test::Step(settings);
		
		printf("%4.2f %4.2f %4.2f %4.2f \n", velocity.x, velocity.y, velocity2.x, velocity2.y);	
	}
	static Test* Create()
	{
		return new KineticenergyCollision;
	}
	
};

static int testIndex = RegisterTest("Kinetic Energy and Work", "Kinetic Energy: Collision", KineticenergyCollision::Create);
