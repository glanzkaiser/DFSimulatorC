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
#include <iostream> 

// This is used to test sensor shapes.
class ProjectileDropped : public Test
{
public:

	enum
	{
		e_count = 10
	};

	ProjectileDropped()
	{
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-46.0f, 0.0f), b2Vec2(46.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(5.6f, 0.0f), b2Vec2(5.6f, 10.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		// Create the net centering at x=0
		{
			b2PolygonShape shape;
			shape.SetAsBox(0.5f, 0.125f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 20.0f;
			fd.friction = 0.2f;

			b2RevoluteJointDef jd;

			b2Body* prevBody = ground;
			for (int32 i = 0; i < e_count; ++i)
			{
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(-4.5f + 1.0f * i, 5.0f); // 5.0f is the height 
				b2Body* body = m_world->CreateBody(&bd);
				body->CreateFixture(&fd);

				b2Vec2 anchor(-5.0f + 1.0f * i, 5.0f); //create the chain ball anchor
				jd.Initialize(prevBody, body, anchor);
				m_world->CreateJoint(&jd);

				if (i == (e_count >> 1))
				{
					m_middle = body;
				}
				prevBody = body;
			}

			b2Vec2 anchor(-5.0f + 1.0f * e_count, 5.0f); // the right anchor
			jd.Initialize(prevBody, ground, anchor);
			m_world->CreateJoint(&jd);
		}
		// Create the ball
		b2CircleShape ballShape;
		ballShape.m_p.SetZero();
		ballShape.m_radius = 0.5f;
		
		b2FixtureDef ballFixtureDef;
		ballFixtureDef.restitution = 0.15f; // the bounciness
		ballFixtureDef.density = 7.3f; // this will affect the ball mass
		ballFixtureDef.friction = 0.1f;
		ballFixtureDef.shape = &ballShape;
		
		b2BodyDef ballBodyDef;
		ballBodyDef.type = b2_dynamicBody;
		ballBodyDef.position.Set(-52.14199f, 40.0f);
		// ballBodyDef.angularDamping = 0.2f;

		m_ball = m_world->CreateBody(&ballBodyDef);
		b2Fixture *ballFixture = m_ball->CreateFixture(&ballFixtureDef);
		int theta = 0;
		float v0 = 20.0f;
		m_ball ->SetLinearVelocity(b2Vec2(v0*cos(theta), 0));

		// Create Breakable dynamic body
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-44.48716f, 30.0f);
			bd.angle = 0.85f * b2_pi;
			m_body1 = m_world->CreateBody(&bd);

			m_shape1.SetAsBox(0.5f, 0.5f, b2Vec2(-0.5f, 0.0f), 0.0f);
			m_piece1 = m_body1->CreateFixture(&m_shape1, 1.0f);
			
			m_shape2.SetAsBox(0.5f, 0.5f, b2Vec2(0.5f, 0.0f), 0.0f);
			m_piece2 = m_body1->CreateFixture(&m_shape2, 1.0f);
			
			m_body1 ->SetLinearVelocity(b2Vec2(v0*cos(theta), 0));
		}

		m_break = false;
		m_broke = false;
	}
	b2Body* m_middle;
	b2Body* m_ball;
	
	b2Body* m_body1;
	b2Vec2 m_velocity;
	float m_angularVelocity;
	b2PolygonShape m_shape1;
	b2PolygonShape m_shape2;
	b2Fixture* m_piece1;
	b2Fixture* m_piece2;
	bool m_broke;
	bool m_break;
	
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

		if (maxImpulse > 40.0f)
		{
			// Flag the body for breaking.
			m_break = true;
		}
	}

	void Break()
	{
		// Create two bodies from one.
		b2Body* body1 = m_piece1->GetBody();
		b2Vec2 center = body1->GetWorldCenter();

		body1->DestroyFixture(m_piece2);
		m_piece2 = NULL;

		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position = body1->GetPosition();
		bd.angle = body1->GetAngle();
		b2Body* body2 = m_world->CreateBody(&bd);
		m_piece2 = body2->CreateFixture(&m_shape2, 1.0f);

		// Compute consistent velocities for new bodies based on
		// cached velocity.
		b2Vec2 center1 = body1->GetWorldCenter();
		b2Vec2 center2 = body2->GetWorldCenter();
		
		b2Vec2 velocity1 = m_velocity + b2Cross(m_angularVelocity, center1 - center);
		b2Vec2 velocity2 = m_velocity + b2Cross(m_angularVelocity, center2 - center);

		body1->SetAngularVelocity(m_angularVelocity);
		body1->SetLinearVelocity(velocity1);
		
		body2->SetAngularVelocity(m_angularVelocity);
		body2->SetLinearVelocity(velocity2);
	}

	void Step(Settings& settings) override
	{
		b2MassData massData = m_ball->GetMassData();
		g_debugDraw.DrawString(5, m_textLine, "Ball Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		
		b2Vec2 position = m_ball->GetPosition();
		g_debugDraw.DrawString(5, m_textLine, "Ball Position, x = %.6f", position.x);		
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Ball Position, y = %.6f", position.y);
		m_textLine += m_textIncrement;

		b2Vec2 positionbox1 = m_body1->GetPosition();
		g_debugDraw.DrawString(5, m_textLine, "Box 1 Position, x = %.6f", positionbox1.x);		
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box 1 Position, y = %.6f", positionbox1.y);
		m_textLine += m_textIncrement;

		printf("%4.2f %4.2f %4.2f %4.2f \n", position.x, position.y,positionbox1.x, positionbox1.y);

		if (m_break)
		{
			Break();
			m_broke = true;
			m_break = false;
		}

		// Cache velocities to improve movement on breakage.
		if (m_broke == false)
		{
			m_velocity = m_body1->GetLinearVelocity();
			m_angularVelocity = m_body1->GetAngularVelocity();
		}

		Test::Step(settings);
	}
	static Test* Create()
	{
		return new ProjectileDropped;
	}
	
};

static int testIndex = RegisterTest("Motion in 2D", "Projectile Dropped", ProjectileDropped::Create);
