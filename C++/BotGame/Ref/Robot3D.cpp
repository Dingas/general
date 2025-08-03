/*******************************************************************
		   Hierarchical Multi-Part Model Example
********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gl/glut.h>
#include <utility>
#include <vector>
#include "VECTOR3D.h"
#include "QuadMesh.h"

const int vWidth  = 650;    // Viewport width in pixels
const int vHeight = 500;    // Viewport height in pixels
const float PI = 3.14159265358979323846f;

bool pinched = 0;
bool showControls = 0;
bool mouseDown = false;
bool flameOn = false;
bool pinching = false;

int armSelection = 0;
int jointSelection = 0;
int walkPhase = 0;
int lastX = 0;
int lastY = 0;

float cameraDistance = 22.0f;
float cameraHeight = 6.0f;
float cameraAngleX = -PI / 2;  // -90 degrees to start looking at origin from positive Z
float cameraAngleY = 1.2f;   // About 70 degrees to match initial height





// Note how everything depends on robot body dimensions so that can scale entire robot proportionately
// just by changing robot body scale
float robotBodyRadius = 5;
float upperArmLength = robotBodyRadius*0.75;
float upperArmWidth = 0.125*robotBodyRadius;
float lowerArmLength = robotBodyRadius * 0.75;
float lowerArmWidth = 0.125 * robotBodyRadius;
float gunLength = upperArmLength / 4;
float gunWidth = upperArmWidth;
float gunDepth = upperArmWidth;
float sawRadius = 1;
float sawThickness = 1;
float eyeRadius = 1;
float clawLength = 1.5;
float clawWidth = 1;
float clawDepth = 0.3;
float pinchAngle = 45;
float stanchionLength = robotBodyRadius;
float stanchionRadius = 0.1*robotBodyRadius;
float baseWidth = 2 * robotBodyRadius;
float baseLength = 0.25*stanchionLength;
float engineHeight = 2;
float coneHeight = 1;
float thrust = 0;

float endObjectScale[6][3] = {
	{eyeRadius, eyeRadius, eyeRadius}, // Arm 0
	{eyeRadius, eyeRadius, eyeRadius}, // Arm 1
	{eyeRadius, eyeRadius, eyeRadius}, // Arm 2
	{sawRadius, sawRadius, sawThickness}, // Arm 3
	{clawLength, clawWidth, clawDepth}, // Arm 4
	{gunLength, gunWidth, gunDepth}  // Arm 5
};

// Control Robot body rotation on base
float robotAngle = 0.0;

// Control arm rotation
float shoulderAngle[6][3] = {
	{-40.0, 0.0, 0.0}, // Arm 0
	{-40.0, 0.0, 0.0}, // Arm 1
	{-40.0, 0.0, 0.0}, // Arm 2
	{-40.0, 0.0, 0.0}, // Arm 3
	{-40.0, 0.0, 0.0}, // Arm 4
	{-40.0, 0.0, 0.0}  // Arm 5
};
float elbowAngle[6][3] = {
	{-80.0, 0.0, 0.0}, // Arm 0
	{-80.0, 0.0, 0.0}, // Arm 1
	{-80.0, 0.0, 0.0}, // Arm 2
	{-40.0, 0.0, 0.0}, // Arm 3
	{-40.0, 0.0, 0.0}, // Arm 4
	{-40.0, 0.0, 0.0}  // Arm 5
};
float endAngle[6][3] = {
	{0, 0.0, 0.0}, // Arm 0
	{0, 0.0, 0.0}, // Arm 1
	{0, 0.0, 0.0}, // Arm 2
	{0, 0.0, 0.0}, // Arm 3
	{0, 0.0, 0.0}, // Arm 4
	{0, 0.0, 0.0}  // Arm 5
};

float jointRadius = 0.7;
float startAngles[3] = { 0,120,240 };



// Lighting/shading and material properties for robot - upcoming lecture - just copy for now
// Robot RGBA material properties (NOTE: we will learn about this later in the semester)
GLfloat robotBody_mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat robotBody_mat_specular[] = { 0.45f,0.55f,0.45f,1.0f };
GLfloat robotBody_mat_diffuse[] = { 0.1f,0.35f,0.1f,1.0f };
GLfloat robotBody_mat_shininess[] = { 32.0F };


GLfloat robotArm_mat_ambient[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
GLfloat robotArm_mat_diffuse[] = { 0.5f,0.0f,0.0f,1.0f };
GLfloat robotArm_mat_specular[] = { 0.7f, 0.6f, 0.6f, 1.0f };
GLfloat robotArm_mat_shininess[] = { 32.0F };

GLfloat gun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat gun_mat_diffuse[] = { 0.01f,0.0f,0.01f,0.01f };
GLfloat gun_mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat gun_mat_shininess[] = { 100.0F };

GLfloat robotLowerBody_mat_ambient[] = { 0.25f, 0.25f, 0.25f, 1.0f };
GLfloat robotLowerBody_mat_diffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat robotLowerBody_mat_specular[] = { 0.774597f, 0.774597f, 0.774597f, 1.0f };
GLfloat robotLowerBody_mat_shininess[] = { 76.8F };




// MY STUFF!!!
// Material properties for different objects
GLfloat eye_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // White for eyes
GLfloat eye_mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat eye_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat eye_mat_shininess[] = { 32.0f };

GLfloat saw_mat_ambient[] = { 0.8f, 0.4f, 0.2f, 1.0f }; // Brown for saw
GLfloat saw_mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat saw_mat_diffuse[] = { 0.8f, 0.4f, 0.2f, 1.0f };
GLfloat saw_mat_shininess[] = { 32.0f };

GLfloat claw_mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Gray for pincer
GLfloat claw_mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat claw_mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat claw_mat_shininess[] = { 32.0f };

// Flame colors
GLfloat flame_mat_ambient[] = { 0.2f, 0.1f, 0.0f, 1.0f };   // Darker ambient color
GLfloat flame_mat_diffuse[] = { 1.0f, 0.5f, 0.0f, 1.0f };   // Bright orange for diffuse
GLfloat flame_mat_specular[] = { 1.0f, 1.0f, 0.0f, 1.0f };  // Bright yellow for specular highlights
GLfloat flame_mat_shininess[] = { 50.0f };                   // Shininess factor







////////////////////////////////////////////////
// Light properties
GLfloat light_position0[] = { -4.0F, 8.0F, 8.0F, 1.0F };
GLfloat light_position1[] = { 4.0F, 8.0F, 8.0F, 1.0F };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_ambient[] = { 0.2F, 0.2F, 0.2F, 1.0F };


// Mouse button
int currentButton;

// A flat open mesh
QuadMesh *groundMesh = NULL;

// Structure defining a bounding box, currently unused
typedef struct BoundingBox {
    VECTOR3D min;
	VECTOR3D max;
} BBox;

// Default Mesh Size
int meshSize = 16;

// Prototypes for functions in this module
void initOpenGL(int w, int h);
void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void mouseMotionHandler(int xMouse, int yMouse);
void keyboard(unsigned char key, int x, int y);
void functionKeys(int key, int x, int y);
void gunSpin(int param);
void drawRobot();
void drawBody();
void drawThruster();

void drawClaw();
void drawEye();
void drawSaw();
void drawGun();
void drawCylinder(float radius, float height);
void drawCone(float baseRadius, float height);
void drawDisk(float innerRadius, float outerRadius, int slices, int loops);

void drawArm();
void updateArmAngles(int armIndex, float shoulderDelta, float elbowDelta, float endDelta);
void drawEndObject(int armIndex);

void flame();
void walker(int param);
void pinch(int param);
void drawControls();


int main(int argc, char **argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(vWidth, vHeight);
	glutInitWindowPosition(200, 30);
	glutCreateWindow("3D Hierarchical Example");

	// Initialize GL
	initOpenGL(vWidth, vHeight);

	// Register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotionHandler);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(functionKeys);

	// Start event loop, never returns
	glutMainLoop();

	return 0;
}


// Set up OpenGL. For viewport and projection setup see reshape(). 
void initOpenGL(int w, int h)
{
	// Set up and enable lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);   // This second light is currently off

	// Other OpenGL setup
	glEnable(GL_DEPTH_TEST);   // Remove hidded surfaces
	glShadeModel(GL_SMOOTH);   // Use smooth shading, makes boundaries between polygons harder to see 
	glClearColor(0.4F, 0.4F, 0.4F, 0.0F);  // Color and depth for glClear
	glClearDepth(1.0f);
	glEnable(GL_NORMALIZE);    // Renormalize normal vectors 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   // Nicer perspective

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// Other initializatuion
	// Set up ground quad mesh
	VECTOR3D origin = VECTOR3D(-16.0f, 0.0f, 16.0f);
	VECTOR3D dir1v = VECTOR3D(1.0f, 0.0f, 0.0f);
	VECTOR3D dir2v = VECTOR3D(0.0f, 0.0f, -1.0f);
	groundMesh = new QuadMesh(meshSize, 32.0);
	groundMesh->InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v);

	VECTOR3D ambient = VECTOR3D(0.0f, 0.05f, 0.0f);
	VECTOR3D diffuse = VECTOR3D(0.4f, 0.8f, 0.4f);
	VECTOR3D specular = VECTOR3D(0.04f, 0.04f, 0.04f);
	float shininess = 0.2;
	groundMesh->SetMaterial(ambient, diffuse, specular, shininess);

}


// Callback, called whenever GLUT determines that the window should be redisplayed
// or glutPostRedisplay() has been called.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	// Create Viewing Matrix V
	// Set up the camera at position (0, 6, 22) looking at the origin, up along positive y axis
	//gluLookAt(0.0, 6.0, 22.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	  // Calculate camera position using spherical coordinates
	float camX = cameraDistance * sin(cameraAngleY) * cos(cameraAngleX);
	float camZ = cameraDistance * sin(cameraAngleY) * sin(cameraAngleX);
	float camY = cameraDistance * cos(cameraAngleY);

	// Set up the camera
	gluLookAt(camX, camY, camZ,    // Camera position
		0.0, 0.0, 0.0,        // Look at point
		0.0, 1.0, 0.0);       // Up vector

	// Draw Robot

	// Apply modelling transformations M to move robot
	// Current transformation matrix is set to IV, where I is identity matrix
	// CTM = IV
	drawRobot();
	

	// Draw ground
	glPushMatrix();
	glTranslatef(0.0, -20.0, 0.0);
	groundMesh->DrawMesh(meshSize);
	glPopMatrix();

	if (showControls) {
		drawControls();
	}

	glutSwapBuffers();   // Double buffering, swap buffers
}

void drawCylinder(float radius, float height) {
	GLUquadric* quadric = gluNewQuadric();
	gluCylinder(quadric, radius, radius, height, 32, 32);  // Draw cylinder
	gluDeleteQuadric(quadric);
}

void drawCone(float baseRadius, float height) {
	GLUquadric* quadric = gluNewQuadric();
	gluCylinder(quadric, baseRadius, 0.0, height, 32, 32);  // Draw cone
	gluDeleteQuadric(quadric);
}

void drawDisk(float innerRadius, float outerRadius, int slices, int loops) {
	GLUquadric* quadric = gluNewQuadric(); // Create a new quadric object

	// Draw the disk
	gluDisk(quadric, innerRadius, outerRadius, slices, loops);

	gluDeleteQuadric(quadric); // Clean up the quadric object
}

void drawRobot()
{
	glPushMatrix();
	 // spin robot on base. 
	 glRotatef(robotAngle, 0.0, 1.0, 0.0);

	 drawBody();

	 drawArm();
	glPopMatrix();
	
	// don't want to spin fixed base in this example
	drawThruster();

	glPopMatrix();
}


void drawBody()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, robotBody_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotBody_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotBody_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotBody_mat_shininess);
	

	glPushMatrix();
	glScalef(robotBodyRadius, robotBodyRadius, robotBodyRadius);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();

	// Draw the cylinder (engine)
	glPushMatrix();
	glTranslatef(0.0f, -0.4*robotBodyRadius, 0.0f); // Position it at the bottom of the sphere
	glRotatef(90, 1.0f, 0.0f, 0.0f); // Align the cylinder vertically
	glScalef(1.0f, 1.0f, engineHeight);      // Scale cylinder height
	drawCylinder(1, 1);
	glPopMatrix();


	glMaterialfv(GL_FRONT, GL_AMBIENT, flame_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, flame_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, flame_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, flame_mat_shininess);
	// Draw the flame
	glPushMatrix();
	glTranslatef(0.0f, -0.4 * robotBodyRadius - engineHeight, 0.0f); // Position it at the end of the cylinder
	glRotatef(90, 1.0f, 0.0f, 0.0f); // Align the cone vertically



	glScalef(thrust*0.2, thrust*0.2, coneHeight + thrust);
	drawCone(1, 1);
	glPopMatrix();
}


void flame(int param)
{
	if (flameOn) {
		thrust = rand() * 0.0001;
		glutPostRedisplay();
		glutTimerFunc(10, flame, 0);
	}
}



void drawThruster()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, robotLowerBody_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotLowerBody_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotLowerBody_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotLowerBody_mat_shininess);

	glPushMatrix();
	// Position stanchion and base with respect to body
	glTranslatef(0, -1.5*robotBodyRadius, 0.0); // this will be done last

	/*/ stanchion
	glPushMatrix();
	glScalef(stanchionRadius, stanchionLength, stanchionRadius);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0, 1.0, 1.0, 20, 10);
	glPopMatrix();
	*/
	// base
	glPushMatrix();
	// Position base with respect to parent stanchion
	glTranslatef(0.0, -0.25*stanchionLength, 0.0);
	// Build base
	glScalef(baseWidth, baseLength, baseWidth);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();
}

