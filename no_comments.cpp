#include <stdio.h>
#include <string>
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
 
using namespace std;
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
double volume[100][3];
 
// ----------------------------------------------------------
// readCordinates
// ----------------------------------------------------------
void readCordinates(string fileName) {
    ifstream file;
    double x, y, z;
    int row = 0;
    file.open(fileName);
    while(!file.eof()) {
        file >> x >> y >> z;
        volume[row][0] = x;
        volume[row][1] = y;
        volume[row][2] = z;
        row++;
    }
    file.close();
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
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glutSolidCube(1);
        glTranslated(0.0, 0.0 , -3.0);
    // --------------------------------------

    glFlush();
    glutSwapBuffers();


 
}
 
// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys( int key, int x, int y ) {
 
    //  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    
    //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    
    else if(key == 113) // q for exiting program
        exit(0);
    
    //  Request display update
    glutPostRedisplay();
 
}
 
// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){
 
    string fileName = "";
    cout << "Give name of text file with extension: ";
    cin >> fileName;
    readCordinates(fileName);

    //  Initialize GLUT and process user parameters
    glutInit(&argc,argv);
    
    //  Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
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
