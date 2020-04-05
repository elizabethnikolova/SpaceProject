#include <math.h>
#include <GL/glew.h>
#include <GL\glut.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <gl\GLU.h>
#define STB_IMAGE_IMPLEMENTATION //if not defined the function implementations are not included
#include "stb_image.h"
#include "Shader.h"


#ifndef M_PI
#define M_PI 3.141592
#endif

bool inittex();
bool initGL();
void render();
bool LoadTexture(const char* filename, GLuint& texID);
void close();
void createSphere(float, int);
void drawCircle(int, int);
GLuint CreateSphere(float width, GLuint& VBO, GLuint& EBO);
void DrawSphere(GLuint vaoID);



//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

Shader shader;

GLuint gVAO, gVBO, gEBO;
GLuint texID1, texID2;

/*float sphereAngle = 0;
float redCubeAngle = 0;
float greenCubeAngle = 0;
float blueCubeAngle = 0;*/


int width = 700;
int height =700;

//695700
const float sunR = 3;
const float orbitalSp = 0.2;

float mercuryR = sunR*0.04;
float venusR = sunR*0.09;
float earthR = sunR*0.09;
float marsR = sunR*0.05;
float jupiterR = sunR*0.9;
float saturnR = sunR*0.74;
float uranusR = sunR*0.36;
float neptuneR = sunR*0.35;

float mercuryO = sunR*8.3;
float venusO = sunR*15.6;
float earthO = sunR*21.5;
float marsO = sunR*32.8;
float jupiterO = sunR*111.9;
float saturnO = sunR*206;
float uranusO = sunR*413.5;
float neptuneO = sunR*647.3;

float mercuryOSp = 0;
float venusOSp = 0;
float earthOSp = 0;
float marsOSp = 0;
float jupiterOSp = 0;
float saturnOSp = 0;
float uranusOSp = 0;
float neptuneOSp = 0;

float mercuryRSp = 0;
float venusRSp = 0;
float earthRSp = 0;
float marsRSp = 0;
float jupiterRSp = 0;
float saturnRSp = 0;
float uranusRSp = 0;
float neptuneRSp = 0;

static GLfloat g_fViewDistance = -2400;
static BOOL g_bButton1Down = FALSE;
static int g_yClick = 0;


void MouseButton(int button, int state, int x, int y)
{
	// Respond to mouse button presses.
	// If button1 pressed, mark this state so we know in motion function.
	if (button == GLUT_LEFT_BUTTON)
	{
		//g_fViewDistance += 4.0;
		g_bButton1Down = (state == GLUT_DOWN) ? TRUE : FALSE;
		//g_yClick = y - 3 * g_fViewDistance;
	}
	else if (button == GLUT_RIGHT_BUTTON){
		g_fViewDistance -= 4.0;
	}
	glutPostRedisplay();
}

void MouseMotion(int x, int y)
{
	// If button1 pressed, zoom in/out if mouse is moved up/down.
	if (g_bButton1Down)
	{
		//g_fViewDistance = (y - g_yClick) / 3.0;
		g_fViewDistance++;
		if (g_fViewDistance < 3.0)
			g_fViewDistance = 3.0;
		glutPostRedisplay();
	}
}

void press(unsigned char key, int xmouse, int ymouse)
{
	switch (key){
	case 'w':
		g_fViewDistance -= 10;
		break;

	case 's':
		g_fViewDistance += 10;
		break;

	default:
		break;
	}
}