void drawArm() {
	

	int hemisphere = 1;

	for (int i = 0; i < 6; i++) {
		if (i > 2) {
			hemisphere = -1;
		}
		glMaterialfv(GL_FRONT, GL_AMBIENT, robotArm_mat_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, robotArm_mat_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, robotArm_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SHININESS, robotArm_mat_shininess);

		glPushMatrix();


		float angle = (i % 3) * 120.0f; // 120 degrees apart
		glRotatef(angle, 0.0, 1.0, 0.0); // Rotate around Y-axis to position arms

		// Position the arm on the sphere's surface
		glTranslatef(0, hemisphere*robotBodyRadius / 4, robotBodyRadius / 2);
		glRotatef(shoulderAngle[i][0], 1.0, 0.0, 0.0);
		glRotatef(shoulderAngle[i][1], 0.0, 1.0, 0.0);
		glRotatef(shoulderAngle[i][2], 0.0, 0.0, 1.0);

		// build shoulder
		glPushMatrix();
		glutSolidSphere(jointRadius, 15, 15);
		glPopMatrix();

		// Draw upper arm
		glPushMatrix();
		glTranslatef(0.0f, -upperArmLength / 2, 0.0f); // Position the upper arm correctly
		glScalef(upperArmWidth, upperArmLength, upperArmWidth);
		glutSolidCube(1.0);
		glPopMatrix();

		// elbow joint
		glPushMatrix();
		glTranslatef(0, -(upperArmLength), 0.0);


		glutSolidSphere(0.5, 15, 15);
		glPopMatrix();


		//lower arm
		glPushMatrix();
		glTranslatef(-(0.5 * robotBodyRadius + 0.5 * upperArmWidth), -(upperArmLength), 0.0);
		glRotatef(elbowAngle[i][0], 1.0, 0.0, 0.0);
		glRotatef(elbowAngle[i][1], 0, 1, 0.0);
		glRotatef(elbowAngle[i][2], 0, 0.0, 1);
		glTranslatef((0.5 * robotBodyRadius + 0.5 * upperArmWidth), -(0.5 * upperArmLength), 0.0);

		glScalef(upperArmWidth, upperArmLength, upperArmWidth);

		glutSolidCube(1.0);
		glPopMatrix();


		//end part
		glPushMatrix();
		glTranslatef(-(0.5 * robotBodyRadius + 0.5 * upperArmWidth), -(upperArmLength), 0.0);
		glRotatef(elbowAngle[i][0], 1.0, 0.0, 0.0);
		//glRotatef(elbowAngle[i][1], 0, 1, 0.0);
		//glRotatef(elbowAngle[i][2], 0, 0.0, 1);
		glTranslatef((0.5 * robotBodyRadius + 0.5 * upperArmWidth), (0.5 * upperArmLength), 0.0);

		

		glTranslatef(0, -(lowerArmLength + lowerArmLength*0.5), 0.0);
		//glScalef(endObjectScale[i][0], endObjectScale[i][1], endObjectScale[i][2]);
		glRotatef(endAngle[i][0], 1.0, 0.0, 0.0);
		glRotatef(endAngle[i][1], 0, 1, 0.0);
		glRotatef(endAngle[i][2], 0, 0.0, 1);

		drawEndObject(i);
		glPopMatrix();

		glPopMatrix();

	}
	
	
}



