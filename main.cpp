#include<cstdio>
#include<iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include<time.h>
#include <vector>
#include <cstring>
#include <Windows.h>
#include <MMSystem.h>

using namespace std;

float position[100]={0.025f},positiony[100]={.875f},speed = 0.05f;
bool ap=false,sp=false,wp=false,dp=false,qp=false,gm;
bool mainscr=true,lvl2=false,lvl1=false,lvl3=false,lvl4=false;
int fps=120;
float thick= 0.05f;
bool cnt=false;bool xf=false;
int score=0;
bool changeColorCLick=false,changeColorbody=false;
int colorPick=0;
bool scrDone=true,pause=false;

int rvalueb=0,gvalueb=0,bvalueb=255;
int rvalueh=255,gvalueh=0,bvalueh=0;

void init() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

///text display
const int font1=(int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2=(int)GLUT_BITMAP_HELVETICA_18 ;
const int font3=(int)GLUT_BITMAP_8_BY_13;

void renderBitmapString(float x, float y, void *font,const char *string)
{
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void output(float x, float y,int flag, string s)
{

  glBegin(GL_QUADS);
   if(flag==1){
  glColor3ub(0, 0, 0);
  glVertex2f(x-.01f,y+.04f);
  glVertex2f(x-.01f,y+.04f-.05f);
  glVertex2f(x-.01f+.4f,y+.04f-.05f);
  glVertex2f(x-.01f+.4f,y+.04f);
   }
   else if(flag==2){
  if(s.compare("RED")==0) glColor3ub(255, 0, 0);
  else if(s.compare("GREEN")==0) glColor3ub(0,255, 0);
  else if(s.compare("BLUE")==0) glColor3ub(0, 0, 255);
  else if(s.compare("YELLOW")==0) glColor3ub(255, 255, 0);
  else if(s.compare("VIOLET")==0) glColor3ub(144, 0, 255);
  else if(s.compare("PINK")==0) glColor3ub(255,0,255);
  glVertex2f(x+.13,y+.04f);
  glVertex2f(x+.13,y+.04f-.05f);
  glVertex2f(x+.13+.1f,y+.04f-.05f);
  glVertex2f(x+.13+.1f,y+.04f);
   }

  glEnd();

  glColor3ub(255, 255, 255);
  glRasterPos2f(x, y);
  int len, i;
  len = s.length();
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
  }

}
int windowWidth,windowHeight;
void handleMouse(int button, int state, int x, int y) {
     windowWidth  = glutGet(GLUT_WINDOW_WIDTH)/2;
     windowHeight = glutGet(GLUT_WINDOW_HEIGHT)/2;
     //cout << windowHeight << windowWidth << endl;
    // cout << .60*windowWidth+windowWidth << (.11*windowHeight+windowHeight);
	if (button == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN){
		   // if(x>=300&&x<=450&&y>=225&&y<=255){
            if(x>=(.8*windowWidth)&&x<=(.2*windowWidth+windowWidth)&&y>=(.6*windowHeight)&&y<=(.68*windowHeight)){
                lvl1=true;mainscr=false;lvl2=false;lvl3=false;lvl4=false;
            }
			//else if(x>=300&&x<=450&&y>=270&&y<=300){
            else if(x>=(.8*windowWidth)&&x<=(.2*windowWidth+windowWidth)&&y>=(.72*windowHeight)&&y<=(.8*windowHeight)){
                lvl2=true;mainscr=false;lvl1=false;lvl3=false;lvl4=false;
            }
            else if(x>=(.8*windowWidth)&&x<=(.2*windowWidth+windowWidth)&&y>=(.84*windowHeight)&&y<=(.92*windowHeight)){
                lvl3=true;mainscr=false;lvl2=false;lvl1=false;lvl4=false;
            }
             else if(x>=(.8*windowWidth)&&x<=(.2*windowWidth+windowWidth)&&y>=(.96*windowHeight)&&y<=(.04*windowHeight+windowHeight)){
                lvl4=true;mainscr=false;lvl2=false;lvl3=false;lvl1=false;
            }
            //snake color change
            else if(x>=(.60*windowWidth+windowWidth)&&x<=(windowWidth*2)&&y<=(.11*windowHeight+windowHeight)&&y>=(.06*windowHeight+windowHeight)){
                changeColorCLick=!changeColorCLick;
            }
            //red
            else if(x>=(.88*windowWidth+windowWidth)&&x<=(.98*windowWidth+windowWidth)&&y>=(.16*windowHeight+windowHeight)&&y<=(.21*windowHeight+windowHeight)){
                rvalueh = 255; gvalueh = 0; bvalueh =0;
            }
            //green
            else if(x>=(.88*windowWidth+windowWidth)&&x<=(.98*windowWidth+windowWidth)&&y>=(.23*windowHeight+windowHeight)&&y<=(.28*windowHeight+windowHeight)){
                rvalueh = 0; gvalueh = 255; bvalueh =0;
            }
            //blue
            else if(x>=(.88*windowWidth+windowWidth)&&x<=(.98*windowWidth+windowWidth)&&y>=(.3*windowHeight+windowHeight)&&y<=(.35*windowHeight+windowHeight)){
                rvalueh = 0; gvalueh = 0; bvalueh =255;
            }
            else if(x>=(.88*windowWidth+windowWidth)&&x<=(.98*windowWidth+windowWidth)&&y>=(.4*windowHeight+windowHeight)&&y<=(.45*windowHeight+windowHeight)){
               rvalueb=255; gvalueb=255;bvalueb=0;
            }
            else if(x>=(.88*windowWidth+windowWidth)&&x<=(.98*windowWidth+windowWidth)&&y>=(.47*windowHeight+windowHeight)&&y<=(.52*windowHeight+windowHeight)){
               rvalueb=144; gvalueb=0;bvalueb=255;
            }
            else if(x>=(.88*windowWidth+windowWidth)&&x<=(.98*windowWidth+windowWidth)&&y>=(.54*windowHeight+windowHeight)&&y<=(.59*windowHeight+windowHeight)){
                rvalueb=255; gvalueb=0;bvalueb=255;
            }
			///printf("clicked at (%d, %d)\n", x, y);
		}
	}	glutPostRedisplay();
}

