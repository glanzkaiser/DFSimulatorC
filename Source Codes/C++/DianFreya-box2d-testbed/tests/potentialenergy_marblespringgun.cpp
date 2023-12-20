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
#define DEGTORAD 0.0174532925199432957f

class MarbleSpringgun : public Test
{
public:
	MarbleSpringgun()
	{
		b2Body* ground = NULL;
		
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-46.0f, 0.5f), b2Vec2(12.0f, 0.5f));
			ground->CreateFixture(&shape, 0.0f);
		}
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(12.0f, 0.0f), b2Vec2(12.0f,-20.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(12.0f, -20.0f), b2Vec2(46.0f,-20.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(37.0f, -19.0f), b2Vec2(37.0f,-20.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(35.0f, -19.0f), b2Vec2(35.0f,-20.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			float L = 30.0f;
			float costheta = cosf(40*DEGTORAD);
			float sintheta = sinf(40*DEGTORAD);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(35-costheta*L,-19+sintheta*L), b2Vec2(35,-19));
			ground->CreateFixture(&shape, 0.0f);
		}

			// Create the left triangle, theta = 40, L = 30
			float L = 30.0f;
			float costheta = cosf(40*DEGTORAD);
			float sintheta = sinf(40*DEGTORAD);
			b2ChainShape chainShape2;
			b2Vec2 vertices2[] = {b2Vec2(35-costheta*L,-19), b2Vec2(35-costheta*L,-19+sintheta*L), b2Vec2(35,-19)};
			chainShape2.CreateLoop(vertices2, 3);

			b2FixtureDef groundFixtureDef2;
			groundFixtureDef2.density = 0;
			groundFixtureDef2.shape = &chainShape2;

			b2BodyDef groundBodyDef2;
			groundBodyDef2.type = b2_staticBody;

			b2Body *groundBody2 = m_world->CreateBody(&groundBodyDef2);
			b2Fixture *groundBodyFixture2 = groundBody2->CreateFixture(&groundFixtureDef2);

			// Create a static body as the box for the spring
			b2BodyDef bd1;
			bd1.type = b2_staticBody;
			bd1.angularDamping = 0.1f;

			bd1.position.Set(1.0f, 1.0f);
			b2Body* springbox = m_world->CreateBody(&bd1);

			b2PolygonShape shape1;
			shape1.SetAsBox(0.5f,5.5f);
			springbox->CreateFixture(&shape1, 5.0f);
			
			// Create the left box connected to the spring as the movable object
			b2PolygonShape leftboxShape;
			leftboxShape.SetAsBox(0.5f, 0.5f);
			
			b2FixtureDef leftboxFixtureDef;
			leftboxFixtureDef.restitution = 0.75f;
			leftboxFixtureDef.density = 0.1f; // this will affect the box mass
			leftboxFixtureDef.friction = 0.1f;
			leftboxFixtureDef.shape = &leftboxShape;
			
			b2BodyDef leftboxBodyDef;
			leftboxBodyDef.type = b2_dynamicBody;
			leftboxBodyDef.position.Set(7.0f, 1.0f);

			m_box = m_world->CreateBody(&leftboxBodyDef);
			leftboxFixture = m_box->CreateFixture(&leftboxFixtureDef);
			//m_box->SetGravityScale(-7); // negative means it will goes upward, positive it will goes downward
			
			// Create the marble ball
			b2CircleShape ballShape;
			ballShape.m_p.SetZero();
			ballShape.m_radius = 0.5f;
			
			b2FixtureDef ballFixtureDef;
			ballFixtureDef.restitution = 0.75f;
			ballFixtureDef.density = 0.5f; // this will affect the ball mass
			ballFixtureDef.friction = 0.1f;
			ballFixtureDef.shape = &ballShape;
			
			b2BodyDef ballBodyDef;
			ballBodyDef.type = b2_dynamicBody;
			ballBodyDef.position.Set(15.0f, -1.0f);
			// ballBodyDef.angularDamping = 0.2f;

			m_ball = m_world->CreateBody(&ballBodyDef);
			ballFixture = m_ball->CreateFixture(&ballFixtureDef);	

			// Create the marble ball that will be spawned near the spring
			
			ballShape2.m_p.SetZero();
			ballShape2.m_radius = 0.5f;
			
			ballFixtureDef2.restitution = 0.75f;
			ballFixtureDef2.density = 0.5f; // this will affect the ball mass
			ballFixtureDef2.friction = 0.1f;
			ballFixtureDef2.shape = &ballShape2;
			
			ballBodyDef2.type = b2_dynamicBody;
			ballBodyDef2.position.Set(10.0f, 1.0f);
			
			m_ball2 = m_world->CreateBody(&ballBodyDef2);

			// Make a distance joint for the box / ball with the static box above		
			m_hertz = 1.0f;
			m_dampingRatio = 0.1f;

			b2DistanceJointDef jd;
			jd.Initialize(springbox, m_box, b2Vec2(1.0f, 1.0f), leftboxBodyDef.position);			
			jd.collideConnected = true; // In this case we decide to allow the bodies to collide.
			m_length = jd.length;
			m_minLength = 2.0f;
			m_maxLength = 10.0f;
			b2LinearStiffness(jd.stiffness, jd.damping, m_hertz, m_dampingRatio, jd.bodyA, jd.bodyB);
			
			m_joint = (b2DistanceJoint*)m_world->CreateJoint(&jd);
			m_joint->SetMinLength(m_minLength);
			m_joint->SetMaxLength(m_maxLength);
		
			// Create the Pulley 
			b2PulleyJointDef pulleyDef;
			b2Vec2 anchor1(5.5f, 1.0f); // the position of the end string of the left cord is (5.5,1.0) connecting to the left box
			b2Vec2 anchor2(15.0f, -1.0f); // the position of the end string of the right cord is (15.0f,-1) connecting to the right hanging box
			b2Vec2 groundAnchor1(11.5f, 1.0f ); // the string of the cord is tightened at (11.5, 1.0)
			b2Vec2 groundAnchor2(12.5f,  1.0f);  // the string of the cord is tightened at (12.5, 1.0)
			// the last float is the ratio
			pulleyDef.Initialize(m_box, m_ball, groundAnchor1, groundAnchor2, anchor1, anchor2, 1.0f);
			
			m_joint1 = (b2PulleyJoint*)m_world->CreateJoint(&pulleyDef);

			m_time = 0.0f;
	}
	b2Body* m_box;
	b2Body* m_ball;
	b2Body* m_ball2;

	b2CircleShape ballShape2;
	b2FixtureDef ballFixtureDef2;
	b2BodyDef ballBodyDef2;	

	b2DistanceJoint* m_joint;
	b2Fixture* leftboxFixture;
	b2Fixture* ballFixture;
	b2Fixture* ballFixture2;
	b2PulleyJoint* m_joint1;
	bool m_fixed_camera;
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
			m_box->ApplyForceToCenter(b2Vec2(-150.0f, 0.0f), true);
			break;
		case GLFW_KEY_S:
			m_box->ApplyForceToCenter(b2Vec2(-250.0f, 0.0f), true);
			break;
		case GLFW_KEY_D:
			m_box->ApplyForceToCenter(b2Vec2(150.0f, 0.0f), true);
			break;
		case GLFW_KEY_F:
			m_box->ApplyForceToCenter(b2Vec2(250.0f, 0.0f), true);
			break;
		case GLFW_KEY_G:
			m_box->ApplyForceToCenter(b2Vec2(500.0f, 0.0f), true);
			break;
		case GLFW_KEY_B:
			m_ball2->CreateFixture(&ballFixtureDef2);	
			break;
		case GLFW_KEY_L:
			m_world->DestroyJoint(m_joint1); //Thanks beautiful..
			break;
		case GLFW_KEY_M:
			m_ball->DestroyFixture(ballFixture); //Thanks beautiful..
			break;
		case GLFW_KEY_C:
			m_fixed_camera = !m_fixed_camera;
			if(m_fixed_camera)
			{
				g_camera.m_center = b2Vec2(2.0f, -10.0f);
				g_camera.m_zoom = 1.3f; // zoom out camera
			}
			break;
		}
	}
	void UpdateUI() override
	{
		ImGui::SetNextWindowPos(ImVec2(10.0f, 300.0f));
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
		b2MassData massDatar = m_ball->GetMassData();
		b2Vec2 positionr = m_ball->GetPosition();
		b2Vec2 velocityr = m_ball->GetLinearVelocity();
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		
		g_debugDraw.DrawString(5, m_textLine, "Press A/S/D/F/G to apply different force to the box");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press L to disconnected the string between the spring and the ball");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press M to delete the first ball");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press B to create a new ball near the spring");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Spring position = (%4.1f, %4.1f)", position.x, position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Spring velocity = (%4.1f, %4.1f)", velocity.x, velocity.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Marble position = (%4.1f, %4.1f)", positionr.x, positionr.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Marble velocity = (%4.1f, %4.1f)", velocityr.x, velocityr.y);
		m_textLine += m_textIncrement;		
		g_debugDraw.DrawString(5, m_textLine, "Spring Mass = %.6f", massData.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Marble Mass = %.6f", massDatar.mass);
		m_textLine += m_textIncrement;
		// Print the result in every time step then plot it into graph with either gnuplot or anything

		g_camera.m_center.x = m_box->GetPosition().x;
		Test::Step(settings);
		if(!m_fixed_camera)
		{
			g_camera.m_center = m_box->GetPosition();
			g_camera.m_zoom = 1.3f; // zoom out camera
		}	
		float positionnew = (positionr.x + positionr.y);
		printf("%4.2f %4.2f %4.2f\n", positionr.x, positionr.y, positionnew);
		
		Test::Step(settings);
	}
	static Test* Create()
	{
		return new MarbleSpringgun;
	}
	
};

static int testIndex = RegisterTest("Potential Energy and Conservation of Energy", "Marble Spring Gun", MarbleSpringgun::Create);