// Function to draw different end objects with materials
void drawEndObject(int armIndex) {
	switch (armIndex) {
	case 0:  // Top arm 1
	case 1:  // Top arm 2
	case 2:  // Top arm 3
		
		drawEye();  // Draw an eye at the end
		break;
	case 3:  // Bottom arm 1
		
		drawSaw();  // Draw a saw at the end
		break;
	case 4:  // Bottom arm 2
		
		drawClaw();  // Draw a claw at the end
		break;
	case 5:  // Bottom arm 3

		drawGun();  // Draw a gun at the end
		break;
	default:
		break;
	}
}

void drawSaw() {
	// Set material properties for saw
	glMaterialfv(GL_FRONT, GL_AMBIENT, saw_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, saw_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, saw_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, saw_mat_shininess);
	GLUquadric* quadric = gluNewQuadric();

	float sawRadius = 1.2;      // Radius of the saw
	float sawThickness = 0.1;  // Thickness of the saw (5% of the radius)

	// Draw the cylinder
	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0); // Align the cylinder along the z-axis
	gluCylinder(quadric, sawRadius, sawRadius, sawThickness, 50, 10);
	glPopMatrix();

	// Draw the bottom disk
	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0); // Align the disk with the cylinder base
	gluDisk(quadric, 0.0, sawRadius, 50, 10);
	glPopMatrix();

	// Draw the top disk
	glPushMatrix();
	glTranslatef(0.0, 0.0, sawThickness); // Move to the top of the cylinder
	glRotatef(90.0, 0.0, 1.0, 0.0); // Align the disk with the cylinder top
	gluDisk(quadric, 0.0, sawRadius, 50, 10);
	glPopMatrix();

	// Clean up the quadric object
	gluDeleteQuadric(quadric);
}

