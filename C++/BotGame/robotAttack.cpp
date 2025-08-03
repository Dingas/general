#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <cmath>
//#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <algorithm> 

int windowWidth = 800;
int windowHeight = 600;

// NEW STUFF

// shield stuff (Didn't make the cut)
int shieldCharges = 3;  // Number of shield charges
bool shieldActive = false;  // Is the shield currently active
float shieldFlashTime = 0.0f;  // Time when the shield was last activated
const float SHIELD_FLASH_DURATION = 0.5f;  // Duration of the shield flash

//Mersenne Twister rng stuff
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(0, 2);

// Global texture variables
GLuint steelTexture;      // For body and arms
GLuint eyeTexture;        // For robot eyes
GLuint thrusterTexture;   // For thrusters
GLuint metalTexture;


// Structure for vertices from OBJ file
struct OBJVertex {
    GLdouble x, y, z;
    GLdouble nx, ny, nz;
};

// Explosion struct
struct Explosion {
    float posX, posY, posZ;  // Position
    float size;              // Current size
    float maxSize;           // Maximum size
    float lifetime;          // How long the explosion lasts
    float startTime;         // When the explosion started
    bool active;             // Whether the explosion is active
};

// Vector to store active explosions
std::vector<Explosion> explosions;

// Mr. Handy
struct Robot {
    float posX, posY=5, posZ;
    float rotY;
    float thrust;
    float pinchAngle = 10;
    bool isAlive;
    bool pinched = 0;
    bool walker;
    int armSelection = 0;
    int jointSelection = 0;
    int walkPhase = 0;

    float nextShootTime;    // When this robot will next shoot
    bool canShoot;          // Whether this robot can shoot

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

    float arm1Rot, arm2Rot;
    float leg1Rot, leg2Rot;
    float armRotation;
    float legRotation;
};

struct Projectile {
    float posX, posY, posZ;
    float dirX, dirY, dirZ;
    bool active;
    bool fromCannon;
};

// Global variables
std::vector<OBJVertex> objVertices;
std::vector<int> objFaces;
std::vector<Robot> robots;
std::vector<Projectile> projectiles;

float eye[3] = { 0.0f, 10.0f, 15.0f };
float center[3] = { 0.0f, 0.0f, 0.0f };
float up[3] = { 0.0f, 1.0f, 0.0f };

int lastMouseX = 0, lastMouseY = 0;
bool mousePressed = false;
float cannonPitch = 0.0f; // Vertical angle
bool laserMode = false;
float laserCooldown = 0.0f;
const float LASER_FIRE_RATE = 0.1f;  // Fire a laser every 0.1 seconds

int kills = 0;
const float MIN_SHOOT_DELAY = 1.0f;  // Minimum time between shots (seconds)
const float MAX_SHOOT_DELAY = 6.0f;  // Maximum time between shots (seconds)

//Handy
float robotBodyRadius = 2;
float upperArmLength = robotBodyRadius * 0.75;
float upperArmWidth = 0.125 * robotBodyRadius;
float lowerArmLength = robotBodyRadius * 0.75;
float lowerArmWidth = 0.125 * robotBodyRadius;
float gunLength = upperArmLength / 4;
float gunWidth = upperArmWidth;
float gunDepth = upperArmWidth;
float sawRadius = 0.3;
float sawThickness = 0.7;
float eyeRadius = 0.5;
float clawLength = 0.8;
float clawWidth = 0.5;
float clawDepth = 0.3;
float pinchAngle = 45;
float stanchionLength = robotBodyRadius;
float stanchionRadius = 0.1 * robotBodyRadius;
float baseWidth = 2 * robotBodyRadius;
float baseLength = 0.25 * stanchionLength;
float engineHeight = 0.5;
float coneHeight = 0.5;
float thrust = 0;
float jointRadius = 0.2;

float endObjectScale[6][3] = {
    {eyeRadius, eyeRadius, eyeRadius}, // Arm 0
    {eyeRadius, eyeRadius, eyeRadius}, // Arm 1
    {eyeRadius, eyeRadius, eyeRadius}, // Arm 2
    {sawRadius, sawRadius, sawThickness}, // Arm 3
    {clawLength, clawWidth, clawDepth}, // Arm 4
    {gunLength, gunWidth, gunDepth}  // Arm 5
};




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
GLfloat eye_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // White for eyes (remember to add more detail, not just white balls)
GLfloat eye_mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat eye_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat eye_mat_shininess[] = { 32.0f };

GLfloat saw_mat_ambient[] = { 0.8f, 0.4f, 0.2f, 1.0f }; // Brown/gold(?) for pizza cutter
GLfloat saw_mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat saw_mat_diffuse[] = { 0.8f, 0.4f, 0.2f, 1.0f };
GLfloat saw_mat_shininess[] = { 32.0f };

GLfloat claw_mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Gray for pinchy
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


bool anyRobotsAlive();

