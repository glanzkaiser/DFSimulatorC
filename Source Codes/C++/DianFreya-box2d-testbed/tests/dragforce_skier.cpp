/*
Test case for collision/jerking issue.
*/

#include "test.h"
#include <iostream> 


class DragforceSkier : public Test
{
public:
	DragforceSkier()
	{		
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			float const PlatformWidth = 8.0f;

			/*
			First angle is from the horizontal and should be negative for a downward slope.
			Second angle is relative to the preceding slope, and should be positive, creating a kind of
			loose 'Z'-shape from the 3 edges.
			If A1 = -10, then A2 <= ~1.5 will result in the collision glitch.
			If A1 = -30, then A2 <= ~10.0 will result in the glitch.
			*/
			float const Angle1Degrees = -40.0f;
			float const Angle2Degrees = 0.0f;
			
			/*
			The larger the value of SlopeLength, the less likely the glitch will show up.
			*/
			float const SlopeLength = 5100.0f;

			float const SurfaceFriction = 0.04f;

			// Convert to radians
			float const Slope1Incline = -Angle1Degrees * b2_pi / 180.0f;
			float const Slope2Incline = Slope1Incline - Angle2Degrees * b2_pi / 180.0f;
			//

			m_platform_width = PlatformWidth;

			// Horizontal platform
			b2Vec2 v1(-PlatformWidth, 0.0f);
			b2Vec2 v2(0.0f, 0.0f);
			b2Vec2 v3(SlopeLength * cosf(Slope1Incline), -SlopeLength * sinf(Slope1Incline));
			b2Vec2 v4(v3.x + SlopeLength * cosf(Slope2Incline), v3.y - SlopeLength * sinf(Slope2Incline));
			b2Vec2 v5(v4.x, v4.y - 1.0f);

			b2Vec2 vertices[5] = { v5, v4, v3, v2, v1 };

			b2ChainShape shape;
			shape.CreateLoop(vertices, 5);
			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = SurfaceFriction;

			ground->CreateFixture(&fd);
		}
			float const BodyWidth = 1.0f;
			float const BodyHeight = 2.5f;
			float const SkiLength = 3.0f;

			/*
			Larger values for this seem to alleviate the issue to some extent.
			*/
			float const SkiThickness = 0.3f;
			float const SkiFriction = 0.04f;
			float const SkiRestitution = 0.15f;

			b2BodyDef skiBodyDef;
			b2Body* skier = m_world->CreateBody(&skiBodyDef);

			// Create the ski geometry from vertices
			b2PolygonShape ski;
			b2Vec2 verts[4];
			verts[0].Set(-SkiLength / 2 - SkiThickness, -BodyHeight / 2);
			verts[1].Set(-SkiLength / 2, -BodyHeight / 2 - SkiThickness);
			verts[2].Set(SkiLength / 2, -BodyHeight / 2 - SkiThickness);
			verts[3].Set(SkiLength / 2 + SkiThickness, -BodyHeight / 2);
			ski.Set(verts, 4);

			b2FixtureDef skiFixtureDef;
			skiFixtureDef.restitution = SkiRestitution;
			skiFixtureDef.density = 85.8586019936297f; // density = mass*1.010101199925053
			skiFixtureDef.friction = SkiFriction;
			skiFixtureDef.shape = &ski;

			skiBodyDef.type = b2_dynamicBody;
			float initial_y = BodyHeight / 2 + SkiThickness;
			skiBodyDef.position.Set(-m_platform_width / 2, initial_y);
			
			m_skier = m_world->CreateBody(&skiBodyDef);
			b2Fixture *skiFixture = m_skier->CreateFixture(&skiFixtureDef);
			m_skier->SetLinearVelocity(b2Vec2(4.5f, 0.0f));
			
			b2CircleShape ballShape;
			ballShape.m_p.SetZero();
			ballShape.m_radius = 0.5f;
			
			b2FixtureDef ballFixtureDef;
			ballFixtureDef.restitution = 0.75f;
			ballFixtureDef.density = 3.3f; // this will affect the ball mass
			ballFixtureDef.friction = 0.1f;
			ballFixtureDef.shape = &ballShape;
			
			b2BodyDef ballBodyDef;
			ballBodyDef.type = b2_dynamicBody;
			ballBodyDef.position.Set(-m_platform_width / 2 - 1.0f, initial_y);
			
			m_ball = m_world->CreateBody(&ballBodyDef);
			b2Fixture *ballFixture = m_ball->CreateFixture(&ballFixtureDef);	
			m_ball->SetAngularVelocity(1.0f);
			m_ball->SetLinearVelocity(b2Vec2(4.5f, 0.0f));

			g_camera.m_center = b2Vec2(m_platform_width / 2.0f, 0.0f);
			g_camera.m_zoom = 1.1f;
			m_fixed_camera = true;
			// I Love my Wife!!!
			m_time = 0.0f;	
	}
	b2Body* m_ball;
	b2Body* m_skier;
	float m_platform_width;
	float m_time;
	bool m_fixed_camera;

	void Keyboard(int key) override
	{
		switch (key)
		{
			case GLFW_KEY_C:
			m_fixed_camera = !m_fixed_camera;
			if(m_fixed_camera)
			{
				g_camera.m_center = b2Vec2(m_platform_width / 2.0f, 0.0f);
			}
			break;
		}
	}

	void Step(Settings& settings) override
	{
		b2Vec2 v = m_skier->GetLinearVelocity();
		b2MassData massData1 = m_skier->GetMassData();
		b2Vec2 position = m_skier->GetPosition();
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		float omega = m_skier->GetAngularVelocity();
		float ke = 0.5f * massData1.mass * b2Dot(v, v) + 0.5f * massData1.I * omega * omega;
				
		g_debugDraw.DrawString(5, m_textLine, "Press C = Camera fixed/tracking");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Position = (%4.1f, %4.1f)", position.x, position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Velocity = (%4.1f, %4.1f)", v.x, v.y); // the velocity for x stop at 91.9 then not increasing anymore
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Mass = %.1f", massData1.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Kinetic energy = %.6f", ke);
		m_textLine += m_textIncrement;

		printf("%4.2f %4.2f %4.2f %4.2f %4.2f\n", position.x, position.y, v.x, v.y, ke);
		if(!m_fixed_camera)
		{
			g_camera.m_center = m_skier->GetPosition();
		}	
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new DragforceSkier;
	}

};

static int testIndex = RegisterTest("Force and Motion", "Drag Force Skier", DragforceSkier::Create);