void drawGun() {

	// Set material properties for gun
	glMaterialfv(GL_FRONT, GL_AMBIENT, gun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gun_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, gun_mat_shininess);


	GLUquadric* quadric = gluNewQuadric(); // Create a new quadric object

	// Draw the cylinder
	gluQuadricDrawStyle(quadric, GLU_FILL);
	glPushMatrix();
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -gunLength / 2.0f); // Move down to center the cylinder
	gluCylinder(quadric, gunWidth, gunWidth, gunLength, 15, 1); // Draw the cylinder
	glPopMatrix(); // Restore the previous matrix

	int partAngle = 0;

	for (int i = 0; i < 4; i++) {
		partAngle += 90;

		glPushMatrix();
		
		glRotatef(partAngle, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, gunWidth, gunLength/2); // Move to the top of the cylinder
		

		glScalef(0.2, 0.2, 1);
		glutSolidCube(1.0);
		glPopMatrix();

	}



	// Draw the top disk
	glPushMatrix(); // Save the current matrix
	glTranslatef(0.0f, 0.0f, gunLength / 2.0f); // Move to the top of the cylinder
	gluDisk(quadric, 0.0f, gunWidth, 15, 1); // Draw the top disk
	glPopMatrix(); // Restore the previous matrix
	glPopMatrix();



	gluDeleteQuadric(quadric); // Clean up the quadric object
}