void drawRobotBody(const Robot& robot, float x, float y, float z, float angle);
void drawRobotArm(const Robot& robot, float x, float y, float z, float shoulderAngle, float elbowAngle);
void drawRobotEye(const Robot& robot, float x, float y, float z);
void drawCylinder(float radius, float height);
void drawCone(float baseRadius, float height);
void drawBody(const Robot& robot);
void drawArm(const Robot& robot);
void drawThruster(const Robot& robot);
void drawEye(const Robot& robot);
void drawSaw(const Robot& robot);
void drawClaw(const Robot& robot);
void drawGun(const Robot& robot);
void drawRobot(const Robot& robot);
void drawEndObject(const Robot& robot, int armIndex);

void hits();
void drawText();

// Cannon position
float cannonX = 0.0f;
float cannonY = 0.0f;
float cannonZ = 10.0f;
float cannonRotation = 0.0f;

bool cannonDestroyed = false;

// Game state
bool gameActive = true;
int currentWave = 1;
float lastTime = 0;
bool firstPersonView = false;  // Start in third-person view

// Function prototypes
void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void update(int value);
void spawnRobotWave();
bool importMeshFromOBJ(const char* filename);
void drawCannon();
void drawProjectiles();
void drawGround();

void mouseMotion(int x, int y);
void mouseButton(int button, int state, int x, int y);

// Import mesh function
bool importMeshFromOBJ(const char* filename) {
    FILE* file = nullptr;
    errno_t err;

    const char* paths[] = {
        "cannon.obj",
        "../511_A3/cannon.obj",
        "../../511_A3/cannon.obj",
        "../511_A3/511_A3/cannon.obj"
    };

    for (const char* path : paths) {
        err = fopen_s(&file, path, "r");
        if (err == 0 && file != nullptr) {
            printf("Successfully opened file: %s\n", path);
            break;
        }
    }

    if (!file) {
        printf("Error: Could not find cannon.obj in any of the expected locations\n");
        return false;
    }

    objVertices.clear();
    objFaces.clear();

    char line[256];
    std::vector<GLdouble> normals;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            OBJVertex v = { 0 };
            if (sscanf_s(line, "v %lf %lf %lf", &v.x, &v.y, &v.z) == 3) {
                objVertices.push_back(v);
            }
        }
        else if (line[0] == 'v' && line[1] == 'n') {
            GLdouble nx, ny, nz;
            if (sscanf_s(line, "vn %lf %lf %lf", &nx, &ny, &nz) == 3) {
                normals.push_back(nx);
                normals.push_back(ny);
                normals.push_back(nz);
            }
        }
    }

    fseek(file, 0, SEEK_SET);

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'f') {
            int v1, v2, v3, v4, n1, n2, n3, n4;
            if (sscanf_s(line, "f %d//%d %d//%d %d//%d %d//%d",
                &v1, &n1, &v2, &n2, &v3, &n3, &v4, &n4) == 8) {
                objFaces.push_back(v1 - 1);
                objFaces.push_back(v2 - 1);
                objFaces.push_back(v3 - 1);
                objFaces.push_back(v4 - 1);

                if (v1 <= objVertices.size() && n1 <= normals.size() / 3) {
                    objVertices[v1 - 1].nx = normals[(n1 - 1) * 3];
                    objVertices[v1 - 1].ny = normals[(n1 - 1) * 3 + 1];
                    objVertices[v1 - 1].nz = normals[(n1 - 1) * 3 + 2];
                }
            }
        }
    }

    fclose(file);
    printf("Loaded %zu vertices and %zu faces\n", objVertices.size(), objFaces.size() / 4);
    return !objVertices.empty() && !objFaces.empty();
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

GLuint loadTexture(const char* filename) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

    if (data) {
        // Determine format based on number of channels
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else {
            printf("Unsupported image format: %s (channels: %d)\n", filename, nrChannels);
            stbi_image_free(data);
            return 0;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        printf("Successfully loaded texture: %s (%dx%d, %d channels)\n",
            filename, width, height, nrChannels);
    }
    else {
        printf("Failed to load texture: %s\n", filename);
        return 0;
    }

    stbi_image_free(data);
    return textureID;
}

// Initialize OpenGL settings and game state
void init() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    // Set up lighting
    GLfloat light_position[] = { 10.0f, 10.0f, 10.0f, 1.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Enable texturing
    glEnable(GL_TEXTURE_2D);

    // Load the steel texture
    steelTexture = loadTexture("steel.jpg");
    metalTexture = loadTexture("metal.jpg");

    // Set texture environment to MODULATE (combines texture with lighting)
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


    // Load cannon mesh
    if (!importMeshFromOBJ("cannon.obj")) {
        printf("Failed to load cannon mesh!\n");
    }

    // Spawn initial wave of Mr. Handy
    spawnRobotWave();
}

// Function to check if any robots are alive
bool anyRobotsAlive() {
    return std::any_of(robots.begin(), robots.end(), [](const Robot& robot){
        return robot.isAlive;
        });
}

void drawShield() {
    if (shieldActive) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(0.0f, 0.0f, 1.0f, 0.05f);  // Blue color with 5% opacity
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(windowWidth, 0);
        glVertex2f(windowWidth, windowHeight);
        glVertex2f(0, windowHeight);
        glEnd();

        glDisable(GL_BLEND);
    }
}