void wall1(){
glColor3f(1.0f, 0.5f, 0.5f);
glBegin(GL_POLYGON);
glVertex2f(-.95,-.95);
glVertex2f(0.59,-.95);
glVertex2f(0.59,.95);
glVertex2f(-.95,.95);
glEnd();
glColor3f(.5f, .5f, 1.0f);
glBegin(GL_POLYGON);
glVertex2f(-.95+thick,-.95+thick);
glVertex2f(0.55,-.95+thick);
glVertex2f(0.55,.95-thick);
glVertex2f(-.95+thick,.95-thick);
glEnd();
}

void wall2(){
     //glColor3f(1.0f, 0.0f, 0.0f);
  glColor3ub(46,45,42);
  glVertex2f( 0.59f, 1.0f);
  glVertex2f( 0.59f, -1.0f);
  glVertex2f( 0.55f, 1.0f);
  glVertex2f( 0.55f, -1.0f);

  glVertex2f( -1.0f+thick, 1.0f);
  glVertex2f( -1.0f+thick, -1.0f);

  glVertex2f( -1.0f, 1.0f-thick);
  glVertex2f( .59f, 1.0f-thick);

  glVertex2f( -1.0f, -1.0f+thick);
  glVertex2f( .59f, -1.0f+thick);

 float xwall=-1.0f;
 while(xwall<0.6f-thick){
        //main wall
        glVertex2f( xwall,-1.0f);
        glVertex2f( xwall ,-1.0f+thick);

        glVertex2f( xwall, 1.0f);
        glVertex2f( xwall ,1.0f-thick);

      //+, horizontal
       if(xwall<.6f-thick*2){
      glVertex2f( xwall, 0.0f);
      glVertex2f( xwall ,0.0f+thick);}

      xwall+=.05f;
 }

 //+, horizontal
      glVertex2f( .5f, 0.0f);
      glVertex2f( .5f ,0.0f+thick);

       glVertex2f( -.9f, 0.0f);
       glVertex2f( .5f, 0.0f);

        glVertex2f( -.9f, .0f+thick);
        glVertex2f( .5f, 0.0f+thick);

float ywall=-1.0f;
//+, vertical
glVertex2f( -.2f, -.9f);
glVertex2f( -.2f, .9f);

glVertex2f( -.2f+thick, -.9f);
glVertex2f( -.2f+thick, .9f);

glVertex2f( -.2f, .9f);
glVertex2f( -.2f+thick, .9f);

 while(ywall<1.0f-thick){
        //main wall
        glVertex2f( -1.0f, ywall);
        glVertex2f( -1.0f+thick, ywall);

        glVertex2f( .55f, ywall);
        glVertex2f( .59f, ywall);

        //+, vertical
        if(ywall<1.0f-thick*2){
        glVertex2f( -.2f, ywall);
        glVertex2f( -.2f+thick, ywall);}
        ywall+=.05f;
 }
}