void drawEye() {
	// Set material properties for eyes
	glMaterialfv(GL_FRONT, GL_AMBIENT, eye_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, eye_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, eye_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, eye_mat_shininess);

	glPushMatrix();
	glutSolidSphere(eyeRadius, 15, 15);
	glPopMatrix();
}

void drawClaw() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, claw_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, claw_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, claw_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, claw_mat_shininess);
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glTranslatef(0, clawLength*0.25, -clawDepth * 0.5);
	// Draw the left part of the claw
	glPushMatrix();
	glTranslatef(-clawWidth / 2, 0.0f, 0.0f); // Position the left claw part
	glRotatef(-pinchAngle, 0.0f, 0.0f, 1.0f); // Rotate left part to close
	glScalef(clawLength, clawDepth, clawWidth); // Scale to create a flat cube
	glutSolidCube(1.0f); // Draw the left claw part
	glPopMatrix();

	// Draw the right part of the claw
	glPushMatrix();
	glTranslatef(clawWidth / 2, 0.0f, 0.0f); // Position the right claw part
	glRotatef(pinchAngle, 0.0f, 0.0f, 1.0f); // Rotate right part to close
	glScalef(clawLength, clawDepth, clawWidth); // Scale to create a flat cube
	glutSolidCube(1.0f); // Draw the right claw part
	glPopMatrix();
	glPopMatrix();
}