// Spawn a new wave of robots
void spawnRobotWave() {
    robots.clear();
    projectiles.clear();
    gameActive = true;
    int numRobots = 2 + currentWave; // Increase number of robots each wave
    std::cout << "Spawning wave " << currentWave << " with " << numRobots << " robots" << std::endl;

    for (int i = 0; i < numRobots; i++) {
        Robot robot;
        if (dist(gen) == 0) { robot.walker = true; } //1/3 robots will be crawling
        robot.posX = -20.0f + (rand() % 40); // Random X position
        robot.posZ = -30.0f - (rand() % 20); // Random starting distance
        robot.posY = 0.0f;
        robot.rotY = 0.0f;
        robot.isAlive = true;
        robot.nextShootTime = MIN_SHOOT_DELAY +
            ((float)rand() / RAND_MAX) * (MAX_SHOOT_DELAY - MIN_SHOOT_DELAY);
        robots.push_back(robot);
    }
}

void drawExplosions() {
    // Set up explosion material (bright orange/yellow)
    GLfloat explosion_mat_ambient[] = { 0.8f, 0.4f, 0.0f, 1.0f };
    GLfloat explosion_mat_diffuse[] = { 1.0f, 0.6f, 0.0f, 1.0f };
    GLfloat explosion_mat_specular[] = { 1.0f, 1.0f, 0.5f, 1.0f };
    GLfloat explosion_mat_shininess[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, explosion_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, explosion_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, explosion_mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, explosion_mat_shininess);

    // Enable blending for a more realistic explosion effect
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (const auto& explosion : explosions) {
        if (explosion.active) {
            glPushMatrix();
            glTranslatef(explosion.posX, explosion.posY, explosion.posZ);

            // Make the explosion a bit transparent
            float alpha = 1.0f - (explosion.size / explosion.maxSize);
            glColor4f(1.0f, 0.6f, 0.0f, alpha);

            // Draw the explosion as a sphere
            glutSolidSphere(explosion.size, 16, 16);

            glPopMatrix();
        }
    }

    glDisable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  // Reset color
}


// Draw the cannon using loaded mesh
void drawCannon() {
    glPushMatrix();
    glTranslatef(cannonX, cannonY, cannonZ);

    // Apply yaw (horizontal rotation)
    glRotatef(cannonRotation, 0.0f, 1.0f, 0.0f);

    // Apply pitch (vertical rotation)
    glRotatef(cannonPitch, 1.0f, 0.0f, 0.0f);

    // Rotate the cannon to be horizontal instead of vertical
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat mat_shininess[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, steelTexture);

    glBegin(GL_QUADS);
    for (size_t i = 0; i < objFaces.size(); i += 4) {
        for (int j = 0; j < 4; j++) {
            int idx = objFaces[i + j];
            glNormal3f(objVertices[idx].nx, objVertices[idx].ny, objVertices[idx].nz);

            // Add texture coordinates based on vertex position
            // This is a simple mapping - you might need to adjust based on your model
            float u = (objVertices[idx].x + 1.0f) / 2.0f;  // Map [-1,1] to [0,1]
            float v = (objVertices[idx].y + 1.0f) / 2.0f;  // Map [-1,1] to [0,1]
            glTexCoord2f(u, v);

            glVertex3f(objVertices[idx].x, objVertices[idx].y, objVertices[idx].z);
        }
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


void drawGround() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, steelTexture);

    // Set material properties
    GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat mat_shininess[] = { 8.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Draw a large textured quad for the ground
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);  // Normal pointing up

    float size = 100.0f;  // Size of the ground plane

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, 0.0f, -size);
    glTexCoord2f(10.0f, 0.0f); glVertex3f(size, 0.0f, -size);
    glTexCoord2f(10.0f, 10.0f); glVertex3f(size, 0.0f, size);
    glTexCoord2f(0.0f, 10.0f); glVertex3f(-size, 0.0f, size);

    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void drawProjectiles() {
    // Draw laser beam if laser mode is active
    if (laserMode&&!cannonDestroyed) {
        // Calculate laser start and end points
        float yawRad = cannonRotation * 3.14159f / 180.0f;
        float pitchRad = cannonPitch * 3.14159f / 180.0f;

        float barrelLength = 2.0f;
        float startX = cannonX - sin(yawRad) * cos(pitchRad) * barrelLength;
        float startY = cannonY + sin(pitchRad) * barrelLength + 0.5f;
        float startZ = cannonZ - cos(yawRad) * cos(pitchRad) * barrelLength;

        float laserLength = 100.0f;
        float endX = startX - sin(yawRad) * cos(pitchRad) * laserLength;
        float endY = startY + sin(pitchRad) * laserLength;
        float endZ = startZ - cos(yawRad) * cos(pitchRad) * laserLength;

        // Draw laser as a line
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);

        glBegin(GL_LINES);
        glVertex3f(startX, startY, startZ);
        glVertex3f(endX, endY, endZ);
        glEnd();

        glEnable(GL_LIGHTING);
    }

    // Draw regular projectiles
    for (const auto& proj : projectiles) {
        if (proj.active) {
            GLfloat proj_ambient[] = { 0.2f, 0.2f, 0.8f, 1.0f };
            GLfloat proj_diffuse[] = { 0.2f, 0.2f, 0.8f, 1.0f };
            GLfloat proj_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
            GLfloat proj_shininess[] = { 100.0f };

            glMaterialfv(GL_FRONT, GL_AMBIENT, proj_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, proj_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, proj_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, proj_shininess);

            glPushMatrix();
            glTranslatef(proj.posX, proj.posY, proj.posZ);
            glutSolidSphere(0.1f, 10, 10);
            glPopMatrix();
        }
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Robot Attack Game");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);

    // Set up timer for animation
    glutTimerFunc(16, update, 0);
    glutMainLoop();
    return 0;
}