void snake2(){
    glPointSize(18.0f);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_POINTS);
   //body
   for(int i=1;i<=score;i++){

     glColor3ub(rvalueb, gvalueb, bvalueb);
     glVertex2f(position[i],positiony[i]);
   }
   //head
        glColor3ub(rvalueh, gvalueh, bvalueh);

   glVertex2f(position[0],positiony[0]);
    glEnd();

}

float ix,iy;
bool fd=true;

void foodGenarate(){
    srand(time(NULL));
    float randomx;
    int xmax,ymax;
    if(lvl1) {
        randomx=-0.925f+thick; xmax=29; ymax=36;
    }
    else if(lvl2||lvl3||lvl4) {
        randomx=-0.925f; xmax=30; ymax=38;
    }
    ix=randomx+(((rand()%xmax))*0.05); // generating random x-axis value
    iy=randomx+(((rand()%ymax))*0.05);
   /// cout << "random x " << ix << "\n";
   /// cout << "random y " << iy << "\n";

    if(ix>-.2f&&ix<-.2f+thick&&iy<.9f&&iy>-.9f){
                //foodGenarate(); recursive call slow the food appearance
                ix+=.05f;
        }
    //Horizontal mid wall crash check
    if(ix>-.9f&&ix<.5f&&iy>.0f&&iy<.0f+thick){
               // foodGenarate();
               iy+=.05f;
        }
        //if food overlap snake
    if(ix==position[0]&&iy==positiony[0]){
    foodGenarate();
    }
    fd=false;
}

void food(){
        glPointSize(18.0f); // we could use circle for responsive food and snake
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if(fd) foodGenarate();

        glBegin(GL_POINTS);
        if(lvl1) glColor3ub(166, 107, 12);
        if(lvl2) glColor3ub(199, 138, 6);
        glVertex2f(ix,iy);
         glEnd();

}



void adcheck(){

    if(lvl1){
        if((position[0])>.526f) {
            position[0]=.526f;
            dp=false;gm=true;

    }
    else if((position[0])<-.926f+thick){
            position[0]=-.925f+thick;
            ap=false;gm=true;
        }
    }

    else if(lvl2){
        if((position[0])>.526f) {
        //cout << position << "  " << positiony << endl;
        position[0]=.525f;
        dp=false;gm=true;
    }
    else if((position[0])<-.926f){
        //cout << position << "  " << positiony << endl;
        position[0]=-.925f;
        ap=false;gm=true;
        }
    }
    else if(lvl3){
        if((position[0])>.526f) {
            position[0]=.526f;
            dp=false;gm=true;

    }
    else if((position[0])<-.926f+thick){
            position[0]=-.925f+thick;
            ap=false;gm=true;

        }
    }
    else if(lvl4){
     if((position[0])>.526f) {
            position[0]=.526f;
            dp=false;gm=true;

    }
    else if((position[0])<-.926f+thick){
            position[0]=-.925f+thick;
            ap=false;gm=true;

        }
    }

}
void swCheck(){

    if(lvl1){
          if((positiony[0])<-.926f+thick){
                      positiony[0]=-.925f;
                    sp=false;gm=true;
                  //  cout << positiony ;
                }
            else if((positiony[0])>.926f-thick){
                    positiony[0]=.925f;
                    wp=false;gm=true;
                  //  cout << positiony ;
                    }
    }
   else if(lvl2){
         if((positiony[0])<-.926f){
               // cout << position << "  " << positiony << endl;
                positiony[0]=-.925f;
                sp=false;gm=true;
            }
        else if((positiony[0])>.926f){
              //  cout << position << "  " << positiony << endl;
                positiony[0]=.925f;
                wp=false;gm=true;
                }
    }
    else if(lvl3){
         if((positiony[0])<-.93f+thick){
                  positiony[0]=-.93f+thick;
                sp=false;gm=true;
                //cout << positiony ;
            }
        else if((positiony[0])>.93f-thick){
                positiony[0]=.93f-thick;
                wp=false;gm=true;
               // cout << positiony ;
                }
    }
    else if(lvl4){
          if((positiony[0])<-.93f+thick){
                  positiony[0]=-.93f+thick;
                sp=false;gm=true;
               // cout << positiony ;
            }
        else if((positiony[0])>.93f-thick){
                positiony[0]=.93f-thick;
                wp=false;gm=true;
               // cout << positiony ;
                }

    }
}

