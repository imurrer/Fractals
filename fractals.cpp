// fractals.cpp
// Isobel Murrer
// 12/3/18
// Draw fractal puzzles

#include <iostream>
#include "gfx.h"
#include <cmath>
#include <math.h>
using namespace std;

// function prototypes
void sierpinski(float x1, float y1, float x2, float y2, float x3, float y3);
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void squareShrink(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void drawSquare(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void circLace(float xc, float yc, float rad);
void drawCircle(float xc, float yc, float rad);
void snowflake(float rad, float xc, float yc, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5);
void drawLine(float xc, float yc, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5);
void fern(float stalk, float angle, float x1, float y1);
void drawLine2(float x1, float y1, float x2, float y2);
void spiralSquare(float rad, float angle, float x1, float y1);
void drawSquare2(float rad, float x1, float y1);
void tree(float rad, float angle, float x1, float y1);
void spirals(float rad, float angle, float x1, float y1);

int main() {
  bool loop = true;
	float width = 700, height = 700, mrgn = 20, lineRad = width/3, noMarg = height-mrgn, stalk = noMarg*4/7, side = stalk/3, fernAng = M_PI/6;
  gfx_open(width, height, "Fractal 'Fun'");
  while (loop) {
    char c = gfx_wait();
    gfx_clear();
    switch (c) {
      case '1': // Sierpinski Triangle  
				sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
        break;
      case '2': // Shrinking Squares  
				squareShrink(width/4, height/4, width-(width/4), height/4, width-(width/4), height-(height/4), width/4, height-(height/4));
        break;
  		case '3':	//Spiral Squares
				spiralSquare(1, M_PI/2, width/2, height/2);
				break;
			case '4':	//Circular Lace
				circLace(width/2, height/2, 2*(width/6));
				break;
			case '5':	//Snowflake
				snowflake(lineRad, width/2, height/2, width/2, lineRad+height/2, (width/2)+lineRad*sin(2*M_PI/5), (height/2)+lineRad*cos(2*M_PI/5), (width/2)+lineRad*sin(4*M_PI/5), (height/2)+lineRad*cos(4*M_PI/5), (width/2)+lineRad*sin(6*M_PI/5), (height/2)+lineRad*cos(6*M_PI/5), (width/2)+lineRad*sin(8*M_PI/5), (height/2)+lineRad*cos(8*M_PI/5));
				break;
			case '6':	//Tree
				tree(7*(height-2*mrgn)/20, M_PI/2, width/2, height-mrgn);
				break;
			case '7':	//Fern
				fern(stalk, M_PI/2, width/2, noMarg);
				break;
      case '8': // Spiral of Spirals 
				spirals(450, M_PI/2, width/2, height/2);
        break;
      case 'q':
        loop = false;
      default:
        break;
  	}
  }

  return 0;
}

void sierpinski(float x1, float y1, float x2, float y2, float x3, float y3){
	//Base case
	if(abs(x2-x1) < 5) return;
	//Draw Triangle
	drawTriangle(x1, y1, x2, y2, x3, y3);
	//Recursive calls
	sierpinski(x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2);
	sierpinski((x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2);
	sierpinski((x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3);
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3){
	gfx_line(x1, y1, x2, y2);
	gfx_line(x2, y2, x3, y3);
	gfx_line(x3, y3, x1, y1);
}

void squareShrink(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
	//Base case
	if(abs(x2-x1) < 2.5) return;

	//Draw Square
	drawSquare(x1, y1, x2, y2, x3, y3, x4, y4);

	//Recursive calls
	squareShrink(x1-(x2-x1)/4.5, y1-(y4-y1)/4.5, x1+(x2-x1)/4.5, y1-(y4-y1)/4.5, x1+(x2-x1)/4.5, y1+(y4-y1)/4.5, x1-(x2-x1)/4.5, y1+(y4-y1)/4.5);
	squareShrink(x2-(x2-x1)/4.5, y2-(y3-y1)/4.5, x2+(x2-x1)/4.5, y2-(y3-y1)/4.5, x2+(x2-x1)/4.5, y2+(y3-y1)/4.5, x2-(x2-x1)/4.5, y2+(y3-y1)/4.5);
	squareShrink(x3-(x3-x4)/4.5, y3-(y3-y2)/4.5, x3+(x3-x4)/4.5, y3-(y3-y2)/4.5, x3+(x3-x4)/4.5, y3+(y3-y2)/4.5, x3-(x3-x4)/4.5, y3+(y3-y2)/4.5);
	squareShrink(x4-(x3-x4)/4.5, y4-(y4-y1)/4.5, x4+(x3-x4)/4.5, y4-(y4-y1)/4.5, x4+(x3-x4)/4.5, y4+(y4-y1)/4.5, x4-(x3-x4)/4.5, y4+(y4-y1)/4.5);
}

void drawSquare(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
	gfx_line(x1, y1, x2, y2);
	gfx_line(x2, y2, x3, y3);
	gfx_line(x3, y3, x4, y4);
	gfx_line(x4, y4, x1, y1);
}

void circLace(float xc, float yc, float rad){
	//Base case
	if(rad < 1) return;	//not enough small circles?

	//Draw Circle
	drawCircle(xc, yc, rad);

	//Recursive calls
	circLace(xc+rad*cos(M_PI/3), yc-rad*sin(M_PI/3), rad/3);
	circLace(xc+rad*cos(2*M_PI/3), yc-rad*sin(2*M_PI/3), rad/3);
	circLace(xc+rad*cos(M_PI), yc-rad*sin(M_PI), rad/3);
	circLace(xc+rad*cos(4*M_PI/3), yc-rad*sin(4*M_PI/3), rad/3);
	circLace(xc+rad*cos(5*M_PI/3), yc-rad*sin(5*M_PI/3), rad/3);
	circLace(xc+rad*cos(2*M_PI), yc-rad*sin(2*M_PI), rad/3);
}

void drawCircle(float xc, float yc, float rad){
	gfx_circle(xc, yc, rad);
}

void snowflake(float rad, float xc, float yc, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5){	
	//Base case
	if(rad < .5) return;	//not enough small lines?

	//Draw Line
	drawLine(xc, yc, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);
	//Recursive calls
	snowflake(rad/3, x1, y1, x1, rad/3+y1, x1+rad/3*sin(2*M_PI/5), y1+rad/3*cos(2*M_PI/5), x1+rad/3*sin(4*M_PI/5), y1+rad/3*cos(4*M_PI/5), x1+rad/3*sin(6*M_PI/5), y1+rad/3*cos(6*M_PI/5), x1+rad/3*sin(8*M_PI/5), y1+rad/3*cos(8*M_PI/5));
	snowflake(rad/3, x2, y2, x2+rad/3*sin(2*M_PI/5), y2+rad/3*cos(2*M_PI/5), x2+rad/3*sin(4*M_PI/5), y2+rad/3*cos(4*M_PI/5), x2+rad/3*sin(6*M_PI/5), y2+rad/3*cos(6*M_PI/5), x2+rad/3*sin(8*M_PI/5), y2+rad/3*cos(8*M_PI/5), x2+rad/3*sin(2*M_PI), y2+rad/3*cos(2*M_PI));
	snowflake(rad/3, x3, y3, x3+rad/3*sin(2*M_PI/5), y3+rad/3*cos(2*M_PI/5), x3+rad/3*sin(4*M_PI/5), y3+rad/3*cos(4*M_PI/5), x3+rad/3*sin(6*M_PI/5), y3+rad/3*cos(6*M_PI/5), x3+rad/3*sin(8*M_PI/5), y3+rad/3*cos(8*M_PI/5), x3+rad/3*sin(2*M_PI), y3+rad/3*cos(2*M_PI));
	snowflake(rad/3, x4, y4, x4+rad/3*sin(2*M_PI/5), y4+rad/3*cos(2*M_PI/5), x4+rad/3*sin(4*M_PI/5), y4+rad/3*cos(4*M_PI/5), x4+rad/3*sin(6*M_PI/5), y4+rad/3*cos(6*M_PI/5), x4+rad/3*sin(8*M_PI/5), y4+rad/3*cos(8*M_PI/5), x4+rad/3*sin(2*M_PI), y4+rad/3*cos(2*M_PI));
	snowflake(rad/3, x5, y5, x5+rad/3*sin(2*M_PI/5), y5+rad/3*cos(2*M_PI/5), x5+rad/3*sin(4*M_PI/5), y5+rad/3*cos(4*M_PI/5), x5+rad/3*sin(6*M_PI/5), y5+rad/3*cos(6*M_PI/5), x5+rad/3*sin(8*M_PI/5), y5+rad/3*cos(8*M_PI/5), x5+rad/3*sin(2*M_PI), y5+rad/3*cos(2*M_PI));
}

void drawLine(float xc, float yc, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5){
	gfx_line(xc, yc, x1, y1);
	gfx_line(xc, yc, x2, y2);
	gfx_line(xc, yc, x3, y3);
	gfx_line(xc, yc, x4, y4);
	gfx_line(xc, yc, x5, y5);
}

void fern(float stalk, float angle, float x1, float y1){
	//Base case
	if(stalk < 4) return;
	//Draw Line
	drawLine2(x1, y1, x1+cos(angle)*stalk, y1+(-1)*sin(angle)*stalk);
	//Recursive call
	for(float i=1; i<=4; i++){
		fern(stalk/3, angle+M_PI/6, x1+(i*stalk/4)*cos(angle), y1-(i*stalk/4)*sin(angle));
		fern(stalk/3, angle-M_PI/6, x1+(i*stalk/4)*cos(angle), y1-(i*stalk/4)*sin(angle));
	}
}

void drawLine2(float x1, float y1, float x2, float y2){
	gfx_line(x1, y1, x2, y2);
}

void spiralSquare(float rad, float angle, float x1, float y1){
	//Base case
	if(rad > 350) return;
	//Draw square
	drawSquare2(rad/2.5, x1, y1);	
	//Recursive Call
	spiralSquare(rad*1.15, angle+M_PI/4, x1-rad*cos(angle), y1+rad*sin(angle));
}

void drawSquare2(float side, float x1, float y1){
	gfx_line(x1, y1, x1+side, y1);
	gfx_line(x1+side, y1, x1+side, y1+side);
	gfx_line(x1+side, y1+side, x1, y1+side);
	gfx_line(x1, y1+side, x1, y1);
}

void tree(float rad, float angle, float x1, float y1){
	//Base case
	if(rad < 1.5) return;
	//Draw line
	gfx_line(x1, y1, x1+rad*cos(angle), y1-rad*sin(angle));
	//Recursive Call
	tree(rad*2/3, angle+M_PI/5, x1+rad*cos(angle),y1-rad*sin(angle));
	tree(rad*2/3, angle-M_PI/5, x1+rad*cos(angle),y1-rad*sin(angle));
}

void spirals(float rad, float angle, float x1, float y1){
	//Base Case
	if(rad <1.3) return;
	//Draw line
	gfx_point(x1-rad*cos(angle), y1+rad*sin(angle));
	//Recursive Call
	spirals(rad*.888, angle-M_PI/5, x1, y1);
	spirals(rad*.4, angle-M_PI/3, x1-rad*cos(angle), y1+rad*sin(angle));	
}