void display(void)
{
	// Farb- und Tiefenbuffer leeren4
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0, 11.0, g_fViewDistance, 0.0, 0, -1, 0, 1, 0);
	//g_fViewDistance += 0.5;


	GLUquadricObj *quadratic = NULL;
	quadratic = gluNewQuadric();         // Create A Pointer To The Quadric Object  
	gluQuadricTexture(quadratic, GL_TRUE);      // Create Texture Coords  
	gluQuadricNormals(quadratic, GLU_SMOOTH);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID1);

	gluSphere(quadratic, 4.0, 20, 20);

	//Sun render
	glColor3f(1, 1, 0);
	glutSolidSphere(sunR, 25, 25);

	for (int i = 0; i < 16; i++)
	{
		glPushMatrix();
	}

	/*
	glColor3f(1, 1, 1);
	drawCircle(5, 25);//Sphere circle

	glRotatef(sphereAngle, 0, 1, 0);
	
	//Sphere
	glTranslatef(5, 0, 0);
	glutSolidSphere(1.0, 25, 25);

	glPushMatrix();
	glPushMatrix();
	glPushMatrix();

	//Red cube circle
	drawCircle(5, 25);

	//Green cube circle
	glRotatef(90, 1.0, 0.0, 0.0);
	drawCircle(5, 25);

	//Blue cube circle
	glRotatef(90, 0.0, 0.0, 1.0);
	drawCircle(5, 25);

	//Red cube
	glPopMatrix();

	glRotatef(redCubeAngle, 0, 1, 0);
	glColor3f(0.981, 0.048, 0.196);
	glTranslatef(5, 0, 0);
	glutSolidCube(1.0);

	//Green Cube
	glPopMatrix();

	glRotatef(greenCubeAngle, 0, 0, 1);
	glColor3f(0.353, 0.871, 0.235);
	glTranslatef(5, 0, 0);
	glutSolidCube(1.0);

	//Blue cube
	glPopMatrix();

	glRotatef(blueCubeAngle, 1, 0, 0);
	glColor3f(0.325, 0.784, 1);
	glTranslatef(0, 5, 0);
	glutSolidCube(1.0);
	*/

	//Mercury
	glPopMatrix();

	glColor3f(0, 1, 1);
	glRotatef(mercuryOSp, 0, 1, 0);
	glTranslatef(mercuryO, 0, 0);
	glutSolidSphere(mercuryR, 25, 25);

	//Venus
	glPopMatrix();

	glColor3f(0, 1, 0);
	glRotatef(venusOSp, 0, 2, 0);
	glTranslatef(venusO, 0, 0);
	glRotatef(venusOSp, 0, 0, 2);
	glutSolidSphere(venusR, 25, 25);

	//Earth
	glPopMatrix();

	glColor3f(0, 0, 1);
	glRotatef(earthOSp, 0, 1, 0);
	glTranslatef(earthO, 0, 0);
	glutSolidSphere(earthR, 25, 25);

	//Mars
	glPopMatrix();

	glColor3f(1, 1, 1);
	glRotatef(marsOSp, 0, 1, 0);
	glTranslatef(marsO, 0, 0);
	glutSolidSphere(marsR, 25, 25);

	//Jupiter
	glPopMatrix();
	glColor3f(1, 0, 0);
	glRotatef(jupiterOSp, 0, 1, 0);
	glTranslatef(jupiterO, 0, 0);
	glutSolidSphere(jupiterR, 25, 25);

	//Saturn
	glPopMatrix();

	glColor3f(1, 1, 0);
	glRotatef(saturnOSp, 0, 1, 0);
	glTranslatef(saturnO, 0, 0);
	glutSolidSphere(saturnR, 25, 25);

	//Uranus
	glPopMatrix();

	glColor3f(1, 0, 1);
	glRotatef(uranusOSp, 0, 1, 0);
	glTranslatef(uranusO, 0, 0);
	glutSolidSphere(uranusR, 25, 25);

	//Neptune
	glPopMatrix();

	glColor3f(0, 1, 1);
	glRotatef(neptuneOSp, 0, 1, 0);
	glTranslatef(neptuneO, 0, 0);
	glutSolidSphere(neptuneR, 25, 25);

	//Mercury circle
	glPopMatrix();

	glColor3f(1, 1, 1);
	drawCircle(mercuryO, 100);

	//Venus circle
	glPopMatrix();

	glColor3f(1, 1, 1);
	drawCircle(venusO, 100);

	//Earth circle
	glPopMatrix();

	glColor3f(1, 1, 1);
	drawCircle(earthO, 100);

	//Mars circle
	glPopMatrix();

	glColor3f(1, 1, 1);
	drawCircle(marsO, 100);

	//Jupiter circle
	glPopMatrix();

	glColor3f(1, 1, 1);
	drawCircle(jupiterO, 100);

	//Saturn circle
	glPopMatrix();

	glColor3f(1, 1, 1);
	drawCircle(saturnO, 100);

	//Uranus circle
	glPopMatrix();

	glColor3f(1, 1, 1);
	drawCircle(uranusO, 100);

	//Neptune circle
	glPopMatrix();

	glColor3f(1, 1, 1);
	drawCircle(neptuneO, 100);


	glPopMatrix();

	//if (sphereAngle > 360)
		//sphereAngle = 0;
	/*if (redCubeAngle > 360)
		redCubeAngle = 0;
	if (greenCubeAngle > 360)
		greenCubeAngle = 0;
	if (blueCubeAngle > 360)
		blueCubeAngle = 0;*/

	//Setting the rotation angles for each shape(setting the rotation speed)
	mercuryOSp += orbitalSp;
	venusOSp += orbitalSp*0.73;
	earthOSp += orbitalSp*0.62;
	marsOSp += orbitalSp*0.50;
	jupiterOSp += orbitalSp*0.27;
	saturnOSp += orbitalSp*0.20;
	uranusOSp += orbitalSp*0.14;
	neptuneOSp += orbitalSp*0.11;

	mercuryRSp += 7;
	venusRSp += 8;
	earthRSp += 5;
	marsRSp += 6;
	jupiterRSp += 1;
	saturnRSp += 2;
	uranusRSp += 4;
	neptuneRSp += 3;


	//sphereAngle += 0.2;
	/*redCubeAngle += 1.1;
	greenCubeAngle += 0.35;
	blueCubeAngle += 1.78;*/

	
	
	glutSwapBuffers();
}

void timer(int val)
{
	glutTimerFunc(val, timer, val);
	glutPostRedisplay();
}

