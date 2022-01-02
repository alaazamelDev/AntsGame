#include "PowerSupply.h"

GLuint PowerSupply::psTexture[2];

PowerSupply::PowerSupply()
{

}

void draw_circle(float x, float y, float z, float radius) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glLoadIdentity();
	//glTranslatef(x, y, z);
	static const int circle_points = 100;
	static const float angle = 2.0f * 3.1416f / circle_points;

	// this code (mostly) copied from question:
	glBegin(GL_POLYGON);
	double angle1 = 0.0;
	glVertex2d(radius * cos(0.0), radius * sin(0.0));
	int i;
	for (i = 0; i < circle_points; i++)
	{
		glVertex2d(radius * cos(angle1), radius *sin(angle1));
		angle1 += angle;
	}
	glEnd();
	glPopMatrix();
}

void drawSphere(double r, int lats, int longs) {
	//The parameters lat defines how many horizontal lines you want to have in
	//your sphere and lon how many vertical lines.
	//r is the radius of your sphere.
	float M_PI = 3.14;
	int i, j;
	for (i = 0; i <= lats; i++) {
		double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(r * x * zr0, r * y * zr0, r * z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(r * x * zr1, r * y * zr1, r * z1);
		}
		glEnd();
	}
}

void drawCylinder(int nmax, int nmin, float height, float radius)
{
	double M_PI = 3.14;
	double MAX = height / nmax;
	double MIN = 2.0 * M_PI / nmin;
	int i, j;

	for (i = 0; i < nmax; ++i) {
		GLfloat z0 = 0.5 * height - i * MAX;
		GLfloat z1 = z0 - MAX;

		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0; j <= nmin; ++j) {
			double a = j * MIN;
			GLfloat x = radius * cos(a);
			GLfloat y = radius * sin(a);
			glNormal3f(x / radius, y / radius, 0.0);
			glTexCoord2f(j / (GLfloat)nmin, i / (GLfloat)nmax);
			glVertex3f(x, y, z0);

			glNormal3f(x / radius, y / radius, 0.0);
			glTexCoord2f(j / (GLfloat)nmin, (i + 1) / (GLfloat)nmax);
			glVertex3f(x, y, z1);
		}
		glEnd();
	}
}

void PowerSupply::drawCube()
{
	glPushMatrix();

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(1, 1, -1);
	glTexCoord2d(0, 1); glVertex3f(-1, 1, -1);
	glTexCoord2d(1, 1); glVertex3f(-1, 1, 1);
	glTexCoord2d(1, 0); glVertex3f(1, 1, 1);
	glEnd();



	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(1, -1, 1);
	glTexCoord2d(0, 1);  glVertex3f(-1, -1, 1);
	glTexCoord2d(1, 1);  glVertex3f(-1, -1, -1);
	glTexCoord2d(1, 0); glVertex3f(1, -1, -1);
	glEnd();


	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex3f(-1, 1, 1);
	glTexCoord2d(1, 1); glVertex3f(-1, -1, 1);
	glTexCoord2d(1, 0); glVertex3f(1, -1, 1);
	glEnd();



	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(1, -1, -1);
	glTexCoord2d(0, 1); glVertex3f(-1, -1, -1);
	glTexCoord2d(1, 1);	glVertex3f(-1, 1, -1);
	glTexCoord2d(1, 0); glVertex3f(1, 1, -1);
	glEnd();


	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(-1, 1, 1);
	glTexCoord2d(0, 1); glVertex3f(-1, 1, -1);
	glTexCoord2d(1, 1); glVertex3f(-1, -1, -1);
	glTexCoord2d(1, 0); glVertex3f(-1, -1, 1);
	glEnd();


	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(1, 1, -1);
	glTexCoord2d(0, 1); glVertex3f(1, 1, 1);
	glTexCoord2d(1, 1); glVertex3f(1, -1, 1);
	glTexCoord2d(1, 0); glVertex3f(1, -1, -1);

	glEnd();
	glPopMatrix();
}


// This component represent a small resistor on the board 
void PowerSupply::resistor()
{
	glPushMatrix();
	glColor4d(1, 0, 0, 0.9);
	glBindTexture(GL_TEXTURE_2D, psTexture[0]);
	glPushMatrix();
	glTranslatef(15, -1.95, 2);
	glScaled(1, 1, 0.9);
	drawCube();
	glPopMatrix();
	glColor4d(1, 1, 1, 1);
	glPopMatrix();
}

// this is an integrated circuit
void PowerSupply::drawIntegratedCircuit()
{
	glPushMatrix();
	glColor4d(1, 0, 0, 0.9);
	glBindTexture(GL_TEXTURE_2D, psTexture[0]);
	glPushMatrix();
	glTranslatef(15, -1.95, 2);
	glScaled(0.3, 1, 0.95);
	drawCube();
	glPopMatrix();
	glColor4d(1, 1, 1, 1);
	glPopMatrix();
}

void PowerSupply::draw()
{

	//اسطوانات
	feuse();
	bigCapacitor();
	smallCapacitor();
}

void PowerSupply::feuse()
{
	// cylinder
	glPushMatrix();
	glTranslatef(-9, -2, -17);
	miniCylinder();
	glPopMatrix();

	// top close circle
	glPushMatrix();
	glTranslatef(-11.5, -2, -17);
	glRotatef(90, 0, 1, 0);
	draw_circle(-12, -2, -17, 1.5);
	glPopMatrix();

	// bottom close circle
	glPushMatrix();
	glTranslatef(-6.5, -2, -17);
	glRotatef(90, 0, 1, 0);
	draw_circle(-12, -2, -17, 1.5);
	glPopMatrix();
}

void PowerSupply::bigCapacitor()
{
	glPushMatrix();

	// Draw the cylinder part
	glPushMatrix();
	glColor3f(0.5f, 0.1f, 0.3f);
	glTranslatef(22, 7, -6);
	glScaled(4, 4, 4);
	bigCylinder();
	glPopMatrix();

	// Draw the upper sphere
	glColor3f(0.4f, 0.1f, 0.3f);
	glTranslatef(22, 15, -6);
	drawSphere(5.75, 30, 25);

	glPopMatrix();
}

void PowerSupply::smallCapacitor()
{
	glPushMatrix();
	glColor3f(0.1f, 0.3f, 0.4f);
	glTranslatef(9, 4.5, -9);
	glScaled(3, 3, 3);
	bigCylinder();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2f, 0.3f, 0.9f);
	glTranslatef(9, 12, -9);
	drawSphere(4, 30, 25);
	glPopMatrix();
}

void PowerSupply::drawTransformer()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, psTexture[2]);
	glScalef(10, 10, 5);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, psTexture[3]);
	glTranslatef(0, 2, 0);
	glScalef(12, 6, 4);
	drawCube();
	glPopMatrix();
}

void PowerSupply::miniCylinder()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, psTexture[1]);
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(90, 0, 1, 0);
	drawCylinder(40, 40, 5, 1.5);
	glPopMatrix();
	glColor4d(1, 1, 1, 1);
	glPopMatrix();

}

void PowerSupply::bigCylinder()
{
	glBindTexture(GL_TEXTURE_2D, psTexture[1]);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawCylinder(40, 40, 5, 1.5);
	glPopMatrix();
}

