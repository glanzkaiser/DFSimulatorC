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

class SpringTest : public Test
{
public:
	SpringTest()
	{
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-46.0f, 0.0f), b2Vec2(46.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
			// Create a static body as the box for the spring
			b2BodyDef bd1;
			bd1.type = b2_staticBody;
			bd1.angularDamping = 0.1f;

			bd1.position.Set(1.0f, 0.5f);
			b2Body* springbox = m_world->CreateBody(&bd1);

			b2PolygonShape shape1;
			shape1.SetAsBox(0.5f, 0.5f);
			springbox->CreateFixture(&shape1, 5.0f);
			
			// Create the box as the movable object
			b2PolygonShape boxShape;
			boxShape.SetAsBox(0.5f, 0.5f);
			
			b2FixtureDef boxFixtureDef;
			boxFixtureDef.restitution = 0.75f;
			boxFixtureDef.density = 7.3f; // this will affect the box mass
			boxFixtureDef.friction = 0.1f;
			boxFixtureDef.shape = &boxShape;
			
			b2BodyDef boxBodyDef;
			boxBodyDef.type = b2_dynamicBody;
			boxBodyDef.position.Set(5.0f, 0.5f);

			m_box = m_world->CreateBody(&boxBodyDef);
			b2Fixture *boxFixture = m_box->CreateFixture(&boxFixtureDef);
			//m_box->SetGravityScale(-7); // negative means it will goes upward, positive it will goes downward
			// Make a distance joint for the box / ball with the static box above		
			m_hertz = 1.0f;
			m_dampingRatio = 0.1f;

			b2DistanceJointDef jd;
			jd.Initialize(springbox, m_box, b2Vec2(1.0f, 0.5f), boxBodyDef.position);			
			jd.collideConnected = true; // In this case we decide to allow the bodies to collide.
			m_length = jd.length;
			m_minLength = 2.0f;
			m_maxLength = 10.0f;
			b2LinearStiffness(jd.stiffness, jd.damping, m_hertz, m_dampingRatio, jd.bodyA, jd.bodyB);
			
			m_joint = (b2DistanceJoint*)m_world->CreateJoint(&jd);
			m_joint->SetMinLength(m_minLength);
			m_joint->SetMaxLength(m_maxLength);

			m_time = 0.0f;
	}
	b2Body* m_box;
	b2DistanceJoint* m_joint;
	float m_length;
	float m_time;
	float m_minLength;
	float m_maxLength;
	float m_hertz;
	float m_dampingRatio;
	
	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_A:
			//m_box->SetLinearVelocity(b2Vec2(30.0f, 0.0f));
			m_box->ApplyForceToCenter(b2Vec2(-8000.0f, 0.0f), true);
			break;
		case GLFW_KEY_S:
			//m_box->SetLinearVelocity(b2Vec2(-30.0f, 0.0f));
			m_box->ApplyForceToCenter(b2Vec2(-5000.0f, 0.0f), true);
			break;
		case GLFW_KEY_D:
			m_box->ApplyForceToCenter(b2Vec2(5000.0f, 0.0f), true);
			break;
		case GLFW_KEY_F:
			m_box->ApplyForceToCenter(b2Vec2(8000.0f, 0.0f), true);
			break;
		case GLFW_KEY_G:
			m_box->ApplyForceToCenter(b2Vec2(12000.0f, 0.0f), true);
			break;
		}
	}
	void UpdateUI() override
	{
		ImGui::SetNextWindowPos(ImVec2(10.0f, 100.0f));
		ImGui::SetNextWindowSize(ImVec2(260.0f, 150.0f));
		ImGui::Begin("Joint Controls", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

		if (ImGui::SliderFloat("Length", &m_length, 0.0f, 20.0f, "%.0f"))
		{
			m_length = m_joint->SetLength(m_length);
		}

		if (ImGui::SliderFloat("Hertz", &m_hertz, 0.0f, 10.0f, "%.1f"))
		{
			float stiffness;
			float damping;
			b2LinearStiffness(stiffness, damping, m_hertz, m_dampingRatio, m_joint->GetBodyA(), m_joint->GetBodyB());
			m_joint->SetStiffness(stiffness);
			m_joint->SetDamping(damping);
		}

		if (ImGui::SliderFloat("Damping Ratio", &m_dampingRatio, 0.0f, 2.0f, "%.1f"))
		{
			float stiffness;
			float damping;
			b2LinearStiffness(stiffness, damping, m_hertz, m_dampingRatio, m_joint->GetBodyA(), m_joint->GetBodyB());
			m_joint->SetStiffness(stiffness);
			m_joint->SetDamping(damping);
		}

		ImGui::End();
	}
	void Step(Settings& settings) override
	{
		b2MassData massData = m_box->GetMassData();
		b2Vec2 position = m_box->GetPosition();
		b2Vec2 velocity = m_box->GetLinearVelocity();
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		
		g_debugDraw.DrawString(5, m_textLine, "Press A/S/D/F/G to apply different force to the box");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Mass position = (%4.1f, %4.1f)", position.x, position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Mass velocity = (%4.1f, %4.1f)", velocity.x, velocity.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		// Print the result in every time step then plot it into graph with either gnuplot or anything

		printf("%4.2f\n", position.x);
		
		Test::Step(settings);
	}
	static Test* Create()
	{
		return new SpringTest;
	}
	
};

static int testIndex = RegisterTest("Oscillations", "Spring Test", SpringTest::Create);
