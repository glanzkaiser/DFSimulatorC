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
#define DEGTORAD 0.0174532925199432957f

class RunawayTruck: public Test
{
public:
	RunawayTruck()
	{		
		m_speed = 50.0f;

		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f;

			shape.SetTwoSided(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));
			ground->CreateFixture(&fd);
		}
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f;

			float L = 257.0f;
			float costheta = cosf(15*DEGTORAD);
			float sintheta = sinf(15*DEGTORAD);

			shape.SetTwoSided(b2Vec2(-150-costheta*L,-95+sintheta*L), b2Vec2(-150.0f,-95.0f));
			ground->CreateFixture(&fd);

		}
		// Create the left triangle, theta = 15, L = 30
		float L = 257.0f;
		float costheta = cosf(15*DEGTORAD);
		float sintheta = sinf(15*DEGTORAD);
		b2ChainShape chainShape2;
		b2Vec2 vertices2[] = {b2Vec2(-150-costheta*L,-95), b2Vec2(-150-costheta*L,-95+sintheta*L), b2Vec2(-150,-95)};
		chainShape2.CreateLoop(vertices2, 3);

		b2FixtureDef groundFixtureDef2;
		groundFixtureDef2.density = 0;
		groundFixtureDef2.shape = &chainShape2;

		b2BodyDef groundBodyDef2;
		groundBodyDef2.type = b2_staticBody;

		b2Body *groundBody2 = m_world->CreateBody(&groundBodyDef2);
		b2Fixture *groundBodyFixture2 = groundBody2->CreateFixture(&groundFixtureDef2);

		// Create the right triangle
		b2ChainShape chainShape;
		b2Vec2 vertices[] = {b2Vec2(-197,-120), b2Vec2(-20,-120), b2Vec2(-20,0)};
		chainShape.CreateLoop(vertices, 3);

		b2FixtureDef groundFixtureDef;
		groundFixtureDef.density = 0;
		groundFixtureDef.shape = &chainShape;

		b2BodyDef groundBodyDef;
		groundBodyDef.type = b2_staticBody;

		b2Body *groundBody = m_world->CreateBody(&groundBodyDef);
		b2Fixture *groundBodyFixture = groundBody->CreateFixture(&groundFixtureDef);
		
		// Car
		{
			b2PolygonShape chassis;
			b2Vec2 vertices[8];
			vertices[0].Set(-4.5f, -0.5f);
			vertices[1].Set(4.5f, -0.5f);
			vertices[2].Set(4.5f, 0.5f);
			vertices[3].Set(0.0f, 0.5f);
			vertices[4].Set(-4.05f, 0.2f);
			vertices[5].Set(-4.6f, 0.0f);
			chassis.Set(vertices, 6);

			b2CircleShape circle;
			circle.m_radius = 0.4f;

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-23.0f, 1.0f);
			m_car = m_world->CreateBody(&bd);
			m_car->CreateFixture(&chassis, 10.0f);

			b2FixtureDef fd;
			fd.shape = &circle;
			fd.density = 1.0f;
			fd.friction = 0.0f;

			bd.position.Set(-26.0f, 0.35f);
			m_wheel1 = m_world->CreateBody(&bd);
			m_wheel1->CreateFixture(&fd);

			bd.position.Set(-24.0f, 0.4f);
			m_wheel2 = m_world->CreateBody(&bd);
			m_wheel2->CreateFixture(&fd);

			bd.position.Set(-20.0f, 0.4f);
			m_wheel3 = m_world->CreateBody(&bd);
			m_wheel3->CreateFixture(&fd);

			b2WheelJointDef jd;
			b2Vec2 axis(0.0f, 1.0f);

			float mass1 = m_wheel1->GetMass();
			float mass2 = m_wheel2->GetMass();
			float mass3 = m_wheel3->GetMass();

			float hertz = 4.0f;
			float dampingRatio = 0.7f;
			float omega = 2.0f * b2_pi * hertz;

			jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 200.0f;
			jd.enableMotor = true;
			jd.stiffness = mass1 * omega * omega;
			jd.damping = 2.0f * mass1 * dampingRatio * omega;
			jd.lowerTranslation = -0.25f;
			jd.upperTranslation = 0.25f;
			jd.enableLimit = true;
			m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);

			jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 100.0f;
			jd.enableMotor = false;
			jd.stiffness = mass2 * omega * omega;
			jd.damping = 2.0f * mass2 * dampingRatio * omega;
			jd.lowerTranslation = -0.25f;
			jd.upperTranslation = 0.25f;
			jd.enableLimit = true;
			m_spring2 = (b2WheelJoint*)m_world->CreateJoint(&jd);

			jd.Initialize(m_car, m_wheel3, m_wheel3->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 100.0f;
			jd.enableMotor = false;
			jd.stiffness = mass2 * omega * omega;
			jd.damping = 2.0f * mass2 * dampingRatio * omega;
			jd.lowerTranslation = -0.25f;
			jd.upperTranslation = 0.25f;
			jd.enableLimit = true;
			m_spring3 = (b2WheelJoint*)m_world->CreateJoint(&jd);
			//m_car->SetLinearVelocity(b2Vec2(-10.0f, 0.0f));
			
		}
		m_time = 0.0f;
	}
	bool m_fixed_camera;
	float m_time;
	b2Body* m_box;
	b2Body* m_car;	
	b2Body* m_wheel1;
	b2Body* m_wheel2;
	b2Body* m_wheel3;

	float m_speed;
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;
	b2WheelJoint* m_spring3;

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_A:
			m_spring1->SetMotorSpeed(m_speed);
			break;
		case GLFW_KEY_S:
			m_spring1->SetMotorSpeed(0.0f);
			break;
		case GLFW_KEY_D:
			m_spring1->SetMotorSpeed(-m_speed);
			break;
		case GLFW_KEY_C:
			m_fixed_camera = !m_fixed_camera;
			if(m_fixed_camera)
			{
				g_camera.m_center = b2Vec2(2.0f, -10.0f);
				g_camera.m_zoom = 3.3f; // zoom out camera
			}
			break;
		}
	}

	void Step(Settings& settings) override
	{
		m_time += 1.0f / 60.0f;
		b2MassData massData1 = m_car->GetMassData();
		b2Vec2 position1 = m_car->GetPosition();
		b2Vec2 velocity1 = m_car->GetLinearVelocity();

		g_debugDraw.DrawString(5, m_textLine, "Press C = Camera fixed/tracking");
		m_textLine += m_textIncrement;				
		g_debugDraw.DrawString(5, m_textLine, "Keys: left = a, brake = s, right = d, hz down = q, hz up = e");
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Car Mass = %4.2f", massData1.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Car position = (%4.1f, %4.1f)", position1.x, position1.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Car velocity = (%4.1f, %4.1f)", velocity1.x, velocity1.y);
		m_textLine += m_textIncrement;

		g_camera.m_center.x = m_car->GetPosition().x;
		Test::Step(settings);
		if(!m_fixed_camera)
		{
			g_camera.m_center = m_car->GetPosition();
			g_camera.m_zoom = 3.3f; // zoom out camera
		}	
	}

	static Test* Create()
	{
		return new RunawayTruck;
	}

	
};

static int testIndex = RegisterTest("Potential Energy and Conservation of Energy", "Runaway Truck", RunawayTruck::Create);
