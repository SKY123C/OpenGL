#include <windows.h>
#include <GL/freeglut.h>

//摄像机离物体的距离
GLfloat G_fDistance = 3.6f;
//物体的旋转角度 
GLfloat G_fAngle_horizon = 0.0f;
GLfloat G_fAngle_vertical = 0.0f;


void myinit(void);//用户初始化函数
void myReshape(GLsizei w, GLsizei h);//窗口大小变化的回调函数
void display(void);
//响应键盘输入, 从而设定物体移近移远以及旋转的回调函数
void processSpecialKeys(int key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);


//主函数
int main(int argc, char* argv[])
{
	//固定步骤：
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("实战：画一个茶壶和一个正方形");

	//调用初始化函数
	myinit();

	//设定窗口大小变化的回调函数
	glutReshapeFunc(myReshape);

	//设定键盘控制的回调函数
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);

	//开始OPENGL的循环
	glutDisplayFunc(display);

	//Idle的意思是闲逛，很有趣，其实这个函数就是用来对glutDisplayFunc查漏补缺的
	//定时调用来防止遗漏信息。
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}


//用户初始化函数
void myinit(void)
{
	//“glEnable(GL_DEPTH_TEST): 用来开启更新深度缓冲区的功能,也就是,如果通过比较后深度值发生变化了,会进行更新深度缓冲区的操作。
	//启动它,OpenGL就可以跟踪在Z轴上的像素,这样,它只会再那个像素前方没有东西时,才会绘画这个像素。”
	glEnable(GL_DEPTH_TEST);
}

//窗口大小变化时的回调函数
void myReshape(GLsizei w, GLsizei h)
{
	//设定视区
	glViewport(0, 0, w, h);
	//设定透视方式
	glMatrixMode(GL_PROJECTION);
	//初始化/重置矩阵为单位矩阵
	glLoadIdentity();
	gluPerspective(60.0, 1.0*(GLfloat)w / (GLfloat)h, 1.0, 30.0);
	//	gluPerspective(60.0, 1.0, 1.0, 30.0);	//调整窗口比例时物体会变形
}

//每桢OpenGL都会调用这个函数，用户应该把显示代码放在这个函数中
void display(void)
{
	//设置清除屏幕的颜色，并清除屏幕和深度缓冲
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//模型视景矩阵堆栈应用随后的矩阵操作
	glMatrixMode(GL_MODELVIEW);
	//载入单位化矩阵
	glLoadIdentity();

	//将物体向Z轴平移-G_fDistance (使坐标中心位于摄像机前方)，改变了GL_MODELVIEW的栈顶
	glTranslatef(0.0, 0.0, -G_fDistance);
	//旋转函数（这里用来配合用户调整观察物体的位置）
	glRotatef(G_fAngle_horizon, 0.0f, 1.0f, 0.0f);
	glRotatef(G_fAngle_vertical, 1.0f, 0.0f, 0.0f);


	//绘制物体

	//画一个正方形面
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	//	glColor3ub(255, 0, 255);
	glBegin(GL_QUADS);
	glVertex3f(-1.0, -1.0f, 0.0f);
	glVertex3f(1.0, -1.0f, 0.0f);
	glVertex3f(1.0, 1.0f, 0.0f);
	glVertex3f(-1.0, 1.0f, 0.0f);
	glEnd();

	//画一个茶壶
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glutWireTeapot(1.0);
	//	glutSolidTeapot(1.0);


		//交换前后缓冲区保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）。
	glutSwapBuffers();
	//	glFlush();
}

//对于键盘上特殊符号的响应函数
void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT: //左箭头可以向左旋转
		G_fAngle_horizon -= 5.0f;
		break;
	case GLUT_KEY_RIGHT: //右箭头可以向右旋转
		G_fAngle_horizon += 5.0f;
		break;
	case GLUT_KEY_UP: //上箭头可以向上旋转
		G_fAngle_vertical -= 5.0f;
		break;
	case GLUT_KEY_DOWN: //下箭头可以向下旋转
		G_fAngle_vertical += 5.0f;
		break;
	}
	//	glutPostRedisplay();
}
//对于键盘上正常符号的响应函数
void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 97:	//"a"图靠近镜头
		G_fDistance -= 0.3f;
		break;
	case 65:		//"A"图远离镜头
		G_fDistance += 0.3f;
		break;
	case 27:	//"esc"退出绘图窗口
		exit(0);
	}
	//	glutPostRedisplay();
}
