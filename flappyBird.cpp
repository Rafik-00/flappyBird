#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<random>
#include<cmath>
#include <glut.h>

void Anim(void);

float a = 100;
float ga = 100;
int b[9];
float c = 300;
float d = 115;
float gd = 115;
float trans = 0;
float birdDownY;
float birdUpY;
float birdFirstX;
float birdLastX;
float bb = 0;
float br = 1;
float bg = 0;
int hasWon = 0;
int lives = 3;
int score = 0;
int blockPassed = 0;
int pick;
int xTrans =0;
bool hit = false;
int hitBlock;
float powerDim;

void drawPowerUp(float x, float y) {
	if (hit)
		y = -150;
	glColor3f(0.8f, 0.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(x, y, 0);
	glVertex3f(x, y+15, 0);
	glVertex3f(x+15, y+15, 0);
	glVertex3f(x+15, y, 0);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(x+7.5, y , 0.0f);
	glVertex3f(x+7.5, y+14, 0.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(x + 5, y+10, 0.0f);
	glVertex3f(x + 7.5, y + 14, 0.0f);
	glVertex3f(x + 10, y + 10, 0.0f);
	glEnd();

}

void drawBird(int red, int green, int blue) {
	// start of bird
	glBegin(GL_POLYGON);
	glColor3f(red, green, blue);
	glVertex3f(10.0f, trans + 155.5f, 0.0f);
	glVertex3f(30.0f, trans + 155.0f, 0.0f);
	glVertex3f(30.0f, trans + 140.0f, 0.0f);
	glVertex3f(10.0f, trans + 140.0f, 0.0f);
	birdDownY = trans + 140;
	birdUpY = trans + 155;
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(30.0f, trans + 155.0f, 0.0f);
	glVertex3f(35.0f, trans + 147.5f, 0.0f);
	glVertex3f(30.0f, trans + 140.0f, 0.0f);

	birdFirstX = 35;
	birdLastX = 10;
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(20.0f, trans + 157.0f, 0.0f);
	glVertex3f(5.0f, trans + 145.0f, 0.0f);
	glVertex3f(20.0f, trans + 150.0f, 0.0f);
	glEnd();
}

void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void Timer(int value) {
	if (lives >= 1 && hasWon < 9)
		score += 1;

	// recall the Timer function after 20 seconds (20,000 milliseconds)
	glutTimerFunc(1000, Timer, 0);
}
void Timer2(int value) {
	if (lives >= 1 && hasWon < 9) {
		xTrans -= 0.06;
		a -= 0.06;
		d -= 0.06;
		ga -= 0.06;
		gd -= 0.06;
		trans -= 0.1;
	}
	glutPostRedisplay();
	// recall the Timer function after 20 seconds (20,000 milliseconds)
	glutTimerFunc(1, Timer2, 0);
}

void drawBlock(int i, int power) {
	float R = 0.0;
	float G = 0.6;
	float B = 0.2;
	if (hit) {
		R = 1.0;
		G = 1.0;
		B = 1.0;
		
	}
	
	 if (power == 1) {
		drawPowerUp(d + i + 50, 150);
		powerDim = d + i + 50;
	}
		
		glBegin(GL_QUADS); // GL_QUAD_STRIP
		glColor3f(R, G, B);
		glVertex3f(a + i, b[i / 100], 0.0f);
		glVertex3f(a + i, c, 0.0f);
		glVertex3f(d + i, c, 0.0f);
		glVertex3f(d + i, b[i / 100], 0.0f);
		glEnd();
		glBegin(GL_QUADS); // GL_QUAD_STRIP
		glVertex3f(a + i, 0.0f, 0.0f);
		glVertex3f(a + i, b[i / 100] - 90, 0.0f);
		glVertex3f(d + i, b[i / 100] - 90, 0.0f);
		glVertex3f(d + i, 00.0f, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(a + i, b[i / 100], 0.0f);
		glVertex3f(d + i, c, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(d + i, b[i / 100], 0.0f);
		glVertex3f(a + i, c, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(a + i, b[i / 100] - 90, 0.0f);
		glVertex3f(d + i, 0.0f, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(d + i, b[i / 100] - 90, 0.0f);
		glVertex3f(a + i, 0.0f, 0.0f);
		glEnd();
	
		
		
		
}

void set1(int x) {
	drawBlock(0, x);
	drawBlock(100, 0);
	drawBlock(200, 0);
}
void set2(int x) {
	drawBlock(300, x);
	drawBlock(400, 0);
	drawBlock(500,0);
}
void set3(int x) {
	drawBlock(600,x);
	drawBlock(700,0);
	drawBlock(800,0);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f,0.7f,1.0f,0.0f);
	if (lives <= 0) {
		glColor3f(1, 1, 1);
		char* p0s[20];
		sprintf((char*)p0s, "GAME OVER SCORE: %d", score);
		print(80, 150, (char*)p0s);
	}



	drawBird(br, bg, bb);
		

	if (pick == 1) {
		set1(1);
		set2(0);
		set3(0);
	}
	else if (pick == 2) {
		set2(1);
		set1(0);
		set3(0);
	}
	else if (pick == 3) {
		set3(1);
		set2(0);
		set1(0);
	}
	else {
		set3(0);
		set1(1);
		set2(0);
	}

	if (gd <= 0) {
		ga = 85;
		gd = 100;
		hasWon++;
		
		blockPassed++;
		cout << "blockPassed = " << blockPassed;
	}
	if ((birdFirstX>=powerDim && birdFirstX <= powerDim+15 && birdUpY>=150 && birdUpY <= 150+15)||(birdLastX>=powerDim && birdLastX <= powerDim+15 && birdUpY>=150 && birdDownY <= 150+15)) {
		// handel bird power up
		hit = true;
		hitBlock = blockPassed + 2;

	}
	if (blockPassed>=hitBlock) {
		hit = false;
	}

	if (birdUpY >= 300 || birdDownY <= 0) {
		lives = 0;
	}
	
	if (((((birdFirstX >= ga && birdFirstX < gd) || (birdLastX >= ga && birdLastX <= gd)) && (birdDownY <= b[blockPassed] - 90 || birdUpY >= b[blockPassed])) || birdUpY >= 300 || birdDownY <= 0)&&(blockPassed>=hitBlock)) {
		br = 0;
		bb = 1;
		//if (!hit) {
			lives--;
			
			trans = b[blockPassed] -35 -140;//+140
		//}
	}
	else {
		br = 1;
		bb = 0;
	}
	

	glColor3f(1, 1, 1);
	char* p0s[20];
	sprintf((char*)p0s, "Score: %d", score);
	print(150, 260, (char*)p0s);
	if(lives<= 0)
		sprintf((char*)p0s, "Lives: %d", 0);
	else
		sprintf((char*)p0s, "Lives: %d", lives);
	print(250, 260, (char*)p0s);
	if (lives <= 0) {
		glColor3f(1, 1, 1);
		char* p0s[20];
		sprintf((char*)p0s, "GAME OVER SCORE: %d", score);
		print(80, 150, (char*)p0s);
	}
	if (hasWon >= 9) {
		glColor3f(1, 1, 1);
		char* p0s[20];
		sprintf((char*)p0s, "YOU WON! SCORE: %d", score);
		print(80, 150, (char*)p0s);
	}


	glFlush();

}

void key(unsigned char key, int mx, int my) {
	if (key == 'w')
	{
		trans += 30;
	}
	glutPostRedisplay();
}

void main(int argc, char** argr) {
	srand(time(0));
	for (int i = 0; i < sizeof(b); i++)
	{
		b[i] = rand() % (290 - 50 + 1) + 50;
		cout << b[i];
	}
	hasWon = 0;
	score = 0;
	hit = false;
	blockPassed = 0;
	pick = (rand() % 3)+1;
	cout << "rand" << pick;
	xTrans = 0;
	hitBlock = 0;



	glutInit(&argc, argr);

	glutInitWindowSize(500, 300);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("Flappy birds RAFIK");
	glutDisplayFunc(Display);
	glutIdleFunc(Anim);
	glutKeyboardFunc(key);
	glutTimerFunc(1000, Timer, 0);
	glutTimerFunc(1, Timer2, 0);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 300, 0.0, 300);

	glutMainLoop();
}

void Anim() {
	if (lives >= 1 && hasWon < 9) {
		/*a -= 0.1;
		d -= 0.1;
		ga -= 0.1;
		gd -= 0.1;
		trans -= 0.25;*/

	}
	glutPostRedisplay();
}
