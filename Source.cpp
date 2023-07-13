#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<iostream>
#include <stdlib.h>
#include <math.h>
#include <sstream> 
#include<string>
#include<GL/glut.h> 
#define PI 3.14

using namespace std;

typedef struct treenode {
	int data;
	int id;
	float x, y, r;
	int size;
	struct treenode* left;
	struct treenode* right;
	
}TREENODE;

TREENODE* root = NULL;

int w, sub1, n, w2,  inst;
int id = 0, se, item, i = 0;

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}

void add_node(TREENODE** l_root, TREENODE* current) {
	if (*l_root == NULL) {
		*l_root = current;
		return;
	}
	if (current->data < (*l_root)->data) {
		swap(*l_root, current);
	}
	if ((*l_root)->left == NULL) {
		(*l_root)->left = current;
	}
	else {
		add_node(&((*l_root)->right), current);
		if ((*l_root)->left->size < (*l_root)->right->size) {
			swap((*l_root)->left, (*l_root)->right);
		}
		(*l_root)->size = (*l_root)->right->size + 1;
	}
}

void accept_tree() {
	int ele;
	cout << "\n Enter the input nodes (enter 0 to start)\n";
	while (1) {
		fflush(stdin);
		cin >> ele;
		if (ele == 0) {
			break;
		}
		TREENODE* current = new TREENODE;
		current->data = ele;
		current->right = NULL;
		current->left = NULL;
		
		current->id = id;
		id += 1;
		n += 1;
		add_node(&root, current);
	}
}

void draw_text(string temp, float x, float y) {
	glColor3f(0, 0, 0);
	char* text = new char[temp.length() + 1];
	strcpy(text, temp.c_str());
	GLvoid* font_style = GLUT_BITMAP_HELVETICA_18;
	glRasterPos3f(x, y, 0);
	for (int i = 0; text[i] != '\0'; i++) {
		glutBitmapCharacter(font_style, text[i]);
	}
}

void drawCircle(float segments, float radius, float sx, float sy)
{
	float theta = 2 * 3.1415926 / segments;
	float tan_factor = tanf(theta);
	float radial_factor = cosf(theta);
	float x = radius;
	float y = 0;
	int cache_pt = 0;
	double cache_x;
	double cache_y;
	glBegin(GL_LINES);
	for (int ii = 0; ii < segments; ii++) {
		if (!cache_pt) {
			cache_x = x + sx;
			cache_y = y + sy;
			cache_pt = 1;
		}
		else {
			glVertex2f(x + sx, y + sy);
			cache_x = x + sx;
			cache_y = y + sy;
		}
		float tx = -y;
		float ty = x;
		x += tx * tan_factor;
		y += ty * tan_factor;
		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
	glFlush();
}
void draw_line(float x1, float y1, float x2, float y2) {
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}
void drawNode(TREENODE* t_root, float x1, float y1, int level) {
	if (t_root == NULL) {
		return;
	}
	float segments = 40;
	float radius = 1.0;
	float left_angle = 245;
	float right_angle = 115;
	float branch_length = 12 - level * 2.5;
	float angle_change = 20;
	root->x = x1;
	root->y = y1;
	root->r = radius;
	drawCircle(segments, radius, x1, y1);
	char buff[5];
	_itoa_s(t_root->data, buff, 10);
	draw_text(buff, x1, y1);
	if (t_root->left) {
		float angle = left_angle - level * angle_change;
		double radian = angle * 3.14 / 180;
		float m = (double)tan((double)radian);
		float x2 = x1 + branch_length * sin((double)radian);
		float y2 = y1 + branch_length * cos((double)radian);
		drawNode(t_root->left, x2, y2, level + 1);
		draw_line(x1, y1, x2, y2);
	}
	if (t_root->right) {
		float angle = right_angle + level * angle_change;
		float radian = angle * 3.14 / 180;
		float m = (double)tan((double)radian);
		float x2 = x1 + branch_length * sin((double)radian);
		float y2 = y1 + branch_length * cos((double)radian);
		drawNode(t_root->right, x2, y2, level + 1);
		draw_line(x1, y1, x2, y2);
	}

}




void display(void) {

	glClearColor(0.7, 0.95, 1, 0.8);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0, 10, -30);

	glColor3f(0, 0, 0);
	char text[] = "Leftist Heap Sort";
	GLvoid* font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	glRasterPos3f(-5, 5, 0);
	for (int i = 0; text[i] != '\0'; i++) {
		glutBitmapCharacter(font_style, text[i]);
	}
	drawNode(root, 0, 3, 0);
	
	glutSwapBuffers();
}


void mouseInstr(int bt, int st, int x, int y) {
	if (bt == GLUT_RIGHT_BUTTON && st == GLUT_DOWN) {
		glutHideWindow();
		glutSetWindow(w);
		glutShowWindow();
		
	}
}
void dispInstr() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	

	glColor3f(0, 0, 0);

	char text[] = "INSTRUCTIONS";

	GLvoid* font_style = GLUT_BITMAP_HELVETICA_18;
	glRasterPos3f(200, 480, 0);
	for (int i = 0; text[i] != '\0'; i++) {
		glutBitmapCharacter(font_style, text[i]);
	}

	draw_text("=> RIGHT CLICK to go to the leftist heap window.", 10, 390);
	

	glFlush();
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {

	accept_tree();

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	inst = glutCreateWindow("Instructions");
	init();
	glutDisplayFunc(dispInstr);
	glutMouseFunc(mouseInstr);

	glutInitDisplayMode(GLUT_DOUBLE);

	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	w = glutCreateWindow("Leftist Heap Sort");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutHideWindow();

	glutMainLoop();

	return 0;
}