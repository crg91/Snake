#ifndef SNAKE_H
#define SNAKE_H
#include<iostream>
#include<ctime>
#include<GL/glut.h>
using namespace std;

const GLint edge= 50;
const GLint countDownTime= 50;
enum Status{rightDir, leftDir, upDir, downDir};
enum Status1{CONTINUE, PAUSED, OVER};
Status1 gameStatus= CONTINUE;
bool grid[edge][edge]= {};

class node
{
public:
	GLint xVal;
	GLint yVal;
	node* next;
	node(GLint x, GLint y)
	{
		xVal= x;
		yVal= y;
		next= NULL;
	}
};

class Snake
{
private:
	node* head;
	node* tail;
	GLint length;
	GLint storeTime;
	Status direction;
	GLint seed[2];
	GLint special[2];
	GLint counter;
	GLint countDown;
	GLint score;
public:
	Snake()
	{
		head=tail=NULL;
		length=0;
		direction= rightDir;
		storeTime= clock();
		generateSeed();
		generateSpecial();
		counter=0;
		countDown=countDownTime;
		score=0;
	}

	void insert(GLint, GLint);
	void draw();
	void assignSeed();
	void assignSpecial();
	bool ifSeedValid();
	bool ifSpecialValid();
	void generateSeed();
	void generateSpecial();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void move();
};

#endif