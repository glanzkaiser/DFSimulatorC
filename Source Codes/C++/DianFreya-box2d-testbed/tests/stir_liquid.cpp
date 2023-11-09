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

class StirLiquid : public Test
{
public:

	StirLiquid()
	{
		m_world->SetGravity(b2Vec2(0.0f,-9.0f));
		{	
			b2CircleShape shape;
			shape.m_p.SetZero();
			shape.m_radius = 0.5f; // the ball radius

			float minX = 0.0f;
			float maxX = 5.0f;
			float minY = 4.0f;
			float maxY = 6.0f;
			
			for (int32 i = 0; i < 500; ++i)
			{
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position = b2Vec2(RandomFloat(minX,maxX),RandomFloat(minY,maxY));
				b2Body* body = m_world->CreateBody(&bd);
				body->CreateFixture(&shape, 0.01f);
			}
			
		}
		// Perimeter Ground body
		{
			b2BodyDef bd;
			b2Body* ground = m_world->CreateBody(&bd);

			b2EdgeShape shapeGround;
			shapeGround.SetTwoSided(b2Vec2(-40.0f, 0.0f), b2Vec2(30.0f, 0.0f));
			ground->CreateFixture(&shapeGround, 0.0f);
			
			b2EdgeShape shapeTop;
			shapeTop.SetTwoSided(b2Vec2(-40.0f, 40.0f), b2Vec2(30.0f, 40.0f));
			ground->CreateFixture(&shapeTop, 0.0f);

			b2EdgeShape shapeLeft;
			shapeLeft.SetTwoSided(b2Vec2(-40.0f, 0.0f), b2Vec2(-40.0f, 40.0f));
			ground->CreateFixture(&shapeLeft, 0.0f);
			
			b2EdgeShape shapeRight;
			shapeRight.SetTwoSided(b2Vec2(30.0f, 0.0f), b2Vec2(30.0f, 40.0f));
			ground->CreateFixture(&shapeRight, 0.0f);
		}
		
		{
			b2PolygonShape shape;
			shape.SetAsBox(1.5f, 1.5f);
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(0.0f,20.0f);
			bd.bullet = true;
			b2Body* body = m_world->CreateBody(&bd);
			body->CreateFixture(&shape, 1.0f);
			body->SetLinearVelocity(b2Vec2(0.0f, -5.0f));
		}
	}

	static Test* Create()
	{
		return new StirLiquid;
	}
};

static int testIndex = RegisterTest("Fluids Flow", "Stir Liquid", StirLiquid::Create);