void drawRobot(const Robot& robot)
{
    glPushMatrix();
    // spin robot on base. 
    glTranslatef(0, 3, 0);
    glRotatef(robot.robotAngle, 0.0, 1.0, 0.0);

    drawBody(robot);

    drawArm(robot);
    glPopMatrix();

    glPopMatrix();
}


void drawBody(const Robot& robot)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, robotBody_mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, robotBody_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, robotBody_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, robotBody_mat_shininess);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, steelTexture);

    // Create a quadric object for textured sphere
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);  // Enable texture coordinates
    gluQuadricNormals(quadric, GLU_SMOOTH);  // Enable smooth normals

    // Draw the body sphere
    glPushMatrix();
    glScalef(robotBodyRadius, robotBodyRadius, robotBodyRadius);
    gluSphere(quadric, 0.5, 20, 20);  // Replace glutSolidSphere with gluSphere
    glPopMatrix();

    // Draw the cylinder (engine)
    glPushMatrix();
    glTranslatef(0.0f, -0.4 * robotBodyRadius, 0.0f); // Position it at the bottom of the sphere
    glRotatef(90, 1.0f, 0.0f, 0.0f); // Align the cylinder vertically
    glScalef(0.2, 0.5, 1);
    
    // Use the quadric for the cylinder too
    gluCylinder(quadric, 1.0, 1.0, engineHeight, 20, 5);
    glPopMatrix();

    // Change material for flame
    glMaterialfv(GL_FRONT, GL_AMBIENT, flame_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, flame_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, flame_mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, flame_mat_shininess);
    
    // Draw the flame
    glPushMatrix();
    glTranslatef(0.0f, -0.4 * robotBodyRadius - engineHeight, 0.0f); // Position it at the end of the cylinder
    glRotatef(90, 1.0f, 0.0f, 0.0f); // Align the cone vertically
    
    // Use the quadric for the cone too
    float flameRadius = 1.0 * robot.thrust * 0.2;
    float flameHeight = coneHeight + robot.thrust;
    gluCylinder(quadric, flameRadius, 0.0, flameHeight, 20, 5);  // Cone is cylinder with 0 top radius
    glPopMatrix();

    // Clean up
    gluDeleteQuadric(quadric);
    glDisable(GL_TEXTURE_2D);
}

void drawArm(const Robot& robot) {


    int hemisphere = 1;

    for (int i = 0; i < 6; i++) {
        if (i > 2) {
            hemisphere = -1;
        }
        glMaterialfv(GL_FRONT, GL_AMBIENT, robotArm_mat_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, robotArm_mat_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, robotArm_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SHININESS, robotArm_mat_shininess);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, steelTexture);

        glPushMatrix();
        


        float angle = (i % 3) * 120.0f; // 120 degrees apart
        glRotatef(angle, 0.0, 1.0, 0.0); // Rotate around Y-axis to position arms

        // Position the arm on the sphere's surface
        glTranslatef(0, hemisphere * robotBodyRadius / 4, robotBodyRadius / 2);
        glRotatef(robot.shoulderAngle[i][0], 1.0, 0.0, 0.0);
        glRotatef(robot.shoulderAngle[i][1], 0.0, 1.0, 0.0);
        glRotatef(robot.shoulderAngle[i][2], 0.0, 0.0, 1.0);

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


        glutSolidSphere(jointRadius, 15, 15);
        glPopMatrix();


        //lower arm
        glPushMatrix();
        
        glTranslatef(-(0.5 * robotBodyRadius + 0.5 * upperArmWidth), -(upperArmLength), 0.0);
        glRotatef(robot.elbowAngle[i][0], 1.0, 0.0, 0.0);
        glRotatef(robot.elbowAngle[i][1], 0, 1, 0.0);
        glRotatef(robot.elbowAngle[i][2], 0, 0.0, 1);
        glTranslatef((0.5 * robotBodyRadius + 0.5 * upperArmWidth), -(0.5 * upperArmLength), 0.0);

        glScalef(upperArmWidth, upperArmLength, upperArmWidth);

        glutSolidCube(1.0);
        glPopMatrix();


        //end part
        glPushMatrix();
        
        glTranslatef(-(0.5 * robotBodyRadius + 0.5 * upperArmWidth), -(upperArmLength), 0.0);
        glRotatef(robot.elbowAngle[i][0], 1.0, 0.0, 0.0);
        //glRotatef(robot.elbowAngle[i][1], 0, 1, 0.0);
        //glRotatef(robot.elbowAngle[i][2], 0, 0.0, 1);
        glTranslatef((0.5 * robotBodyRadius + 0.5 * upperArmWidth), (0.5 * upperArmLength), 0.0);



        glTranslatef(0, -(lowerArmLength + lowerArmLength * 0.5), 0.0);
        //glScalef(endObjectScale[i][0], endObjectScale[i][1], endObjectScale[i][2]);
        glRotatef(robot.endAngle[i][0], 1.0, 0.0, 0.0);
        glRotatef(robot.endAngle[i][1], 0, 1, 0.0);
        glRotatef(robot.endAngle[i][2], 0, 0.0, 1);

        drawEndObject(robot, i);
        glPopMatrix();

        glPopMatrix();

    }


}



