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

class BlockSlidestoHigherLevel: public Test
{
public:
	BlockSlidestoHigherLevel()
	{		
		// Create the first horizontal track
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.0f;

			shape.SetTwoSided(b2Vec2(-20.0f, -76.0f), b2Vec2(27.0f, -76.0f));
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
			float hs0[7] = {1.3f*b2_pi, 1.4f*b2_pi, 1.5f*b2_pi, 1.6f*b2_pi, 1.7f*b2_pi, 1.8f*b2_pi, 1.9f*b2_pi};
			float yc0 = 1.26f*b2_pi;
			for (int32 i = 0; i < 7; ++i)
			{
				float y0 = hs0[i];
				shape.SetTwoSided(b2Vec2(44+24*cos(yc0), -59+24*sin(yc0)), b2Vec2(44+24*cos(yc0 + 0.1f*b2_pi), -59+24*sin(yc0 + 0.1f*b2_pi)));
				ground->CreateFixture(&fd);
				yc0 = y0;
			}

		}
		// Create the second higher horizontal track
		b2Body* ground2= NULL;
		{
			b2BodyDef bd;
			ground2 = m_world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f; // the friction for the higher level track

			shape.SetTwoSided(b2Vec2(67.0f, -66.0f), b2Vec2(108.0f, -66.0f));
			ground2->CreateFixture(&fd);

		}
		// Boxes
		{
			b2PolygonShape boxShape1;
			boxShape1.SetAsBox(0.5f, 0.5f);

			b2FixtureDef boxFixtureDef1;
			boxFixtureDef1.restitution = 0.0f;
			boxFixtureDef1.density = 0.5f/1.0f; // this will affect the mass
			boxFixtureDef1.friction = 0.01f; // if we set this to 0, then the box will keep moving, so we set this at a very small decimal number
			boxFixtureDef1.shape = &boxShape1;
			
			b2BodyDef boxBodyDef1;
			boxBodyDef1.type = b2_dynamicBody;

			boxBodyDef1.position.Set(17.5f, -75.5f);
			m_box = m_world->CreateBody(&boxBodyDef1);
			b2Fixture *boxFixture1 = m_box->CreateFixture(&boxFixtureDef1);
		
		}

		m_time = 0.0f;
	}
	bool m_fixed_camera;
	float m_time;
	b2Body* m_box;
	
	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_D:
			m_box->SetLinearVelocity(b2Vec2(30.0f, 0.0f));
			break;
		case GLFW_KEY_F:
			m_box->SetLinearVelocity(b2Vec2(33.0f, 0.0f));
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
		b2MassData massData2 = m_box->GetMassData();
		b2Vec2 position2 = m_box->GetPosition();
		b2Vec2 velocity2 = m_box->GetLinearVelocity();	

		g_debugDraw.DrawString(5, m_textLine, "Press C = Camera fixed/tracking");
		m_textLine += m_textIncrement;				
		g_debugDraw.DrawString(5, m_textLine, "Keys: push the box to the right with d= linear velocity 30 m/s");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Keys: push the box to the right with f = linear velocity 33 m/s");
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		
		g_debugDraw.DrawString(5, m_textLine, "Box Mass = %4.2f", massData2.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box position = (%4.1f, %4.1f)", position2.x, position2.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box velocity = (%4.1f, %4.1f)", velocity2.x, velocity2.y);
		m_textLine += m_textIncrement;
		
		Test::Step(settings);
		if(!m_fixed_camera)
		{
			g_camera.m_center = m_box->GetPosition();
			g_camera.m_zoom = 3.3f; // zoom out camera
		}	
	}

	static Test* Create()
	{
		return new BlockSlidestoHigherLevel;
	}

	
};

static int testIndex = RegisterTest("Potential Energy and Conservation of Energy", "Block Slides to Higher Level", BlockSlidestoHigherLevel::Create);
