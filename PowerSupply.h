
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include "texture.h"
#include "Model_3DS.h"

#pragma once

class PowerSupply
{
public:
	PowerSupply();
	void PowerSupply::resistor(); // draw resistor
	void PowerSupply::drawIntegratedCircuit();//لرسم مكعب أصغر
	void PowerSupply::draw();
	void PowerSupply::feuse();
	void PowerSupply::bigCapacitor();
	void PowerSupply::smallCapacitor();
	void PowerSupply::drawTransformer();
	static GLuint psTexture[2];

private:
	void PowerSupply::drawCube(); // draw resistor
	void PowerSupply::miniCylinder();//اسطوانةصغيرة
	void PowerSupply::bigCylinder();//اسطوانة كبيرة 

};

