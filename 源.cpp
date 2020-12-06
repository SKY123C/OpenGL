#include <windows.h>
#include <GL/freeglut.h>

//�����������ľ���
GLfloat G_fDistance = 3.6f;
//�������ת�Ƕ� 
GLfloat G_fAngle_horizon = 0.0f;
GLfloat G_fAngle_vertical = 0.0f;


void myinit(void);//�û���ʼ������
void myReshape(GLsizei w, GLsizei h);//���ڴ�С�仯�Ļص�����
void display(void);
//��Ӧ��������, �Ӷ��趨�����ƽ���Զ�Լ���ת�Ļص�����
void processSpecialKeys(int key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);


//������
int main(int argc, char* argv[])
{
	//�̶����裺
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ʵս����һ�������һ��������");

	//���ó�ʼ������
	myinit();

	//�趨���ڴ�С�仯�Ļص�����
	glutReshapeFunc(myReshape);

	//�趨���̿��ƵĻص�����
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);

	//��ʼOPENGL��ѭ��
	glutDisplayFunc(display);

	//Idle����˼���й䣬����Ȥ����ʵ�����������������glutDisplayFunc��©��ȱ��
	//��ʱ��������ֹ��©��Ϣ��
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}


//�û���ʼ������
void myinit(void)
{
	//��glEnable(GL_DEPTH_TEST): ��������������Ȼ������Ĺ���,Ҳ����,���ͨ���ȽϺ����ֵ�����仯��,����и�����Ȼ������Ĳ�����
	//������,OpenGL�Ϳ��Ը�����Z���ϵ�����,����,��ֻ�����Ǹ�����ǰ��û�ж���ʱ,�Ż�滭������ء���
	glEnable(GL_DEPTH_TEST);
}

//���ڴ�С�仯ʱ�Ļص�����
void myReshape(GLsizei w, GLsizei h)
{
	//�趨����
	glViewport(0, 0, w, h);
	//�趨͸�ӷ�ʽ
	glMatrixMode(GL_PROJECTION);
	//��ʼ��/���þ���Ϊ��λ����
	glLoadIdentity();
	gluPerspective(60.0, 1.0*(GLfloat)w / (GLfloat)h, 1.0, 30.0);
	//	gluPerspective(60.0, 1.0, 1.0, 30.0);	//�������ڱ���ʱ��������
}

//ÿ��OpenGL�����������������û�Ӧ�ð���ʾ����������������
void display(void)
{
	//���������Ļ����ɫ���������Ļ����Ȼ���
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//ģ���Ӿ������ջӦ�����ľ������
	glMatrixMode(GL_MODELVIEW);
	//���뵥λ������
	glLoadIdentity();

	//��������Z��ƽ��-G_fDistance (ʹ��������λ�������ǰ��)���ı���GL_MODELVIEW��ջ��
	glTranslatef(0.0, 0.0, -G_fDistance);
	//��ת������������������û������۲������λ�ã�
	glRotatef(G_fAngle_horizon, 0.0f, 1.0f, 0.0f);
	glRotatef(G_fAngle_vertical, 1.0f, 0.0f, 0.0f);


	//��������

	//��һ����������
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	//	glColor3ub(255, 0, 255);
	glBegin(GL_QUADS);
	glVertex3f(-1.0, -1.0f, 0.0f);
	glVertex3f(1.0, -1.0f, 0.0f);
	glVertex3f(1.0, 1.0f, 0.0f);
	glVertex3f(-1.0, 1.0f, 0.0f);
	glEnd();

	//��һ�����
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glutWireTeapot(1.0);
	//	glutSolidTeapot(1.0);


		//����ǰ�󻺳�����֤ǰ���OpenGL��������ִ�У��������������ڻ������еȴ�����
	glutSwapBuffers();
	//	glFlush();
}

//���ڼ�����������ŵ���Ӧ����
void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT: //���ͷ����������ת
		G_fAngle_horizon -= 5.0f;
		break;
	case GLUT_KEY_RIGHT: //�Ҽ�ͷ����������ת
		G_fAngle_horizon += 5.0f;
		break;
	case GLUT_KEY_UP: //�ϼ�ͷ����������ת
		G_fAngle_vertical -= 5.0f;
		break;
	case GLUT_KEY_DOWN: //�¼�ͷ����������ת
		G_fAngle_vertical += 5.0f;
		break;
	}
	//	glutPostRedisplay();
}
//���ڼ������������ŵ���Ӧ����
void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 97:	//"a"ͼ������ͷ
		G_fDistance -= 0.3f;
		break;
	case 65:		//"A"ͼԶ�뾵ͷ
		G_fDistance += 0.3f;
		break;
	case 27:	//"esc"�˳���ͼ����
		exit(0);
	}
	//	glutPostRedisplay();
}
