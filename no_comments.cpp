#include <stdio.h>
#include <string>
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
<<<<<<< HEAD
#include <algorithm>
=======
#include <cmath>
>>>>>>> 41a09653f9ba3875c7dab37afedf4a3ecefa5e5f
#include <map>
#include <fstream>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
 
using namespace std;

struct rgb {
    double red;
    double green;
    double blue; 
};

struct coordinate {
    double x;
    double y;
    double z;
};

// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
void specialKeys();
 
// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y=0; 
double rotate_x=0;
// weights = array of the values read ob the text file
// cubes = 3d matrix with the values of weights on each cube
double largo, ancho, alto , weights[1001], cubes[10][10][10];

// init color mapping
rgb color1 = {91.0,192.0,235.0};
rgb color2 = {133.0,203.0,51.0};
rgb color3 = {253.0,231.0,76.0};
rgb color4 = {255.0,188.0,66.0};
rgb color5 = {216.0,17.0,89.0}; 
map<int, rgb> color_map = {
    {1, color1},
    {2, color2},
    {3, color3},
    {4, color4},
    {5, color5}
};

coordinate coordinates[5][5][5];

double min_distance = 0;
double max_distance = 0;

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
    coordinate point;
    for(int i = 0; i < int(largo); i++) {
        for(int j = 0; j < int(ancho); j++) {
            for(int k = 0; k < int(alto); k++) {
                point.x = i + 0.1;
                point.y = j + 0.1;
                point.z = k + 0.1;
                coordinates[i][j][k] = point;
                cubes[i][j][k] = weights[row];
                row++;
            }
        }
    }
}

// ----------------------------------------------------------
// calculate min and max distance
// ----------------------------------------------------------

void calculateMinMax() {
    double distance;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            for(int k = 0; k < 5; k++) {
                coordinate point = coordinates[i][j][k];
                distance = sqrt(pow(point.x - 0, 2) + pow(point.y - 0, 2) + pow(point.z - 0, 2));
                min_distance =  max(min_distance, distance);
                max_distance = min(max_distance, distance);
            }
        }
    }
}

// ----------------------------------------------------------
// updateCoordinatesOfMatrix
// ----------------------------------------------------------
void updateMatrix(int axis, double value) {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            for(int k = 0; k < 5; k++) {
                coordinate point = coordinates[i][j][k];
                // x axis
                if (axis == 1) {
                    point.x = point.x * cos(value) - point.y*sin(value);
                    coordinates[i][j][k] = point;
                } else if (axis == 2) { // y axis
                    point.y  = point.x*sin(value) + point.y * cos(value);
                    coordinates[i][j][k] = point;
                }
            }
        }
    }
    calculateMinMax();
}

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){
 
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    // Reset transformations
    glLoadIdentity();

    // Rotate when user changes rotate_x and rotate_y
    glRotatef(rotate_x, 1.0, 0.0, 0.0 );
    glRotatef(rotate_y, 0.0, 1.0, 0.0 );      
    
    // ADDED - SOLID CUBE ------------------
    int value = 0;
    double distance, alpha = 0.5;
    rgb aux;
    for(int i = 0; i < int(largo); i++) {
        for(int j = 0; j < int(ancho); j++) {
            for(int k = 0; k < int(alto); k++) {
                value = cubes[i][j][j];
                aux = color_map[value];

                // keep center with less transparency
                if (i >= 1 && i <= 3 && j >= 1 && j <= 3 && k >= 1 && k <= 3) {
                    alpha = 1.0;
                }
                else {
                    alpha = 0.1;
                }
                coordinate point = coordinates[i][j][k];
                // calculate distance to origin
                distance = sqrt(pow(point.x - 0, 2) + pow(point.y - 0, 2) + pow(point.z, 2));
                // normalize
                distance = (distance - min_distance) / (max_distance - min_distance);
                distance = abs(distance-1);
                glPushMatrix();
                if (alpha == 1.0) {
                    if (k > 3) {
                        glColor4d((aux.red) / 255.0 ,
                        (aux.green) / 255.0, 
                        (aux.blue) / 255.0, 0.8);
                    } else {
                        glColor4d((aux.red) / 255.0 ,
                        (aux.green) / 255.0, 
                        (aux.blue) / 255.0, alpha);
                    }
                } else {
                    glColor4d((aux.red) / 255.0 ,
                        (aux.green) / 255.0, 
                        (aux.blue) / 255.0, distance);
                }
                    glTranslated(0.0 + 0.1 * float(i), 0.0 + 0.1 * float(j) , 0.0 + 0.1 * float(k));
                    glutSolidCube(0.1);
                glPopMatrix();
            }
        }
    }
    
    glFlush();
    glutSwapBuffers();
}
 
// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys( int key, int x, int y ) {
 
    //  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT) {
        rotate_y += 5;
        updateMatrix(2, 5);
    
    //  Left arrow - decrease rotation by 5 degree
    } else if (key == GLUT_KEY_LEFT) {
        rotate_y -= 5;
        updateMatrix(2, -5);
    } else if (key == GLUT_KEY_UP) {
        rotate_x += 5;
        updateMatrix(x, 5);
    } else if (key == GLUT_KEY_DOWN) {
        rotate_x -= 5;
        updateMatrix(x, -5);
    }
    
    else if(key == 113) // q for exiting program
        exit(0);
    
    //  Request display update
    glutPostRedisplay();
 
}
 
// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){
 
    // get data from file
    string fileName = "";
    cout << "Give name of text file with extension: ";
    cin >> fileName;
    readCoordinates(fileName);

    //  Initialize GLUT and process user parameters
    glutInit(&argc,argv);
    
    //  Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // window size
    glutInitWindowSize(480, 480);
    
    // Create window
    glutCreateWindow("Awesome Cube");
    
    //  Enable Z-buffer depth test
    // glEnable(GL_DEPTH_TEST);

    // ADDED - CUBE TRANSPARENCY ---------------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // -----------------------------------------------
    
    // Callback functions
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    // ADDED - CUBE TRANSPARENCY ---------------------
    // glDisable(GL_BLEND);
    // -----------------------------------------------
    
    //  Pass control to GLUT for events
    glutMainLoop();
    
    //  Return to OS
    return 0;
 
}
