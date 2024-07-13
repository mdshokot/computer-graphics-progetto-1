#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include "myHeaders.h"
#include <vector>
//header for the global variables
#include "globals.h"
#include "geometricShape.h"
#include "createShape.h"
#include "createWorld.h"
#include "Missile.h"
#include "entities/Player.h"
#include "entities/Projectile.h"
#include <chrono> 



#define PI 3.14159265358979323846

static unsigned int programID;
static unsigned int programID_text;
GLuint textVAO, textVBO;

//identificativi  
mat4 Projection;
GLuint MatProj, MatModel;

//all entities 
vector<GeometricShape*> lives;
Player* player;
vector<Missile*> missiles;
vector<Projectile*> projectiles;
GeometricShape* background;
float lastTime = 0.0f;
GLuint isBackgroundShader, resolution, timeLocation;

std::chrono::steady_clock::time_point lastProjectileTime;
int projectileCooldown = 500; 

void gameOver(std::string text)
{
	renderText(programID_text, Projection, text, textVAO, textVBO, width / 2 - text.length() * 10.0f, height / 2, 1.0f, vec3(1.0f, 0.0f,0.0f));
}

void spawnMissile() {
	Missile* newMissile = new Missile(MatModel, 3.0f, 0.1f);
	vec4 color2 = vec4(1.0f, 1.0f, 0.0f, 1.0f); // Red
	vec4 color1 = vec4(1.0f, 0.0f, 0.0f, 1.0f); // Red
	newMissile->createPolygonalShape(createTriangle(20), color1, color2);
	newMissile->setRadius(10);

	// Randomize the spawn position outside the screen
	float x = rand() % width;
	float y = rand() % height;
	if (rand() % 2 == 0) x = (rand() % 2 == 0) ? -100 : width + 100;
	else y = (rand() % 2 == 0) ? -100 : height + 100;

	newMissile->updatePos(vec3(x, y, 0.0f));
	newMissile->initVao();
	missiles.push_back(newMissile);
}


void missileTimer(int value) {
	// Generate a random number between 1 and 5 for the number of missiles to spawn
	int numMissiles = rand() % 3 + 1; // Generates a random number between 1 and 5 (inclusive)

	// Spawn the random number of missiles
	for (int i = 0; i < numMissiles; ++i) {
		spawnMissile();
	}
	glutTimerFunc(4000, missileTimer, 0); // Spawn a new missile every 5 seconds
}


void mouse(int x, int y)
{
	float dx = x - player->getPosition().x;
	float dy = (height - y) - player->getPosition().y;
	float angle = atan2(-dx, dy) * 180 / PI;

	player->setTargetAngle(angle);
}

void keyboard(unsigned char key, int x, int y)
{
	glm::vec3 currentVelocity = player->getVelocity();
	switch (key) {
	case 'w':
		currentVelocity += glm::vec3(0.0f, 1.0f, 0.0f) * player->getMaxSpeed() * player->getPlayerAcceleration();
		if (glm::length(currentVelocity) > player->getMaxSpeed())
			currentVelocity = glm::normalize(currentVelocity) * player->getMaxSpeed();
		player->setVelocity(currentVelocity);
		break;
	}
	glutPostRedisplay();
}