// Callback, called at initialization and whenever user resizes the window.
void reshape(int w, int h)
{
	// Set up viewport, projection, then change to modelview matrix mode - 
	// display function will then set up camera and do modeling transforms.
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)w / h, 0.2, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set up the camera at position (0, 6, 22) looking at the origin, up along positive y axis
	gluLookAt(0.0, 6.0, 22.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

bool stop = false;


// Function to update angles based on user input
void updateArmAngles(int armIndex, int joint, float deltaX, float deltaY, float deltaZ) {
	// Update angles based on joint selection
	if (joint == 0) { // Shoulder
		shoulderAngle[armIndex][0] += deltaX; // Up/Down
		shoulderAngle[armIndex][1] += deltaY; // Left/Right
		shoulderAngle[armIndex][2] += deltaZ; // Roll
	}
	else if (joint == 1) { // Elbow
		elbowAngle[armIndex][0] += deltaX; // Up/Down
		elbowAngle[armIndex][1] += deltaY; // Left/Right
		elbowAngle[armIndex][2] += deltaZ; // Roll
	}
	else if (joint == 2) { // End
		endAngle[armIndex][0] += deltaX; // Up/Down
		endAngle[armIndex][1] += deltaY; // Left/Right
		endAngle[armIndex][2] += deltaZ; // Roll
	}
}

// Callback, handles input from the keyboard, non-arrow keys
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		armSelection = 0;
		break;
	case '2':
		armSelection = 1;
		break;
	case '3':
		armSelection = 2;
		break;
	case '4':
		armSelection = 3;
		break;
	case '5':
		armSelection = 4;
		break;
	case '6':
		armSelection = 5;
		break;

	case 's':
		jointSelection = 0;
		break;
	case 'e':
		jointSelection = 1;
		break;
	case 'h':
		jointSelection = 2;
		break;
	case 'f':
		flameOn = true;
		glutTimerFunc(10, flame, 0);
		break;
	case 'F':
		flameOn = false;
		break;
	case 'r':
		robotAngle += 2.0;
		break;
	case 'R':
		robotAngle -= 2.0;
		break;
	case 'z':
		updateArmAngles(armSelection, jointSelection, 2.0, 0.0, 0.0); // Adjust up
		break;
	case 'Z':
		updateArmAngles(armSelection, jointSelection, -2.0, 0.0, 0.0); // Adjust down
		break;

	case 'x':
		updateArmAngles(armSelection, jointSelection, 0, 2, 0.0); // Rotate
		break;
	case 'X':
		updateArmAngles(armSelection, jointSelection, 0, -2, 0.0); // Rotate
		break;

	case 'v':
		updateArmAngles(armSelection, jointSelection, 0, 0, 2); // Rotate
		break;
	case 'V':
		updateArmAngles(armSelection, jointSelection, 0, 0, -2); // Rotate
		break;

		/*
	case 'x':
		updateArmAngles(armSelection, jointSelection, 0.0, 2.0, 0.0); // Adjust left/right
		break;
	case 'X':
		updateArmAngles(armSelection, jointSelection, 0.0, -2.0, 0.0); // Adjust left/right
		break;
	case 'c':
		updateArmAngles(armSelection, jointSelection, 0.0, 0.0, 2.0); // Adjust roll
		break;
	case 'C':
		updateArmAngles(armSelection, jointSelection, 0.0, 0.0, -2.0); // Adjust roll
		break;

		*/

	case 't':

		break;
		

	case 'p':
		pinching = true;
		glutTimerFunc(10, pinch, 0);
		break;
	case 'P':
		pinching = false;
		break;

	case 'c':
		glutTimerFunc(10, gunSpin, 0);
		stop = false;
		break;
	case 'C':
		stop = true;
		break;

	case 'w':
		walkPhase = 0;
		shoulderAngle[4][0] = -40;
		elbowAngle[4][0] = -40;
		glutTimerFunc(10, walker, 0);
		break;

	case 'W':
		walkPhase = -1;
		break;
	}

	glutPostRedisplay();   // Trigger a window redisplay
}