void init()
{
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, 0.0, 2500);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (!LoadTexture("concrete3.jpg", texID1))
	{
		printf("Could not load texture \"concrete3.jpg\"");
	}

	glLoadIdentity();
	//gluLookAt(200.0, 11.0,-50.0, 11.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void drawCircle(float radius, int numSegments)
{
	float step = 360 / numSegments;
	float x, y;

	glBegin(GL_LINE_STRIP);
	for (float i = 0; i <= 360; i += step)
	{
		x = radius*cos(i*M_PI / 180);
		y = radius*sin(i*M_PI / 180);
		glVertex3f(x, 0, y);
	}
	glVertex3f(radius*cos(0.0), 0, radius*sin(0.0));
	glEnd();
}

// compute screen coordinates first
void gluPerspective(
	const float &angleOfView,
	const float &imageAspectRatio,
	const float &n, const float &f,
	float &b, float &t, float &l, float &r)
{
	float scale = tan(angleOfView * 0.5 * M_PI / 180) * n;
	r = imageAspectRatio * scale, l = -r;
	t = scale, b = -t;
}

bool inittex()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Use OpenGL 3.3
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Initialize OpenGL
				if (!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}

	return success;
}

bool initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	glewExperimental = GL_TRUE;

	glewInit();

	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		success = false;
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (!LoadTexture("concrete.jpg", texID1))
	{
		printf("Could not load texture \"concrete.jpg\"");
	}
	if (!LoadTexture("opengl_logo.png", texID2))
	{
		printf("Could not load texture \"opengl_logo.png\"");
	}

	shader.Load(".\\shaders\\vertex.vs", ".\\shaders\\fragment.fs");
	shader.use(); //we have to use the shader before setting uniforms
	shader.setInt("Texture1", 0); //tell the shader that the sampler Texture1 should take its data from texture unit 0 (GL_TEXTURE0)
	shader.setInt("Texture2", 1);

	gVAO = CreateSphere(1.0f, gVBO, gEBO);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //other modes GL_FILL, GL_POINT

	return success;
}

bool LoadTexture(const char* filename, GLuint& texID)
{
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //these are the default values for warping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// read the texture
	GLint width, height, channels;
	stbi_set_flip_vertically_on_load(true); //flip the image vertically while loading
	unsigned char* img_data = stbi_load(filename, &width, &height, &channels, 0); //read the image data

	if (img_data)
	{   //3 channels - rgb, 4 channels - RGBA
		GLenum format;
		switch (channels)
		{
		case 4:
			format = GL_RGBA;
			break;
		default:
			format = GL_RGB;
			break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, img_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture\n");
	}
	stbi_image_free(img_data);

	return true;
}

void close()
{
	//delete GL programs, buffers and objects
	glDeleteProgram(shader.ID);
	glDeleteVertexArrays(1, &gVAO);
	glDeleteBuffers(1, &gVBO);

	//Delete OGL context
	SDL_GL_DeleteContext(gContext);
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//not actually necessary because GL_TEXTURE0 is active by default
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID1);
	//if multiple textures have to be bound at the same time they are placed in different texture units (slots) -
	//available are GL_TEXTURE0 - GL_TEXTURE15, to be used they have to be activated
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texID2);

	DrawSphere(gVAO);
}

GLuint CreateSphere(float width, GLuint& VBO, GLuint& EBO)
{
	GLfloat vertices[] = {
		//vertex position //vertex color
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // bottom left
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left 
	};
	//indexed drawing - we will be using the indices to point to a vertex in the vertices array
	GLuint indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	GLuint VAO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//we have to change the stride to 6 floats, as each vertex now has 6 attribute values
	//the last value (pointer) is still 0, as the position values start from the beginning
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //the data comes from the currently bound GL_ARRAY_BUFFER
	glEnableVertexAttribArray(0);

	//here the pointer is the size of 3 floats, as the color values start after the 3rd value from the beginning
	//in other words we have to skip the first 3 floats of the vertex attributes to get to the color values
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	//the elements buffer must be unbound after the vertex array otherwise the vertex array will not have an associated elements buffer array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return VAO;
}

void DrawSphere(GLuint vaoID)
{
	glUseProgram(shader.ID);
	glBindVertexArray(vaoID);

	//glDrawElements uses the indices in the EBO to get to the vertices in the VBO
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void drawCircle(int radius, int numSegments)
{
	float step = 360 / numSegments;
	float x, y;

	glBegin(GL_LINE_STRIP);
	for (float i = 0; i <= 360; i += step)
	{
		x = radius*cos(i*M_PI / 180);
		y = radius*sin(i*M_PI / 180);
		glVertex3f(x, 0, y);
	}
	glVertex3f(radius*cos(0.0), 0, radius*sin(0.0));
	glEnd();
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Transformationen");

	glutDisplayFunc(display);
	glutTimerFunc(10, timer, 10);

	init();
	initGL();

	glutMotionFunc(MouseMotion);
	glutMouseFunc(MouseButton);
	glutKeyboardFunc(press);


	glutMainLoop();

	return 0;
}
