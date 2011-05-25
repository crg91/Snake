#ifndef SNAKE1_H
#define SNAKE1_H

#include "Snake.h"
#include "numbers.h"

void Snake::insert(GLint x, GLint y)
{
	if(head==NULL && tail== NULL)
	{
		head= tail= new node(x, y);
	}

	else
	{
		node* ptr= new node(x, y);
		ptr->next= tail;
		tail= ptr;
	}

	length++;
}

void drawGrid(int i, int j)
{
	//glColor3f(0.0, 1.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_QUADS);
			glVertex2f(i- 0.5, j- 0.5);
			glVertex2f(i+ 0.5, j- 0.5);
			glVertex2f(i+ 0.5, j+ 0.5);
			glVertex2f(i- 0.5, j+ 0.5);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUADS);
			glVertex2f(i- 0.5, j- 0.5);
			glVertex2f(i+ 0.5, j- 0.5);
			glVertex2f(i+ 0.5, j+ 0.5);
			glVertex2f(i- 0.5, j+ 0.5);
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawSingleDigiNumber(GLint value, GLfloat x,GLfloat y,GLfloat length )
{
	switch(value)
	{
	case 0:
		drawZero(x, y, 0.0, length);
		break;
	case 1:
		drawOne(x, y, 0.0, length);
		break;
	case 2:
		drawTwo(x, y, 0.0, length);
		break;
	case 3:
		drawThree(x, y, 0.0, length);
		break;
	case 4:
		drawFour(x, y, 0.0, length);
		break;
	case 5:
		drawFive(x, y, 0.0, length);
		break;
	case 6:
		drawSix(x, y, 0.0, length);
		break;
	case 7:
		drawSeven(x, y, 0.0, length);
		break;
	case 8:
		drawEight(x, y, 0.0, length);
		break;
	case 9:
		drawNine(x, y, 0.0, length);
		break;
	default:
		break;
	}
}
void drawFourDigiNumber(GLint value, GLfloat x, GLfloat y, GLfloat length)
{
	int d1, d2, d3, d4;
	d4=value%10;
	value= value/10;
	d3=value%10;
	value= value/10;
	d2=value%10;
	value= value/10;
	d1= value%10;
	drawSingleDigiNumber(d1, x, y, length);
	drawSingleDigiNumber(d2, x + 2*length, y, length);
	drawSingleDigiNumber(d3, x + 4*length, y, length);
	drawSingleDigiNumber(d4, x + 6*length, y, length);
}


void Snake::draw()
{
	node* ptr= tail;

	
	for(;ptr!=NULL; ptr=ptr->next)
	{
		glColor3f(0.0, 1.0, 0.0);
		drawGrid(ptr->xVal, ptr->yVal);
	}

	glColor3f(1.0, 0.0, 0.0);
	drawGrid(seed[0], seed[1]);

	if(counter==5)
	{
		glColor3f(0.0, 0.0, 1.0);
		drawGrid(special[0], special[1]);
		glColor3f(1.0, 1.0, 1.0);
		drawFourDigiNumber(countDown, edge+1, 20.0, 1.2);
	}

	glColor3f(1.0,1.0, 0.0);
	glBegin(GL_QUADS);
	   glVertex2f(edge-0.5, -0.5);
	   glVertex2f(edge, -0.5);
	   glVertex2f(edge, edge-0.5);
	   glVertex2f(edge-0.5, edge-0.5);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	drawFourDigiNumber(score, edge+1.0, 40.0, 1.2);
}

void Snake::assignSeed()
{
	seed[0]= rand()%edge;
	seed[1]= rand()%edge;
}

void Snake::assignSpecial()
{
	special[0]= rand()%edge;
	special[1]= rand()%edge;
}

bool Snake::ifSeedValid()
{
	node* ptr= tail;

	for(;ptr!= NULL; ptr= ptr->next)
	{
		if(ptr->xVal==seed[0] && ptr->yVal== seed[1])
		{
			return false;
		}
	}

	if(counter==5 && seed[0]==special[0] && seed[1]== special[1])//to take care the seed does not overlap the special seed
	{
		return false;
	}

	return true;
}

