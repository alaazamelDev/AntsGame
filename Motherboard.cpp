#include "Motherboard.h"

//Model_3DS *cpuModel;




Motherboard::Motherboard()
{
	//groundTex = LoadTexture("Resources/Textures/4.bmp");
	//instanciate the model object
	//cpuModel = new Model_3DS();
	//cpuModel->Load("Resources/Models/corei7.3DS");
}

GLuint Motherboard::mbTexture[7];

void drawCube() {
	glBegin(GL_QUADS);

	//glColor3f(0, 1, 0);
	glTexCoord2d(1, 0); glVertex3f(1, 1, -1);
	glTexCoord2d(0, 0); glVertex3f(-1, 1, -1);
	glTexCoord2d(0, 1); glVertex3f(-1, 1, 1);
	glTexCoord2d(1, 1); glVertex3f(1, 1, 1);

	//glColor3f(1, 0.5, 0);
	glTexCoord2d(1, 1); glVertex3f(1, -1, 1);
	glTexCoord2d(0, 1); glVertex3f(-1, -1, 1);
	glTexCoord2d(0, 0); glVertex3f(-1, -1, -1);
	glTexCoord2d(1, 0); glVertex3f(1, -1, -1);

	//glColor3f(1, 0, 0);
	glTexCoord2d(1, 1); glVertex3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex3f(-1, 1, 1);
	glTexCoord2d(0, 0); glVertex3f(-1, -1, 1);
	glTexCoord2d(1, 0); glVertex3f(1, -1, 1);

	//glColor3f(1, 1, 0);
	glTexCoord2d(1, 0); glVertex3f(1, -1, -1);
	glTexCoord2d(0, 0); glVertex3f(-1, -1, -1);
	glTexCoord2d(0, 1); glVertex3f(-1, 1, -1);
	glTexCoord2d(1, 1); glVertex3f(1, 1, -1);

	//glColor3f(0, 0, 1);
	glTexCoord2d(1, 1); glVertex3f(-1, 1, 1);
	glTexCoord2d(1, 0); glVertex3f(-1, 1, -1);
	glTexCoord2d(0, 0); glVertex3f(-1, -1, -1);
	glTexCoord2d(0, 1); glVertex3f(-1, -1, 1);

	//glColor3f(1, 0, 1);
	glTexCoord2d(1, 0); glVertex3f(1, 1, -1);
	glTexCoord2d(1, 1); glVertex3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex3f(1, -1, 1);
	glTexCoord2d(0, 0); glVertex3f(1, -1, -1);

	glEnd();
}
void drawRAMPins() {

	// texture[0]= copper
	glBindTexture(GL_TEXTURE_2D, Motherboard::mbTexture[0]);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0.2, 0);
	glScalef(0.15, 0.1, 0.15);
	drawCube();
	glPopMatrix();
}

void ramSide(bool isPCI = false) {

	// texture[1]=ram side
	glBindTexture(GL_TEXTURE_2D, Motherboard::mbTexture[1]);

	if (isPCI)	// texture[1]=pci tex
		glBindTexture(GL_TEXTURE_2D, Motherboard::mbTexture[3]);

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0.2, 0);
	glScalef(0.03, 0.2, 2);
	drawCube();
	glPopMatrix();

}

void slot( bool isPCI = false) {

	glPushMatrix();
	glScalef(1, 1, 0.4);

	// Draw long Sides of RAM
	glPushMatrix();
	ramSide(isPCI);
	glTranslatef(0, 0, 1);
	ramSide(isPCI);
	glPopMatrix();

	// Down Side
	glPushMatrix();
	glTranslatef(2, 0, 0.5);
	glRotatef(90, 0, 1, 0);
	glScalef(0.25, 1, 1);
	ramSide(isPCI);
	glPopMatrix();

	//// UP Side
	//glPushMatrix();
	//glTranslatef(-2, 0, 0.5);
	//glRotatef(90, 0, 1, 0);
	//glScalef(0.25, 1, 1);
	//ramSide(isPCI);
	//glPopMatrix();

	// Draw pins
	for (GLfloat x = -1.6; x < +1.6; x += 0.4) {
		glPushMatrix();
		glTranslatef(x, 0, +0.2);
		drawRAMPins();
		glPopMatrix();
	}

	for (GLfloat x = -1.6; x < +1.6; x += 0.4) {
		glPushMatrix();
		glTranslatef(x, 0, 0.8);
		drawRAMPins();
		glPopMatrix();
	}
	glPopMatrix();
}

