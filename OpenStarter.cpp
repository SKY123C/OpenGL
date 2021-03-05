// OpenGLStarter.cpp : Defines the entry point for the console application.
//



//��Ҫ������ͷ�ļ�
#include <windows.h>
#include <GL/freeglut.h>

//����������ڵĴ�С
#define WINDOW_HEIGHT 300
#define WINDOW_WIDTH 500

//�����������ľ���
float G_fDistance = 3.6f;
//�������ת�Ƕ� 
float G_fAngle_horizon = 0.0;
float G_fAngle_vertical = 0.0f;

float a = 1.0;

////////////////////////////////////////////////
void myinit(void);
void myReshape(GLsizei w, GLsizei h);
void display(void);

//��Ӧ��������, �Ӷ��趨�����ƽ���Զ�Լ���ת�Ļص�����
void processSpecialKeys(int key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);


////////////////////////////////////////////////
//������
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	//��ʼ��OPENGL��ʾ��ʽ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	//�趨OPENGL����λ�úʹ�С
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	//�򿪴���
	glutCreateWindow("OpenGL");

	//���ó�ʼ������
	myinit();

	//�趨���ڴ�С�仯�Ļص�����
	glutReshapeFunc(myReshape);

	//�趨���̿��ƵĻص�����
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);

	//��ʼOPENGL��ѭ��
	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}

////////////////////////////////////////////////
//�û���ʼ������
void myinit(void)
{
	//your initialization code
	glEnable(GL_DEPTH_TEST);
}

//���ڴ�С�仯ʱ�Ļص�����
void myReshape(GLsizei w, GLsizei h)
{
	//�趨����
	glViewport(0, 0, 500, 500);

	//�趨͸�ӷ�ʽ
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	gluPerspective(30, 1, 1, 30.0);

	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 30.0);
}

//ÿ��OpenGL�����������������û�Ӧ�ð���ʾ����������������
void display(void)
{
	//���������Ļ����ɫ���������Ļ����Ȼ���
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//���ó�ģ�;���ģʽ
	glMatrixMode(GL_MODELVIEW);

	//���뵥λ������
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -G_fDistance);
	glRotatef(G_fAngle_horizon, 0.0f, 1.0f, 0.0f);
	glRotatef(G_fAngle_vertical, 1.0f, 0.0f, 0.0f);

	////////////////////////////////////////////////
	//��������

	//��һ����������
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-1.0, -1.0f, 0.0f);
	glVertex3f(1.0, -1.0f, 0.0f);
	glVertex3f(1.0, 1.0f, 0.0f);
	glVertex3f(-1.0, 1.0f, 0.0f);
	glEnd();

	//��һ�����
	glColor3f(0.0f, 1.0f, 0.0f);
	glutWireTeapot(1.0);
	//	glutSolidTeapot(1.0);


		//����ǰ�󻺳���
	glutSwapBuffers();
}


void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		G_fAngle_horizon -= 5.0f;
		break;
	case GLUT_KEY_RIGHT:
		G_fAngle_horizon += 5.0f;
		break;
	case GLUT_KEY_UP:
		G_fAngle_vertical -= 5.0f;
		break;
	case GLUT_KEY_DOWN:
		G_fAngle_vertical += 5.0f;
		break;
	}
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 97:	//"a"
		G_fDistance -= 0.3f;
		break;
	case 65:		//"A"
		G_fDistance += 0.3f;
		break;
	case 27:	//"esc"
		exit(0);
	}
}