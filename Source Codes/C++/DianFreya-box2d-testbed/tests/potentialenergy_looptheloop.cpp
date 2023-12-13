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

class LooptheLoop: public Test
{
public:
	LooptheLoop()
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
		// Create the down line
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.0f;

			shape.SetTwoSided(b2Vec2(20.0f, 0.0f), b2Vec2(20.0f, -60.0f));
			ground->CreateFixture(&fd);

		}
		// 
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.0f;

			// hs0[11] will define the parameter t for each of the vertices that create the circle			
			// Use parametric equation to get circle shape of radius 24
			// (cos t, sin t)
			float hs0[11] = {b2_pi, 1.1f*b2_pi, 1.2f*b2_pi, 1.3f*b2_pi, 1.4f*b2_pi, 1.5f*b2_pi, 1.6f*b2_pi, 1.7f*b2_pi, 1.8f*b2_pi, 1.9f*b2_pi};
			float yc0 = 0.99f*b2_pi;
			for (int32 i = 0; i < 11; ++i)
			{
				float y0 = hs0[i];
				shape.SetTwoSided(b2Vec2(44+24*cos(yc0), -59+24*sin(yc0)), b2Vec2(44+24*cos(yc0 + 0.1f*b2_pi), -59+24*sin(yc0 + 0.1f*b2_pi)));
				ground->CreateFixture(&fd);
				yc0 = y0;
			}

			// Use parametric equation to get circle shape of radius 12
			// (cos t, sin t)
			float hs2[12] = {0.0f, 0.1f*b2_pi, 0.2f*b2_pi, 0.3f*b2_pi, 0.4f*b2_pi, 0.5f*b2_pi, 0.6f*b2_pi, 0.7f*b2_pi, 0.8f*b2_pi, 0.9f*b2_pi, b2_pi};
			float yc1 = 0.0f;
			for (int32 i = 0; i < 12; ++i)
			{
				float y2 = hs2[i];
				shape.SetTwoSided(b2Vec2(56+12*cos(yc1), -60+12*sin(yc1)), b2Vec2(56+12*cos(yc1 + 0.1f*b2_pi), -60+12*sin(yc1 + 0.1f*b2_pi)));
				ground->CreateFixture(&fd);
				yc1 = y2;
			}
		}
		// Boxes
		{
			b2PolygonShape boxShape1;
			boxShape1.SetAsBox(0.5f, 0.5f);

			b2FixtureDef boxFixtureDef1;
			boxFixtureDef1.restitution = 0.0f;
			boxFixtureDef1.density = 0.5f/8.0f; // this will affect the left elevator mass
			boxFixtureDef1.friction = 0.0f; //frictionless
			boxFixtureDef1.shape = &boxShape1;
			
			b2BodyDef boxBodyDef1;
			boxBodyDef1.type = b2_dynamicBody;

			boxBodyDef1.position.Set(20.5f, 0.5f);
			m_box = m_world->CreateBody(&boxBodyDef1);
			b2Fixture *boxFixture1 = m_box->CreateFixture(&boxFixtureDef1);
			//m_box->SetLinearVelocity(b2Vec2(0.0f, -1000.0f));
		}

		// Car
		{
			b2PolygonShape chassis;
			b2Vec2 vertices[8];
			vertices[0].Set(-1.5f, -0.5f);
			vertices[1].Set(1.5f, -0.5f);
			vertices[2].Set(1.5f, 0.0f);
			vertices[3].Set(0.0f, 0.9f);
			vertices[4].Set(-1.15f, 0.9f);
			vertices[5].Set(-1.5f, 0.2f);
			chassis.Set(vertices, 6);

			b2CircleShape circle;
			circle.m_radius = 0.4f;

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(20.0f, 1.0f);
			m_car = m_world->CreateBody(&bd);
			m_car->CreateFixture(&chassis, 1.0f);

			b2FixtureDef fd;
			fd.shape = &circle;
			fd.density = 1.0f;
			fd.friction = 0.9f;

			bd.position.Set(19.0f, 0.35f);
			m_wheel1 = m_world->CreateBody(&bd);
			m_wheel1->CreateFixture(&fd);

			bd.position.Set(21.0f, 0.4f);
			m_wheel2 = m_world->CreateBody(&bd);
			m_wheel2->CreateFixture(&fd);

			b2WheelJointDef jd;
			b2Vec2 axis(0.0f, 1.0f);

			float mass1 = m_wheel1->GetMass();
			float mass2 = m_wheel2->GetMass();

			float hertz = 4.0f;
			float dampingRatio = 0.7f;
			float omega = 2.0f * b2_pi * hertz;

			jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 20.0f;
			jd.enableMotor = true;
			jd.stiffness = mass1 * omega * omega;
			jd.damping = 2.0f * mass1 * dampingRatio * omega;
			jd.lowerTranslation = -0.25f;
			jd.upperTranslation = 0.25f;
			jd.enableLimit = true;
			m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);

			jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 10.0f;
			jd.enableMotor = false;
			jd.stiffness = mass2 * omega * omega;
			jd.damping = 2.0f * mass2 * dampingRatio * omega;
			jd.lowerTranslation = -0.25f;
			jd.upperTranslation = 0.25f;
			jd.enableLimit = true;
			m_spring2 = (b2WheelJoint*)m_world->CreateJoint(&jd);
		}
		m_time = 0.0f;
	}
	bool m_fixed_camera;
	float m_time;
	b2Body* m_box;
	b2Body* m_car;	
	b2Body* m_wheel1;
	b2Body* m_wheel2;

	float m_speed;
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_F:
			m_box->SetLinearVelocity(b2Vec2(5000.0f, 0.0f));
			break;
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
		b2MassData massData2 = m_box->GetMassData();
		b2Vec2 position1 = m_car->GetPosition();
		b2Vec2 velocity1 = m_car->GetLinearVelocity();
		b2Vec2 position2 = m_box->GetPosition();
		b2Vec2 velocity2 = m_box->GetLinearVelocity();	

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

		g_debugDraw.DrawString(5, m_textLine, "Box Mass = %4.2f", massData2.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box position = (%4.1f, %4.1f)", position2.x, position2.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box velocity = (%4.1f, %4.1f)", velocity2.x, velocity2.y);
		m_textLine += m_textIncrement;
		

		g_camera.m_center.x = m_car->GetPosition().x;
		Test::Step(settings);
		if(!m_fixed_camera)
		{
			g_camera.m_center = m_box->GetPosition();
			g_camera.m_zoom = 3.3f; // zoom out camera
		}	
	}

	static Test* Create()
	{
		return new LooptheLoop;
	}

	
};

static int testIndex = RegisterTest("Potential Energy and Conservation of Energy", "Loop-the-Loop", LooptheLoop::Create);