// Function to draw different end objects with materials
void drawEndObject(const Robot& robot, int armIndex) {
    switch (armIndex) {
    case 0:  // Top arm 1
    case 1:  // Top arm 2
    case 2:  // Top arm 3

        drawEye(robot);  // Draw an eye at the end
        break;
    case 3:  // Bottom arm 1

        drawSaw(robot);  // Draw a saw at the end
        break;
    case 4:  // Bottom arm 2

        drawClaw(robot);  // Draw a claw at the end
        break;
    case 5:  // Bottom arm 3

        drawGun(robot);  // Draw a gun at the end
        break;
    default:
        break;
    }
}

void drawSaw(const Robot& robot) {
    // Set material properties for saw
    glMaterialfv(GL_FRONT, GL_AMBIENT, saw_mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, saw_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, saw_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, saw_mat_shininess);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, steelTexture);
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

void drawGun(const Robot& robot) {

    // Set material properties for gun
    glMaterialfv(GL_FRONT, GL_AMBIENT, gun_mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, gun_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, gun_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, gun_mat_shininess);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, steelTexture);


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
        glTranslatef(0.0f, gunWidth, gunLength / 2); // Move to the top of the cylinder


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

void drawEye(const Robot& robot) {
    // Set material properties for eyes
    glMaterialfv(GL_FRONT, GL_AMBIENT, eye_mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, eye_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, eye_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, eye_mat_shininess);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, steelTexture);

    glPushMatrix();
    glutSolidSphere(eyeRadius, 15, 15);
    glPopMatrix();
}

void drawClaw(const Robot& robot) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, claw_mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, claw_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, claw_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, claw_mat_shininess);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, steelTexture);
    glPushMatrix();
    glRotatef(180, 1, 0, 0);
    glTranslatef(0, clawLength * 0.25, -clawDepth * 0.5);
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




void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:  // ESC key
        exit(0);
        break;
    case 'a':
        cannonRotation += 5.0f;
        break;
    case 'd':
        cannonRotation -= 5.0f;
        break;
    case 'v':
        // Toggle between first-person and third-person view
        firstPersonView = !firstPersonView;
        break;
    case 'f':
        // Toggle laser mode
        laserMode = !laserMode;
        break;

    case 'g':
        
        if (!gameActive && !cannonDestroyed) {
            currentWave++;
            spawnRobotWave();
        }
        break;

    case 'r':
        kills = 0;
        currentWave = 1;
        spawnRobotWave();
        cannonDestroyed = false;
        cannonPitch = 0;
    break;
    case ' ':  // Spacebar to fire cannon
    {
        if (!cannonDestroyed) {
            // Calculate spawn position at the end of the cannon barrel
            float yawRad = cannonRotation * 3.14159f / 180.0f;
            float pitchRad = cannonPitch * 3.14159f / 180.0f;

            // Offset from cannon center to barrel end (adjust these values based on your cannon model)
            float barrelLength = 2.0f;  // Length of the cannon barrel

            // Calculate spawn position
            float spawnX = cannonX - sin(yawRad) * cos(pitchRad) * barrelLength;
            float spawnY = cannonY + sin(pitchRad) * barrelLength + 0.5f;  // Add height offset
            float spawnZ = cannonZ - cos(yawRad) * cos(pitchRad) * barrelLength;

            Projectile proj;
            proj.posX = spawnX;
            proj.posY = spawnY;
            proj.posZ = spawnZ;

            // Direction is the same as before
            proj.dirX = -sin(yawRad) * cos(pitchRad);
            proj.dirY = sin(pitchRad);
            proj.dirZ = -cos(yawRad) * cos(pitchRad);

            proj.active = true;
            proj.fromCannon = true;
            projectiles.push_back(proj);
        };
    }
    break;
    }
    glutPostRedisplay();
}
/*
void hits() {
    kills += 1;
    if (kills >= (currentWave + 3)) {
        gameActive = false;
    }
}
*/