void cubicShape() {

	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glScalef(0.7, 0.05, 0.7);
	drawCube();
	glPopMatrix();
}

void pinConnector() {

	glPushMatrix();

	glTranslatef(0, 0.05, 0);
	glScalef(0.05, 0.05, 0.05);
	//glRotatef(90, 0, 0, 1);

	// texture[3]= pin connector
	glBindTexture(GL_TEXTURE_2D, Motherboard::mbTexture[3]);

	glBegin(GL_QUADS);

	//glColor3f(1, 0, 0);
	glTexCoord2d(1, 1); glVertex3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex3f(-1, 1, 1);
	glTexCoord2d(0, 0); glVertex3f(-1, -1, 1);
	glTexCoord2d(1, 0); glVertex3f(1, -1, 1);

	//glColor3f(1, 1, 0);
	glTexCoord2d(1, 0); glVertex3f(1, -1, -1);
	glTexCoord2d(0, 0); glVertex3f(-1, -1, -1);
	glTexCoord2d(0, 1); glVertex3f(-1, 1, -1);
	glTexCoord2d(1, 1); glVertex3f(1, 1, -1);

	//glColor3f(0, 0, 1);
	glTexCoord2d(1, 1); glVertex3f(-1, 1, 1);
	glTexCoord2d(1, 0); glVertex3f(-1, 1, -1);
	glTexCoord2d(0, 0); glVertex3f(-1, -1, -1);
	glTexCoord2d(0, 1); glVertex3f(-1, -1, 1);

	//glColor3f(1, 0, 1);
	glTexCoord2d(1, 0); glVertex3f(1, 1, -1);
	glTexCoord2d(1, 1); glVertex3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex3f(1, -1, 1);
	glTexCoord2d(0, 0); glVertex3f(1, -1, -1);

	glEnd();

	glPopMatrix();

}

void powerConnector()
{

	for (GLfloat x = 0; x < 1; x += 0.1) {
		for (GLfloat z = 0; z < 0.2; z += 0.1) {
			glPushMatrix();
			glTranslatef(x, 0, z);
			pinConnector();
			glPopMatrix();
		}
	}
}

void Motherboard::draw()
{
	// place Texture 
	//glBindTexture(GL_TEXTURE_2D, groundTex);

	// Draw the ground of motherboard
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);

	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);	 glVertex2f(-5, -3);
	glTexCoord2d(0, 1);	 glVertex2f(-5, 3);
	glTexCoord2d(1, 1);	 glVertex2f(+5, +3);
	glTexCoord2d(1, 0);	 glVertex2f(+5, -3);
	glEnd();
	glPopMatrix();
	glColor3f(1, 1, 1);

	// Draw Ram Slots
	//ramSlots();

	// Draw PCI Slots
	//pciSlots();

	// Draw North Bridge
	//bridge();

	// Draw South Bridge
	glPushMatrix();
	glTranslatef(-3, 0, 2);
	glScalef(0.7, 0.7, 0.7);
	//bridge();
	glPopMatrix();

	// Draw ROM
	//rom();

	// Draw Graphics Card Slot
	//graphicsCardSlot();

	// Draw Motherboard power connector
	//motherboardPowerConnector();

	// Draw the cpu model
	//CPU();

	// Draw the Input/Output ports
	//IOPorts();
}

void Motherboard::drawMotherboardScene()
{

}

void Motherboard::ramSlots()
{

	// Draw Two Slots of RAM
	glPushMatrix();
	glTranslatef(2, 0, 1.0);
	slot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, 0, 1.7);
	slot();
	glPopMatrix();
}

