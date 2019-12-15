
 #include <windows.h>

 #include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>

#endif


#include <iostream>
#include <time.h>
#include <math.h>
#include "ImageLoader.h"
#include <stdlib.h>


// All Variable Declarations



// Texture
GLuint roadTextureID;
GLuint fenceTextureID;
GLuint snowTextureID;
GLuint skyTextureID;



// Game State Variable
int score = 0;
float dist = 30.0f;   // distance between snowmen
float maxLength = 2100;



// Penguin Data
float rotSpeed = 10.0f;  // penguin rotation speed
float yRotationAngle = 0.0f;  //
bool penguinDirectionLeft = true;
float penguinYLocation = 2.3;    // Penguin location on y axis
bool changingDirection = false;



// Track and Camera Data
 // actual vector representing the camera's direction
float x = 0.0f, z = 0.0f;	// XZ position of the camera
float zSpeed = 0.1;



// Snowman Data
bool inSnowmanZone = false;
float yLocation = 0.75f; // snowman y location
float rotAngle = 0;
int snowmanCrossed = 0;  // Number of snowman crossed.. act as a pointer
int snowmenPerSet = 7;  //
int arr[15];  // contains random values for x position of each snowman
int snowmanZPosition[15];  // contains random values for z position of each snowman
float snowmanDist = 0.0;   // actual distance between snowmen.. calculated for each snowman
float snowmanDistFromCamera = 100;
int snowmanCrossCounter = 0; // used in collision logic
float distFromBall = -91.0;
int state = 1;  // x positions flipped if state =-1
float snowmanRound = 0; // set of snowmen completed
int randomn; // Temp variable



void reshape(int, int);
void timer(int);


void startGame()
{
    score = 0;
    yRotationAngle = 0.0f;  //
    penguinDirectionLeft = true;
    changingDirection = false;
    x = 0;
    z = 0;
    zSpeed = 0.1;
    rotAngle = 0;
    snowmanCrossed = 0;
    snowmanDist = 0.0;   // actual distance between snowmen.. calculated for each snowman
    snowmanDistFromCamera = 100;
    snowmanCrossCounter = 0; // used in collision logic
    distFromBall = -91.0;
    state = 1;  // x positions flipped if state =-1
    snowmanRound = 0; // set of snowmen completed

    srand(time(NULL));

    for(int i = 0; i < snowmenPerSet; i++)
    {

        arr[i] = (rand() % 3) - 1;   // -1, 0, 1
        snowmanZPosition[i] = (rand() % 3);

        if(i>1)
        {
            if(arr[i] == arr[i-1] && snowmanZPosition[i] == snowmanZPosition[i-1]) // agr x aur z position same ha
                arr[i] *= (rand() % 2) * -1;

            if(snowmanZPosition[i] == 0 && snowmanZPosition[i-1] == 0)
                snowmanZPosition[i] = (rand() % 1) + 1; // no 3 snowman in the same row
        }


    }

    distFromBall = -90 - dist * snowmanZPosition[0];   // setting distance of first snowman



}


void runner(){


	glColor3f(0.1f, 0.15f, 0.25f);
    glTranslatef(x, penguinYLocation, z + (maxLength)-2.5);	//2.5 away from camera

	glRotatef(yRotationAngle*rotSpeed, 0.2f, 1.0f, 0.1f);
	glutSolidSphere(0.1f, 20, 20);

    //hand 1
    glPushMatrix();
    glTranslatef(0.09, 0.02, 0);
    glRotatef(45,0,1,0);
    glutSolidCone(0.015,0.05,20,20);
    glPopMatrix();


    //hand 2
    glPushMatrix();
    glTranslatef(-0.09, 0.02, 0);
    glRotatef(-45,0,1,0);
    glutSolidCone(0.015,0.05,20,20);
    glPopMatrix();



    //cap
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0, 0.14,0.0);
    glPushMatrix();
    glRotatef(90, 1,0,0);
    glutSolidTorus(0.01, 0.035, 20, 20);


    glPopMatrix();
    glPushMatrix();
    glRotatef(270, 1,0,0);
    glColor3f(0.9,0.1,0.0);
    glutSolidCone(0.04, 0.07, 20, 20);
    glPopMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(0, 0.07, 0.0);
    glutSolidSphere(0.01,20,20);
    glPopMatrix();

	//Head
	glColor3f(0.1f, 0.15f, 0.25f);
    glTranslatef(0, 0.1f, 0);
    glutSolidSphere(0.05,20,20);




    // feet
    glColor3f(0.8f, 0.5f, 0.1f);
    glPushMatrix();
    glTranslatef(-0.04, -0.2f, -0.01);
    glRotatef(170,1,0,0);
    glutSolidCone(0.015,0.15,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.04, -0.2f, -0.01);
    glRotatef(-180,1,0,0);
    glutSolidCone(0.015,0.15,20,20);
    glPopMatrix();



}