bool Snake::ifSpecialValid()
{
	node* ptr= tail;

	for(;ptr!=NULL; ptr= ptr->next)
	{
		if(ptr->xVal==special[0] && ptr->yVal== special[1])
		{
			return false;
		}
	}

	if(special[0]==seed[0] && special[1]== seed[1])
	{
		return false;
	}

	return true;
}

void Snake::generateSeed()
{
	assignSeed();
	while(!ifSeedValid())
	{
		assignSeed();
	}
}

void Snake::generateSpecial()
{
	assignSpecial();
	while(!ifSpecialValid())
	{
		assignSpecial();
	}

	countDown= countDownTime;
}

void Snake::moveRight()
{
	if(direction!=leftDir)
	{
		if(countDown==0) //i.e. time over in getting the special seed
		{
			counter=0;
			generateSpecial();
		}

		direction= rightDir;
		if((head->xVal<edge-1 && grid[head->xVal+ 1][head->yVal]== 1) || (head->xVal== edge-1 && grid[0][head->yVal]==1))
		{
			gameStatus= OVER;
		}

		else if(head->xVal<edge-1 && head->xVal+1== seed[0] && head->yVal==seed[1])
		{
			score= score+ 10;
			head->next= new node(head->xVal+ 1, head->yVal);
			head= head->next;
			grid[head->xVal][head->yVal]=1;
			generateSeed();
			if(counter!=5)
			{
				counter++;
				if(counter==5)
				{
					generateSpecial();
				}
			}
		}

		else if(head->xVal== edge-1 && seed[0]==0 && head->yVal==seed[1])
		{
			score= score+ 10;
			head->next= new node(0, head->yVal);
			head= head->next;
			grid[head->xVal][head->yVal]=1;
			generateSeed();
			if(counter!=5)
			{
				counter++;
				if(counter==5)
				{
					generateSpecial();
				}
			}
		}


		else if(head->xVal< edge-1)
		{
			if(counter==5 && countDown>0 && head->xVal+ 1==special[0] && head->yVal==special[1])//i.e. it stikies special seed
			{
				counter=0;
				score= score+ 10*countDown;
				generateSpecial();
				
			}

			if(tail==head)//i.e. one node
			{
				head->xVal= head->xVal+1;
			}
			else
			{
				node* ptr= tail;
				tail= tail->next;
				grid[ptr->xVal][ptr->yVal]=0;
				ptr->xVal= head->xVal+ 1;
				ptr->yVal= head->yVal;
				ptr->next= NULL;
				head->next= ptr;
				head= head->next;
				grid[head->xVal][head->yVal]=1;
			}
		}

		else//when head->xVal==edge-1
		{
			if(counter==5 && special[0]==0 && special[1]==head->yVal)
			{
				counter=0;
				score= score+ 10*countDown;
				generateSpecial();
				
			}

			if(tail==head)
			{
				head->xVal= 0;
			}
			else
			{
				node* ptr= tail;
				tail= tail->next;
				grid[ptr->xVal][ptr->yVal]= 0;
				ptr->xVal= 0;
				ptr->yVal= head->yVal;
				ptr->next= NULL;
				head->next= ptr;
				head= head->next;
				grid[head->xVal][head->yVal]=1;
			}
		}

		if(counter==5)
		{
			countDown--;
		}

		storeTime= clock();
	}
}