void reset(){
     //reset position
      if(lvl1){
        if(qp){
            qp=false;gm=false;cnt=true;score=0;
            position[0] = 0.025f;
            positiony[0] =.675f;
            cout << position[0] << " r " << positiony[0] << endl;
        }
      }
     if(lvl2){
        if(qp){
            qp=false;gm=false;cnt=true;score=0;
            position[0] = 0.025f;
            positiony[0] =.925f;
            cout << position[0] << " r " << positiony[0] << endl;
        }
     }
}

void midWallCheck(){
        if(lvl2){
        //vertical mid wall crash check
        if(position[0]>-.2f&&position[0]<-.2f+thick&&positiony[0]<.9f&&positiony[0]>-.9f){
                        gm=true;//cnt=false;
                }
        //Horizontal mid wall crash check
        if(position[0]>-.9f&&position[0]<.5f&&positiony[0]>.0f&&positiony[0]<.0f+thick){
                        gm=true;//cnt=false;
                }
        }
}

void foodEatCheck(){
        //check if food is eaten
        if((ix>=position[0]&&ix<=position[0]+0.04)&&(iy>=positiony[0]&&iy<=positiony[0]+0.04)){
            score++;
            fd=true;
        }
       else if((ix<=position[0]&&ix>=position[0]-0.04)&&(iy<=positiony[0]&&iy>=positiony[0]-0.04)){
            score++;
            fd=true;
        }
         else if((ix>=position[0]&&ix<=position[0]+0.04)&&(iy<=positiony[0]&&iy>=positiony[0]-0.04)){
            score++;
            fd=true;
        }
         else if((ix<=position[0]&&ix>=position[0]-0.04)&&(iy>=positiony[0]&&iy<=positiony[0]+0.04)){
            score++;
            fd=true;
        }
}

void selfCollide(){

    for(int i=1;i<=score;i++){
        if((position[i]==position[0])&&(positiony[i]==positiony[0])){
           gm=true; cnt=true;
        }
       else if((position[i]==position[0])&&(positiony[i]==positiony[0])){
           gm=true; cnt=true;
        }
         else if((position[i]==position[0])&&(positiony[i]==positiony[0])){
           gm=true; cnt=true;
        }
         else if((position[i]==position[0])&&(positiony[i]==positiony[0])){
           gm=true; cnt=true;
        }
    }

}

void update(int value) {


    if(!pause){
        reset();

        if(!gm){
            foodEatCheck();
            selfCollide();
            //body
            for(int i=score;i>0;i--){
            position[i]=position[i-1];
            positiony[i]=positiony[i-1];
            }

            // X-axis
            // right
            if(dp){ cnt=true; position[0]+=speed; }
            //left
            if(ap){ cnt=true; position[0]-=speed; }
            //left-right wall collide check
            adcheck();

            // Y-axis
            //down
            if(sp){ cnt=true;positiony[0]-=speed; }
            //up
            if(wp){ cnt=true; positiony[0]+=speed; }
            //up-down wall collide check
            swCheck();
            }
    midWallCheck();

    if(cnt==true&&gm==false) glutPostRedisplay();

    if(gm&&cnt){ cnt=false;
                cout <<"game over your score is " << score << endl;
                sndPlaySound("C:\\Users\\pc\\Desktop\\CG\\snakebody\\evil.wav",SND_ASYNC|SND_FILENAME);
        }
}
    glutTimerFunc(150, update, 0);
}