void drawSnowMan()
{

    glColor3f(1.0f, 1.0f, 1.0f);	//color of snowman

// Draw Body

    glTranslatef(0.0f, yLocation, 0.0f);
    glutSolidSphere(0.75f, 20, 20);
    glRotatef(rotAngle, 0.0f, 1.0f, 0.0f);

// Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f, 20, 20);

// Draw Eyes
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f, 10, 10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

// Draw Nose
    glColor3f(1.0f, 0.5f, 0.5f);
    glutSolidCone(0.08f, 0.85f, 10, 2);


}

void pressKey(int key, int xx, int yy)
{

    switch (key) {
    case GLUT_KEY_LEFT:

	if (x != -2.0f) {
	    x = x - 2.0f;
        penguinYLocation = 2.4;   // to create jump effect
	}

	break;
    case GLUT_KEY_RIGHT:
	if (x != 2.0f) {
	    x = x + 2.0f;
        penguinYLocation = 2.4;  // to create jump effect
	}
	break;
    case GLUT_KEY_UP:
	break;
    case GLUT_KEY_DOWN:
	break;
    }


}

void drawAllSnowmen(float offset)
{

    // draw totalS snowmen at randome positions

    snowmanDist = 0;

    for(int i = 0; i < snowmenPerSet; i++)
    {

    snowmanDist += dist*snowmanZPosition[i];
    glPushMatrix();

    glTranslatef(state*arr[i]* 2.0, 0,   (maxLength)-snowmanDistFromCamera-snowmanDist-offset);

    drawSnowMan();
    glPopMatrix();

   // float temp = rand() % 2;  // 0 = snowman ya to usi row me ayga 1 = snowman agli row me // 2 = snowman usse agli row me


    }


    //std::cout << distFromBall << "\n";
}

void drawSky()
{
    //glColor3f(1.0,1.0,1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, skyTextureID);


    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
    glVertex3f(-20.0f, 50.0f, -10000.0f);

        glTexCoord2f(0.0, 500.0);
    glVertex3f(-20.0f, 0.0f, 10000.0f);


        glTexCoord2f(1, 500.0);
    glVertex3f(20.0f, 0.0f, 10000.0f);


        glTexCoord2f(1, 0);
    glVertex3f(20.0f, 50.0f, -10000.0f);

    glEnd();


}


void drawText( const char *text ,int length,int x ,int y)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix=new double [16];
	glGetDoublev(GL_PROJECTION_MATRIX,matrix);
	glLoadIdentity();

	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x,y);
	for(int i=0;i<length;i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)text[i]);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixd(matrix);
		glMatrixMode(GL_MODELVIEW);

	}
}




void renderScene(void)
{

    //drawSky();
    //Collision

    glClearColor(0.45,0.7,0.9,1.0);
    if(z < distFromBall + 1 && z > distFromBall - 1)
    {
        inSnowmanZone = true;
      //  std::cout << arr[snowmanCrossed] << "\n";
        if(x == arr[snowmanCrossed]*2*state)
        {
            	char buf [20];
                sprintf(buf,"Score = %d Play Again?",score);

            if(MessageBox(NULL, buf, "GAME OVER", MB_YESNO) == IDYES)
                startGame();
            else
                exit(0);

        }

    }
        if(z <= distFromBall - 1 && inSnowmanZone)
        {
            inSnowmanZone = false;
            snowmanCrossed++;
            if(snowmanZPosition[snowmanCrossed] == 0)
                snowmanCrossed++;

            distFromBall = distFromBall - (dist * snowmanZPosition[snowmanCrossed]);

        }


    if(snowmanCrossed >= snowmenPerSet)
    {
        snowmanCrossed = 0;
        snowmanRound = z*-1;

       // snowmanDistFromCamera = 10;
        state *= -1;
        distFromBall = - 90 - snowmanRound - dist * snowmanZPosition[0];
        zSpeed += 0.02;
        dist -= 3;
    }

   // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(x, 3.0f, z + (maxLength) , x, 3.0f, -1.0f, 0.0f, 1.0f, 0.0f);	//z+1500.0f means make camera move 1500f backward,y coordinates are for inclination
    //cout<<z<<endl;


    //sky
    glColor3f(1.0,1.0,1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, skyTextureID);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
    glVertex3f(-50.0f, 12.0f, -5000.0f);

        glTexCoord2f(0.0, 1000.0);
    glVertex3f(-50.0f, 0.0f, 5000.0f);


        glTexCoord2f(5, 1000.0);
    glVertex3f(50.0f, 0.0f, 5000.0f);


        glTexCoord2f(5, 0);
    glVertex3f(50.0f, 12.0f, -5000.0f);

    glEnd();



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, snowTextureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
        glVertex3f(-3.0f, 0.0f, -10000.0f);

        glTexCoord2f(0.0, 2000.0);
    glVertex3f(-3.0f, 0.0f, 10000.0f);


        glTexCoord2f(1.0, 2000.0);
    glVertex3f(3.0f, 0.0f, 10000.0f);


        glTexCoord2f(1.0, 0.0);
    glVertex3f(3.0f, 0.0f, -10000.0f);

    glEnd();
    glDisable(GL_TEXTURE_2D);



    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D, snowTextureID);


    glBegin(GL_QUADS);
    		glTexCoord2f(0.0f,0.0f);
    glVertex3f(-3.0f, 3.0f, -10000.0f);
    		glTexCoord2f(0.0f,3000.0f);

    glVertex3f(-4.0f, 0.0f, 10000.0f);
    		glTexCoord2f(10.0f,3000.0f);
    glVertex3f(-300.0f, 3.0f, 10000.0f);
    		glTexCoord2f(10.0f,0.0f);
    glVertex3f(-300.0f, 0.0f, -10000.0f);

    glEnd();




    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    		glTexCoord2f(0.0f,0.0f);
    glVertex3f(3.0f, 3.0f, -10000.0f);
    		glTexCoord2f(0.0f,3000.0f);
    glVertex3f(4.0f, 0.0f, 10000.0f);
    		glTexCoord2f(10.0f,3000.0f);
    glVertex3f(300.0f, 3.0f, 10000.0f);
    		glTexCoord2f(10.0f,0.0f);
    glVertex3f(300.0f, 0.0f, -10000.0f);

    glEnd();






    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, fenceTextureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-2.3f, 0.0f, -10000.0f);
    glTexCoord2f(0.0f,2000.0f);
    glVertex3f(-2.3f, 0.0f, 10000.0f);
    glTexCoord2f(1.0f,2000.0f);
    glVertex3f(-4.0f, 2.0f, 10000.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-4.0f, 0.0f, -10000.0f);

    glEnd();


    glColor3f(1.0f, 1.0f, 1.0f);


    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(2.3f, 0.0f, -10000.0f);
    		glTexCoord2f(0.0f,2000.0f);
    glVertex3f(2.3f, 0.0f, 10000.0f);
    		glTexCoord2f(1.0f,2000.0f);
    glVertex3f(4.0f, 2.0f, 10000.0f);
    		glTexCoord2f(1.0f,0.0f);
    glVertex3f(4.0f, 0.0f, -10000.0f);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    drawAllSnowmen(snowmanRound);
    runner();
    drawText("A", 3, 5, 5);
   // background();
    glutSwapBuffers();

}




