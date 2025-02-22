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
#define RADTODEG 57.295779513082320876f

class RacecarWallCollision: public Test
{
public:
	RacecarWallCollision()
	{		
		m_speed = 1000.0f;
		// Create the line below
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f;

			shape.SetTwoSided(b2Vec2(-20.0f, 0.0f), b2Vec2(300.0f, 0.0f));
			ground->CreateFixture(&fd);

		}

		// Create the line that is 30 degree toward the positive x axis
		{
			float L = 10.0f;
			int theta = 30;
			float deginrad = theta*DEGTORAD;
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f;

			shape.SetTwoSided(b2Vec2(70.0f, 0.0f), b2Vec2(cosf(deginrad)*L + 70.0f, sinf(deginrad)*L +0.0f));
			ground->CreateFixture(&fd);

		}
		// Create the upper line
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f;

			shape.SetTwoSided(b2Vec2(-20.0f, 10.0f), b2Vec2(300.0f, 10.0f));
			ground->CreateFixture(&fd);

		}
		// Create the vertical line on the right
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f;

			shape.SetTwoSided(b2Vec2(300.0f, 0.0f), b2Vec2(300.0f, 10.0f));
			ground->CreateFixture(&fd);

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
			bd.position.Set(25.0f, 1.0f);
			
			b2FixtureDef fd;
			fd.shape = &circle;
			fd.density = 77.0f;
			fd.friction = 0.9f;

			m_car = m_world->CreateBody(&bd);
			m_car->CreateFixture(&chassis, 1.0f);
			
			bd.position.Set(24.0f, 0.35f);
			m_wheel1 = m_world->CreateBody(&bd);
			m_wheel1->CreateFixture(&fd);

			bd.position.Set(26.0f, 0.45f);
			m_wheel2 = m_world->CreateBody(&bd);
			m_wheel2->CreateFixture(&fd);

			b2WheelJointDef jd;
			b2Vec2 axis(0.0f, 1.0f);

			float mass1 = m_wheel1->GetMass();
			float mass2 = m_wheel2->GetMass();

			float hertz = 4.0f;
			float dampingRatio = 0.1f;
			float omega = 2.0f * b2_pi * hertz;

			jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis);
			int theta = 30;
			float deginrad = theta*DEGTORAD;

			// minus means movement to the right / clockwise rotation
			// positive means movement to the left / counterclockwise rotation
			jd.motorSpeed = -100000.0f; 
			jd.maxMotorTorque = 400.0f;
			jd.enableMotor = true;
			jd.stiffness = mass1 * omega * omega;
			jd.damping = 2.0f * mass1 * dampingRatio * omega;
			jd.lowerTranslation = -0.25f;
			jd.upperTranslation = 0.25f;
			jd.enableLimit = true;
			m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);

			jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
			jd.motorSpeed = -100000.0f;
			jd.maxMotorTorque = 400.0f;
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
	b2Body* m_car;	
	b2Body* m_wheel1;
	b2Body* m_wheel2;

	float m_speed;
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;
	int theta = 30;		
	float deginrad = theta*DEGTORAD;

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_G:
			m_car->SetLinearVelocity(b2Vec2(5100.0f, 4800.0f)); //  set this as you wish
			break;		
		case GLFW_KEY_A:
			m_spring1->SetMotorSpeed(m_speed);
			m_spring2->SetMotorSpeed(m_speed);
			break;
		case GLFW_KEY_S:
			m_spring1->SetMotorSpeed(0.0f);
			m_spring2->SetMotorSpeed(0.0f);
			break;
		case GLFW_KEY_D:
			m_spring1->SetMotorSpeed(-m_speed);
			m_spring2->SetMotorSpeed(-m_speed);
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
		float m = 80;
		float Jx;
		float Jy;
		float vf = 50;
		float vi = 70;
		int theta_i = 30;
		int theta_f = -10;
		Jx = m*(vf*cosf(theta_f*DEGTORAD) - vi*cosf(theta_i*DEGTORAD));
		Jy = m*(vf*sinf(theta_f*DEGTORAD) - vi*sinf(theta_i*DEGTORAD));
		float J = sqrt(pow(Jx,2) + pow(Jy,2));
		int theta;
		theta = acosf(Jx/J) * RADTODEG;

		b2MassData massData1 = m_car->GetMassData();
		b2MassData massData2 = m_wheel1->GetMassData();
		b2MassData massData3 = m_wheel2->GetMassData();
		b2Vec2 position1 = m_car->GetPosition();
		b2Vec2 velocity1 = m_car->GetLinearVelocity();
		
		g_debugDraw.DrawString(5, m_textLine, "Press C = Camera fixed/tracking");
		m_textLine += m_textIncrement;				
		g_debugDraw.DrawString(5, m_textLine, "Keys: left = a, brake = s, right = d, set the car to hit the wall at 30 degree = g ");
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Car Mass = %4.2f", massData1.mass + massData2.mass + massData3.mass );
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Car position = (%4.1f, %4.1f)", position1.x, position1.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Car velocity = (%4.1f, %4.1f)", velocity1.x, velocity1.y);
		m_textLine += m_textIncrement;		
		g_debugDraw.DrawString(5, m_textLine, "(J_{x}, J_{y}) = %4.2f i + %4.2f j", Jx, Jy);
		m_textLine += m_textIncrement;		
		g_debugDraw.DrawString(5, m_textLine, "J = %4.2f ", J);
		m_textLine += m_textIncrement;		
		g_debugDraw.DrawString(5, m_textLine, "The angle of J = %4.5f ", acosf(Jx/J) * RADTODEG);
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
		return new RacecarWallCollision;
	}

	
};

static int testIndex = RegisterTest("Center of Mass", "Racecar-Wall Collision", RacecarWallCollision::Create);
