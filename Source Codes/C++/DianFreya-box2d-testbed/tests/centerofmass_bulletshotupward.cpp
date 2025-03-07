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

class BulletShotUpward : public Test
{
public:
	BulletShotUpward()
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
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-46.0f, 12.0f), b2Vec2(4.5f, 12.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(5.5f, 12.0f), b2Vec2(46.0f, 12.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		
			// Create the bullet
			b2CircleShape ballShape;
			ballShape.m_p.SetZero();
			ballShape.m_radius = 0.3f;
			
			b2FixtureDef ballFixtureDef;
			ballFixtureDef.restitution = 0.0f;
			ballFixtureDef.density = 0.37f; // this will affect the ball mass
			ballFixtureDef.friction = 0.1f;
			ballFixtureDef.shape = &ballShape;
			
			b2BodyDef ballBodyDef;
			ballBodyDef.type = b2_dynamicBody;
			ballBodyDef.position.Set(5.0f, 0.5f);
			// ballBodyDef.angularDamping = 0.2f;

			m_ball = m_world->CreateBody(&ballBodyDef);
			ballFixture = m_ball->CreateFixture(&ballFixtureDef);
			
			// Create the box as the movable object with friction 0
			b2PolygonShape boxShape;
			boxShape.SetAsBox(1.5f, 1.0f);
			
			b2FixtureDef boxFixtureDef;
			boxFixtureDef.restitution = 0.75f;
			boxFixtureDef.density = 5.0f/6.0f; // this will affect the box mass
			boxFixtureDef.friction = 0.0f;
			boxFixtureDef.shape = &boxShape;
			
			b2BodyDef boxBodyDef;
			boxBodyDef.type = b2_dynamicBody;
			boxBodyDef.position.Set(5.0f, 12.5f);

			m_box = m_world->CreateBody(&boxBodyDef);
			b2Fixture *boxFixture = m_box->CreateFixture(&boxFixtureDef);
	
			
			m_time = 0.0f;	
	}
	b2Body* m_box;
	b2Body* m_ball;
	
	b2Fixture* ballFixture;
	float m_bulletvelocity;
	float m_time;

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_S:
			m_ball->SetLinearVelocity(b2Vec2(0.0f, 1000.0f));
			break;
		case GLFW_KEY_A:
			m_ball->SetLinearVelocity(b2Vec2(0.0f, 500.0f));
			break;
		}
	}
	void UpdateUI() override
	{
		ImGui::SetNextWindowPos(ImVec2(10.0f, 200.0f));
		ImGui::SetNextWindowSize(ImVec2(420.0f, 150.0f));
		ImGui::Begin("Bullet velocity controls", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

		if (ImGui::SliderFloat("Bullet", &m_bulletvelocity, 0.0f, 1000.0f, "%.0f"))
		{
			m_ball->SetLinearVelocity(b2Vec2(0.0f, m_bulletvelocity));
		}
		
		ImGui::End();
	}
	void Step(Settings& settings) override
	{		
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		b2MassData massData = m_box->GetMassData();
		b2MassData massData2 = m_ball->GetMassData();
		b2Vec2 position = m_box->GetPosition();
		b2Vec2 velocity = m_box->GetLinearVelocity();
		b2Vec2 positionbullet = m_ball->GetPosition();
		b2Vec2 velocitybullet = m_ball->GetLinearVelocity();
		
		g_debugDraw.DrawString(5, m_textLine, "Press S to shoot the bullet with velocity of 1000 m/s");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press A to shoot the bullet with velocity of 500 m/s");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box position = (%4.1f, %4.1f)", position.x, position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Box velocity = (%4.1f, %4.1f)", velocity.x, velocity.y);
		m_textLine += m_textIncrement;
		
		g_debugDraw.DrawString(5, m_textLine, "Bullet position = (%4.1f, %4.1f)", positionbullet.x, positionbullet.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Bullet velocity = (%4.1f, %4.1f)", velocitybullet.x, velocitybullet.y);
		m_textLine += m_textIncrement;
		
		g_debugDraw.DrawString(5, m_textLine, "Box Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;		
		g_debugDraw.DrawString(5, m_textLine, "Bullet Mass = %.6f", massData2.mass);
		m_textLine += m_textIncrement;
		Test::Step(settings);
		
		g_camera.m_zoom = 1.4f; // zoom out camera

		printf("%4.2f %4.2f %4.2f %4.2f \n", position.x, position.y, velocity.x, velocity.y);	
	}
	static Test* Create()
	{
		return new BulletShotUpward;
	}
	
};

static int testIndex = RegisterTest("Center of Mass", "Bullet Shot Upward", BulletShotUpward::Create);