GLuint loadTexture(ImageLoader texture)
{
    // this function takes texture data and return a bounded texture id
    GLuint textureID;

    glEnable(GL_TEXTURE_2D);

    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texture.iWidth, texture.iHeight, GL_RGB, GL_UNSIGNED_BYTE, texture.textureData);
    return textureID;

}

void addLight()
{
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0};
   GLfloat mat_shininess[] = { 0.05 };
   GLfloat light_position[] = { -1.0, 10.0, 10.0,0 };
   GLfloat light_color[] = {0.0, 0.0, 0.0, 0.2};
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT0, GL_COLOR, light_color);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_COLOR_MATERIAL);
}



int main(int argc, char *argv[])
{
    startGame();

    glutInit(&argc, argv);
    glutInitWindowSize(900,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Game");

    srand(time(NULL));
	randomn =  (rand() % 3) - 1;

	addLight();
	ImageLoader roadTexture("Debug/Texture/road.bmp");
    roadTextureID = loadTexture(roadTexture);

    ImageLoader grassTexture("Debug/Texture/footpath.bmp");
    fenceTextureID = loadTexture(grassTexture);

    ImageLoader snowTexture("Debug/Texture/snow.bmp");
    snowTextureID = loadTexture(snowTexture);

    ImageLoader skyTexture("Debug/Texture/sky.bmp");
    skyTextureID = loadTexture(skyTexture);

    //loadTexture("E:\\UBIT\\CG\\SnowmanRUnner\\bin\\Debug\\road.bmp");
	//loadTexture("E:\\UBIT\\CG\\SnowmanRUnner\\bin\\Debug\\grass.bmp");
	//addLight();
    glutDisplayFunc(renderScene);

    glutReshapeFunc(reshape);
    glutIdleFunc(renderScene);
    glutTimerFunc(0, timer, 0);

    glutSpecialFunc(pressKey);


    glutIgnoreKeyRepeat(1);



    glEnable(GL_DEPTH_TEST);


    glutMainLoop();

    return EXIT_SUCCESS;
}



void reshape(int w, int h)
{
     // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
	h = 1;
    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);




}


void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(200/60, timer, 0);

    if(penguinYLocation > 2.3)
    {
        penguinYLocation -= 0.005;
        z -= 0.05;
    }



    if(penguinDirectionLeft)
    {
            if(yRotationAngle <= 2.0)
                yRotationAngle += 0.15;

            else
                penguinDirectionLeft = false;
    }

    else
    {
        if(yRotationAngle >= -2.0)
            yRotationAngle -= 0.15;

        else
            penguinDirectionLeft = true;

    }

    rotSpeed += 0.00001;









    z -= zSpeed;
    zSpeed += 0.00001;
    score = -z/1;

}
