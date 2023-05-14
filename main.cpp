#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
//#include <MMSystem.h>
#include<math.h>
#include<bits/stdc++.h>
#define  PI 3.1416

#include "BmpLoader.h"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 750
using namespace std;

unsigned int ID[1000];
double speed=0;
double window_angle=0;
bool fan_c=true,window=false;


bool light1=true, light2=false, light3=false, light4=false;
bool diff_light_on=true, spec_light_on=true, amb_light_on=true;
bool em=true,em_1=false;
bool train_1=false,train_2=false,train_reset=false;
bool day=true,rotate_sky=true;


double train_speed1=0,train_speed2=0,wheel_speed_2=0,wheel_speed_1=0;
double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1000, windowWidth=750;
GLfloat angle1 = 0.0, angle2 = 0.0, angle3=0.0, angle4=0.0, axis_x=0.0, theta=0.0, alpha=0.0, axis_y=0.0,theta1=0.0;
GLboolean bRotate = false, uRotate = false;
double x = 0, y = 0, z = 0;
double x_up = 0, y_up = 1, z_up = 0;

double lpan = 0, rpan = 0, fdist = 0;
double dx = 0, dy = 0, dz = 0;
double yaw =0, pitch= 0, roll = 0;
double sx = 1,sy=1,sz=1;




//const float ar = float(WINDOW_WIDTH)/float(WINDOW_HEIGHT);

//GLfloat eyeX = 5;
//GLfloat eyeY = 5;
//GLfloat eyeZ = 17;

//GLfloat eyeX = 8;
GLfloat eyeX = 25;
GLfloat eyeY = 13;
GLfloat eyeZ = 150;

//GLfloat eyeX = 3;
//GLfloat eyeY = 13;
//GLfloat eyeZ = 70;


//GLfloat lookX = 4;
//GLfloat lookY = 2;
//GLfloat lookZ = 0;

GLfloat lookX = 10;
GLfloat lookY = 5;
GLfloat lookZ = 5;

//GLfloat lookX = 4;
//GLfloat lookY = 2;
//GLfloat lookZ = 0;

static GLfloat v_pyramid[38][3] =
{
    {0.0, 0.0, 0.0}, //0 origin
    {0.0, 0.0, 14.0},//1 wall
    {0.0, 12.0, 14.0},//2 wall
    {0.0, 12.0, 0.0},// 3 wall
    {1.0, 0.0, 0.0},//4 floor
    {0.0, 0.0, 1.0},//5 floor
    {1.0, 0.0, 1.0},// 6 floor
    {1.0, 0.0, 0.0},//7 cube
    {0.0, 0.0, 1.0},//8 cube
    {1.0, 0.0, 1.0},// 9 cube
    {1.0, 1.0, 0.0},// 10 cube
    {0.0, 1.0, 0.0},// 11 cube
    {0.0, 1.0, 1.0},//12 cube
    {1.0, 1.0, 1.0},// 13 cube
    {1.0, 0.0, 0.0},// 14 basket
    {1.5, 1.0, 0.0},// 15 basket
    {-0.5, 1.0, 0.0},// 16 basket
    {1.0, 0.0, 1.0},// 17 basket
    {1.5, 1.0, 1.0},// 18 basket
    {-0.5, 1.0, 1.0},// 19 basket
    {0.0, 0.0, 1.0}, //20 basket
    {-1.0, 0.0, 0.0}, //21 origin
    {-1.0, 0.0, 14.0},//22 wall
    {-1.0, 12.0, 14.0},//23 wall
    {-1.0, 12.0, 0.0},//24 wall
    {0.0,0.0,0.0},//25 fence
    {1.0,0.0,0.0},//26 fence
    {1.0,1.0,0.0},//27 fence
    {0.5,1.1,-0.5},//28 fence
    {0.0,1.0,0.0},//29 fence
    {0.0,0.0,-1.0},//30 fence
    {1.0,0.0,-1.0},//31 fence
    {1.0,1.0,-1.0},//32 fence
    {0.0,1.0,-1.0},//33 fence
    {0.0,0.0,1.0},//34 pyramid
    {1.0,0.0,1.0},//35 pyramid
    {1.0,0.0,0.0},//36 pyramid
    {0.5,0.5,0.5},//37 pyramid


};



static GLubyte p_Indices[4][3] =
{
    {0, 37, 35},
    {36, 37, 35},
    {36,0, 37},
    {34,37, 0}


};
static GLubyte p_cube_Indices[1][4] =
{
    {36,35,34,0}


};

static GLubyte wallIndices[6][4] =
{
    {0, 3, 2, 1},
    {3, 24, 23, 2},
    {1, 2, 23, 22},
    {24, 21, 22, 23},
    {0, 21, 24, 3},
    {0, 1, 22, 11}

};
static GLubyte floorIndices[1][4] =
{
    {4, 0, 5, 6}

};

static GLubyte cubeIndices[6][4] =
{
    {11, 0, 7, 10},
    {8, 12, 11, 0},
    {8, 12, 13, 9},
    {7, 10, 13, 9},
    {7, 9, 8, 0},
    {11, 12, 13, 10}

};


static GLubyte basketIndices[5][4] =
{
    {17, 18, 19, 20},
    {16, 15, 14, 0},
    {20, 19, 16, 0},
    {15, 18, 17, 14},
    {0, 14, 17, 20},


};
static GLubyte fenceIndices[4][5] =
{
    {25,26,27,28,29},
    {26,31,32,28,27},
    {25,30,33,28,29},
    {31,30,33,28,32}


};
static GLubyte fence_cube_Indices[1][4] =
{
    {26,25,31,30}


};


static GLfloat colors[10][3] =
{
    //polygon colors
    {1.0, 1.0, 1.0},
    {0.5, 0.5, 0.5},
    //quad er shuru ekhan theke
    {0.5f, 0.0f, 1.0f}, //purple
    {1.0, 0.5, 0.0}, //idk what color
    {0.0f, 1.0f, 0.0f}, //green
    {1.0f, 1.0f, 0.0f}, //yellow
    {0.0, 0.0, 1.0}, //blue
    {1.0, 0.5, 0.0}, //idk what color
    {0.0, 0.0, 0.0},// black
    {1.0f, 0.0f, 0.0f}//red
};

static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    //GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    //GLfloat light_position[] = { 13.8, 10.7, 9, 1.0 };
    GLfloat light_position[] = { -70,125,-165, 1.0 };

    glEnable( GL_LIGHT0);
    //fv=floot vector
    //GL_LIGHT0=0th light
    if(amb_light_on) glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    else glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);

    if(diff_light_on) glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    else glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);

    if(spec_light_on) glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    else glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);

    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    /*GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); */
}

void light_off(GLenum light_num)
{
    glDisable(light_num);
}
void spotlight1()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    //GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { -63,39,-8+3, 1.0 };

    glEnable( GL_LIGHT1);
    //fv=floot vector
    //GL_LIGHT0=0th light
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);

    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 35.0);
}
void spotlight2()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    //GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { -63+280,39,-8+3, 1.0 };

    glEnable( GL_LIGHT2);
    //fv=floot vector
    //GL_LIGHT0=0th light
    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);

    GLfloat spot_direction[] = {0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 20.0);
}
void moon_light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.01, 0.01, 0.01, 1.0};
    GLfloat light_diffuse[]  = { 0.1, 0.1, 0.1, 1.0 };
    //GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light_specular[] = { 0.01, 0.01, 0.01, 1.0 };
    GLfloat light_position[] = { -120,120,-120, 1.0 };

    glEnable( GL_LIGHT3);
    //fv=floot vector
    //GL_LIGHT0=0th light
    glLightfv( GL_LIGHT3, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT3, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT3, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT3, GL_POSITION, light_position);

    /*GLfloat spot_direction[] = { 0.0, -1.0, 1.0 };
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT3, GL_SPOT_CUTOFF, 40.0);*/
}
void set_mat_prop(float colR, float colG, float colB, bool em=false, float shine=60)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { colR, colG, colB, 1.0 };
    GLfloat mat_diffuse[] = { colR, colG, colB, 1.0 };
    GLfloat mat_specular[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_emission[] = {1, 1, 1, 1.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(em) glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

}


void LoadTexture(const char*filename, int idx)
{
    glGenTextures(1, &ID[idx]);
    glBindTexture(GL_TEXTURE_2D, ID[idx]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[idx]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void  cube(int c, bool em_on=false)
{


    // glColor3f(1,0,0);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        if(c==0)
        {
            set_mat_prop(1,0.5,0);
        }
        else if(c==1)
        {
            set_mat_prop(0.5,0.5,0.5);
        }
        else if(c==2)
        {
            set_mat_prop(0,0,1);
        }
        else if(c==3)
        {
            set_mat_prop(0.4,0,0);
        }
        else if(c==4)
        {

            set_mat_prop(1,1,0);

        }
        else if(c==5)
        {
            set_mat_prop(1,1,1,em_on);
        }
        else if(c==6)
        {
            set_mat_prop(1,1,0);
        }
        else if(c==8)
        {
            set_mat_prop(0,1,0);
        }
        else if(c==9)
        {
            set_mat_prop(0.5,0,1.0);
        }


        else if(c==7)
        {
            if(i%2==1)
                set_mat_prop(1,0.5,0);
            else
                set_mat_prop(1.0,1.0,0.0);
        }
        else if(c==10)
        {
            set_mat_prop(1,1,1);
        }
        else if(c==11)
        {
            set_mat_prop(0,0.8,0.8);
        }
        else if(c==12)
        {
            set_mat_prop(1,1,1);
        }
        else if(c==13)
        {
            set_mat_prop(0,0,0);
        }
        else if(c==14)
        {
            set_mat_prop(.21,.71,.52);
        }
        else if(c==15)
        {
            set_mat_prop(.80,.61,.50);
        }
        getNormal3p(v_pyramid[cubeIndices[i][0]][0], v_pyramid[cubeIndices[i][0]][1], v_pyramid[cubeIndices[i][0]][2],
                    v_pyramid[cubeIndices[i][1]][0], v_pyramid[cubeIndices[i][1]][1], v_pyramid[cubeIndices[i][1]][2],
                    v_pyramid[cubeIndices[i][2]][0], v_pyramid[cubeIndices[i][2]][1], v_pyramid[cubeIndices[i][2]][2]);

        glVertex3fv(&v_pyramid[cubeIndices[i][0]][0]);
        //glTexCoord2f(0,1);
        glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[cubeIndices[i][1]][0]);
        //glTexCoord2f(1,1);;
        glTexCoord2f(1,0);
        glVertex3fv(&v_pyramid[cubeIndices[i][2]][0]);
        //glTexCoord2f(0,0);
        glTexCoord2f(1,1);
        glVertex3fv(&v_pyramid[cubeIndices[i][3]][0]);
        //glTexCoord2f(1,0);
        glTexCoord2f(0,1);
    }
    glEnd();


}
void  draw_fence()
{

    // glColor3f(1,0,0);
    set_mat_prop(1.0,0.5,0.0);
    glBegin(GL_POLYGON);
    for (GLint i = 0; i <4; i++)
    {
        getNormal3p(v_pyramid[fenceIndices[i][0]][0], v_pyramid[fenceIndices[i][0]][1], v_pyramid[fenceIndices[i][0]][2],
                    v_pyramid[fenceIndices[i][1]][0], v_pyramid[fenceIndices[i][1]][1], v_pyramid[fenceIndices[i][1]][2],
                    v_pyramid[fenceIndices[i][2]][0], v_pyramid[fenceIndices[i][2]][1], v_pyramid[fenceIndices[i][2]][2]);

        glVertex3fv(&v_pyramid[fenceIndices[i][0]][0]);
        //glTexCoord2f(0,1);
        glVertex3fv(&v_pyramid[fenceIndices[i][1]][0]);
        //glTexCoord2f(1,1);;
        glVertex3fv(&v_pyramid[fenceIndices[i][2]][0]);
        //glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[fenceIndices[i][3]][0]);
        //glTexCoord2f(1,0);
        glVertex3fv(&v_pyramid[fenceIndices[i][4]][0]);
    }
    glEnd();
    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        getNormal3p(v_pyramid[fence_cube_Indices[i][0]][0], v_pyramid[fence_cube_Indices[i][0]][1], v_pyramid[fence_cube_Indices[i][0]][2],
                    v_pyramid[fence_cube_Indices[i][1]][0], v_pyramid[fence_cube_Indices[i][1]][1], v_pyramid[fence_cube_Indices[i][1]][2],
                    v_pyramid[fence_cube_Indices[i][2]][0], v_pyramid[fence_cube_Indices[i][2]][1], v_pyramid[fence_cube_Indices[i][2]][2]);

        glVertex3fv(&v_pyramid[fence_cube_Indices[i][0]][0]);
        //glTexCoord2f(0,1);
        glVertex3fv(&v_pyramid[fence_cube_Indices[i][1]][0]);
        //glTexCoord2f(1,1);;
        glVertex3fv(&v_pyramid[fence_cube_Indices[i][2]][0]);
        //glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[fence_cube_Indices[i][3]][0]);
        //glTexCoord2f(1,0);

    }
    glEnd();


}

