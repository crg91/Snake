#include "Snake.cpp"


Snake s1;


void init()
{
	s1.insert(25, 25);
	s1.insert(24, 25);
	s1.insert(23, 25);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	s1.draw();
	
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.5, edge-0.5+ 10, -0.5, edge-0.5, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void special(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		s1.moveLeft();
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		s1.moveRight();
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		s1.moveUp();
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		s1.moveDown();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void animation()
{
	s1.move();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize((20+5)*25, 20*25);
	glutCreateWindow(">>crg<<");
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	glutIdleFunc(animation);
	glutMainLoop();
	return 0;
}