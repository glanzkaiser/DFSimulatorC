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
#include "imgui/imgui.h"
class WorkPulleyelevator : public Test
{
public:
	WorkPulleyelevator()
	{
		float y = 16.0f;
		float z = -28.0f;
		float L = 12.0f;
		float a = 1.0f;
		float b = 2.0f;

		m_world->SetGravity(b2Vec2(0.0f,-9.8f));
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2CircleShape circle;
			circle.m_radius = 2.0f;

			circle.m_p.Set(-10.0f, y + b + L);
			ground->CreateFixture(&circle, 0.0f);

			circle.m_p.Set(10.0f, y + b + L);
			ground->CreateFixture(&circle, 0.0f);
		}
		{

			// Create the box hanging on the left
			b2PolygonShape boxShape1;
			boxShape1.SetAsBox(a, b); // width and length of the left box / left elevator
			
			b2FixtureDef boxFixtureDef1;
			boxFixtureDef1.restitution = 0.75f;
			boxFixtureDef1.density = 950.0f/8.0f; // this will affect the left elevator mass
			boxFixtureDef1.friction = 0.3f;
			boxFixtureDef1.shape = &boxShape1;
			
			b2BodyDef boxBodyDef1;
			boxBodyDef1.type = b2_dynamicBody;
			boxBodyDef1.position.Set(-10.0f, z);
			// boxBodyDef2.fixedRotation = true;

			m_boxl = m_world->CreateBody(&boxBodyDef1);
			b2Fixture *boxFixture1 = m_boxl->CreateFixture(&boxFixtureDef1);
			
			// Create the box hanging on the right
			b2PolygonShape boxShape2;
			boxShape2.SetAsBox(a, b); // width and length of the right box / right elevator
			
			b2FixtureDef boxFixtureDef2;
			boxFixtureDef2.restitution = 0.75f;
			boxFixtureDef2.density = 150.0f; // this will affect the right elevator mass
			boxFixtureDef2.friction = 0.3f;
			boxFixtureDef2.shape = &boxShape2;
			
			b2BodyDef boxBodyDef2;
			boxBodyDef2.type = b2_dynamicBody;
			boxBodyDef2.position.Set(10.0f, z); // the distance traveled by the right elevator is 54 meter
			// boxBodyDef2.fixedRotation = true;

			m_boxr = m_world->CreateBody(&boxBodyDef2);
			b2Fixture *boxFixture2 = m_boxr->CreateFixture(&boxFixtureDef2);
			m_boxr->SetLinearVelocity(b2Vec2(0.0f, 5.0f)); // Apply the right elevator motor to set linear velocity upward

			b2PulleyJointDef pulleyDef;
			b2Vec2 anchor1(-10.0f, z + b);
			b2Vec2 anchor2(10.0f, z + b );
			b2Vec2 groundAnchor1(-10.0f, y + b + L);
			b2Vec2 groundAnchor2(10.0f, y + b + L);
			pulleyDef.Initialize(m_boxl, m_boxr, groundAnchor1, groundAnchor2, anchor1, anchor2, 1.5f);

			m_joint1 = (b2PulleyJoint*)m_world->CreateJoint(&pulleyDef);

			m_time = 0.0f;
		}
	}
	b2Body* m_boxl;
	b2Body* m_boxr;
	float m_vel1;
	float m_vel2;
	float l_mass;
	float r_mass;
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
				g_camera.m_center = b2Vec2(2.0f, 10.0f);
				g_camera.m_zoom = 3.3f; // zoom out camera
			}
			break;
		}
	}
	void UpdateUI() override
	{
		ImGui::SetNextWindowPos(ImVec2(10.0f, 200.0f));
		ImGui::SetNextWindowSize(ImVec2(420.0f, 150.0f));
		ImGui::Begin("Elevator Controls", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

		if (ImGui::SliderFloat("Left Elevator velocity", &m_vel1, -50.0f, 100.0f, "%.0f"))
		{
			m_boxl->SetLinearVelocity(b2Vec2(0.0f, m_vel1));
		}
		if (ImGui::SliderFloat("Right Elevator velocity", &m_vel2, -50.0f, 100.0f, "%.0f"))
		{
			m_boxr->SetLinearVelocity(b2Vec2(0.0f, m_vel2));
		}
		if (ImGui::SliderFloat("Left Elevator mass", &l_mass, 0.0f, 5000.0f, "%.0f"))
		{
			b2MassData boxMassData1;
			boxMassData1.mass = l_mass;
			boxMassData1.I = 30.0f;
			m_boxl->SetMassData(&boxMassData1);
		}
		if (ImGui::SliderFloat("Right Elevator mass", &r_mass, 0.0f, 5000.0f, "%.0f"))
		{
			b2MassData boxMassData2;
			boxMassData2.mass = r_mass;
			boxMassData2.I = 30.0f;
			m_boxr->SetMassData(&boxMassData2);		
		}
		ImGui::End();
	}
	void Step(Settings& settings) override
	{
		Test::Step(settings);
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		float m = m_boxl->GetMass();	// same result as GetMassData()	
		b2MassData massData1 = m_boxl->GetMassData();
		b2MassData massData2 = m_boxr->GetMassData();
		b2Vec2 position1 = m_boxl->GetPosition();
		b2Vec2 velocity1 = m_boxl->GetLinearVelocity();
		b2Vec2 position2 = m_boxr->GetPosition();
		b2Vec2 velocity2 = m_boxr->GetLinearVelocity();
		float ratio = m_joint1->GetRatio();
		float L = m_joint1->GetCurrentLengthA() + ratio * m_joint1->GetCurrentLengthB();
		
		g_debugDraw.DrawString(5, m_textLine, "Press C = Camera fixed/tracking");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Left Elevator Mass = %4.2f", massData1.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Left Elevator Mass Center = %4.2f", massData1.center);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Left Elevator Inertia = %4.2f", massData1.I);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Left Elevator position = (%4.1f, %4.1f)", position1.x, position1.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Left Elevator velocity = (%4.1f, %4.1f)", velocity1.x, velocity1.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Right Elevator Mass = %4.2f", massData2.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Right Elevator position = (%4.1f, %4.1f)", position2.x, position2.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Right Elevator velocity = (%4.1f, %4.1f)", velocity2.x, velocity2.y);
		m_textLine += m_textIncrement;

		g_debugDraw.DrawString(5, m_textLine, "L1 + %4.2f * L2 = %4.2f", (float) ratio, (float) L);
		m_textLine += m_textIncrement;
		if(!m_fixed_camera)
		{
			g_camera.m_center = m_boxr->GetPosition();
			g_camera.m_zoom = 3.3f; // zoom out camera
		}	
	}

	static Test* Create()
	{
		return new WorkPulleyelevator;
	}

	b2PulleyJoint* m_joint1;
};

static int testIndex = RegisterTest("Kinetic Energy and Work", "Freight Elevator", WorkPulleyelevator::Create);