void Snake::moveLeft()
{
	if(direction!=rightDir)
	{
		if(countDown==0) //i.e. time over in getting the special seed
		{
			counter=0;
			generateSpecial();
		}

		direction= leftDir;
		if((head->xVal>0 && grid[head->xVal- 1][head->yVal]== 1) || (head->xVal== 0 && grid[edge-1][head->yVal]==1))
		{
			gameStatus= OVER;
		}

		else if(head->xVal>0 && head->xVal-1== seed[0] && head->yVal==seed[1])
		{
			score= score+ 10;
			head->next= new node(head->xVal- 1, head->yVal);
			head= head->next;
			grid[head->xVal][head->yVal]=1;
			generateSeed();
			if(counter!=5)
			{
				counter++;
				if(counter==5)
				{
					generateSpecial();
				}
			}
		}

		else if(head->xVal== 0 && seed[0]==edge-1 && head->yVal==seed[1])
		{
			score= score+ 10;
			head->next= new node(edge-1, head->yVal);
			head= head->next;
			grid[head->xVal][head->yVal]=1;
			generateSeed();
			if(counter!=5)
			{
				counter++;
				if(counter==5)
				{
					generateSpecial();
				}
			}
		}

		else if(head->xVal> 0)
		{
			if(counter==5 && special[0]== head->xVal- 1 && special[1]== head->yVal)
			{
				counter=0;
				score= score+ 10*countDown;
				generateSpecial();
				
			}

			if(head==tail)
			{
				head->xVal= head->xVal- 1;
			}
			else
			{
				node* ptr= tail;
				tail= tail->next;
				grid[ptr->xVal][ptr->yVal]=0;
				ptr->xVal= head->xVal- 1;
				ptr->yVal= head->yVal;
				ptr->next= NULL;
				head->next= ptr;
				head= head->next;
				grid[head->xVal][head->yVal]=1;
			}
		}

		else//when head->xVal==0
		{
			if(counter==5 && special[0]==edge-1 && special[1]==head->yVal)
			{
				counter=0;
				score= score+ 10*countDown;
				generateSpecial();
				
			}

			if(head==tail)
			{
				head->xVal= edge-1;
			}
			else
			{
				node* ptr= tail;
				tail= tail->next;
				grid[ptr->xVal][ptr->yVal]= 0;
				ptr->xVal= edge-1;
				ptr->yVal= head->yVal;
				ptr->next= NULL;
				head->next= ptr;
				head= head->next;
				grid[head->xVal][head->yVal]=1;
			}
		}

		if(counter==5)
		{
			countDown--;
		}

		storeTime= clock();
	}
}

void Snake::moveUp()
{
	if(direction!=downDir)
	{
		if(countDown==0) //i.e. time over in getting the special seed
		{
			counter=0;
			generateSpecial();
		}

		direction= upDir;
		if((head->yVal< edge-1 && grid[head->xVal][head->yVal+1]== 1) || (head->yVal== edge-1 && grid[head->xVal][0]==1))
		{
			gameStatus= OVER;
		}

		else if(head->yVal< edge-1 && head->xVal== seed[0] && head->yVal+1==seed[1])
		{
			score= score+ 10;
			head->next= new node(head->xVal, head->yVal+1);
			head= head->next;
			grid[head->xVal][head->yVal]=1;
			generateSeed();
			if(counter!=5)
			{
				counter++;
				if(counter==5)
				{
					generateSpecial();
				}
			}
		}

		else if(head->yVal== edge-1 && seed[0]== head->xVal && seed[1]==0)
		{
			score= score+ 10;
			head->next= new node(head->xVal, 0);
			head= head->next;
			grid[head->xVal][head->yVal]=1;
			generateSeed();
			if(counter!=5)
			{
				counter++;
				if(counter==5)
				{
					generateSpecial();
				}
			}

		}

		else if(head->yVal< edge-1)
		{
			if(counter==5 && special[0]== head->xVal && special[1]== head->yVal+ 1)
			{
				counter=0;
				score= score+ 10*countDown;
				generateSpecial();
				
			}

			if(head==tail)
			{
				head->yVal= head->yVal+1;
			}
			else
			{
				node* ptr= tail;
				tail= tail->next;
				grid[ptr->xVal][ptr->yVal]=0;
				ptr->xVal= head->xVal;
				ptr->yVal= head->yVal+ 1;
				ptr->next= NULL;
				head->next= ptr;
				head= head->next;
				grid[head->xVal][head->yVal]=1;
			}
		}

		else//when head->yVal==edge-1
		{
			if(counter==5 && special[0]==head->xVal && special[1]==0)
			{
				counter=0;
				score= score+ 10*countDown;
				generateSpecial();
				
			}

			if(head==tail)
			{
				head->yVal=0;
			}
			else
			{
				node* ptr= tail;
				tail= tail->next;
				grid[ptr->xVal][ptr->yVal]= 0;
				ptr->xVal= head->xVal;
				ptr->yVal= 0;
				ptr->next= NULL;
				head->next= ptr;
				head= head->next;
				grid[head->xVal][head->yVal]=1;
			}
		}

		if(counter==5)
		{
			countDown--;
		}

		storeTime= clock();
	}
}