void gunSpin(int param)
{
	if (!stop)
	{
		endAngle[5][1] += 1.0;
		glutPostRedisplay();
		glutTimerFunc(10, gunSpin, 0);
	}
}


void pinch(int param)
{
	if (pinching)
	{
		if (pinched) {
			pinchAngle += 1;
			if (pinchAngle > 60) {
				pinched = 0;
			}
		}
		else {
			pinchAngle -= 1;
			if (pinchAngle < 0) {
				pinched = 1;
			}
		}
		glutPostRedisplay();
		glutTimerFunc(10, pinch, 0);
	}
}


void walker(int param) {
	float topAngle = shoulderAngle[4][0];
	float lowAngle = elbowAngle[4][0];

	switch (walkPhase)
	{
	case 0:
		if (topAngle > -60) {
			topAngle -= 1;
		}
		else { 
			walkPhase = 1; 
		}

		break;
	case 1:
		if (lowAngle < 0) {
			lowAngle += 1;
		}
		else {
			walkPhase = 2;
		}
		break;
	case 2:
		if (topAngle < 0) {
			topAngle += 1;
		}
		else {
			walkPhase = 3;
		}
		break;
	case 3:
		if (lowAngle > -40) {
			lowAngle -= 1;
		}
		else {
			walkPhase = 4;
		}
		break;
	case 4:
		if (topAngle > -40) {
			topAngle -= 1;
		}
		else {
			walkPhase = 0;
		}
		break;
	}

	shoulderAngle[4][0] = topAngle;
	elbowAngle[4][0] = lowAngle;

	glutPostRedisplay();
	glutTimerFunc(10, walker, 0);
}



// Callback, handles input from the keyboard, function and arrow keys
void functionKeys(int key, int x, int y)
{
	// Help key
	if (key == GLUT_KEY_F1)
	{
		if (showControls) {
			showControls = 0;
		}
		else { 
			showControls = 1;
		}
	} 

	glutPostRedisplay();   // Trigger a window redisplay
}
void drawControls() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, vWidth, 0, vHeight, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);

	const char* controls[] = {
		"Controls:",
		"F1 - Toggle Control Layout",
		"w/W - Walk Cycle/Stop",
		"c/C - spin gun/stop",
		"p/P - pinch claw/stop",
		"r/R - rotate bot",
		"1-6 - select limb",
		"s/e/h - select joint (shoulder, elbow, hand)",
		"z/Z - Rotate part by X (up/down)",
		"x/X - Rotate part by Y (roll)",
		"v/V - Rotate part by Z",
		"",
		"ESC - Exit"
	};

	int lineHeight = 20; // Space between lines
	int numLines = sizeof(controls) / sizeof(controls[0]);

	for (int i = 0; i < numLines; i++) {
		glRasterPos2f(10, vHeight - 30 - (i * lineHeight));
		for (const char* c = controls[i]; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


// Update the mouse function
void mouse(int button, int state, int x, int y)
{
	currentButton = button;

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			mouseDown = true;
			lastX = x;
			lastY = y;
		}
		else {
			mouseDown = false;
		}
	}
}

// Update the mouse motion handler
void mouseMotionHandler(int xMouse, int yMouse)
{
	if (mouseDown) {
		// Calculate the change in mouse position
		int deltaX = xMouse - lastX;
		int deltaY = yMouse - lastY;

		// Update camera angles
		cameraAngleX += (float)deltaX * 0.005f;
		cameraAngleY -= (float)deltaY * 0.005f;

		// Clamp the vertical angle to avoid flipping
		if (cameraAngleY < 0.1f) cameraAngleY = 0.1f;
		if (cameraAngleY > PI - 0.1f) cameraAngleY = PI - 0.1f;

		lastX = xMouse;
		lastY = yMouse;
		glutPostRedisplay();
	}
}

