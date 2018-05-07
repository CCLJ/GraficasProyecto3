#include <stdio.h>
#include <string>
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <map>
#include <fstream>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f, z=5.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;
double shouldRotate = false;

// weights = array of the values read ob the text file
// cubes = 3d matrix with the values of weights on each cube
double largo, ancho, alto , weights[1001], cubes[10][10][10];


struct rgb {
    double red;
    double green;
    double blue; 
};
// init color mapping
rgb color1 = {255.0,255.0,255.0};
rgb color2 = {24.0,53.0,103.0};
rgb color3 = {46.0,100.0,158.0};
rgb color4 = {23.0,173.0,203.0};
rgb color5 = {0.0,250.0,250.0}; 
map<int, rgb> color_map = {
    {1, color1},
    {2, color2},
    {3, color3},
    {4, color4},
    {5, color5}
};

// ----------------------------------------------------------
// readCoordinates
// ----------------------------------------------------------
void readCoordinates(string fileName) {

    ifstream file;
    double x;
    int row = 0;
    file.open(fileName);
    file >> largo >> ancho >> alto;
    while(!file.eof()) {
        file >> x;
        x = fmod(x,5.0) + 1;
        weights[row] = x;
        row++;
    }
    file.close();

    row = 0;
    for(int i = 0; i < int(largo); i++) {
        for(int j = 0; j < int(ancho); j++) {
            for(int k = 0; k < int(alto); k++) {
                cubes[i][j][k] = weights[row];
                row++;
            }
        }
    }
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

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

double miN = 99999999, maX = -1, distance;

void drawSnowMan() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	const double a = t*90.0;
    int value = 0;
    double distance;
    rgb aux;
    largo = int(largo);
    ancho = int(ancho);
    alto = int(alto);
    // Iterate over the dimensions of the cube
    for(int i = 0; i < int(largo); i++) {
        for(int j = 0; j < int(ancho); j++) {
            for(int k = 0; k < int(alto); k++) {
            	// obtain the information of the cube at the current positions
                value = cubes[i][j][j];
                // get the color it represent
                aux = color_map[value];
                // calculate the euclidean distance
                distance += sqrt(pow(x-0.0 + 0.1 * float(i),2) + pow(0.5f-0.0 + 0.1 * float(j), 2) + pow(z - 0.0 + 0.1 * float(k),2));
                // obtain min and max
                miN = min(miN, distance);
                maX = max(maX, distance);
                // normalize the value between 1 and 0
                distance = (distance-miN) / (maX-miN);
                if (distance != distance) {
                	distance = 0.5;
                }
                // draw the cube
                glPushMatrix();
                    glColor4d(
                        (aux.red) / 255.0 , 
                        (aux.green) / 255.0, 
                        (aux.blue) / 255.0, distance);
                    glTranslated(0.0 + 0.1 * float(i), 0.0 + 0.1 * float(j) , 0.0 + 0.1 * float(k));
                    if (shouldRotate) {
     					glRotated(a,0,0,1);
     				}
                    glutSolidCube(0.1);
                glPopMatrix();
            }
        }
    }
    glFlush();
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 0.5f, z,
			x+lx, 0.3f,  z+lz,
			0.0f, 1.0f,  0.0f);

	glPushMatrix();
	glTranslatef(0, 0, 0);
	drawSnowMan();
	glPopMatrix();
	glutSwapBuffers();
}

struct Coordinate {
    int x;
    int y;
    int z;
};

