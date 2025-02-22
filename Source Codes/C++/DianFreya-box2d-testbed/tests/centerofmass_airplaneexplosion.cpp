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

// This is used to test sensor shapes.
class AirplaneExplosion : public Test
{
public:

	enum
	{
		e_count = 7
	};

	AirplaneExplosion()
	{
		// Ground body
		{
			b2BodyDef bd;
			b2Body* ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		// Create spaceship 
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(15.0f, 25.0f);
			m_ship2 = m_world->CreateBody(&bd);

			b2Vec2 vertices[3];

			vertices[0].Set(-2.0f, 0.0f);
			vertices[1].Set(1.0f, 2.0f);
			vertices[2].Set(0.0f, 4.0f);
			shape_left.Set(vertices, 3);

			vertices[0].Set(2.0f, 0.0f);
			vertices[1].Set(-1.0f, 2.0f);
			vertices[2].Set(0.0f, 4.0f);
			shape_right.Set(vertices, 3);

			vertices[0].Set(2.0f, 0.0f);
			vertices[1].Set(0.0f, 1.3f);
			vertices[2].Set(-2.0f, 0.0f);
			shape_bottom.Set(vertices, 3);

			m_pieceleft = m_ship2->CreateFixture(&shape_left, 2.0f);
			m_pieceright = m_ship2->CreateFixture(&shape_right, 2.0f);
			m_piecebottom = m_ship2->CreateFixture(&shape_bottom, 2.0f);

			//m_ship2->SetLinearVelocity(1.0f,1.0f); 
			m_ship2->SetAngularVelocity(1.0f); 
			
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
		
		b2Body* body_spaceship1 = m_pieceleft->GetBody();
		b2Vec2 spaceship_center = body_spaceship1->GetWorldCenter();

		body_spaceship1->DestroyFixture(m_pieceright);
		m_pieceright = NULL;
		
		body_spaceship1->DestroyFixture(m_piecebottom);
		m_piecebottom = NULL;

		b2BodyDef bd_spaceship;
		bd_spaceship.type = b2_dynamicBody;
		bd_spaceship.position = body_spaceship1->GetPosition();
		bd_spaceship.angle = body_spaceship1->GetAngle();

		b2Body* body_spaceship2 = m_world->CreateBody(&bd_spaceship);
		m_pieceright = body_spaceship2->CreateFixture(&shape_right, 1.0f);
		
		b2Body* body_spaceship3 = m_world->CreateBody(&bd_spaceship);
		m_piecebottom = body_spaceship3->CreateFixture(&shape_bottom, 1.0f);

		// Compute consistent velocities for new bodies based on
		// cached velocity.
		b2Vec2 spaceship_center1 = body_spaceship1->GetWorldCenter();
		b2Vec2 spaceship_center2 = body_spaceship2->GetWorldCenter();
		b2Vec2 spaceship_center3 = body_spaceship3->GetWorldCenter();
		
		b2Vec2 spaceship_velocity1 = m_spaceshipvelocity + b2Cross(m_spaceshipangularVelocity, spaceship_center1 - spaceship_center);
		b2Vec2 spaceship_velocity2 = m_spaceshipvelocity + b2Cross(m_spaceshipangularVelocity, spaceship_center2 - spaceship_center);
		b2Vec2 spaceship_velocity3 = m_spaceshipvelocity + b2Cross(m_spaceshipangularVelocity, spaceship_center3 - spaceship_center);

		body_spaceship1->SetAngularVelocity(m_spaceshipangularVelocity);
		body_spaceship1->SetLinearVelocity(spaceship_velocity1);

		body_spaceship2->SetAngularVelocity(m_spaceshipangularVelocity);
		body_spaceship2->SetLinearVelocity(spaceship_velocity2);

		body_spaceship3->SetAngularVelocity(m_spaceshipangularVelocity);
		body_spaceship3->SetLinearVelocity(spaceship_velocity3);
	}

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_D:
			m_break = true;
			break;
		}
	}

	void Step(Settings& settings) override
	{
		b2Vec2 v = m_ship2->GetLinearVelocity();
		float angle = m_ship2->GetAngle();
		float ship_vel = 2.1510f;
		b2MassData massData = m_ship2->GetMassData();
		b2Vec2 ship_position = m_ship2->GetPosition();
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
			m_ship2->SetLinearVelocity(b2Vec2(-ship_vel*sinf(angle), ship_vel*cosf(angle)));
			
			m_spaceshipvelocity = m_ship2->GetLinearVelocity();
			m_spaceshipangularVelocity = m_ship2->GetAngularVelocity();			
		}

		g_debugDraw.DrawString(5, m_textLine, "Press D to make plane explodes");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Airplane position = (%4.1f, %4.1f)", ship_position.x, ship_position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Linear velocity =  (%4.1f, %4.1f)", v.x, v.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Total linear velocity= %.6f", v);
		m_textLine += m_textIncrement;
		
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new AirplaneExplosion;
	}

	b2Body* m_ship2;
	b2Vec2 m_spaceshipvelocity;
	float m_spaceshipangularVelocity;
	b2PolygonShape shape_left;
	b2PolygonShape shape_right;
	b2PolygonShape shape_bottom;
	b2Fixture* m_pieceleft;
	b2Fixture* m_pieceright;
	b2Fixture* m_piecebottom;
	
	float m_time;
	bool m_broke;
	bool m_break;
};

static int testIndex = RegisterTest("Center of Mass", "Airplane Explosion", AirplaneExplosion::Create);