void Motherboard::pciSlots()
{
	glPushMatrix();
	glTranslatef(-0.1, 0, 0);

	glPushMatrix();
	glTranslatef(-2.8, 0, -1.2);
	glScalef(0.8, 1, 0.7);
	glRotatef(90, 0, 1, 0);
	slot(true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.3, 0, -1.2);
	glScalef(0.8, 1, 0.7);
	glRotatef(90, 0, 1, 0);
	slot(true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.8, 0, -1.2);
	glScalef(0.8, 1, 0.7);
	glRotatef(90, 0, 1, 0);
	slot(true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.3, 0, -1.2);
	glScalef(0.8, 1, 0.7);
	glRotatef(90, 0, 1, 0);
	slot(true);
	glPopMatrix();

	glPopMatrix();
}

void Motherboard::bridge()
{
	glPushMatrix();
	glTranslatef(0, -0.045, 0);

	// texture[4]= icTex
	glBindTexture(GL_TEXTURE_2D, Motherboard::mbTexture[4]);
	glPushMatrix();
	glTranslatef(-1, -0.1, 0);
	cubicShape();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 0, 0);
	glScalef(0.8, 1, 0.8);
	cubicShape();
	glPopMatrix();

	// texture[5]= metalTexture
	glBindTexture(GL_TEXTURE_2D, Motherboard::mbTexture[5]);
	glTranslatef(-1.25, -0.2, 0);
	for (GLfloat x = -0.2; x < 1.0; x += 0.3) {
		for (GLfloat z = -0.5; z < +0.5; z += 0.2) {
			glPushMatrix();
			glTranslatef(x, 0, z);
			glScalef(0.1, 3, 0.1);
			cubicShape();
			glPopMatrix();
		}
	}

	glPopMatrix();
}

void Motherboard::rom()
{
	glBindTexture(GL_TEXTURE_2D, Motherboard::mbTexture[4]);
	glPushMatrix();
	glTranslatef(-2, -0.145, 2);
	glScalef(0.5, 1, 0.5);
	cubicShape();
	glPopMatrix();
}

void Motherboard::IOPorts()
{
	glBindTexture(GL_TEXTURE_2D, Motherboard::mbTexture[5]);

	glPushMatrix();
	glTranslatef(2, 0.26, -2.75);
	glScalef(0.2, 0.25, 0.2);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.4, 0.36, -2.75);
	glScalef(0.2, 0.35, 0.2);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.2, 0.165, -2.75);
	glScalef(0.6, 0.15, 0.2);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.1, 0.36, -2.75);
	glScalef(0.2, 0.35, 0.2);
	drawCube();
	glPopMatrix();
}

void Motherboard::CPU() {

	glPushMatrix();

	// Down Layer
	glPushMatrix();
	glTranslatef(3, 0.04, -0.2);
	glRotatef(90, 0, 1, 0);
	glScalef(0.8, 0.03, 0.8);

	// texture[5]= cpuTex & metalTex
	glBindTexture(GL_TEXTURE_2D, Motherboard::mbTexture[5]);
	drawCube();
	glPopMatrix();

	// Upper Layer
	glPushMatrix();
	glTranslatef(3, 0.04, -0.2);
	glScalef(0.7, 0.06, 0.7);

	// texture[5]= cpuTex & metalTex
	glBindTexture(GL_TEXTURE_2D, Motherboard::mbTexture[6]);
	drawCube();
	glPopMatrix();

	glPopMatrix();
}

void Motherboard::graphicsCardSlot()
{

	glPushMatrix();
	glTranslatef(-2.3, 0, -0.8);
	glScalef(0.8, 1, 0.7);
	glRotatef(90, 0, 1, 0);
	slot(true);
	glPopMatrix();

}

void Motherboard::motherboardPowerConnector()
{
	glPushMatrix();
	glTranslatef(2, 0, 2.5);
	powerConnector();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0, 2.5);
	powerConnector();
	glPopMatrix();
}