void handleKeypress(unsigned char key, int x, int y) {

	switch (key) {
        case 'a': ///left
            if(gm==false&&dp==false){
            gm=false;cout << position[0] << " " << gm << endl;
            ap=true; wp=false; sp=false; dp=false; qp=false;
            }
            break;
        case 'd': ///right
            if(gm==false&&ap==false){
            gm=false;
            cout << position[0] << " " << gm << endl;
            dp=true; wp=false; sp=false; ap=false; qp=false;
            }
            break;

        case 'w': ///up
            if(gm==false&&sp==false){
            gm=false;
            wp=true; ap=false; sp=false; dp=false; qp=false;
            }
            break;

        case 's': ///down
            if(gm==false&&wp==false){
            gm=false;
            sp=true; wp=false; ap=false; dp=false; qp=false;
            } break;

        case 'r': ///restart
            gm=false; fd=true;
            sp=false; wp=false; ap=false; dp=false; qp=true;
            break;

        case 'm': ///main menu
            mainscr=true; lvl2=false;lvl1=false;
            gm=false; fd=true;
            sp=false; wp=false; ap=false; dp=false; qp=true;
            break;
        case 'p': ///pause
            pause=true;
            break;
        case 'o': ///resume
            pause=false;
            break;

    //if(cnt==true)
        glutPostRedisplay();
       }
}

void colorChange(){

    output(0.61f,-0.1f,1,"SNAKE COLOR CHANGE");
    if(changeColorCLick){
         output(0.65f,-0.15f,1,"HEAD");
         output(0.75f,-0.2f,2,"RED");
         output(0.75f,-0.27f,2,"GREEN");
         output(0.75f,-0.34f,2,"BLUE");

         output(0.65f,-0.39f,1,"BODY");
         output(0.75f,-0.44f,2,"YELLOW");
         output(0.75f,-0.51f,2,"VIOLET");
         output(0.75f,-0.58f,2,"PINK");
    }
    output(.65f,.5f,1,"Press r for");
    output(.65f,.45f,1,"restart");
    output(.65f,.35f,1,"Press m for");
    output(.65f,.3f,1,"Main Menu");
    output(.65f,.2f,1,"Press p for");
    output(.65f,.15f,1,"Pause");
    output(.65f,.05f,1,"Press o for");
    output(.65f,.0f,1,"Resume");

}

void scoreboard(){
    ///score board
    glColor3ub(0, 255, 0);
    renderBitmapString(0.65f,0.85f,(void *)font1,"Scoreboard");

    ///score
    char buffer [50];
    sprintf (buffer, "SCORE: %d", score);
    glColor3ub(255, 255, 255);
    renderBitmapString(0.65f,0.68f,(void *)font3,buffer);

}

void level1(){

    glPushMatrix();

glPushMatrix();
  glBegin(GL_LINES);

/*divider between score and level*/
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex2f( 0.6f, 1.0f);
  glVertex2f( 0.6f, -1.0f);
  glEnd();
glPopMatrix();
glPushMatrix();
  wall1();
glPopMatrix();
glPushMatrix();
  glEnd();
  glPopMatrix();
  //food
  glPushMatrix();
food();
glPopMatrix();
glPushMatrix();
  snake2();
glPopMatrix();
glPushMatrix();
  colorChange();
glPopMatrix();

glPopMatrix();

    //level
    glColor3ub(255, 255, 255);
    renderBitmapString(0.65f,0.75f,(void *)font3,"Level: 1");
    scoreboard();


}

void level2(){
    glPushMatrix();
glBegin(GL_QUADS);
glColor3ub(128,184,103);
glVertex2f(.6f,-1.0f);
glVertex2f(.6f,1.0f);
glVertex2f(-1.0f,1.0f);
glVertex2f(-1.0f,-1.0f);
glEnd();

glBegin(GL_QUADS);

glColor3ub(138,134,125);
glVertex2f(-1.0f,1.0-thick);
glVertex2f(.6f,1.0-thick);
glVertex2f(.6f,1.0);
glVertex2f(-1.0f,1.0);

glVertex2f(-1.0f,-1.0);
glVertex2f(.6f,-1.0);
glVertex2f(.6f,-1.0+thick);
glVertex2f(-1.0f,-1.0+thick);

glVertex2f(-1.0f,-1.0);
glVertex2f(-1.0f+thick,-1.0);
glVertex2f(-1.0f+thick,1.0);
glVertex2f(-1.0f,1.0);

glVertex2f(.6f,-1.0);
glVertex2f(.6f,1.0);
glVertex2f(.6f-thick,1.0);
glVertex2f(.6f-thick,-1.0);

glVertex2f(-.2f,-1.0+thick*2);
glVertex2f(-.2f+thick,-1.0+thick*2);
glVertex2f(-.2f+thick,1.0-thick*2);
glVertex2f(-.2f,1.0-thick*2);

glVertex2f(-1.0+thick*2,0.0f);
glVertex2f(.6-thick*2,0.0f);
glVertex2f(.6-thick*2,0.0f+thick);
glVertex2f(-1.0+thick*2,0.0f+thick);




glEnd();

glPushMatrix();
  glBegin(GL_LINES);//divider between score and level
  glColor3f(1.0f, 0.0f, 0.0f);// glColor3f(.75f, 1.0f, 0.0f);
  glVertex2f( 0.6f, 1.0f);
  glVertex2f( 0.6f, -1.0f);
glPopMatrix();

//wall
glPushMatrix();
  wall2();
glPopMatrix();
glEnd();




//food
glPushMatrix();
food();
glPopMatrix();
//snake
glPushMatrix();
  snake2();
glPopMatrix();

//color change
glPushMatrix();
  colorChange();
glPopMatrix();

glPopMatrix();


    //level
    glColor3ub(255, 255, 255);
    renderBitmapString(0.65f,0.75f,(void *)font3,"Level: 2");
    scoreboard();


}