void update(int value) {
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // Variables for distance calculations (declared once)
    float dx, dy, dz, distSq, t, length;
    float closestX, closestY, closestZ;
    float distX, distY, distZ;

    // Check if all robots are destroyed
    if (!anyRobotsAlive() && gameActive) {
        gameActive = false;  // End the current wave
    }

    // Update explosions
    for (auto& explosion : explosions) {
        if (explosion.active) {
            float elapsed = currentTime - explosion.startTime;
            if (elapsed >= explosion.lifetime) {
                explosion.active = false;
            }
            else {
                // Update explosion size based on lifetime
                float progress = elapsed / explosion.lifetime;
                // Grow quickly, then shrink
                if (progress < 0.3f) {
                    explosion.size = explosion.maxSize * (progress / 0.3f);
                }
                else {
                    explosion.size = explosion.maxSize * (1.0f - ((progress - 0.3f) / 0.7f));
                }
            }
        }
    }

    // Laser mode hit detection
    if (laserMode) {
        // Calculate laser start and direction
        float yawRad = cannonRotation * 3.14159f / 180.0f;
        float pitchRad = cannonPitch * 3.14159f / 180.0f;

        float barrelLength = 2.0f;
        float startX = cannonX - sin(yawRad) * cos(pitchRad) * barrelLength;
        float startY = cannonY + sin(pitchRad) * barrelLength + 0.5f;
        float startZ = cannonZ - cos(yawRad) * cos(pitchRad) * barrelLength;

        float dirX = -sin(yawRad) * cos(pitchRad);
        float dirY = sin(pitchRad);
        float dirZ = -cos(yawRad) * cos(pitchRad);

        // Check each robot for laser intersection
        for (auto& robot : robots) {
            if (robot.isAlive) {
                // Simple ray-sphere intersection test
                dx = robot.posX - startX;
                dy = (robot.posY + 1.0f) - startY;  // Aim at robot center
                dz = robot.posZ - startZ;

                // Project robot position onto laser ray
                t = dx * dirX + dy * dirY + dz * dirZ;

                // Find closest point on ray to robot center
                closestX = startX + dirX * t;
                closestY = startY + dirY * t;
                closestZ = startZ + dirZ * t;

                // Check if this point is within robot's "radius"
                distX = closestX - robot.posX;
                distY = closestY - (robot.posY + 1.0f);
                distZ = closestZ - robot.posZ;
                distSq = distX * distX + distY * distY + distZ * distZ;

                // More generous laser hit detection
                if (distSq < 1.5f * 1.5f && t > 0) {  // Hit if distance < 1.5 and in front of laser
                    // Create explosion at robot position
                    Explosion exp;
                    exp.posX = robot.posX;
                    exp.posY = robot.posY + 1.0f;  // Center of robot
                    exp.posZ = robot.posZ;
                    exp.maxSize = 3.0f;
                    exp.size = 0.1f;  // Start small
                    exp.lifetime = 1.0f;  // Last for 1 second
                    exp.startTime = currentTime;
                    exp.active = true;
                    explosions.push_back(exp);

                    robot.isAlive = false;
                    kills += 1;
                }
            }
        }
    }

    // Update projectiles and check for collisions
    for (size_t i = 0; i < projectiles.size(); i++) {
        auto& proj = projectiles[i];
        if (proj.active) {
            // Update projectile position
            proj.posX += proj.dirX * 10.0f * deltaTime;
            proj.posY += proj.dirY * 10.0f * deltaTime;
            proj.posZ += proj.dirZ * 10.0f * deltaTime;

            // Check for collisions with other projectiles
            for (size_t j = i + 1; j < projectiles.size(); j++) {
                auto& other = projectiles[j];
                if (other.active && proj.fromCannon != other.fromCannon) {
                    // Only check collisions between player and enemy projectiles
                    dx = other.posX - proj.posX;
                    dy = other.posY - proj.posY;
                    dz = other.posZ - proj.posZ;
                    distSq = dx * dx + dy * dy + dz * dz;

                    // More generous projectile-projectile collision
                    if (distSq < (0.6f * 0.6f)) {
                        // Create small explosion at collision point (How many big booms we givin' it?)
                        Explosion exp;
                        exp.posX = (proj.posX + other.posX) / 2.0f;  // Midpoint
                        exp.posY = (proj.posY + other.posY) / 2.0f;
                        exp.posZ = (proj.posZ + other.posZ) / 2.0f;
                        exp.maxSize = 1.0f;  // Smaller explosion
                        exp.size = 0.1f;
                        exp.lifetime = 0.5f;  // Shorter lifetime
                        exp.startTime = currentTime;
                        exp.active = true;
                        explosions.push_back(exp);

                        proj.active = false;
                        other.active = false;
                        break;  // This projectile is now inactive
                    }
                }
            }

            // If still active, check for collisions with robots (only player projectiles)
            if (proj.active && proj.fromCannon) {
                for (auto& robot : robots) {
                    if (robot.isAlive) {
                        // Simple sphere-sphere collision test
                        dx = robot.posX - proj.posX;
                        dy = (robot.posY + 1.0f) - proj.posY;
                        dz = robot.posZ - proj.posZ;
                        distSq = dx * dx + dy * dy + dz * dz;

                        // More generous projectile-robot collision
                        if (distSq < (1.8f * 1.8f)) {
                            // Create explosion at robot position (big boom)
                            Explosion exp;
                            exp.posX = robot.posX;
                            exp.posY = robot.posY + 1.0f;  // Center of robot
                            exp.posZ = robot.posZ;
                            exp.maxSize = 3.0f;
                            exp.size = 0.1f;
                            exp.lifetime = 1.0f;
                            exp.startTime = currentTime;
                            exp.active = true;
                            explosions.push_back(exp);

                            robot.isAlive = false;
                            proj.active = false;
                            kills += 1;
                            break;
                        }
                    }
                }
            }

            // Check if enemy projectile hits the cannon
            if (proj.active && !proj.fromCannon) {
                dx = cannonX - proj.posX;
                dy = (cannonY + 0.5f) - proj.posY;
                dz = cannonZ - proj.posZ;
                distSq = dx * dx + dy * dy + dz * dz;

                // Keep cannon hit detection the same to maintain game balance
                if (distSq < (1.5f * 1.5f)) {  // Assuming cannon radius of 1.5
                    proj.active = false;
                    cannonDestroyed = true;
                    cannonPitch = -45;

                }
            }

            // Deactivate projectiles that go too far
            if (proj.posZ < -100.0f || proj.posZ > 100.0f ||
                proj.posX < -100.0f || proj.posX > 100.0f ||
                proj.posY < -10.0f || proj.posY > 100.0f) {
                proj.active = false;
            }
        }
    }

    // Update robot positions and animations
    for (auto& robot : robots) {
        if (robot.isAlive) {
            robot.posZ += 2.0f * deltaTime;  // Move forward

            // Check if it's time for this robot to shoot
            if (currentTime >= robot.nextShootTime) {
                // Create a new projectile from the robot
                Projectile proj;
                proj.posX = robot.posX;
                proj.posY = robot.posY + 1.0f;  // Shoot from robot "head"
                proj.posZ = robot.posZ;

                // Calculate direction toward cannon
                dx = cannonX - robot.posX;
                dy = (cannonY + 1.0f) - (robot.posY + 1.0f);
                dz = cannonZ - robot.posZ;

                // Normalize direction vector
                length = sqrt(dx * dx + dy * dy + dz * dz);
                proj.dirX = dx / length;
                proj.dirY = dy / length;
                proj.dirZ = dz / length;

                // Add some randomness to make it not perfectly accurate
                proj.dirX += ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
                proj.dirY += ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
                proj.dirZ += ((float)rand() / RAND_MAX - 0.5f) * 0.1f;

                // Re-normalize
                length = sqrt(proj.dirX * proj.dirX + proj.dirY * proj.dirY + proj.dirZ * proj.dirZ);
                proj.dirX /= length;
                proj.dirY /= length;
                proj.dirZ /= length;

                proj.active = true;
                proj.fromCannon = false;  // Mark as enemy projectile
                projectiles.push_back(proj);

                // Schedule next shot
                robot.nextShootTime = currentTime + MIN_SHOOT_DELAY +
                    ((float)rand() / RAND_MAX) * (MAX_SHOOT_DELAY - MIN_SHOOT_DELAY);
            }

            // Animations
            // Thruster
            thrust = rand() * 0.0001;

            // Walker animation
            if (robot.walker) {
                float topAngle = robot.shoulderAngle[4][0];
                float lowAngle = robot.elbowAngle[4][0];

                switch (robot.walkPhase) {
                case 0:
                    if (topAngle > -60) {
                        topAngle -= 1;
                    }
                    else {
                        robot.walkPhase = 1;
                    }
                    break;
                case 1:
                    if (lowAngle < 0) {
                        lowAngle += 1;
                    }
                    else {
                        robot.walkPhase = 2;
                    }
                    break;
                case 2:
                    if (topAngle < 0) {
                        topAngle += 1;
                    }
                    else {
                        robot.walkPhase = 3;
                    }
                    break;
                case 3:
                    if (lowAngle > -40) {
                        lowAngle -= 1;
                    }
                    else {
                        robot.walkPhase = 4;
                    }
                    break;
                case 4:
                    if (topAngle > -40) {
                        topAngle -= 1;
                    }
                    else {
                        robot.walkPhase = 0;
                    }
                    break;
                }

                robot.shoulderAngle[4][0] = topAngle;
                robot.elbowAngle[4][0] = lowAngle;
            }

            // Gun spin animation
            robot.endAngle[5][1] += 1.0;

            // Pinch animation
            if (robot.pinched == 0) {
                robot.pinchAngle += 1;
                if (robot.pinchAngle > 60) {
                    robot.pinched = 0;
                }
            }
            else {
                robot.pinchAngle -= 1;
                if (robot.pinchAngle < 0) {
                    robot.pinched = 1;
                }
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // Schedule next update
}



// Main display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float yawRad = cannonRotation * 3.14159f / 180.0f;
    float pitchRad = cannonPitch * 3.14159f / 180.0f;

    if (firstPersonView) {
        // First-person view (from cannon perspective)
        float camX = cannonX;
        float camY = cannonY + 1.0f;
        float camZ = cannonZ;

        float lookX = camX - sin(yawRad) * cos(pitchRad);
        float lookY = camY + sin(pitchRad);
        float lookZ = camZ - cos(yawRad) * cos(pitchRad);

        gluLookAt(camX, camY, camZ,
            lookX, lookY, lookZ,
            0.0f, 1.0f, 0.0f);
    }
    else {
        // Third-person view (above and behind cannon)
        // Calculate position behind the cannon based on its rotation
        float camDistance = 10.0f;  // Distance behind cannon
        float camHeight = 8.0f;    // Height above cannon

        float camX = cannonX + sin(yawRad) * camDistance;
        float camY = cannonY + camHeight;
        float camZ = cannonZ + cos(yawRad) * camDistance;

        // Look at a point slightly in front of the cannon
        float lookX = cannonX - sin(yawRad) * 10.0f;
        float lookY = cannonY + 0.5f + sin(pitchRad) * 5.0f;  // Adjust based on pitch
        float lookZ = cannonZ - cos(yawRad) * 10.0f;

        gluLookAt(camX, camY, camZ,
            lookX, lookY, lookZ,
            0.0f, 1.0f, 0.0f);

        // Draw explosions
        drawExplosions();

        if (!gameActive || cannonDestroyed) {
            drawText();
        }
    }

    // Draw ground
    drawGround();

    // Draw cannon (only in third-person view)
    if (!firstPersonView) {
        drawCannon();
    }

    // Draw robots
    for (const auto& robot : robots) {
        if (robot.isAlive) {
            glPushMatrix();
            glTranslatef(robot.posX, robot.posY, robot.posZ);
            glRotatef(robot.rotY, 0.0f, 1.0f, 0.0f);
            drawRobot(robot);
            glPopMatrix();
        }
    }

    // Draw projectiles
    drawProjectiles();
    drawText();
    glutSwapBuffers();
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mousePressed = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP) {
            mousePressed = false;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Fire cannon on right click
        Projectile proj;
        proj.posX = cannonX;
        proj.posY = cannonY + 1.0f;
        proj.posZ = cannonZ;

        // Calculate direction based on cannon rotation and pitch
        float yawRad = cannonRotation * 3.14159f / 180.0f;
        float pitchRad = cannonPitch * 3.14159f / 180.0f;

        proj.dirX = -sin(yawRad) * cos(pitchRad);
        proj.dirY = sin(pitchRad);
        proj.dirZ = -cos(yawRad) * cos(pitchRad);

        proj.active = true;
        proj.fromCannon = true;
        projectiles.push_back(proj);
    }
}

void mouseMotion(int x, int y) {
    if (mousePressed&&!cannonDestroyed) {
        // Calculate the difference in mouse position
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;

        // Update cannon rotation (yaw) based on horizontal mouse movement
        cannonRotation -= deltaX * 0.5f;

        // Update cannon pitch based on vertical mouse movement
        cannonPitch += deltaY * 0.25f;

        // Clamp pitch to prevent flipping
        if (cannonPitch > 45.0f) cannonPitch = 45.0f;
        if (cannonPitch < -20.0f) cannonPitch = -20.0f;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}

void drawText() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, windowWidth, 0, windowHeight, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);  // Set text color to white

    // Prepare the text to display
    std::string waveText = "Current Wave: " + std::to_string(currentWave);
    std::string killText = "Kills: " + std::to_string(kills);

    // Position the text in the top left corner
    int lineHeight = 20; // Space between lines
    float xPos = 10.0f;  // X position for text
    float yPos = windowHeight - 30.0f; // Y position for text

    // Draw the current wave text
    glRasterPos2f(xPos, yPos);
    for (const char& c : waveText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Draw the kills text below the current wave text
    yPos -= lineHeight; // Move down for the next line
    glRasterPos2f(xPos, yPos);
    for (const char& c : killText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Draw the shield charge indicator in the top right corner
    float chargeXPos = windowWidth - 50.0f;  // X position for charge indicator
    float chargeYPos = windowHeight - 30.0f; // Y position for charge indicator
    for (int i = 0; i < 3; i++) {
        if (i < shieldCharges) {
            glColor3f(0.0f, 0.0f, 1.0f);  // Blue for active charges
        }
        else {
            glColor3f(0.5f, 0.5f, 0.5f);  // Gray for inactive charges
        }
        glBegin(GL_QUADS);
        glVertex2f(chargeXPos + (i * 20), chargeYPos);
        glVertex2f(chargeXPos + (i * 20) + 15, chargeYPos);
        glVertex2f(chargeXPos + (i * 20) + 15, chargeYPos + 10);
        glVertex2f(chargeXPos + (i * 20), chargeYPos + 10);
        glEnd();
    }

    // Check if cannon is destroyed
    const char* message;
    if (cannonDestroyed) {
        message = "GAME OVER press r to restart";
    }
    else if (!gameActive) {
		projectiles.clear();
        message = "Wave complete! Press g for next wave.";
    }
    else {
        // No message during active gameplay
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        return;
    }

    // Position the game over message in the center of the screen for better visibility
    int textWidth = 0;
    for (const char* c = message; *c != '\0'; c++) {
        textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, *c);
    }

    float centerXPos = (windowWidth - textWidth) / 2.0f;  // Center horizontally
    float centerYPos = windowHeight / 2.0f;               // Center vertically

    // Draw the message with a slight shadow effect for better readability
    glColor3f(0.0f, 0.0f, 0.0f);  // Shadow color
    glRasterPos2f(centerXPos + 2, centerYPos - 2);  // Shadow position
    for (const char* c = message; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    // Draw the actual text
    glColor3f(1.0f, 0.2f, 0.2f);  // Red color for game over
    glRasterPos2f(centerXPos, centerYPos);
    for (const char* c = message; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}