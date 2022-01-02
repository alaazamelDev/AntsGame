#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "texture.h"

#pragma once
class Motherboard
{

public:
	Motherboard();
	void Motherboard::draw();	// a function used to draw the motherboard model
	void Motherboard::drawMotherboardScene();
	void Motherboard::ramSlots();
	void Motherboard::pciSlots();
	void Motherboard::bridge();
	void Motherboard::rom();
	void Motherboard::IOPorts();
	void Motherboard::graphicsCardSlot();
	void Motherboard::motherboardPowerConnector();
	void Motherboard::CPU();
	static GLuint mbTexture[7];

private:
	/*void Motherboard::ramSlots();
	void Motherboard::pciSlots();
	void Motherboard::bridge();
	void Motherboard::rom();
	void Motherboard::IOPorts();
	void Motherboard::graphicsCardSlot();
	void Motherboard::motherboardPowerConnector();
	void Motherboard::CPU();*/
};

