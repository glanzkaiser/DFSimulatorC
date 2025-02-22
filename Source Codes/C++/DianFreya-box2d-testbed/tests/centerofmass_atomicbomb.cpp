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

#include <iostream> // for printf

class AtomicBomb : public Test
{
public:

	enum
	{
		e_count = 7
	};

	AtomicBomb()
	{
		m_world->SetGravity(b2Vec2(0.0f,-9.8f));
		// Ground body
		{
			b2BodyDef bd;
			b2Body* ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-999999990.0f, 0.0f), b2Vec2(99999990.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		// Create spaceship 
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-30.0f, 1.5f);
			m_airplane1 = m_world->CreateBody(&bd);

			b2Vec2 vertices[3];

			vertices[0].Set(-2.0f, 0.0f);
			vertices[1].Set(0.0f, 2.0f);
			vertices[2].Set(2.0f, 0.0f);
			shape_airplane.Set(vertices, 3);

			vertices[0].Set(-2.0f, 0.0f);
			vertices[1].Set(-2.0f, -1.0f);
			vertices[2].Set(2.0f, -1.0f);
			vertices[3].Set(2.0f, 0.0f);
			shape_shell.Set(vertices, 4);

			m_pieceairplane = m_airplane1->CreateFixture(&shape_airplane, 2.0f);
			m_pieceshell = m_airplane1->CreateFixture(&shape_shell, 2.0f);
			
		}
		
		m_break = false;
		m_broke = false;
	}

	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
	{
		if (m_broke)
		{
			// The body already broke.
			return;
		}

		// Should the body break?
		int32 count = contact->GetManifold()->pointCount;

		float maxImpulse = 0.0f;
		for (int32 i = 0; i < count; ++i)
		{
			maxImpulse = b2Max(maxImpulse, impulse->normalImpulses[i]);
		}

		if (maxImpulse > 50.0f)
		{
			// Flag the body for breaking.
			m_break = true;
		}
	}

	void Break()
	{
		// Create three bodies from one.
		
		b2Body* body_airplane1 = m_pieceairplane->GetBody();
		b2Vec2 airplane_center = body_airplane1->GetWorldCenter();

		body_airplane1->DestroyFixture(m_pieceshell);
		m_pieceshell = NULL;
		
		b2BodyDef bd_airplane;
		bd_airplane.type = b2_dynamicBody;
		bd_airplane.position = body_airplane1->GetPosition();
		bd_airplane.angle = body_airplane1->GetAngle();

		b2Body* body_airplane2 = m_world->CreateBody(&bd_airplane);
		m_pieceshell = body_airplane2->CreateFixture(&shape_shell, 1.0f);

		// Compute consistent velocities for new bodies based on
		// cached velocity.
		b2Vec2 airplane_center1 = body_airplane1->GetWorldCenter();
		b2Vec2 airplane_center2 = body_airplane2->GetWorldCenter();
		
		b2Vec2 airplane_velocity1 = m_airplanevelocity + b2Cross(m_airplaneangularVelocity, airplane_center1 - airplane_center);
		b2Vec2 airplane_velocity2 = m_airplanevelocity + b2Cross(m_airplaneangularVelocity, airplane_center2 - airplane_center);

		body_airplane1->SetAngularVelocity(m_airplaneangularVelocity);
		body_airplane1->SetLinearVelocity(airplane_velocity1);

		body_airplane2->SetAngularVelocity(m_airplaneangularVelocity);
		body_airplane2->SetLinearVelocity(airplane_velocity2);
		//printf("%4.2f %4.2f \n", airplane_velocity2.x, airplane_velocity2.y);
		

	}

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_C:
			m_fixed_camera = !m_fixed_camera;
			if(m_fixed_camera)
			{
				g_camera.m_center = b2Vec2(2.0f, 10.0f);
				g_camera.m_zoom = 2.3f; // zoom out camera
			}
		case GLFW_KEY_D:
			m_break = true;
			
			break;
		case GLFW_KEY_S:
			int theta = 60;
			float v0 = 20.0f;
			m_airplane1->SetAngularVelocity(-0.5f); 
			m_airplane1 ->SetLinearVelocity(b2Vec2(v0*cos(theta*DEGTORAD), v0*sin(theta*DEGTORAD)));
			break;
		}
	}

	void Step(Settings& settings) override
	{
		b2Vec2 v = m_airplane1->GetLinearVelocity();
		float angular_vel = m_airplane1->GetAngularVelocity();
		float angle = -60; // to make the movement to the right
		float airplane_vel = 20.0f;
		b2MassData massData = m_airplane1->GetMassData();
		b2Vec2 airplane_position = m_airplane1->GetPosition();
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
				
		if (m_break)
		{
			Break();
			m_broke = true;
			m_break = false;
		}

		// Cache velocities to improve movement on breakage.
		if (m_broke == false)
		{
			m_airplanevelocity = m_airplane1->GetLinearVelocity();
			m_airplaneangularVelocity = m_airplane1->GetAngularVelocity();			
		}

		g_debugDraw.DrawString(5, m_textLine, "Press C to focus the camera on the airplane");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press S to flies the airplane");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press D to drop the bomb shell");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Airplane position = (%4.1f, %4.1f)", airplane_position.x, airplane_position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Linear velocity =  (%4.1f, %4.1f)", v.x, v.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Angular velocity =  %4.2f", angular_vel);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Total linear velocity= %.6f", v);
		m_textLine += m_textIncrement;
		
		if(!m_fixed_camera)
		{
			g_camera.m_center = m_airplane1->GetPosition();
		}	
		printf("%4.2f %4.2f %4.2f \n", airplane_position.x, airplane_position.y, v);
		
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new AtomicBomb;
	}

	b2Body* m_airplane1;
	b2Vec2 m_airplanevelocity;
	float m_airplaneangularVelocity;
	b2PolygonShape shape_airplane;
	b2PolygonShape shape_shell;
	b2Fixture* m_pieceshell;
	b2Fixture* m_pieceairplane;
	
	bool m_fixed_camera;
	float m_time;
	bool m_broke;
	bool m_break;
};

static int testIndex = RegisterTest("Center of Mass", "Atomic Bomb", AtomicBomb::Create);