void update(int value)
{

	// Calculate time
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f; // Convert to seconds
	lastTime = currentTime;

	player->update(0.01f); // Pass delta time to the player's update method

	for (auto it = missiles.begin(); it != missiles.end();)
	{
		(*it)->seek(player->getPosition());

		bool isCollision = Entity::checkCollision(player->getPosition(), player->getRadius(), (*it)->getPosition(), (*it)->getRadius());
		if (isCollision) {
			if (!lives.empty()) {
				lives.pop_back();
				if (lives.empty()) {
					cout << "Game Over! No more lives left.\n";
				}
			}
			delete* it;
			it = missiles.erase(it);
		}
		else {
			++it;
		}
	}


	// Update projectiles
	for (auto it = projectiles.begin(); it != projectiles.end();)
	{
		(*it)->update(0.01f); // Update projectile position

		// Check if projectile is out of bounds
		if ((*it)->isOutOfBounds(width, height))
		{
			delete* it;
			it = projectiles.erase(it); // Remove projectile from list
		}
		else
		{
			// Check collision with missiles
			bool collisionDetected = false;
			for (auto missileIt = missiles.begin(); missileIt != missiles.end(); ++missileIt)
			{
				if ((*it)->checkCollisionWithMissile((*missileIt)->getPosition(), (*missileIt)->getRadius()))
				{
					// Handle projectile-missile collision
					delete* it;
					it = projectiles.erase(it); // Remove projectile from list
					delete* missileIt;
					missiles.erase(missileIt); // Remove missile from list
					collisionDetected = true;
					player->updatePoints();
					break; // Exit missile collision loop after collision
				}
			}

			if (!collisionDetected)
			{
				++it;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(17, update, 0); // Approximately 60 updates per second
}

void initShader() {
	GLenum ErrorCheckValue = glGetError();
	char* vertexShader = (char*)"vertexShader.glsl";
	char* fragmentShader = (char*)"fragmentShader.glsl";

	programID = Shader::createProgram(vertexShader, fragmentShader);

	glUseProgram(programID);

	//Generazione del program shader per la gestione del testo
	vertexShader = (char*)"vertexShader_Text.glsl";
	fragmentShader = (char*)"fragmentShader_Text.glsl";

	programID_text = Shader::createProgram(vertexShader, fragmentShader);
}

// Funzione per bloccare il ridimensionamento
void reshape(int w, int h) {
	if (w != width || h != height) {
		// Maintain the same viewport size regardless of the new window size
		glViewport(0, 0, width, height);
		// Optionally, reset the window size to the desired dimensions
		glutReshapeWindow(width, height);
	}
}

// Function to initialize GLUT and create a window
void initializeGLUT(int& argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(title);

	glewExperimental = GL_TRUE;
	glewInit();
}

void initWorld() {
	//init projection for view in 2d with all the trasformation and rotation in the vertexShader 
	Projection = ortho(0.0f, float(width), 0.0f, float(height));
	MatProj = glGetUniformLocation(programID, "Projection");
	MatModel = glGetUniformLocation(programID, "Model");

	// Get uniform locations
	isBackgroundShader = glGetUniformLocation(programID, "isBackgroundShader");
	resolution = glGetUniformLocation(programID, "resolution");
	// Get uniform location for time
	timeLocation = glGetUniformLocation(programID, "time");

	glViewport(0, 0, width, height);

	lives = createLives(5, 0.5f, MatModel);
	player = createPlayer(MatModel);
	player->setRadius(20);
	background = new GeometricShape(MatModel);

	background->createPolygonalShape(createRectangle(width,height), vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	background->updatePos(vec3(width / 2.0f, height / 2.0f,0));


	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
}

void initVao() {
	for (GeometricShape* live : lives) {
		live->initVao();
	}
	player->initVao();

	background->initVao();
}


void draw() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (lives.empty()) {
		gameOver("Game Over!");
	}
	else {
		// Activate the shader program
		glUseProgram(programID);
		glUniform2f(resolution, width, height);
		glUniform1f(timeLocation, glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
		glUniform1i(isBackgroundShader, 1);
		background->draw();
		glUniform1i(isBackgroundShader, 0);
		// Draw entities
		for (GeometricShape* live : lives) {
			live->draw();
		}
		player->draw();

		for (Missile* missile : missiles) {
			missile->draw();
		}

		for (Projectile* projectile : projectiles) {
			projectile->draw();
		}

		// Draw points
		string str = "Points: " + to_string(player->getPoints());
		renderText(programID_text, Projection, str, textVAO, textVBO, width / 2 - 100.0f, height - 20.0f, 0.5f, vec3(1.0f, 1.0f, 1.0f));
	}
	
	glutSwapBuffers();
	// Unbind the VAO after drawing
	glBindVertexArray(0);
}

// Function to handle mouse button clicks
void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		auto currentTime = std::chrono::steady_clock::now();
		auto timeSinceLastProjectile = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastProjectileTime).count();
		if (timeSinceLastProjectile >= projectileCooldown) {


			float dx = x - player->getPosition().x;
			float dy = (height - y) - player->getPosition().y;
			float angle = atan2(-dx, dy) * 180 / PI;

			glm::vec3 currentVelocity = player->getVelocity();
			float angleRadians = angle * PI / 180.0f;
			glm::vec3 direction = glm::vec3(-sin(angleRadians), cos(angleRadians), 0.0f);
			direction = glm::normalize(direction);

			// Create a velocity vector with magnitude 5 in the calculated direction
			glm::vec3 velocity = direction * 5.0f;

			// Create a projectile
			Projectile* p = new Projectile(MatModel, player->getPosition(), velocity);
			vec4 color1 = vec4(1.0f, 1.0f, 1.0f, 1.0f); 
			vec4 color2 = vec4(1.0f, 1.0f, 1.0f, 1.0f); 
			p->createPolygonalShape(createTriangle(5), color1, color2);
			p->setRadius(3.0f); // Example radius

			// Set projectile position to player's position
			p->initVao();

			// Add projectile to the list
			projectiles.push_back(p);

			// Update last projectile time
			lastProjectileTime = currentTime;
		}
	}
}

void initTextVAO(GLuint* textVAO, GLuint* textVBO)
{
	glGenVertexArrays(1, textVAO);
	glGenBuffers(1, textVBO);
	glBindVertexArray(*textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, *textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}



int main(int argc, char* argv[])
{
	srand(static_cast<unsigned>(time(0))); // Seed the random number generator
	initializeGLUT(argc, argv);
	//init the shader 
	initShader();
	//init world entities 
	initWorld();
	initVao();
	initTextVAO(&textVAO, &textVBO);
	initFreetype();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	lastProjectileTime = std::chrono::steady_clock::now();
	lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	// Call missileTimer to start spawning missiles
	glutTimerFunc(0, missileTimer, 0);
	// Registra la funzione di rendering
	glutDisplayFunc(draw);
	// Register the function to handle keyboard input
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mouseClick);
	// Start the update loop
	glutTimerFunc(17, update, 0);
	//glutPassiveMotionFunc(mouse);
	//ogni 50 millisecondi 
	// Registra la funzione di callback per il ridimensionamento
	glutReshapeFunc(reshape);
	//main loop
	glutMainLoop();

	return 0;
}