void Snake::moveDown()
{
	if(direction!=upDir)
	{
		if(countDown==0) //i.e. time over in getting the special seed
		{
			counter=0;
			generateSpecial();
		}

		direction= downDir;
		if((head->yVal> 0 && grid[head->xVal][head->yVal-1]== 1) || (head->yVal== 0 && grid[head->xVal][edge-1]==1))
		{
			gameStatus= OVER;
		}

		else if(head->yVal> 0 && head->xVal== seed[0] && head->yVal-1==seed[1])
		{
			score= score+ 10;
			head->next= new node(head->xVal, head->yVal-1);
			head= head->next;
			grid[head->xVal][head->yVal]=1;
			generateSeed();
			if(counter!=5)
			{
				counter++;
				if(counter==5)
				{
					generateSpecial();
				}
			}
		}

		else if(head->yVal== 0 && seed[0]== head->xVal && seed[1]==edge-1)
		{
			score= score+ 10;
			head->next= new node(head->xVal, edge-1);
			head= head->next;
			grid[head->xVal][head->yVal]=1;
			generateSeed();
			if(counter!=5)
			{
				counter++;
				if(counter==5)
				{
					generateSpecial();
				}
			}
		}

		else if(head->yVal> 0)
		{
			if(counter==5 && special[0]== head->xVal && special[1]== head->yVal-1)
			{
				counter=0;
				score= score+ 10*countDown;
				generateSpecial();
				
			}

			if(head==tail)
			{
				head->yVal= head->yVal-1;
			}
			else
			{
				node* ptr= tail;
				tail= tail->next;
				grid[ptr->xVal][ptr->yVal]=0;
				ptr->xVal= head->xVal;
				ptr->yVal= head->yVal- 1;
				ptr->next= NULL;
				head->next= ptr;
				head= head->next;
				grid[head->xVal][head->yVal]=1;
			}
		}

		else//when head->yVal==0
		{
			if(counter==5 && special[0]== head->xVal && special[1]== edge-1)
			{
				counter=0;
				score= score+ 10*countDown;
				generateSpecial();
				
			}

			if(head==tail)
			{
				head->yVal= edge-1;
			}
			else
			{
				node* ptr= tail;
				tail= tail->next;
				grid[ptr->xVal][ptr->yVal]= 0;
				ptr->xVal= head->xVal;
				ptr->yVal= edge-1;
				ptr->next= NULL;
				head->next= ptr;
				head= head->next;
				grid[head->xVal][head->yVal]=1;
			}
		}

		if(counter==5)
		{
			countDown--;
		}

		storeTime= clock();
	}
}

void Snake::move()
{
	if(storeTime <= clock()- 70 && gameStatus==CONTINUE)
	{
		if(direction== rightDir)
		{
			moveRight();
		}
		else if(direction== leftDir)
		{
			moveLeft();
		}
		else if(direction== upDir)
		{
			moveUp();
		}
		else//(direction== downDir)
		{
			moveDown();
		}

		glutPostRedisplay();
	}
}

#endif