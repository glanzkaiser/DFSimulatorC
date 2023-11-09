
// GLEW needs to be included first
#include <GL/glew.h>

// GLFW is included next
#include <GLFW/glfw3.h>
#include "ShaderLoader.h"
#include "Camera.h"
#include "LightRenderer.h"

#include "MeshRenderer.h"
#include "TextureLoader.h"
#include <btBulletDynamicsCommon.h>
#include<chrono>

void initGame();
void renderScene();

Camera* camera;
LightRenderer* light;

MeshRenderer* sphere;
MeshRenderer* sphere2;
MeshRenderer* sphere3;
MeshRenderer* ground;

//physics
btDiscreteDynamicsWorld* dynamicsWorld;

void initGame() {
	
	// Enable the depth testing
	glEnable(GL_DEPTH_TEST); 
	
	ShaderLoader shader;

	GLuint flatShaderProgram = shader.createProgram("/root/SourceCodes/CPP/Assets/Shaders/FlatModel.vs", "/root/SourceCodes/CPP/Assets/Shaders/FlatModel.fs");
	GLuint texturedShaderProgram = shader.createProgram("/root/SourceCodes/CPP/Assets/Shaders/TexturedModel.vs", "/root/SourceCodes/CPP/Assets/Shaders/TexturedModel.fs");

	camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 8.0f, 30.0f)); //camera position at y=+8 and z=+30

	light = new LightRenderer(MeshType::kTriangle, camera);
	light->setProgram(flatShaderProgram);
	light->setPosition(glm::vec3(0.0f, 3.0f, 0.0f));

	TextureLoader tLoader;

	GLuint sphereTexture = tLoader.getTextureID("/root/SourceCodes/CPP/Assets/Textures/globe.jpg");
	GLuint groundTexture = tLoader.getTextureID("/root/SourceCodes/CPP/Assets/Textures/ground.jpg");

	//init physics
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));
	
	// Sphere Rigid Body
	btCollisionShape* sphereShape = new btSphereShape(1); // sphere with radius 1
	btCollisionShape* sphereShape2 = new btSphereShape(1);
	btCollisionShape* sphereShape3 = new btSphereShape(1);
	
	// Set the initial location where the spheres fall
	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-3, 13, 0)));
	btDefaultMotionState* sphereMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 13, 0)));
	btDefaultMotionState* sphereMotionState3 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(3, 13, 0)));

	btScalar mass = 5.0;
	btScalar mass2 = 10.0;
	btScalar mass3 = 15.0;
	btVector3 sphereInertia(0, 0, 0);
	btVector3 sphereInertia2(0, 0, 0);
	btVector3 sphereInertia3(0, 0, 0);
	sphereShape->calculateLocalInertia(mass, sphereInertia);
	sphereShape2->calculateLocalInertia(mass2, sphereInertia2);
	sphereShape3->calculateLocalInertia(mass3, sphereInertia3);

	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState, sphereShape, sphereInertia);
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI2(mass2, sphereMotionState2, sphereShape2, sphereInertia2);
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI3(mass3, sphereMotionState3, sphereShape3, sphereInertia3);

	btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
	btRigidBody* sphereRigidBody2 = new btRigidBody(sphereRigidBodyCI2);
	btRigidBody* sphereRigidBody3 = new btRigidBody(sphereRigidBodyCI3);
	sphereRigidBody->setRestitution(1.0f);
	sphereRigidBody->setFriction(1.0f);
	sphereRigidBody2->setRestitution(1.0f);
	sphereRigidBody2->setFriction(1.0f);
	sphereRigidBody3->setRestitution(1.0f);
	sphereRigidBody3->setFriction(1.0f);

	dynamicsWorld->addRigidBody(sphereRigidBody);
	dynamicsWorld->addRigidBody(sphereRigidBody2);
	dynamicsWorld->addRigidBody(sphereRigidBody3);
	
	// Sphere 1 Mesh
	sphere = new MeshRenderer(MeshType::kSphere, camera, sphereRigidBody);
	sphere->setProgram(texturedShaderProgram);
	sphere->setTexture(sphereTexture);
	sphere->setScale(glm::vec3(1.0f));

	//Sphere 2 Mesh
	sphere2 = new MeshRenderer(MeshType::kSphere, camera, sphereRigidBody2);
	sphere2->setProgram(texturedShaderProgram);
	sphere2->setTexture(sphereTexture);
	sphere2->setScale(glm::vec3(1.0f));

	// Sphere 3 Mesh
	sphere3 = new MeshRenderer(MeshType::kSphere, camera, sphereRigidBody3);
	sphere3->setProgram(texturedShaderProgram);
	sphere3->setTexture(sphereTexture);
	sphere3->setScale(glm::vec3(1.0f));

	// Ground Rigid body
	btCollisionShape* groundShape = new btBoxShape(btVector3(4.0f, 0.5f, 4.0f));
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -2.0f, 0)));

	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0.0f, new btDefaultMotionState(), groundShape, btVector3(0, 0, 0));

	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

	groundRigidBody->setFriction(1.0);
	groundRigidBody->setRestitution(0.5);

	groundRigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

	dynamicsWorld->addRigidBody(groundRigidBody);

	// Ground Mesh
	ground = new MeshRenderer(MeshType::kCube, camera, groundRigidBody);
	ground->setProgram(texturedShaderProgram);
	ground->setTexture(groundTexture);
	ground->setScale(glm::vec3(4.0f, 0.5f, 4.0f));
}

void renderScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 0.0, 1.0);

	//light->draw();
	sphere->draw();
	sphere2->draw();
	sphere3->draw();
	ground->draw();
}

int main(int argc, char **argv)
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, " Bullet and OpenGL: Gravity Simulation", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();

	initGame();
	auto previousTime = std::chrono::high_resolution_clock::now();
	while (!glfwWindowShouldClose(window)){

		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();

		dynamicsWorld->stepSimulation(dt);

		renderScene();

		glfwSwapBuffers(window);
		glfwPollEvents();

		previousTime = currentTime;
	}
	glfwTerminate();

	delete camera;
	delete light;

	return 0;
}