void bench()
{
    //boshar jaiga
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(0,3,0);
    glScalef(2,1,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //boshar khuti (left-pisone)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(0.1,3,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //boshar khuti (left-shamne)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(0,0,1.9);
    glScalef(0.1,3,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //boshar khuti (right-pisone)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(1.9,0,0);
    glScalef(0.1,3,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //boshar khuti (left-shamne)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(1.9,0,1.9);
    glScalef(0.1,3,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //left boshar jaigar hatol(upor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(0,4.5,0.1);
    glScalef(0.1,0.3,1.8);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //left boshar jaigar hatol(nich)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(0,5.3,0.1);
    glScalef(0.1,0.3,1.8);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right boshar jaigar hatol(upor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(1.9,4.5,0.1);
    glScalef(0.1,0.3,1.8);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right boshar jaigar hatol(nich)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(1.9,5.2,0.1);
    glScalef(0.1,0.3,1.8);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //left boshar jaigar khara hatol(shmaner)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(0,4,1.9);
    glScalef(0.1,1.6,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right boshar jaigar khara hatol(shamner)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(1.9,4,1.9);
    glScalef(0.1,1.6,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //pishoner araari line nich
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(0.1,4.5,0);
    glScalef(1.8,0.3,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pishoner  araari line  upor
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(0.1,5.3,0);
    glScalef(1.8,0.3,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //left boshar jaigar khara hatol(pishoner)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(0,4,0);
    glScalef(0.1,1.6,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right boshar jaigar khara hatol(pishoner)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(1.9,4,0);
    glScalef(0.1,1.6,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}


void drawpyramid()
{
    set_mat_prop(1,1,1);
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);

        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);//glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);//glTexCoord2f(1,0);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);//glTexCoord2f(0.5,1);
    }
    glEnd();
    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        getNormal3p(v_pyramid[p_cube_Indices[i][0]][0], v_pyramid[p_cube_Indices[i][0]][1], v_pyramid[p_cube_Indices[i][0]][2],
                    v_pyramid[p_cube_Indices[i][1]][0], v_pyramid[p_cube_Indices[i][1]][1], v_pyramid[p_cube_Indices[i][1]][2],
                    v_pyramid[p_cube_Indices[i][2]][0], v_pyramid[p_cube_Indices[i][2]][1], v_pyramid[p_cube_Indices[i][2]][2]);

        glVertex3fv(&v_pyramid[p_cube_Indices[i][0]][0]);//glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[p_cube_Indices[i][1]][0]);//glTexCoord2f(1,0);;
        glVertex3fv(&v_pyramid[p_cube_Indices[i][2]][0]);//glTexCoord2f(1,1);
        glVertex3fv(&v_pyramid[p_cube_Indices[i][3]][0]);//glTexCoord2f(0,1);
    }
    glEnd();

}





void fan()
{

    //glColor3f(1, 0, 0);
    //set_mat_prop(1,1,1);
    GLUquadricObj *q;
    q = gluNewQuadric();
    glRotatef(speed, 0, 0, 1);

    glPushMatrix();
    glRotatef(180,1,0,0);
    gluCylinder(q, 5, 4, 25, 52, 52);
    glPopMatrix();

    glTranslated(0, 0, 0);
    //glColor3f(0, 0, 1);
    set_mat_prop(0,0,0);

    glutSolidSphere(8, 40, 40);


    // glColor3f(0, 1, 1);
    set_mat_prop(1,0,0);
    glBegin(GL_QUADS);
    {
        glVertex3f(5, 5, 0);
        glVertex3f(-5, 5, 0);
        glVertex3f(-5, 33, 0);
        glVertex3f(5, 33, 0);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glVertex3f(5, -5, 0);
        glVertex3f(-5, -5, 0);
        glVertex3f(-5, -33, 0);
        glVertex3f(5, -33, 0);
    }
    glEnd();

    glPushMatrix();
    {
        glRotatef(90,0,0,1);
        glBegin(GL_QUADS);
        {
            glVertex3f(5, 5, 0);
            glVertex3f(-5, 5, 0);
            glVertex3f(-5, 33, 0);
            glVertex3f(5, 33, 0);
        }
        glEnd();

        glBegin(GL_QUADS);
        {
            glVertex3f(5, -5, 0);
            glVertex3f(-5, -5, 0);
            glVertex3f(-5, -33, 0);
            glVertex3f(5, -33, 0);
        }
        glEnd();
    }
    glPopMatrix();



}

void  basket(int c)
{

    //glColor3f(1,0,0);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <5; i++)
    {
        if(c==1)
        {
            if(i==0)
            {
                set_mat_prop(0,1,0);
            }
            else if(i==1)
            {
                set_mat_prop(0.5,0.5,0.5);
            }
            else
            {
                set_mat_prop(0,0,1.0);
            }

        }
        else
        {
            if(i==0)
            {
                set_mat_prop(1,0.5,0);
            }
            else if(i==1)
            {
                set_mat_prop(0.5,0.5,0.5);
            }
            else
            {
                set_mat_prop(0,0,1.0);
            }
        }


        getNormal3p(v_pyramid[basketIndices[i][0]][0], v_pyramid[basketIndices[i][0]][1], v_pyramid[basketIndices[i][0]][2],
                    v_pyramid[basketIndices[i][1]][0], v_pyramid[basketIndices[i][1]][1], v_pyramid[basketIndices[i][1]][2],
                    v_pyramid[basketIndices[i][2]][0], v_pyramid[basketIndices[i][2]][1], v_pyramid[basketIndices[i][2]][2]);

        glVertex3fv(&v_pyramid[basketIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[basketIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[basketIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[basketIndices[i][3]][0]);
    }
    glEnd();


}

void rail_line()
{
    //pataton-1
    glPushMatrix();
    glTranslatef(-180,0,0);
    glScalef(420,1,10);
    cube(10);
    glPopMatrix();

    //pataton-2

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(-180,0,10);
    glScalef(420,1,5);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pataton-3
    glPushMatrix();
    glTranslatef(-180,0,15);
    glScalef(420,1,10);
    cube(10);
    glPopMatrix();


    //railline ar dui pash (front)
    glPushMatrix();
    glTranslatef(-180,1,15.4);
    glScalef(420,0.5,0.3);
    cube(13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-180,1,24.3);
    glScalef(420,0.5,0.3);
    cube(13);
    glPopMatrix();

    for(int i=0; i<420; i++)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,4);
        glPushMatrix();
        glTranslatef(-180+i,1.1,15.7);
        glScalef(0.3,0.2,8.6);
        cube(12);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }

    //railline ar dui pash (back)
    glPushMatrix();
    glTranslatef(-180,1,0.4);
    glScalef(420,0.5,0.3);
    cube(13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-180,1,9.3);
    glScalef(420,0.5,0.3);
    cube(13);
    glPopMatrix();

    for(int i=0; i<420; i++)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,4);
        glPushMatrix();
        glTranslatef(-180+i,1.1,0.7);
        glScalef(0.3,0.2,8.6);
        cube(12);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }


}
void fence()
{
    //main fence shuru
    for(int i=0; i<=420; i+=4)
    {
        glPushMatrix();
        glTranslatef(-180+i,0,-60.5);
        glScalef(1,14,.5);
        draw_fence();
        glPopMatrix();
    }
    //
    glPushMatrix();
    glTranslatef(-180,7,-61.2);
    glScalef(420,1,.2);
    draw_fence();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-180,12.5,-61.2);
    glScalef(420,1,.2);
    draw_fence();
    glPopMatrix();


}

void hills()
{
    //bam pash theke pahar-1/1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,12);
    glPushMatrix();
    glTranslatef(-180,0,-130);
    glScalef(60,150,8);
    glRotatef(60,0,1,0);
    drawpyramid();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_2D);


    //bam pash theke pahar-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    glPushMatrix();
    glTranslatef(-180+60,0,-130);
    glScalef(60,110,8);
    glRotatef(45,0,1,0);
    drawpyramid();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_2D);

    //bam pash theke pahar-2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,12);
    glPushMatrix();
    glTranslatef(-65,0,-130);
    glScalef(65,130,8);
    glRotatef(45,0,1,0);
    drawpyramid();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    //bam pash theke pahar-3
    glPushMatrix();
    glTranslatef(-20,0,-130);
    glScalef(60,80,8);
    glRotatef(75,0,1,0);
    //set_mat_prop(0,1,0);
    drawpyramid();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //bam pash theke pahar-4
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    glPushMatrix();
    glTranslatef(15,0,-130);
    glScalef(80,80,8);
    glRotatef(60,0,1,0);
    drawpyramid();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,12);
    glPushMatrix();
    glTranslatef(90,0,-130);
    glScalef(73+20,150,8);
    glRotatef(30,0,1,0);
    drawpyramid();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    /* glPushMatrix();
     glTranslatef(30,0,-80);
     glScalef(30,100,10);
     glRotatef(120,0,1,0);
     drawpyramid();
     glPopMatrix();*/
}
void platform()
{

    //faka jaiga puron
    glPushMatrix();
    glTranslatef(-180,0,0);
    glScalef(420,1,-2);
    cube(10);
    glPopMatrix();

    //platform ar shamner dewal texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(-180,0,-1.9);
    glScalef(420,5,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //main platform
    glPushMatrix();
    glTranslatef(-180,0,-2);
    glScalef(420,5,-60);
    cube(10);
    glPopMatrix();

    //main platform ar texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,26);
    glPushMatrix();
    glTranslatef(-180,5,-2);
    glScalef(420,0.1,-60);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //main platform(Shamner)
    glPushMatrix();
    glTranslatef(-180,0,25+2);
    glScalef(160+60,5,20-2);
    cube(10);
    glPopMatrix();



    //faka jaiga puron---1
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(-180,0,25);
    glScalef(160+60,1,2);
    cube(10);
    glPopMatrix();
    // glDisable(GL_TEXTURE_2D);

    //faka jaiga puron---2
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(110,0,25);
    glScalef(80+50,1,2);
    cube(10);
    glPopMatrix();


    //main platform ar texture(Shamner)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,26);
    glPushMatrix();
    glTranslatef(-180,5,25+2);
    glScalef(160+60,0.1,20-2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //main platform ar texture(Shamner)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(-180,0,25+20);
    glScalef(160+60,5,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //platform ar shamner dewal texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(-180,0,26.9);
    glScalef(160+60,5,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // glDisable(GL_TEXTURE_2D);
    //main platform(Shamner)
    glPushMatrix();
    glTranslatef(110,0,25+2);
    glScalef(80+50,5,20-2);
    cube(10);
    glPopMatrix();

    //main platform ar texture(Shamner)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,26);
    glPushMatrix();
    glTranslatef(110,5,25+2);
    glScalef(80+50,0.1,20-2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //main platform ar texture(Shamner)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(110,0,25+20);
    glScalef(80+50,5,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //platform ar shamner dewal texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(110,0,26.9);
    glScalef(80+50,5,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void field()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(-180,0,-62);
    glScalef(420,4,-78);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void over_bridge()
{
    //main-overbridge
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,27);
    glPushMatrix();
    glTranslatef(50,30,-9);
    glScalef(15,3,43);
    cube(3);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);


    //over-bridge ar hatol(left-nich)
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(50,35,-3);
    glScalef(1,1,37);
    cube(13);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //over-bridge ar hatol(left upor)
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(50,38,-3);
    glScalef(1,1,37);
    cube(3);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);


    //over-bridge ar khara hatol(left)
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    for(int i=0; i<43; i+=3)
    {
        if(i==3)
            continue;
        glPushMatrix();
        glTranslatef(50,33,-9+i);
        glScalef(1,6,1);
        //if(i%6==0)
        cube(3);
        //else
        //   cube(13);
        glPopMatrix();
        //glDisable(GL_TEXTURE_2D);

    }

    //over-bridge ar hatol(north-nich)
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(50,35,-9);
    glScalef(15,1,1);
    cube(13);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //over-bridge ar hatol(north upor)
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(50,38,-9);
    glScalef(15,1,1);
    cube(3);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);


    //over-bridge ar hatol(right-nich)
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(64,35,-9);
    glScalef(1,1,37);
    cube(13);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //over-bridge ar hatol(right upor)
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(64,38,-9);
    glScalef(1,1,37);
    cube(3);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    //over-bridge ar khara hatol(right)
    for(int i=0; i<43; i+=3)
    {
        if(i==39)
            continue;
        glPushMatrix();
        glTranslatef(64,33,-9+i);
        glScalef(1,6,1);
        // if(i%6==0)
        cube(3);
        //else
        // cube(13);
        glPopMatrix();
        //glDisable(GL_TEXTURE_2D);

    }
    //over-bridge ar hatol(south-nich)
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(51,35,33);
    glScalef(13,1,1);
    cube(13);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //over-bridge ar hatol(south upor)
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEX]TURE_2D,5);
    glPushMatrix();
    glTranslatef(51,38,33);
    glScalef(13,1,1);
    cube(3);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);


    //stairs left
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    for(int i=0; i<28; i+=2)
    {
        glPushMatrix();
        glTranslatef(22+i,5+i,-9);
        glScalef(2,2,6);
        if(i%4==0)
            cube(13);
        else
            cube(3);
        glPopMatrix();
        //glDisable(GL_TEXTURE_2D);

        glPushMatrix();
        glTranslatef(22+i+1,5+i+2,-9+0.2);
        glScalef(0.2,4.4,0.2);
        if(i%4==0)
            cube(3);
        else
            cube(13);
        glPopMatrix();


        //////////////////////////

        glPushMatrix();
        glTranslatef(22+i+1,5+i+2,-9+6-0.2);
        glScalef(0.2,4.4,0.2);
        if(i%4==0)
            cube(13);
        else
            cube(3);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(50,39,-9+0.1);
    glRotatef(180+45,0,0,1);
    glScalef(40,0.5,0.5);
    cube(3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50,39,-9+6-0.1);
    glRotatef(180+45,0,0,1);
    glScalef(40,0.5,0.5);
    cube(3);
    glPopMatrix();


    //stairs right
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    for(int i=0; i<32; i+=2)
    {
        glPushMatrix();
        glTranslatef(65+i,32-i,28);
        glScalef(2,2,6);
        if(i%4==0)
            cube(13);
        else
            cube(3);

        glPopMatrix();
        //glDisable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(65+i+1,32-i+2,28+0.2);
        glScalef(0.2,4.4,0.2);
        if(i%4==0)
            cube(3);
        else
            cube(13);

        glPopMatrix();


        glPushMatrix();
        glTranslatef(65+i+1,32-i+2,28+6-0.2);
        glScalef(0.2,4.4,0.2);
        if(i%4==0)
            cube(3);
        else
            cube(13);

        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(65,39,28+0.25);
    glRotatef(-45,0,0,1);
    glScalef(45,0.5,0.5);
    //glRotatef(-30,1,0,0);
    cube(3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(65,39,28+6-0.25);
    glRotatef(-45,0,0,1);
    glScalef(45,0.5,0.5);
    cube(3);

    glPopMatrix();


    //overbridge ar pillar(north)
    glPushMatrix();
    glTranslatef(57.5,5,-6);
    glScalef(1,25,-1.60);
    cube(3);
    glPopMatrix();

    //overbridge ar pillar(south)
    glPushMatrix();
    glTranslatef(57.5,1,21+10);
    glScalef(1,29,1.60);
    cube(3);
    glPopMatrix();


    //overbridge ar pillar(maje)
    glPushMatrix();
    glTranslatef(57.5,1,7.5-0.8+5);
    glScalef(1,29,1.60);
    cube(3);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void cylinder_3D(GLdouble height, GLdouble r, GLdouble r2,int c)
{
    if(c==1)
    {
        set_mat_prop(1.0,0.5,0.5);
    }
    else if(c==2)
    {
        set_mat_prop(1.0,1.0,1.0);
    }
    else if(c==3)
    {
        set_mat_prop(1.0,0.0,0.0);
    }
    else if(c==4)
    {
        set_mat_prop(0.0,0.0,1.0);
    }


    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj, 1);
    glRotatef(90, 1, 0, 0);

    gluCylinder(qobj,  r, r2, height, 20, 20);
    gluDeleteQuadric(qobj);

}
void circle_3D(GLdouble radius, int c, int em_on)
{
    if(c==1)
    {
        set_mat_prop(1.0,1.0,1.0);
    }
    else if(c==2)
    {
        if(em_on)
            set_mat_prop(1.0,1.0,1.0,1);
        else
            set_mat_prop(1.0,1.0,1.0);
    }
    else if(c==5)
    {

        set_mat_prop(0.760, 0.205, 0.205);
    }

    else if(c==4)
    {

        set_mat_prop(1.0,1.0,0.0);
    }
    else if(c==6)
    {

        set_mat_prop(0.760, 0.205, 0.205);
    }
    else if(c==7)
    {
        set_mat_prop(0.0276, 0.206, 0.920);
    }




    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj, 1);

    glRotatef(270, 1, 0, 0);
    gluSphere(qobj, radius, 20, 20);
    gluDeleteQuadric(qobj);

}

void sub_tree()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 8);
    glPushMatrix();
    glTranslatef(0,40,0);
    cylinder_3D(25,1,1,2);//base
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(0,40,0);
    circle_3D(10,1,0); //leaf
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void sub_tree_upper()
{
    glPushMatrix();
    glTranslatef(0,15,0);
    glRotatef(90,0,1,0);
    glScalef(2,1,2);
    sub_tree();  //1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,13,0);
    glRotatef(10,1,0,0);
    glScalef(2,1,2);
    sub_tree();  //1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,13,0);
    glRotatef(-10,1,0,0);
    glScalef(2,1,2);
    sub_tree();  //1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,15,0);
    glRotatef(10,0,0,1);
    glScalef(2,1,2);
    sub_tree();  //1
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,15,0);
    glRotatef(-10,0,0,1);
    glScalef(2,1,2);
    sub_tree();  //1
    glPopMatrix();
}
void draw_tree()
{



    set_mat_prop(1.0,1.0,1.0);
    glPushMatrix();
    glTranslatef(0,20,-8);
    glRotatef(55,1,0,0);
    glScalef(0.7,0.7,0.7);
    sub_tree();  //1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,20,8);
    glRotatef(-55,1,0,0);
    glScalef(0.7,0.7,0.7);
    sub_tree();  //1
    glPopMatrix();


//3333333333333333333333333

    glPushMatrix();
    sub_tree_upper();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,10,0);
    glScalef(0.8,1,0.8);
    sub_tree_upper();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 8);
    glPushMatrix();
    glTranslatef(0,40,0);
    cylinder_3D(40,4,8,2);  //tree base
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
void tree()
{
    glPushMatrix();
    glTranslatef(35,1,35+20+10);
    glScalef(0.2,0.3,0.2);
    draw_tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(35,1,45+20+10);
    glScalef(0.2,0.3,0.2);
    draw_tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(114,1,35+20+10);
    glScalef(0.2,0.3,0.2);
    draw_tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(114,1,45+20+10);
    glScalef(0.2,0.3,0.2);
    draw_tree();
    glPopMatrix();

}
void draw_lamp()
{
    glPushMatrix();
    glTranslatef(0,40,0);
    //glScalef(0.2,0.3,0.2);
    cylinder_3D(40,0.5,0.5,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4,38.5,0);
    glScalef(0.8,1,3);
    if(em_1)
        cube(5,1);
    else
        cube(5,0);

    glPopMatrix();


}
void lamp()
{
    glPushMatrix();
    glTranslatef(-63,0,-8);
    //glScalef(0.2,0.3,0.2);
    draw_lamp();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-63+280,0,-8);
    //glScalef(1,0.5,1);
    //glRotatef(90,0,1,0);
    draw_lamp();
    glPopMatrix();

}

void draw_jatri_sauni()
{


    //uporer tak
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glPushMatrix();
    glTranslatef(0,20,0);
    glScalef(60,1,10);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //left khuti-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(1,20,10);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //left khuti-2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(20,0,0);
    glScalef(1,20,10);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //left khuti-3
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(40,0,0);
    glScalef(1,20,10);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //bench-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(5,0,2.5);
    glScalef(5,1,2);
    bench();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //bench-2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(25,0,2.5);
    glScalef(5,1,2);
    bench();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //bench-3
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(45,0,2.5);
    glScalef(5,1,2);
    bench();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void jatri_sauni()
{
    //shamner
    glPushMatrix();
    glTranslatef(-60,5,-20);
    //glScalef(0.2,0.3,0.2);
    draw_jatri_sauni();
    glPopMatrix();

    //Pishoner
    glPushMatrix();
    glTranslatef(-10,5,22+10+10);
    //glScalef(0.2,0.3,0.2);
    glRotatef(180,0,1,0);
    draw_jatri_sauni();
    glPopMatrix();

}
void wind_mil()
{
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(-40,3,-110);
    glScalef(1,49,1);
    cube(10);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-39.5,50,-105);
    glScalef(0.2,0.3,0.2);
    fan();
    glPopMatrix();

}

void front_field()
{
    //bam-pasher field-1
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(-180,0,15+20+10);
    glScalef(35+60+60,1,40+10);
    cube(10);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //bam-pasher field-2
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(5,0,15+20+10);
    glScalef(35,1,40+10);
    cube(10);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //bam-pasher field-3
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(-25,0,15+20+10);
    glScalef(30,1,10);
    cube(10);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //bam-pasher field-4
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(-25,0,45+20+10);
    glScalef(30,1,10+10);
    cube(10);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //pond
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glTranslatef(-25,0,25+20+10);
    glScalef(30,0.5,20);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //majer road
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glPushMatrix();
    glTranslatef(40,0,15+10);
    glScalef(70,1,40+20+10+7);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //dan-pasher field
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(110,0,15+20+10);
    glScalef(80+50,1,40+10);
    cube(10);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //mojaik  bamer field
    //bam-pasher field-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(-180,1,15+20+10);
    glScalef(95+60,0.1,40+10);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //bam-pasher field-2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(5,1,15+20+10);
    glScalef(35,0.1,40+10);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //bam-pasher field-3
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(-25,1,15+20+10);
    glScalef(30,0.1,10);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //bam-pasher field-4
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(-25,1,45+20+10);
    glScalef(30,0.1,10+10);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //dan-pasher field
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(110,1,15+20+10);
    glScalef(80+50,0.1,40+10);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //pond ar pashe bench

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(-35,3,49+10);
    glScalef(5,1,12);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //pond ar pashe benchr khuti--1

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(-33,1.1,49+10);
    glScalef(1,1.9,1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pond ar pashe benchr khuti--2

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(-33,1.1,49+6+10);
    glScalef(1,1.9,1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pond ar pashe benchr khuti--2

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(-33,1.1,49+11+10);
    glScalef(1,1.9,1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //footpath
    //left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,22);
    glPushMatrix();
    glTranslatef(40,1,15+10);
    glScalef(5,2,40+20+10+7);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,22);
    glPushMatrix();
    glTranslatef(40+70-5,1,15+10);
    glScalef(5,2,40+20+10+7);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




}
void road()
{
    //left wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glPushMatrix();
    glTranslatef(-180,0,15+20+10+50);
    glScalef(220,12,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //right wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glPushMatrix();
    glTranslatef(110,0,15+20+10+50);
    glScalef(80+50,12,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //footpath-1
    //left
    // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,22);
    glPushMatrix();
    glTranslatef(-180,0,15+20+10+50+2);
    glScalef(220,2.9,4.9);
    cube(10);
    glPopMatrix();
    // glDisable(GL_TEXTURE_2D);

    //left mojaik
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,26);
    glPushMatrix();
    glTranslatef(-180,2.9,15+20+10+50+2);
    glScalef(220,0.1,4.9);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //left mojaik upor nich
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(-180,0,15+20+10+50+2+4.9);
    glScalef(220,3,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right
    // glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D,22);
    glPushMatrix();
    glTranslatef(110,0,15+20+10+50+2);
    glScalef(80+50,2.9,4.9);
    cube(10);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //right mojaik
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,26);
    glPushMatrix();
    glTranslatef(110,2.9,15+20+10+50+2);
    glScalef(130,0.1,4.9);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right mojaik upor nich
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(110,0,15+20+10+50+2+4.9);
    glScalef(130,3,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shamner road
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,23);
    glPushMatrix();
    glTranslatef(-180,0,15+20+10+50+7);
    glScalef(420,1,30);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //footpath-1
    //left
    // glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D,22);
    glPushMatrix();
    glTranslatef(-180,0,15+20+10+50+7+30+0.1);
    glScalef(420,2.9,4.8);
    cube(10);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //mojaik
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,26);
    glPushMatrix();
    glTranslatef(-180,2.9,15+20+10+50+7+30+0.1);
    glScalef(420,0.1,4.8);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //mojaik araari-shamne
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(-180,0,15+20+10+50+7+30+4.9);
    glScalef(420,3,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //mojaik araari-Pishone
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(-180,0,15+20+10+50+7+30);
    glScalef(420,3,0.1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //sob cheye shamner field
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(-180,0,15+20+10+50+7+30+5);
    glScalef(420,1,70);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);






}
void building()
{


    //nicher cube bam theke -1
    glPushMatrix();
    glTranslatef(5,5,-55);
    glScalef(40,5,30);
    cube(10);
    glPopMatrix();

    //nicher cube bam theke -2
    glPushMatrix();
    glTranslatef(45,5,-55);
    glScalef(20,5,20);
    cube(10);
    glPopMatrix();

    //nicher cube bam theke -3
    glPushMatrix();
    glTranslatef(65,5,-55);
    glScalef(40,5,30);
    cube(10);
    glPopMatrix();

    //pillar shmaner-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(5,10,-28);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar shmaner-2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(42,10,-28);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar shmaner-3
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(42,10,-35);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar shmaner-4
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(65,10,-35);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar shmaner-5
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(65,10,-28);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar shmaner-6
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(102,10,-28);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar Pishoner-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(5,10,-55);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar Pishoner-2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(102,10,-55);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //dewal Pishoner
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(8,10,-55);
    glScalef(94,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //dewal left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(5,10,-52);
    glScalef(3,30,24);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //dewal right
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(102,10,-52);
    glScalef(3,30,24);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //ticket counter shamner(nicher)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(87,10,-52);
    glScalef(1,8,17);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //table-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(87+1,15,-52);
    glScalef(5,1,8);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //chair-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(87+1+10,10,-50);
    glScalef(2,1.5,2);
    glRotatef(-90,0,1,0);
    bench();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //ticket counter pasher(nicher)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(88,10,-36);
    glScalef(12,8,1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //ticket counter divider
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(88,10,-44);
    glScalef(12,15,1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //table2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(87+1,15,-43);
    glScalef(5,1,7);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //chair-2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(87+1+10,10,-41);
    glScalef(2,1.5,2);
    glRotatef(-90,0,1,0);
    bench();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //ticket counter shamner(uporer)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(87,30,-52);
    glScalef(1,10,17);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //ticket counter pasher(uporer)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(88,30,-36);
    glScalef(14,10,1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //ticket counter uporer
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(88,30+9,-52);
    glScalef(14,1,16);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //stairs ar moddor cube
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(8,14+10,-40);
    glScalef(10,1,12);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //stairs----1
    for(int i=0; i<14; i++)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,15);
        glPushMatrix();
        glTranslatef(18+i,14+10-i,-40);
        glScalef(1,1,5);
        cube(10);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
    //stairs----2
    for(int i=0; i<=15; i++)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,15);
        glPushMatrix();
        glTranslatef(18+i,15+10+i,-35);
        glScalef(1,1,5);
        cube(10);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }

    //shmaner dewal-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(8,10,-28);
    glScalef(13,30,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shmaner dewal-2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(29,10,-28);
    glScalef(13,30,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //shmaner dewal-3
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(21,10,-28);
    glScalef(8,11,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shmaner dewal-4
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(21,29,-28);
    glScalef(8,11,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //shmaner dewal-5
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(68,10,-28);
    glScalef(13,30,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shmaner dewal-6
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(89,10,-28);
    glScalef(13,30,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //shmaner dewal-7
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(81,10,-28);
    glScalef(8,11,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shmaner dewal-8
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(81,29,-28);
    glScalef(8,11,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pasher dewal right
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(65,10,-32);
    glScalef(3,30,4);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //pasher dewal left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(42,10,-32);
    glScalef(3,30,4);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //1 st floor ar sad
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(34,30+10,-35);
    glScalef(68,1,7);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar shmaner-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(5,10+30,-28);
    glScalef(100,1,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    /*   //pillar shmaner-5
       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D,14);
       glPushMatrix();
       glTranslatef(65,10+30,-28);
       glScalef(40,1,3);
       cube(10);
       glPopMatrix();
       glDisable(GL_TEXTURE_2D);*/



    //pillar Pishoner-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(5,10+30,-55);
    glScalef(3,1,30);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar Pishoner-2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(102,10+30,-55);
    glScalef(3,1,30);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar Pishoner-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(5,10+30,-55);
    glScalef(100,1,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //pillar shmaner-1(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(5,10+31,-28);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar shmaner-2(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(42,10+31,-28);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //pillar shmaner-3(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(65,10+31,-28);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar shmaner-4(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(102,10+31,-28);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar Pishoner-1(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(5,10+31,-55);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar Pishoner-2(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(102,10+31,-55);
    glScalef(3,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //dewal Pishoner(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(8,10+31,-55);
    glScalef(94,30,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //dewal left(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(5,10+31,-52);
    glScalef(3,30,24);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //dewal right(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(102,10+31,-52);
    glScalef(3,30,24);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shmaner dewal-1(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(8,10+31,-28);
    glScalef(13,30,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shmaner dewal-2(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(29,10+31,-28);
    glScalef(13,30,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //shmaner dewal-3(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(21,10+31,-28);
    glScalef(8,11,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shmaner dewal-4(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(21,60,-28);
    glScalef(8,11,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //shmaner dewal-5(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(68,10+31,-28);
    glScalef(13,30,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shmaner dewal-6(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(89,10+31,-28);
    glScalef(13,30,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //shmaner dewal-7(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(81,10+31,-28);
    glScalef(8,11,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shmaner dewal-8(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(81,60,-28);
    glScalef(8,11,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shmaner dewal-2(extra-wall)(2nd floor)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glTranslatef(45,10+31,-28);
    glScalef(20,30,2);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ////////2nd floor ar char dewal ar musaik shuru

    //pillar shmaner-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(5,10+30+31,-28);
    glScalef(100,5,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    /*   //pillar shmaner-5
       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D,14);
       glPushMatrix();
       glTranslatef(65,10+30,-28);
       glScalef(40,1,3);
       cube(10);
       glPopMatrix();
       glDisable(GL_TEXTURE_2D);*/



    //pillar Pishoner-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(5,10+30+31,-55);
    glScalef(3,5,30);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar Pishoner-2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(102,10+30+31,-55);
    glScalef(3,5,30);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pillar Pishoner-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(5,10+30+31,-55);
    glScalef(100,5,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ////////2nd floor ar char dewal ar musaik shuru


    //2nd floor ar sad shuru
    glPushMatrix();
    glTranslatef(5+3,10+31+30,-55+3);
    glScalef(94,1,24);
    cube(10);
    glPopMatrix();
    //2nd floor ar sad sesh

    //dhorjar uporer musaik
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(45,30,-35);
    glScalef(20,10,3);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //dhorjar stairs
    for(int i=1; i<=5; i++)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,14);
        glPushMatrix();
        glTranslatef(45,10-i,-35+i);
        glScalef(20,1,1);
        cube(10);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

    }

    //window shuru

    //window-1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
    glPushMatrix();
    glTranslatef(21,10+11,-28+1.5);
    if(!window)
        glScalef(4,8,0.5);
    else
        glScalef(0.5,8,4);
    //if(window)
    //glRotatef(-180,0,1,0);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
    glPushMatrix();
    glTranslatef(29,10+11,-28+1.5);
    if(!window)
        glScalef(-4,8,0.5);
    else
        glScalef(-0.5,8,4);
    //if(window)
    //glRotatef(-180,0,1,0);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //window-2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
    glPushMatrix();
    glTranslatef(21,10+31+11,-28+1.5);
    if(!window)
        glScalef(4,8,0.5);
    else
        glScalef(0.5,8,4);
    // if(window)
    // glRotatef(90,0,1,0);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
    glPushMatrix();
    glTranslatef(29,10+11+31,-28+1.5);
    if(!window)
        glScalef(-4,8,0.5);
    else
        glScalef(-0.5,8,4);
    // if(window)
    //   glRotatef(90,0,1,0);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //window-3
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
    glPushMatrix();
    glTranslatef(81,10+11,-28+1.5);
    if(!window)
        glScalef(4,8,0.5);
    else
        glScalef(0.5,8,4);
    //  if(window)
    //   glRotatef(90,0,1,0);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
    glPushMatrix();
    glTranslatef(89,10+11,-28+1.5);
    if(!window)
        glScalef(-4,8,0.5);
    else
        glScalef(-0.5,8,4);
    // if(window)
    //  glRotatef(90,0,1,0);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //window-4
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
    glPushMatrix();
    glTranslatef(81,10+31+11,-28+1.5);
    if(!window)
        glScalef(4,8,0.5);
    else
        glScalef(0.5,8,4);
    //if(window)
    //   glRotatef(90,0,1,0);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
    glPushMatrix();
    glTranslatef(89,10+11+31,-28+1.5);
    if(!window)
        glScalef(-4,8,0.5);
    else
        glScalef(-0.5,8,4);
    // if(window)
    //  glRotatef(90,0,1,0);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /* glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D,18);
     glPushMatrix();
     glTranslatef(45,71,-24.9);
     glScalef(20,5,0.1);
     // if(window)
     //  glRotatef(90,0,1,0);
     cube(10);
     glPopMatrix();
     glDisable(GL_TEXTURE_2D);*/


    //text
    //set_mat_prop(1,0,0);
    glPushMatrix();
    glTranslatef(37, 76.5,-25);
    string str="RAILWAY STATION";
    glScalef(0.03,0.03,1);

    for (int i=0; i<str.size(); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();



}

void chair()
{

    glPushMatrix();//khuti
    glTranslatef(0.55,0,0.55);
    glScalef(0.4,2,0.4);
    cube(15);
    glPopMatrix();

    glPushMatrix();//tol
    glTranslatef(0,2,0);
    glScalef(1.5,0.1,1.5);
    cube(15);
    glPopMatrix();

    glPushMatrix();//floor
    glTranslatef(0,2,0);
    glScalef(1.5,2,0.1);
    cube(15);
    glPopMatrix();


}

void draw_train()
{



    glPushMatrix();//floor
    glTranslatef(0,0,0);
    glScalef(45,1,10);
    cube(1);
    glPopMatrix();

    glPushMatrix();//south ar nich
    glTranslatef(5.5,1,0);
    glScalef(39,5,0.5);
    cube(14);
    glPopMatrix();

    glPushMatrix();//south ar upore
    glTranslatef(5.5,10,0);
    glScalef(39,6,0.5);
    cube(14);
    glPopMatrix();

    glPushMatrix();//bogir left pash
    glTranslatef(0,1,0);
    glScalef(0.5,15,10);
    cube(14);
    glPopMatrix();

    glPushMatrix();//bogir right pash
    glTranslatef(44.5,1,0);
    glScalef(0.5,15,10);
    cube(14);
    glPopMatrix();

    int j=0;
    for(int i=0; i<4; i++)
    {
        glPushMatrix();
        glTranslatef(5.5+j,6,0);
        glScalef(6,4,0.5);
        cube(6);
        glPopMatrix();
        j=j+11;
    }

    glPushMatrix();//north ar nich
    glTranslatef(5.5,1,9.5);
    glScalef(39,5,0.5);
    cube(14);
    glPopMatrix();

    glPushMatrix();//north ar upore
    glTranslatef(5.5,10,9.5);
    glScalef(39,6,0.5);
    cube(14);
    glPopMatrix();

    j=0;
    for(int i=0; i<4; i++)
    {
        glPushMatrix();//bogir right pash
        glTranslatef(5.5+j,6,9.5);
        glScalef(6,4,0.5);
        cube(3);
        glPopMatrix();
        j=j+11;
    }

    //dhorja--1
    glPushMatrix();
    glTranslatef(5,1,0);
    glScalef(0.5,15,3);
    cube(14);
    glPopMatrix();

    //dhorja--2
    glPushMatrix();
    glTranslatef(5,1,0+7);
    glScalef(0.5,15,3);
    cube(14);
    glPopMatrix();

    j=0;
    for(int i=0; i<10; i++)
    {
        glPushMatrix();
        glTranslatef(5+0.5+j,1,1);
        glScalef(2,1,1);
        chair();
        glPopMatrix();
        j+=4;

    }

    j=0;
    for(int i=0; i<10; i++)
    {
        glPushMatrix();
        glTranslatef(5+0.5+j+3,1,8.5);
        glScalef(2,1,1);
        glRotatef(180,0,1,0);
        chair();
        glPopMatrix();
        j+=4;

    }

    //two train connector
    glPushMatrix();
    glTranslatef(45,1,1);
    glScalef(3,1,1);
    //glRotatef(180,0,1,0);
    cube(13);
    glPopMatrix();

    //two train connector
    glPushMatrix();
    glTranslatef(45,1,8);
    glScalef(3,1,1);
    //glRotatef(180,0,1,0);
    cube(13);
    glPopMatrix();


    //sad
    glPushMatrix();
    glTranslatef(0,16,0);
    glScalef(45,1,10);
    cube(14);
    glPopMatrix();


    //window south
    j=0;
    for(int i=0; i<3; i++)
    {
        glPushMatrix();
        glTranslatef(5.5+6+j,6,9.4);
        glScalef(5,4,0.1);
        if(window)
        {
            glRotatef(180,1,0,1);
        }

        cube(1);
        glPopMatrix();
        j+=11;
    }

    //window south
    j=0;
    for(int i=0; i<3; i++)
    {
        glPushMatrix();
        glTranslatef(5.5+6+j,6,0.5);
        glScalef(5,4,0.1);
        if(window)
        {
            glRotatef(180,1,0,1);
        }
        cube(1);
        glPopMatrix();
        j+=11;
    }






}
void wheel_1()
{
    int j=0;
    // glPushMatrix();
    for(; j<168; j+=4)
    {
        glPushMatrix();
        glTranslatef(-39+0.5+j,2,15.5);
        if(train_1)
            glRotatef(wheel_speed_1,0,1,0);
        circle_3D(0.5,2,0);
        //gluDisk(q,0.1,0.5,50,50);


        glPopMatrix();

    }
    //glPopMatrix();
    // glPushMatrix();
    j=0;
    for(; j<168; j+=4)
    {
        glPushMatrix();
        glTranslatef(0.5+j-39,2,24.4);
        if(train_1)
            glRotatef(wheel_speed_1,0,1,0);
        circle_3D(0.5,2,0);
        //gluDisk(q,0.1,0.5,50,50);


        glPopMatrix();

    }
    //  glPopMatrix();





}
void wheel_2()
{
    int j=0;
    // glPushMatrix();
    for(; j<168; j+=4)
    {
        glPushMatrix();
        glTranslatef(0.5+j-70,2,0.5);
        if(train_2)
            glRotatef(-wheel_speed_1,0,1,0);
        circle_3D(0.5,2,0);
        //gluDisk(q,0.1,0.5,50,50);


        glPopMatrix();

    }
    //glPopMatrix();
    // glPushMatrix();
    j=0;
    for(; j<168; j+=4)
    {
        glPushMatrix();
        glTranslatef(0.5+j-70,2,9.4);
        if(train_2)
            glRotatef(-wheel_speed_1,0,1,0);
        circle_3D(0.5,2,0);
        //gluDisk(q,0.1,0.5,50,50);


        glPopMatrix();

    }
    //  glPopMatrix();





}
void draw_full_train()
{
    int j=0;
    for(int i=0; i<3; i++)
    {
        glPushMatrix();
        glTranslatef(0+j,0,0);
        draw_train();

        glPopMatrix();
        j+=48;

    }




    glPushMatrix();//floor
    glTranslatef(144,0,0);
    glScalef(25,1,10);
    cube(1);
    glPopMatrix();

    glPushMatrix();//south ar nich
    glTranslatef(144+5.5,1,0);
    glScalef(19,5,0.5);
    cube(14);
    glPopMatrix();

    glPushMatrix();//south ar upore
    glTranslatef(144+5.5,10,0);
    glScalef(19,6,0.5);
    cube(14);
    glPopMatrix();

    glPushMatrix();//bogir left pash
    glTranslatef(144,1,0);
    glScalef(0.5,15,10);
    cube(14);
    glPopMatrix();

    glPushMatrix();//bogir right pash
    glTranslatef(44.5+144-20,1,0);
    glScalef(0.5,15,10);
    cube(14);
    glPopMatrix();

    j=0;
    for(int i=0; i<2; i++)
    {
        glPushMatrix();
        glTranslatef(144+5.5+j,6,0);
        glScalef(7,4,0.5);
        cube(6);
        glPopMatrix();
        j=j+12;
    }

    glPushMatrix();//north ar nich
    glTranslatef(144+5.5,1,9.5);
    glScalef(19,5,0.5);
    cube(14);
    glPopMatrix();

    glPushMatrix();//north ar upore
    glTranslatef(144+5.5,10,9.5);
    glScalef(19,6,0.5);
    cube(14);
    glPopMatrix();

    j=0;
    for(int i=0; i<2; i++)
    {
        glPushMatrix();//bogir right pash
        glTranslatef(144+5.5+j,6,9.5);
        glScalef(7,4,0.5);
        cube(3);
        glPopMatrix();
        j=j+12;
    }

    //dhorja--1
    glPushMatrix();
    glTranslatef(144+5,1,0);
    glScalef(0.5,15,3);
    cube(14);
    glPopMatrix();

    //dhorja--2
    glPushMatrix();
    glTranslatef(144+5,1,0+7);
    glScalef(0.5,15,3);
    cube(14);
    glPopMatrix();


    //sad
    glPushMatrix();
    glTranslatef(0+144,16,0);
    glScalef(25,1,10);
    cube(14);
    glPopMatrix();


    //window south
    j=0;
    for(int i=0; i<1; i++)
    {
        glPushMatrix();
        glTranslatef(5.5+7+j+144,6,9.4);
        glScalef(5,4,0.1);
        if(window)
        {
            glRotatef(180,1,0,1);
        }
        cube(1);
        glPopMatrix();
        j+=12;
    }

    //window south
    j=0;
    for(int i=0; i<1; i++)
    {
        glPushMatrix();
        glTranslatef(5.5+7+j+144,6,0.5);
        glScalef(5,4,0.1);
        if(window)
        {
            glRotatef(180,1,0,1);
        }
        cube(1);
        glPopMatrix();
        j+=12;
    }





}


void train1()
{

    glPushMatrix();
    glTranslatef(-70+200,2,15+10);
    glRotatef(180,0,1,0);
    draw_full_train();
    glPopMatrix();

}
void train2()
{
    glPushMatrix();
    glTranslatef(-70,2,0);
    draw_full_train();
    glPopMatrix();



}
void train()
{


    if(train_1)
    {
        // sndPlaySound("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\audio\\sound1.wav", SND_ASYNC);
        glPushMatrix();
        glTranslatef(-train_speed1,0,0);
        train1();

        glPopMatrix();


    }
    else
    {

        glPushMatrix();
        glTranslatef(-train_speed1,0,0);
        train1();
        glPopMatrix();
    }
    if(train_2)
    {
        // sndPlaySound("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\audio\\sound1.wav", SND_ASYNC);
        glPushMatrix();
        glTranslatef(train_speed2,0,0);
        train2();

        glPopMatrix();


    }
    else
    {
        glPushMatrix();
        glTranslatef(train_speed2,0,0);
        train2();
        glPopMatrix();
    }
    if(train_reset)
    {
        glPushMatrix();
        //glTranslatef(train_speed2,0,0);
        train1();

        glPopMatrix();


        glPushMatrix();
        //glTranslatef(train_speed2,0,0);
        train2();

        glPopMatrix();
        train_speed1=0;
        train_speed2=0;
        train_1= false;
        train_2= false;

        train_reset=false;

    }
}
void wheel()
{
    if(train_1)
    {
        glPushMatrix();
        glTranslatef(-train_speed1,0,0);
        wheel_1();
        glPopMatrix();


    }
    else
    {
        glPushMatrix();
        glTranslatef(-train_speed1,0,0);
        wheel_1();
        glPopMatrix();
    }
    if(train_2)
    {
        glPushMatrix();
        glTranslatef(train_speed2,0,0);
        wheel_2();
        glPopMatrix();


    }
    else
    {
        glPushMatrix();
        glTranslatef(train_speed2,0,0);
        wheel_2();
        glPopMatrix();
    }
    if(train_reset)
    {
        glPushMatrix();
        //glTranslatef(train_speed2,0,0);
        wheel_1();

        glPopMatrix();


        glPushMatrix();
        //glTranslatef(train_speed2,0,0);
        wheel_2();

        glPopMatrix();
        wheel_speed_1=0;
        wheel_speed_2=0;
        train_1= false;
        train_2= false;

        train_reset=false;

    }
}


void sky()
{
    glRotatef(theta1, 1,0,0);
    glPushMatrix();
    glTranslatef(25,0,0);
    circle_3D(220,3,0);
    glPopMatrix();

}
void sun()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 21);
    glPushMatrix();
    glTranslatef(-70,125,-165);
    circle_3D(20,4,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void moon()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 20);
    glPushMatrix();
    glTranslatef(-120,120,-120);
    circle_3D(20,2,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void draw_star()
{
    set_mat_prop(1, 1, 1,1);
    glPushMatrix();
    glBegin(GL_POLYGON);

    glVertex3f(-0.60, 0.77, 0);
    glVertex3f(-0.68, 0.77, 0);
    glVertex3f(-0.7, 0.68, 0);
    glVertex3f(-0.64, 0.63, 0);
    glVertex3f(-0.58, 0.68, 0);

    glEnd();
    glPopMatrix();
}
void star()
{
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, 20);
    glPushMatrix();
    glTranslatef(-10,100,-120);
    glScalef(30,30,30);
    draw_star();
    glPopMatrix();
    // glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-70,115,-120);
    glScalef(10,10,10);
    draw_star();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(50,130,-125);
    glScalef(20,20,20);
    draw_star();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(70+30,125+10,-130);
    glScalef(10,10,10);
    draw_star();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(110+30,70,-120);
    glScalef(10,10,10);
    draw_star();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-120,70,-120);
    glScalef(10,10,10);
    draw_star();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-120,80,-125);
    glScalef(10,10,10);
    draw_star();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-150,40,-80);
    glScalef(20,20,20);
    draw_star();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-170,30,-80);
    glScalef(20,15,20);
    draw_star();
    glPopMatrix();

    /*glPushMatrix();
    glTranslatef(-169,35,-60);
    glScalef(20,15,20);
    draw_star();
    glPopMatrix();*/
}


void shop()
{
    //araari box
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 25);
    glPushMatrix();
    glTranslatef(190,5,-50);
    glScalef(5,5,15);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //shamner box
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 25);
    glPushMatrix();
    glTranslatef(190,5,-50+15);
    glScalef(15,5,5);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //chula
    //glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, 25);
    glPushMatrix();
    glTranslatef(190+5,10,-50+1+15);
    glScalef(3,0.5,3);
    cube(10);
    glPopMatrix();
    //  glDisable(GL_TEXTURE_2D);



    //chular switch-1
    glPushMatrix();
    glTranslatef(190+5+1,10+0.2,-50+1+15-0.1);
    glScalef(0.1,0.1,0.1);
    cube(2);
    glPopMatrix();

    //chular switch-2
    glPushMatrix();
    glTranslatef(190+5+2,10+0.2,-50+1+15-0.1);
    glScalef(0.1,0.1,0.1);
    cube(3);
    glPopMatrix();

    //kattle
    glPushMatrix();
    glTranslatef(190+5+1.5,10+0.5+1.2,-50+1+15+1.5);
    // glScalef(0.1,0.1,0.1);
    glutSolidTeapot(1.5);
    glPopMatrix();


    //cup ar jonno tray
    //chula
    //glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, 25);
    glPushMatrix();
    glTranslatef(190+5+7,10+0.2,-50+1+15+1.5);
    glScalef(1,0.1,1);
    //cube(10);
    circle_3D(2,1,0);
    glPopMatrix();
    //  glDisable(GL_TEXTURE_2D);

    //cup
    for(float i=0; i<3; i+=1.5)
    {
        glPushMatrix();
        glTranslatef(190+5+7-1+i,10+0.15,-50+1+15+1.5-1);
        glScalef(0.5,0.8,1);
        //cube(10);
        basket(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(190+5+7-1+i,10+0.15,-50+1+15+1.8);
        glScalef(0.5,0.8,1);
        //cube(10);
        basket(2);
        glPopMatrix();

    }

    //pishoner dewal
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 27);
    glPushMatrix();
    glTranslatef(190,5,-50-1);
    glScalef(20,20,1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ////pasher dewal
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 27);
    glPushMatrix();
    glTranslatef(190+20,5,-50-1);
    glScalef(1,20,21);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //saad
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 25);
    glPushMatrix();
    glTranslatef(190,25,-50-1);
    glScalef(21,1,21);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //shamner khuti
    //saad
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 25);
    glPushMatrix();
    glTranslatef(190,10,-50+15+4);
    glScalef(1,15,1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //bench

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(190+5,5+2,-20-5);
    glScalef(10,1,5);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //pond ar pashe benchr khuti--1

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(195,5,-18-5);
    glScalef(1,2,1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pond ar pashe benchr khuti--2

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(199,5,-18-5);
    glScalef(1,2,1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pond ar pashe benchr khuti--2

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(204,5,-18-5);
    glScalef(1,2,1);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //jar 1
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, 25);
    glPushMatrix();
    glTranslatef(190+2.5,10+3,-50+15-5);
    //glScalef(1,3,);
    cylinder_3D(3,1,1,3);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);


    //jar 1
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, 25);
    glPushMatrix();
    glTranslatef(190+2.5,10+3,-50+15-5-3);
    //glScalef(1,3,);
    cylinder_3D(3,1,1,4);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);



    //suta
    //araari box
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, 25);
    glPushMatrix();
    glTranslatef(190,23,-50);
    glScalef(1,0.3,19);
    cube(10);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);



}
void day_night()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glPushMatrix();
    glTranslatef(-180+182-1,26,15+20+10+50+7+30+0.1+2.5);
    glScalef(2,2,0.08);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /*  glPushMatrix();
      glTranslatef(3,26,15+20+10+50+7+30+0.1+2.5+0.1);
      string str="D_N";
      glScalef(0.01,0.01,1);

      for (int i=0; i<str.size(); i++)
      {
          glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
      }
      glPopMatrix();*/
}
void drawhuman(int c)
{


    glPushMatrix();
    glTranslatef(5,0,0.5);
    //head
    glPushMatrix();
    glTranslatef(-5.27,0.4,-0.1);
    circle_3D(0.18,5,0);
    glPopMatrix();

    //body
    glEnable(GL_TEXTURE_2D);
    if(c==1)
        glBindTexture(GL_TEXTURE_2D,29);
    else
        glBindTexture(GL_TEXTURE_2D,30);
    glPushMatrix();
    glTranslatef(-5.5,-0.55,0);
    glScalef(-0.5,0.8,0.2);
    glRotated(180,0,1,0);
    cube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //leg-1
    glEnable(GL_TEXTURE_2D);
    if(c==2)
        glBindTexture(GL_TEXTURE_2D,29);
    else
        glBindTexture(GL_TEXTURE_2D,30);
    glPushMatrix();
    glTranslatef(-5.4,-0.8,-0.1);
    glScalef(0.1,0.4,0.05);
    circle_3D(1,1,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //leg-2
    glEnable(GL_TEXTURE_2D);
    if(c==2)
        glBindTexture(GL_TEXTURE_2D,29);
    else
        glBindTexture(GL_TEXTURE_2D,30);
    glPushMatrix();
    glRotated(0,1,0,0);
    glPushMatrix();
    glTranslatef(-5.15,-0.8,-0.1);
    glScalef(0.1,0.4,0.05);
    circle_3D(1,1,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //shoesright
    glPushMatrix();
    glTranslatef(-5.15,-1.15,-0.15);
    glScalef(0.05,0.05,0.1);
    circle_3D(1,1,0);
    glPopMatrix();
    glPopMatrix();

    //shoesleft
    glPushMatrix();
    glTranslatef(-5.4,-1.15,-0.15);
    glScalef(0.05,0.05,0.1);
    //glBindTexture(GL_TEXTURE_2D,4);
    circle_3D(1,1,0);
    glPopMatrix();

    //lefthand
    glPushMatrix();
    glTranslatef(-5.6,-0.1,-0.1);
    glRotated(-30,0,0,1);
    glScalef(0.05,0.4,0.05);
    circle_3D(1,7,0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-5.755,-0.4,-0.1);
    glScalef(0.05,0.05,0.05);
    glRotated(180,0,1,0);
    circle_3D(1,1,0);
    glPopMatrix();

    //right hand
    glPushMatrix();
    glTranslatef(-4.9,-0.1,-0.1);
    glRotated(30,0,0,1);
    glScalef(0.05,0.4,0.05);
    circle_3D(1,7,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.745,-0.4,-0.1);
    glScalef(0.05,0.05,0.05);
    glRotated(180,0,1,0);
    circle_3D(1,1,0);
    glPopMatrix();
    glPopMatrix();
    // glDisable(GL_TEXTURE_2D);



}
void human()
{
    glPushMatrix();
    glTranslatef(107.5,9,50);
    glScalef(2,5,2);
    drawhuman(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(42.5,9,100);
    glScalef(2,5,2);
    glRotatef(-180,0,1,0);
    drawhuman(2);
    glPopMatrix();


}
int clikd=0;

float wcsClkDn[3],wcsClkUp[3];
///////////////////////////////
class point1
{
public:
    point1()
    {
        x=0;
        y=0;
    }
    int x;
    int y;
} clkpt[2];

int flag=0;
GLboolean buttonclk=false;
GLint viewport[4]; //var to hold the viewport info
GLdouble modelview[16]; //var to hold the modelview info
GLdouble projection[16]; //var to hold the projection matrix info

//////////////////////////
void scsToWcs(float sx,float sy, float wcsv[3] );
void processMouse(int button, int state, int x, int y);

///////////////////////////

void scsToWcs(float sx,float sy, float wcsv[3] )
{

    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

    //glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info

    winX = sx;
    winY = (float)viewport[3] - (float)sy;
    winZ = 0;

    //get the world coordinates from the screen coordinates
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    wcsv[0]=worldX;
    wcsv[1]=worldY;
    wcsv[2]=worldZ;


}
void processMouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(flag!=1)
        {
            flag=1;
            clkpt[0].x=x;
            clkpt[0].y=y;
        }


        scsToWcs(clkpt[0].x,clkpt[0].y,wcsClkDn);
        // cout<<"\nD: "<<x<<" "<<y<<" wcs: "<<wcsClkDn[0]<<" "<<wcsClkDn[1];
        if(x>4 && x<61)
        {
            if(y>16 && y<64)
            {
                day=!day;
                light1= !light1;
                light2= !light2;
                light3= !light3;
                light4= !light4;
                em_1 = !em_1;

            }
        }

    }
    else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (flag==1)
        {
            clkpt[1].x=x;
            clkpt[1].y=y;
            flag=0;
        }
        float wcs[3];
        scsToWcs(clkpt[1].x,clkpt[1].y,wcsClkUp);
        //cout<<"\nU: "<<x<<" "<<y<<" wcs: "<<wcsClkUp[0]<<" "<<wcsClkUp[1];

        clikd=!clikd;
    }
}
void r_oll(bool flag)
{
    if(flag)
    {
        angle1+=5;
    }
    else
    {
        angle1-=5;
    }
    x_up= -sin(PI*angle1/180.0);
    y_up = cos(PI*angle1/180);

//    activate_roll=!activate_roll;
}


void p_itch(bool flag)
{

    if(flag)
    {
        angle2=5;
    }
    else
    {
        angle2=-5;
    }


    //GLfloat x = lookX-eyeX;//look_x - eye_x;
    GLfloat y = lookY-eyeY;//look_y - eye_y;
    GLfloat z = lookZ-eyeZ;

    GLfloat dy=y*cos(angle2*PI/180.0)-z*sin(angle2*PI/180.0);
    GLfloat dz =y*sin(angle2*PI/180.0) +z*cos(angle2*PI/180.0);

    lookY =eyeY+dy;
    lookZ =eyeZ+dz;

    //cout<<"pitch"<<lookX<<" "<<lookY<<" "<<lookZ<<endl;
    // printf

    //z_up = sin(PI*angle2/180.0);
    //y_up = cos(PI*angle2/180);
    //activate_pitch=!activate_pitch;

}

void y_aw(bool flag)
{
    if(flag)
    {
        angle3=5;
    }
    else
    {
        angle3=-5;
    }

    GLfloat x = lookX-eyeX;//look_x - eye_x;
    //GLfloat y = lookY-eyeY;//look_y - eye_y;
    GLfloat z = lookZ-eyeZ;

    GLfloat dx = x*cos(angle3*PI/180.0)+z*sin(angle3*PI/180.0);
    //GLfloat dy = y;
    GLfloat dz = -x*sin(angle3*PI/180.0) +z*cos(angle3*PI/180.0);

    lookX = eyeX + dx;
    //lookY = dy;
    lookZ = eyeZ+ dz;

    //cout<<"yaw"<<lookX<<" "<<lookY<<" "<<lookZ<<endl;

    //activate_yaw=!activate_yaw;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-3+lpan, 6+rpan, -3, 6, 3.5+fdist, 1000);
    const float ar = float(WINDOW_WIDTH)/float(WINDOW_HEIGHT);
    gluPerspective(90,ar,3.5+fdist,600);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, x_up,y_up,z_up);

    //glViewport(0, 0, windowHeight, windowWidth);
    //glViewport(350, 20, 800, 700);

    // glRotatef(45, 0, 0, 1 );
    // triangle();
    glRotatef( theta, axis_x, axis_y, 0.0 );


    glScalef(sx,sy,sz);




    rail_line();
    platform();
    fence();
    hills();
    field();
    front_field();
    over_bridge();
    tree();
    lamp();
    jatri_sauni();

    wind_mil();
    building();


    train();
    wheel();

    if(day)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 18);
        glPushMatrix();
        sky();

        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        sun();
    }
    else
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 19);
        glPushMatrix();
        sky();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        moon();
        star();

    }
    road();
    shop();
    day_night();
    human();




















    /*
       glPushMatrix();
       glTranslatef(0,0,Tzval);

       glRotatef( alpha,axis_x, axis_y, 0.0 );
       glRotatef( theta, axis_x, axis_y, 0.0 );
       drawpyramid();
       glPopMatrix();
    */
    /*
      glPushMatrix();
         glTranslatef(0,0,Tzval);
         glScalef(3,3,3);
         glutSolidCube(1);
     glPopMatrix();
    */
    glFlush();
    glutSwapBuffers();
}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    //printf("%c%d%d",key,x,y);
    float x1, z1, r, theta1, dx, dz, dx_norm, dz_norm, r1=1;
    x1=lookX-eyeX;
    z1=lookZ-eyeZ;
    r=sqrt(x1*x1+z1*z1);

    if(x1==0)
    {
        if(z1>0)
        {
            theta1 = 90;
        }
        else if(z1<0)
        {
            theta1 = -90;
        }
    }
    else
        theta1=atan(z1/x1) * 180 / 3.1416;

    if((z1>0 && theta1<0) || (z1<0 && theta1>0))
        theta1 += 180;
    else if(z1<0 && theta1<0)
    {
        theta1 += 360;
    }

    dx = r1*cos(theta1 * 3.1416 / 180);
    dz = r1*sin(theta1 * 3.1416 / 180);

    dx_norm = r1*cos((theta1-90) * 3.1416 / 180);
    dz_norm = r1*sin((theta1-90) * 3.1416 / 180);

    switch ( key )
    {
    case 's':
    case 'S':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'x':
    case 'X':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case '+':
        Tzval+=0.2;
        break;

    case '-':
        Tzval-=0.2;
        break;
//Zooming
    case 'a':
        eyeZ++;
        lookZ++;
        break;
    case 'A':
        eyeZ--;
        lookZ--;
        break;
    case 'b':
        fdist++;
        break;
    case 'B':
        fdist--;
        break;

    case 'c':
        sx+=0.1;
        sy+=0.1;
        sz+=0.1;
        break;
    case 'C':
        sx-=0.1;
        sy-=0.1;
        sz-=0.1;
        break;

    /*   case 'p':
           if(anglePitch<anglePitchLimit1)
           {
               anglePitch += roll_value;
               p_itch();
           }

           break;
       case 'P':
           if(anglePitch>anglePitchLimit2)
           {
               anglePitch -= roll_value;
               p_itch();
           }

           break;
       case 'y':
           if(angleYaw<angleYawLimit1)
           {
               angleYaw += roll_value;
               y_aw();
           }

           break;
       case 'Y':
           if(angleYaw>angleYawLimit2)
           {
               angleYaw -= roll_value;
               y_aw();
           }

           break;
       case 'r':
           if(angleRoll<angleRollLimit1)
           {
               angleRoll += roll_value;
               r_oll();
           }
           break;
       case 'R':

           if(angleRoll>angleRollLimit2)
           {
               angleRoll -= roll_value;
               r_oll();
           }

           break;*/




//pitch

    case 'p':
        p_itch(true);
        break;
    case 'P':
        p_itch(false);
        break;

    //yaw
    case 'y':
        // y=y;
        y_aw(true);

        break;
    case 'Y':
        //y=y;
        y_aw(false);

        break;



    //roll
    case 'r':
        r_oll(true);
        break;
    case 'R':
        r_oll(false);
        break;

    // Moving the camera front-back-left-right
    case 'j':
        eyeX += dx_norm*5;
        eyeZ += dz_norm*5;


        lookX += dx_norm*5;
        lookZ += dz_norm*5;
        break;
    case 'i':
        eyeX += dx*5;
        eyeZ += dz*5;
        lookX += dx*5;
        lookZ += dz*5;
        break;
    case 'k':
        eyeX -= dx*5;
        eyeZ -= dz*5;

        lookX -= dx*5;
        lookZ -= dz*5;
        break;
    case 'l':
        eyeX -= dx_norm*5;
        eyeZ -= dz_norm*5;

        lookX -= dx_norm*5;
        lookZ -= dz_norm*5;
        break;
    case 't':

        eyeY ++;
        break;
    case 'g':
        eyeY --;

        break;

    // case 'm':
    //eyeX+=5;
    // break;
    //case 'n':
    // eyeX-=5;
    // break;

    /*    case 'l':


            if(activate_roll)
            {

                eyeZ++;
                r_oll(false);




            }
            if(activate_pitch)
            {
                eyeZ++;
                p_itch(false);



            }
            if(activate_yaw)
            {

                eyeZ++;
                y_aw(false);



            }
            if(!activate_roll && !activate_pitch && !activate_yaw)
            {
                eyeZ++;
                lookZ++;
            }

            break;
        case 'L':


            if(activate_roll)
            {

                eyeZ--;
                r_oll(true);

            }
            if (activate_pitch)
            {

                eyeZ--;
                p_itch(true);

            }
            if(activate_yaw)
            {

                eyeZ--;
                y_aw(true);

            }



            if(!activate_roll && !activate_pitch && !activate_yaw)
            {
                eyeZ--;
                lookZ--;
            }

            break;*/

//panning
    // case 'n':
    //   lpan-=1;
    //   rpan-=1;

    //   break;

    //case 'N':
    //lpan+=1;
    //rpan +=1;
    //break;

//train
    case '7':
        //train_speed+=0.2;
        train_1 = !train_1;
        // em = !em;
        break;

    case '8':
        //train_speed+=0.2;
        train_2 = !train_2;
        // em = !em;
        break;

    case '9':
        //train_speed+=0.2;
        train_reset = true;
        // em = !em;
        break;



    case 'f':
        fan_c = !fan_c;
        break;

    // on-off switches to whichever it is attached
    case '2':
        light2 = !light2;
        light3=!light3;
        em_1 = !em_1;
        break;
    case '1':
        light1 = !light1;
        em = !em;
        break;
    case '3':
        light4=!light4;

        break;






    // Ambient light on-off
    case 'u':
        amb_light_on = !amb_light_on;
        break;
    // Specular light on-off
    case 'v':
        diff_light_on = !diff_light_on;
        break;
    // Diffuse light on-off
    case 'w':
        spec_light_on = !spec_light_on;
        break;

//window
    case '5':
        window = !window;
        break;
//day-night
    case 'd':
        //light1=true
        day = !day;
        light1= !light1;
        light2= !light2;
        light3= !light3;
        light4= !light4;
        em_1 = !em_1;
        break;


    case 27:  // Escape key
        exit(1);
    }

}



void animate()
{
    if(light1)
    {
        light();
    }
    else
    {
        light_off(GL_LIGHT0);
    }
    if(light2)
    {
        spotlight1();
    }
    else
    {
        light_off(GL_LIGHT1);
    }
    if(light3)
    {
        spotlight2();
    }
    else
    {
        light_off(GL_LIGHT2);
    }
    if(light4)
    {
        moon_light();
    }
    else
    {
        light_off(GL_LIGHT3);
    }

    if(fan_c)
    {
        speed += 10;
    }
    if(train_2)
    {
        //sndPlaySound("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\audio\\sound1.wav", SND_ASYNC);
        train_speed2+=0.5;
        wheel_speed_2+=0.5;
    }
    if(train_1)
    {
        // sndPlaySound("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\audio\\sound1.wav", SND_ASYNC);
        train_speed1+=0.5;
        wheel_speed_1+=0.5;
    }

    if (rotate_sky)
    {
        theta1 += 0.1;
        if( theta1>360  )
        {
            theta1=0;
            //day=!day;

        }

    }
    if (bRotate == true)
    {
        theta += 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    glutPostRedisplay();

}
void changeSize(int w, int h)
{
    /*//Prevent a divide by zero, when window is too short;you cant make a window of zero width.
     if (h == 0)
         h = 1;
     float ratio = (GLfloat)w / (GLfloat)h;         //Calculate aspect ratio of the window

     //Set the perspective coordinate system
     glMatrixMode(GL_PROJECTION);                   //Use the Projection Matrix
     glLoadIdentity();                              //Reset Matrix

     glViewport(0, 0, w, h);                        //Set the viewport to be the entire window
     gluPerspective(60, ratio, 1, 200);             //Set the correct perspective.
     glMatrixMode(GL_MODELVIEW);                    //Get Back to the Modelview*/
    const float ar = float(w)/float(h);
    glViewport(0, 0, w, w/ar);
}

void load_textures()
{
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\field1.bmp",1);//pataton ar majer grass
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\wall4.bmp",2);//platform ar tiles
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\wall2.bmp",3);//platform ar shamner tiles
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\steel.bmp",4);//rail line  ar tiles
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\grass4.bmp",5);//plshoner field
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\road_vertical.bmp",6);//road
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\water.bmp",7);//pond
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\tree_body.bmp",8);//tree_body
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\tree_leaf_1.bmp",9);//tree_l
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\concrete.bmp",10);//jatri sauni pishonwe wall
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\tile1.bmp",11);//jatri sauni pishonwe wall
    //LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\tree_leaf.bmp",12);//jatri sauni pishonwe wall
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\hill_1.bmp",12);//hill-1
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\hill_2.bmp",13);//hill-2
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\brick_titles_2.bmp",14);//hill-2
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\wall5.bmp",15);//buiding ar wall
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\wall2.bmp",16);//buiding ar wall
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\window3.bmp",17);//window
    // LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\capture.jpeg",18);//name
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\sky3.bmp",18);//day
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\nightSky6.bmp",19);//night
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\moon_1.bmp",20);//moon
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\sun3.bmp",21);//sun
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\wall2.bmp",22);//wall
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\road_horizontal.bmp",23);//road_horizontal
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\tree_leaf_2.bmp",24);//road_horizontal
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\wall1.bmp",25);//road_horizontal
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\floor7.bmp",26);//road_horizontal
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\wall4.bmp",27);//road_horizontal
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\d_n6.bmp",28);//day/night
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\shirt_cloth_1.bmp",29);//day/night
    LoadTexture("C:\\Users\\User\\Desktop\\Graphics Project\\1707015_Project\\images\\shirt_cloth_2.bmp",30);//day/night



}
int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutGet(GLUT_SCREEN_WIDTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Railway Station");
    glutReshapeFunc(changeSize);


    load_textures();

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_LIGHTING);
    //light(GL_LIGHT2,5,10,7);
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutMouseFunc(processMouse);
    glutIdleFunc(animate);

    printf("########################################################################################\n");
    printf("########################################################################################\n");
    printf("##############                                                         #################\n");
    printf("##############           PLEASE FOLLOW THE BELOW INSTRUCTIONS          #################\n");
    printf("##############                                                         #################\n");
    printf("########################################################################################\n");
    printf("########################################################################################\n\n\n");
    printf("Use 'r' to roll,\n 'p' to pitch,\n 'y' to yaw,\n and Opposite case the vice versa.\n\n");
    printf("Use 'a' to zoom in(z-axis),\n 'b' to zoom in(near plane),\n 'c' to zoom in(Scaling).\n\n");
    printf("Use 'f' to toggle the fan on-off.\n\n");
    printf("Use '1' to toggle sun light,\n '2' to toggle the spot lamp switch,\n and '3' to toggle moon light.\n\n");
    printf("Use 'u' to toggle ambient,\n 'v' to toggle diffusion,\n and 'w' to toggle specular light property.\n\n\n\n");
    printf("Use 'i' to move camera front (i.e. zoom in),\n 'k' to move camera back (i.e. zoom out),\n 'l' to move camera right,\n 'j' to move camera left,\n 't' to move camera top,\n and 'g' to move camera down.\n \n");
    printf("Use '5' to toggle windows.\n\n");
    printf("Use '7' to toggle front train,\n '8' to toggle the back train,\n and '9' to reset trains.\n\n");
    printf("Use 'd' to toggle between day and night.\n\n");
    glutMainLoop();

    return 0;
}