void generateObjFile() {
    Coordinate coordinates[8];
    Coordinate temp;
    temp.x = 0.0;
    temp.y = 0.0;
    temp.z = 0.0;
    coordinates[0] = temp;
    temp.x = 0.0;
    temp.y = 0.0;
    temp.z = 1.0;
    coordinates[1] = temp;
    temp.x = 0.0;
    temp.y = 1.0;
    temp.z = 0.0;
    coordinates[2] = temp;
    temp.x = 0.0;
    temp.y = 1.0;
    temp.z = 1.0;
    coordinates[3] = temp;
    temp.x = 1.0;
    temp.y = 0.0;
    temp.z = 0.0;
    coordinates[4] = temp;
    temp.x = 1.0;
    temp.y = 0.0;
    temp.z = 1.0;
    coordinates[5] = temp;
    temp.x = 1.0;
    temp.y = 1.0;
    temp.z = 0.0;
    coordinates[6] = temp;
    temp.x = 1.0;
    temp.y = 1.0;
    temp.z = 1.0;
    coordinates[7] = temp;
    int start = -7;
    int end = 0;
    if (FILE *file = fopen("cube.obj", "r")) {
        fclose(file);
        remove("cube.obj");
    }
    ofstream writer("cube.obj", ios::app);
    for (int i = 0; i < int(largo); ++i) {
        for(int j = 0; j < int(ancho); ++j) {
            for (int k = 0; k < int(alto); ++k) {
                // Update the position of each vertices
                for (int x = 0; x < 8; ++x) {
                    temp = coordinates[x];
                    temp.x += 0.1 * float(i);
                    temp.y += 0.1 * float(j);
                    temp.z += 0.1 * float(k);
                    coordinates[x] = temp;
                }
                // write the vertices in the file
                string line;
                for (int x = 0; x < 8; ++x) {
                    line = "v ";
                    temp = coordinates[x];
                    line += to_string(temp.x);
                    line += " ";
                    line += to_string(temp.y);
                    line += " ";
                    line += to_string(temp.z);
                    line += "\n";
                    writer << line;
                }
            }
        }
    }
    string line;
    for (x = 0; x < 8; ++x) {
        start += 8;
        end += 8;
        line = "f " + to_string(start) + "//" + to_string(start+1);
        line += " " + to_string(end-1) + "//" + to_string(start+1);
        line += " " + to_string(start+4) + "//" + to_string(start+1);
        line += "\n";
        writer << line;
        line = "f " + to_string(start) + "//" + to_string(start+1);
        line += " " + to_string(start+2) + "//" + to_string(start+1);
        line += " " + to_string(end-1) + "//" + to_string(start+1);
        line += "\n";
        writer << line;
        line = "f " + to_string(start) + "//" + to_string(end-2);
        line += " " + to_string(start+3) + "//" + to_string(end-2);
        line += " " + to_string(start+2) + "//" + to_string(end-2);
        line += "\n";
        writer << line;
        line  = "f " + to_string(start) +  "//" + to_string(end-2);
        line += " " + to_string(start+1) +  "//" + to_string(end-2);
        line += " " + to_string(start+3) + "//" + to_string(end-2);
        line += "\n";
        writer << line;
        line = "f " + to_string(start+2) + "//" + to_string(start+2);
        line += " " + to_string(end) + "//" + to_string(start+2);
        line += " " + to_string(end-1) + "//" + to_string(start+2);
        line += "\n";
        writer << line;
        line = "f " + to_string(start+2) + "//" + to_string(start+2);
        line += " " + to_string(start+3) + "//" + to_string(start+2);
        line += " " + to_string(end) + "//" + to_string(start+2);
        line += "\n";
        writer << line;
        line = "f " + to_string(start+4) + "//" + to_string(start+4);
        line += " " + to_string(end-1) + "//" + to_string(start+4);
        line += " " + to_string(end) + "//" + to_string(start+4);
        line += "\n";
        writer << line;
        line = "f " + to_string(start+4) + "//" + to_string(start+4);
        line += " " + to_string(end) + "//" + to_string(start+4);
        line += " " + to_string(end-2) + "//" + to_string(end-3);
        line += "\n";
        writer << line;
        line = "f " + to_string(start) + "//" + to_string(start+3);
        line += " " + to_string(end-3) + "//" + to_string(start+3);
        line += " " + to_string(end-2) + "//" + to_string(start+3);
        line += "\n";
        writer << line;
        line = "f " + to_string(start) + "//" + to_string(start+3);
        line += " " + to_string(end-2) + "//" + to_string(start+3);
        line += " " + to_string(start+1) + "//" + to_string(start+3);
        line += "\n";
        writer << line;
        line = "f " + to_string(start+1) + "//" + to_string(start);
        line += " " + to_string(end-2) + "//" + to_string(start);
        line += " " + to_string(end) + "//" + to_string(start);
        line += "\n";
        writer << line;
        line = "f " + to_string(start+1) + "//" + to_string(start);
        line += " " + to_string(end) + "//" + to_string(start);
        line += " " + to_string(end-4) + "//" + to_string(start);
        line += "\n";
        writer << line;
    }
    writer.close();
}

void processNormalKeys(unsigned char key, int xx, int yy) {
        if (key == 27)
              exit(0);
        else if (key == 'q') {
        	generateObjFile(); 
        	exit(0);
        } else if (key == 'r') {
        	shouldRotate = !shouldRotate;
        }
}



void pressKey(int key, int xx, int yy) {

       switch (key) {
             case GLUT_KEY_UP : deltaMove = 0.5f; break;
             case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
       }
}

void releaseKey(int key, int x, int y) { 	

        switch (key) {
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0;break;
        }
} 
void mouseMove(int x, int y) { 	

         // this will only be true when the left button is down
         if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	string fileName = "";
    cout << "Give name of text file with extension: ";
    cin >> fileName;
    readCoordinates(fileName);
    cout << "If you want to rotate the cube press R" << endl;

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}