void wall4()
{
glClear (GL_COLOR_BUFFER_BIT);

glColor3f (1.0, 1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(-.95,-.95);
glVertex2f(.59,-.95);
glVertex2f(.59,.95);
glVertex2f(-.95,.95);
glEnd();
glColor3f (1.0, 0.5,0.5);
glBegin(GL_POLYGON);
glVertex2f(-.95+thick,-.95+thick);
glVertex2f(.59-thick,-.95+thick);
glVertex2f(.59-thick,.95-thick);
glVertex2f(-.95+thick,.95-thick);
glEnd();
glColor3f (1.0, 1.0,0.5);
glBegin(GL_POLYGON);
glVertex2f(-.95+2*thick,.95-2*thick);
glVertex2f(.59-2*thick,.95-2*thick);
glVertex2f(.59-2*thick,.95-3*thick);
glVertex2f(-.95+2*thick,.95-3*thick);
glEnd();
glColor3f (1.0, 1.0,0.5);
glBegin(GL_POLYGON);
glVertex2f(-.95+2*thick,-.95+2*thick);
glVertex2f(.59-2*thick,-.95+2*thick);
glVertex2f(.59-2*thick,-.95+3*thick);
glVertex2f(-.95+2*thick,-.95+3*thick);
glEnd();
glColor3f (1.0, 1.0,0.5);
glBegin(GL_POLYGON);
glVertex2f(-.95+15*thick,-.95+4*thick);
glVertex2f(-.95+14*thick,-.95+4*thick);
glVertex2f(-.95+14*thick,.95-4*thick);
glVertex2f(-.95+15*thick,.95-4*thick);
glEnd();
//food
glPushMatrix();
food();
glPopMatrix();
//snake
glPushMatrix();
  snake2();
glPopMatrix();

//color change
glPushMatrix();
  colorChange();
glPopMatrix();
  glColor3ub(255, 255, 255);
    renderBitmapString(0.65f,0.75f,(void *)font3,"Level: 3");
    scoreboard();
glFlush ();
}
void wall5()
{
glClear (GL_COLOR_BUFFER_BIT);
glColor3f (1.0, 0.5,1.0);
glBegin(GL_POLYGON);
glVertex2f(-.95,-.95);
glVertex2f(.59,-.95);
glVertex2f(.59,.95);
glVertex2f(-.95,.95);
glEnd();
glColor3f (1.0, .5,0.5);
glBegin(GL_POLYGON);
glVertex2f(-.95+thick,-.95+thick);
glVertex2f(.59-thick,-.95+thick);
glVertex2f(.59-thick,.95-thick);
glVertex2f(-.95+thick,.95-thick);
glEnd();
glColor3f (0.5, 0.0,0.5);
glBegin(GL_POLYGON);
glVertex2f(-.95+2*thick,.95-2*thick);
glVertex2f(.59-2*thick,.95-2*thick);
glVertex2f(.59-2*thick,.95-3*thick);
glVertex2f(-.95+2*thick,.95-3*thick);
glEnd();
glColor3f (0.5, 0.0,0.5);
glBegin(GL_POLYGON);
glVertex2f(-.95+2*thick,-.95+2*thick);
glVertex2f(.59-2*thick,-.95+2*thick);
glVertex2f(.59-2*thick,-.95+3*thick);
glVertex2f(-.95+2*thick,-.95+3*thick);
glEnd();
glColor3f (0.5, 0.0,0.5);
glBegin(GL_POLYGON);
glVertex2f(-.95+15*thick,-.95+4*thick);
glVertex2f(-.95+14*thick,-.95+4*thick);
glVertex2f(-.95+14*thick,.95-4*thick);
glVertex2f(-.95+15*thick,.95-4*thick);
glEnd();
glColor3f (0.5, 0.0,0.5);
glBegin(GL_POLYGON);
glVertex2f(-.95+2*thick,-.95+19*thick);
glVertex2f(-.95+13*thick,-.95+19*thick);
glVertex2f(-.95+13*thick,.95-18*thick);
glVertex2f(-.95+2*thick,.95-18*thick);
glEnd();
glColor3f (0.5, 0.0,0.5);
glBegin(GL_POLYGON);
glVertex2f(-.95+16*thick,-.95+19*thick);
glVertex2f(.59-2*thick,-.95+19*thick);
glVertex2f(.59-2*thick,.95-18*thick);
glVertex2f(-.95+16*thick,.95-18*thick);
glEnd();
//food
glPushMatrix();
food();
glPopMatrix();
//snake
glPushMatrix();
  snake2();
glPopMatrix();

//color change
glPushMatrix();
  colorChange();
glPopMatrix();
  glColor3ub(255, 255, 255);
    renderBitmapString(0.65f,0.75f,(void *)font3,"Level: 4");
    scoreboard();
glFlush ();
}

void mainScreenDraw(){

glColor3ub(179, 0, 0);
renderBitmapString(-0.08f,0.7f,(void *)font1,"Snake");

glColor3ub(0, 179, 0);
renderBitmapString(-0.3f,0.5f,(void *)font1,"Click on levels to START");

//renderBitmapString(38,72,(void *)font1,"Press ESC to Exit");

glColor3f(1.0f, 1.0f, 1.0f);
glBegin(GL_POLYGON);//level 1
glVertex2f(-0.2f,0.32f);
glVertex2f(0.2f,0.32f);
glVertex2f(0.2f,0.4f);
glVertex2f(-0.2f,0.4f);
glEnd();
glBegin(GL_POLYGON);//level 2
glVertex2f(-0.2f,0.2f);
glVertex2f(0.2f,0.2f);
glVertex2f(0.2f,0.28f);
glVertex2f(-0.2f,0.28f);
glEnd();
glBegin(GL_QUADS);//level 3
glVertex2f(-0.2f,0.08f);
glVertex2f(0.2f,0.08f);
glVertex2f(0.2f,0.16f);
glVertex2f(-0.2f,0.16f);

glVertex2f(-0.2f,-0.04f);//lvl 4
glVertex2f(0.2f,-0.04f);
glVertex2f(0.2f,0.04f);
glVertex2f(-0.2f,0.04f);
glEnd();

glColor3ub(0, 0, 255);
renderBitmapString(-0.07f,0.35f,(void *)font3,"Level 1");
renderBitmapString(-0.07f,0.23f,(void *)font3,"Level 2");
renderBitmapString(-0.07f,0.11f,(void *)font3,"Level 3");
renderBitmapString(-0.07f,-0.01f,(void *)font3,"Level 4");
}

void mainScreen(){
    mainScreenDraw();
}

void display() {

   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   if(mainscr) mainScreen();
   else if(lvl2) level2();
   else if(lvl1) level1();
   else if(lvl3) wall4();
   else if(lvl4) wall5();
   glutSwapBuffers();
}

// 750*750 is the level size extra 150 is for score board and others

int main(int argc, char** argv) {

    cout << "up-->w\ndown-->s\nleft-->a\nright-->d\nclick on \"snake color change\" for changing snake color.\n";
   cout << "\n\n\nOnly level 2 is fully completed.You may have some difficulties with other levels.\n\n";
   glutInit(&argc, argv);

   glutInitWindowSize(750, 750);
   glutInitWindowPosition(50, 50);
   glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
   glutCreateWindow("Classic Snake");
   glutDisplayFunc(display);
   init();
   glutKeyboardFunc(handleKeypress);
   glutMouseFunc(handleMouse);
   glutTimerFunc(1000, update, 0);
   //sndPlaySound("C:\\Users\\pc\\Desktop\\CG\\snakebody\\evil.wav",SND_ASYNC|SND_FILENAME);
   glutMainLoop();

   return 0;
}
