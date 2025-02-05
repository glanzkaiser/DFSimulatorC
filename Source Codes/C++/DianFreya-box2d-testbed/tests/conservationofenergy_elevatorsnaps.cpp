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

class ElevatorSnaps : public Test
{
public:
	ElevatorSnaps()
	{
		b2Body* ground = NULL;
		m_world->SetGravity(b2Vec2(0.0f,-9.8f));
		// Create the pendulum set
		b2Body* b1;
		{
			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));

			b2BodyDef bd;
			b1 = m_world->CreateBody(&bd);
			b1->CreateFixture(&shape, 0.0f);
		}
		b2Body* b2; // the hanging bar for the pendulum
		{
			b2PolygonShape shape;
			shape.SetAsBox(7.25f, 0.25f);

			b2BodyDef bd;
			bd.position.Set(0.0f, 37.0f);
			b2 = m_world->CreateBody(&bd);
			b2->CreateFixture(&shape, 0.0f);
		}

		b2RevoluteJointDef jdelevator;
		b2Vec2 anchor;

		// Create the elevator
		b2PolygonShape boxShape1;
		boxShape1.SetAsBox(1.0f, 2.0f); 

		b2FixtureDef boxFixtureDef1;
		boxFixtureDef1.restitution = 0.75f;
		boxFixtureDef1.density = 225.0f; // this will affect the left elevator mass
		boxFixtureDef1.friction = 0.3f;
		boxFixtureDef1.shape = &boxShape1;
			
		b2BodyDef boxBodyDef1;
		boxBodyDef1.type = b2_dynamicBody;
		boxBodyDef1.position.Set(0.0f, 24.0f);
		// boxBodyDef2.fixedRotation = true;
		// boxBodyDef1.angularDamping = 0.2f;

		m_boxelevator = m_world->CreateBody(&boxBodyDef1);
		// Create the elevator
		b2Fixture *boxFixture1 = m_boxelevator->CreateFixture(&boxFixtureDef1);
		
		// Create the anchor and connect it to the crate
		anchor.Set(0.0f, 36.0f); // x and y axis position for the Pendulum anchor
		jdelevator.Initialize(b2, m_boxelevator, anchor);
		// to create the joint / rope that connect the elevator
		m_jointelevator = (b2RevoluteJoint*)m_world->CreateJoint(&jdelevator);
		// End of creating the pendulum set
		
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-46.0f, 0.0f), b2Vec2(46.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
			// Create the wall surrounding the spring			
			b2BodyDef bd2;
			bd2.type = b2_staticBody;
			bd2.angularDamping = 0.1f;

			bd2.position.Set(-1.7f, 18.5f);
			b2Body* leftwall = m_world->CreateBody(&bd2);

			b2PolygonShape shape2;
			shape2.SetAsBox(0.5f, 18.5f);
			leftwall->CreateFixture(&shape2, 5.0f);
			
			b2BodyDef bd3;
			bd3.type = b2_staticBody;
			bd3.angularDamping = 0.1f;

			bd3.position.Set(1.65f, 18.5f);
			b2Body* rightwall = m_world->CreateBody(&bd3);

			b2PolygonShape shape3;
			shape3.SetAsBox(0.5f, 18.5f);
			rightwall->CreateFixture(&shape3, 5.0f);
			
			// Create a static body as the box for the spring
			b2BodyDef bd1;
			bd1.type = b2_staticBody;
			bd1.angularDamping = 0.1f;

			bd1.position.Set(0.0f, 0.5f);
			b2Body* springbox = m_world->CreateBody(&bd1);

			b2PolygonShape shape1;
			shape1.SetAsBox(0.5f, 0.5f);
			springbox->CreateFixture(&shape1, 5.0f);
			
			// Create the box as the movable object
			b2PolygonShape boxShape;
			boxShape.SetAsBox(0.5f, 0.1f);
			
			b2FixtureDef boxFixtureDef;
			boxFixtureDef.restitution = 0.0f;
			boxFixtureDef.density = 1.5f; // this will affect the spring mass
			boxFixtureDef.friction = 0.1f;
			boxFixtureDef.shape = &boxShape;
			
			b2BodyDef boxBodyDef;
			boxBodyDef.type = b2_dynamicBody;
			boxBodyDef.position.Set(0.0f, 8.0f); // the spring end will be located in (0,8.0)

			m_box = m_world->CreateBody(&boxBodyDef);
			b2Fixture *boxFixture = m_box->CreateFixture(&boxFixtureDef);
			//m_box->SetGravityScale(-7); // negative means it will goes upward, positive it will goes downward
			// Make a distance joint for the box / ball with the static box above		
			m_hertz = 1.0f;
			m_dampingRatio = 0.1f;

			b2DistanceJointDef jd;
			jd.Initialize(springbox, m_box, b2Vec2(0.0f, 0.5f), boxBodyDef.position);			
			jd.collideConnected = true; // In this case we decide to allow the bodies to collide.
			m_length = jd.length;
			m_minLength = 2.0f; // the relaxed length of the spring: m_minLength 
			m_maxLength = 8.0f;
			b2LinearStiffness(jd.stiffness, jd.damping, m_hertz, m_dampingRatio, jd.bodyA, jd.bodyB);
			
			m_joint = (b2DistanceJoint*)m_world->CreateJoint(&jd);
			m_joint->SetMinLength(m_minLength);
			m_joint->SetMaxLength(m_maxLength);
			
			m_time = 0.0f;
	}
	b2Body* m_box;
	b2Body* m_boxelevator;
	b2DistanceJoint* m_joint;
	b2RevoluteJoint* m_jointelevator;
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
		case GLFW_KEY_W:
			m_box->ApplyForceToCenter(b2Vec2(0.0f, 1000.0f), true);
			break;
		case GLFW_KEY_S:
			m_box->ApplyForceToCenter(b2Vec2(0.0f, -800.0f), true);
			break;
		case GLFW_KEY_L:
			m_world->DestroyJoint(m_jointelevator); //Thanks beautiful..
			break;
		case GLFW_KEY_T:
			m_time = 0.0f;
			break;
		}
	}
	void UpdateUI() override
	{
		ImGui::SetNextWindowPos(ImVec2(10.0f, 200.0f));
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
		b2MassData massDataelevator= m_boxelevator->GetMassData();
		b2Vec2 position = m_box->GetPosition();
		b2Vec2 velocity = m_box->GetLinearVelocity();
		m_time += 1.0f / 60.0f;	// assuming we are using frequency of 60 Hertz 
		float m = massData.mass;
		float g = 9.8f;
		float y =  11.0f; 
		// y = the position at which when we place the mass it would not move / equlibrium position
		// y = y position of the ceiling - m_minLength - initial y position of the mass
		float k = 310.0f;		
		float y_eq = 11.0f;

		g_debugDraw.DrawString(5, m_textLine, "Press L to make the elevator snaps");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press W to apply force 1,000 N upward / S to apply force 1,000 N downward");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Press T to reset time");
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Time (in seconds)= %.6f", m_time);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Elevator Mass = %4.2f", massDataelevator.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Spring position = (%4.1f, %4.1f)", position.x, position.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Spring velocity = (%4.1f, %4.1f)", velocity.x, velocity.y);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Spring Mass = %4.2f", massData.mass);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "The spring constant, k = %4.1f", k);
		m_textLine += m_textIncrement;
		g_debugDraw.DrawString(5, m_textLine, "Equilibrium position for the spring, y = %4.1f", y_eq);
		m_textLine += m_textIncrement;
		// Print the result in every time step then plot it into graph with either gnuplot or anything

		printf("%4.2f %4.2f %4.2f\n", velocity.y, position.y, position.y);
		
		Test::Step(settings);
	}
	static Test* Create()
	{
		return new ElevatorSnaps;
	}
	
};

static int testIndex = RegisterTest("Potential Energy and Conservation of Energy", "Elevator Snaps", ElevatorSnaps::Create);
