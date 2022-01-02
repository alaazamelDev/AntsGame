#include <math.h>		    
#include <windows.h>
#include <gl\gl.h>			
#include <gl\glu.h>			
#include <glaux.h>	
#include <iostream>
#include "glext.h"	               // Header File For Multitexturing
#include <timeapi.h>               //Header File For Timeing 
#include"3DTexture.h"
#include"Model_3DS.h"
#include "PowerSupply.h"
#include "Motherboard.h"

#pragma comment(lib, "legacy_stdio_definitions.lib")
HDC		hDC = NULL;			// Private GDI Device Context
HGLRC	hRC = NULL;			// Permanent Rendering Context
HWND	hWnd = NULL;			// Holds Our Window Handle

#define	MAX_PARTICLES	45


GLdouble WIDTH;
GLdouble HEIGHT;

GLdouble	mouse_x, mouse_y;
GLdouble	mouse_3d_x, mouse_3d_y;
int mouse_wrap_x = 0;
int mouse_wrap_y = 0;
bool invert_mouse = false;  // Used to invert the y-axis for the mouse
GLdouble sensitivity = 8;  // the higher the #, the lower mouse the sensitivity.

bool	keys[256];			// Array Used For The Keyboard Routine
bool  ip;					// Temporary variable used in association with the invert_mouse variable

bool active = TRUE;		// Window Active Flag Set To TRUE By Default
bool fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

bool is_shock_rifle = FALSE;
//bool is_shock_rifle_blast=FALSE;

bool isFire = false;
bool isFireComplete = true;

BOOL done = FALSE;								// Bool Variable To Exit Loop
bool win = true;
bool up;
bool dn;
bool rn;
bool esc;
bool DONE = false;
bool MENU = false;
int item = 1;
bool Selection = false;
bool PlayAgain = false;
bool Options = false;
bool Exit = false;

//int cntclr = 0;

float alpha1 = .25f;
float alpha2 = .25f;
float alpha3 = .25f;
float alpha1a = 0;
float alpha2a = 0;
float alpha3a = 0;
float alpha1ap = 0;
float alpha2ap = 0;
float alpha3ap = 0;

float menuZ = 0;


int loop;
GLdouble V;
GLdouble Angle;
GLdouble AngleZ;
Model_3DS*capacitorModel;
Model_3DS*tree1;
Model_3DS*tree2;
Model_3DS*tree3;
Model_3DS*ANT;

GLUquadricObj *quadratic;	// Storage For Our Quadratic Objects ( NEW )
GLuint	texture[30];
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
GLvoid KillGLWindow(GLvoid);


#define __ARB_ENABLE true											// Used To Disable ARB Extensions Entirely

// #define EXT_INFO													// Do You Want To See Your Extensions At Start-Up?
#define MAX_EXTENSION_SPACE 10240									// Characters for Extension-Strings
#define MAX_EXTENSION_LENGTH 256									// Maximum Of Characters In One Extension-String
bool multitextureSupported = false;									// Flag Indicating Whether Multitexturing Is Supported
bool useMultitexture = true;											// Use It If It Is Supported?
GLint maxTexelUnits = 1;												// Number Of Texel-Pipelines. This Is At Least 1.

PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTextureARB = NULL;  //منشان مؤشر السلاح 

typedef struct												// لتهيئة الاكساء بدال استخدام الملف texture.cpp 
{
	GLubyte	*imageData;
	GLuint	bpp;
	GLuint	width;
	GLuint	height;
	GLuint	texID;
} TextureImage;

GLuint		base;
TextureImage textures[2];


static GLuint	ROOM;				// Storage For The Room Display List
									/*
									// Draw Rom IC
									glPushMatrix();
									glTranslatef(MAX_Cells *0.6, 0, MAX_Cells *0.4);
									glRotatef(90, 0, 1, 0);
									glScalef(MAX_Cells*0.08, MAX_Cells*0.05, MAX_Cells*0.1);
									mbModel.rom();
									glPopMatrix();

									*/

const int  MAX_Cells = 512;
GLdouble xtrans2 = MAX_Cells *0.6 - 20;
GLdouble ytrans2 = 1010;
GLdouble ztrans2 = MAX_Cells *0.4 - 20;

GLdouble xtrans = 0;
GLdouble xtrany = 0;

GLdouble xptrans = 0;
GLdouble ztrans = 0;
GLdouble zptrans = 0;




GLdouble	yrot = 0;				// Y Rotation

const GLdouble piover180 = 0.0174532925f;
GLdouble XP = 0;
GLdouble ZP = 0;
/*اعدادات الماوس المكان الي يتطلع عليه*/
GLdouble sceneroty;
GLdouble heading;
GLdouble _heading = 0;

GLdouble zprot;



GLdouble size = .25f;
int frames = 0;

GLdouble FPS = 0;

GLdouble fire_x = 0;
GLdouble fire_y = 10;
GLdouble fire_xp, fire_yp;
GLdouble fire_z = 0;
GLdouble fire_zp = 0;
GLdouble fire_delay = 0;

int shots_fired = 0;

bool notdie[50];

class Room {


public:
	Motherboard mbModel;
	PowerSupply psModel;
	
	Room() {
		for (int i = 0; i < 50; i++)
			notdie[i] = true;
	}
	inline GLdouble ABS(GLdouble A)
	{
		if (A < 0)
			A = -A;
		return A;
	}
	// Hypotenuse Function
	inline GLdouble Hypot(GLdouble a, GLdouble b)
	{
		return sqrt((a*a) + (b*b));
	}
	AUX_RGBImageRec *LoadBMP(char *Filename)				// تحميل صورة
	{
		FILE *File = NULL;

		if (!Filename)
		{
			return NULL;
		}

		File = fopen(Filename, "r");

		if (File)
		{
			fclose(File);
			return auxDIBImageLoad(Filename);				// يرجع الصورة
		}

		return NULL;
	}
	/*
	منشان الفريمات و السرعة باللعبة







	*/
	// Create A Structure For The Timer Information     
	struct
	{
		__int64       frequency;          // Timer Frequency
		GLdouble            resolution;          // Timer Resolution
		unsigned long mm_timer_start;

		// Multimedia Timer Start Value
		unsigned long mm_timer_elapsed;      // Multimedia Timer Elapsed Time
		bool   performance_timer;

		// Using The Performance Timer?
		__int64       performance_timer_start;      // Performance Timer Start Value
		__int64       performance_timer_elapsed; // Performance Timer Elapsed Time
	} timer;

	// Initialize Our Timer
	void TimerInit(void)
	{
		memset(&timer, 0, sizeof(timer));
		// Clear Our Timer Structure
		// Check To See If A Performance Counter Is Available
		// If One Is Available The Timer Frequency Will Be Updated
		if (!QueryPerformanceFrequency((LARGE_INTEGER *)&timer.frequency))
		{
			// No Performace Counter Available
			timer.performance_timer = FALSE;                      // Set Performance Timer To FALSE
			timer.mm_timer_start = timeGetTime();                 // Use timeGetTime()
			timer.resolution = 1.0f / 1000.0f;                           // Set Our Timer Resolution To .001f
			timer.frequency = 1000;                                     // Set Our Timer Frequency To 1000
			timer.mm_timer_elapsed = timer.mm_timer_start; // Set The Elapsed Time
		}
		else
		{
			// Performance Counter Is Available, Use It Instead Of The Multimedia Timer
			// Get The Current Time And Store It In performance_timer_start
			QueryPerformanceCounter((LARGE_INTEGER *)&timer.performance_timer_start);
			timer.performance_timer = TRUE;    // Set Performance Timer To TRUE
											   // Calculate The Timer Resolution Using The Timer Frequency
			timer.resolution = (GLdouble)(((double)1.0f) / ((double)timer.frequency));
			// Set The Elapsed Time To The Current Time
			timer.performance_timer_elapsed = timer.performance_timer_start;
		}
	}

	// Get Time In Milliseconds
	inline GLdouble TimerGetTime()
	{
		__int64 time;                                  // 'time' Will Hold A 64 Bit Integer
		if (timer.performance_timer)           // Are We Using The Performance Timer?
		{
			QueryPerformanceCounter((LARGE_INTEGER *)&time); // Current Performance Time
															 // Return The Time Elapsed since TimerInit was called
			return ((GLdouble)(time - timer.performance_timer_start) * timer.resolution)*1000.0f;
		}
		else
		{
			// Return The Time Elapsed since TimerInit was called
			return ((GLdouble)(timeGetTime() - timer.mm_timer_start) * timer.resolution)*1000.0f;
		}
	}


	int LoadGLTextures()
	{
		int Status = FALSE;
		AUX_RGBImageRec *TextureImage[1];
		memset(TextureImage, 0, sizeof(void *) * 1);
		if (TextureImage[0] = LoadBMP("texture/floor.bmp"))
		{
			Status = TRUE;
			glGenTextures(1, &texture[1]);				//انشاء الاكساء

			glBindTexture(GL_TEXTURE_2D, texture[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}

		if (TextureImage[0] = LoadBMP("texture/wall.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[2]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}
		if (TextureImage[0] = LoadBMP("cpu.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[3]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[3]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}





		if (TextureImage[0] = LoadBMP("texture/crosshair.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[15]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[15]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}


		if (TextureImage[0] = LoadBMP("texture/ceiling.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[17]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[17]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}

		//// Texture for copper material
		if (TextureImage[0] = LoadBMP("copper.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[4]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[4]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}

		//// Texture for gc_slot_tex
		if (TextureImage[0] = LoadBMP("gc_slot_tex.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[5]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[5]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}

		//// Texture for ics
		if (TextureImage[0] = LoadBMP("ic_text.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[6]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[6]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}

		//// Texture for pci slots
		if (TextureImage[0] = LoadBMP("pci_slot_tex.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[7]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[7]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}

		//// Texture for metal Materials
		if (TextureImage[0] = LoadBMP("metal_tex.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[8]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[8]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}


		if (TextureImage[0] = LoadBMP("ic_tex.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[10]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[10]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}

		if (TextureImage[0] = LoadBMP("flat.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[11]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[11]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}

		if (TextureImage[0] = LoadBMP("cylinder.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[12]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[12]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}

		if (TextureImage[0] = LoadBMP("transformer_1.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[13]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[13]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}

		if (TextureImage[0] = LoadBMP("transformer_2.bmp"))	// Load Particle Texture
		{
			Status = TRUE;								// Set The Status To TRUE
			glGenTextures(1, &texture[14]);				// Create One Texture

														// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[14]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}

		if (TextureImage[0] = LoadBMP("texture/PlayAgain.bmp"))//data/bricksred.bmp")) //"Data/Wall.bmp"))
		{
			Status = TRUE;									// Set The Status To TRUE

			glGenTextures(1, &texture[18]);					// Create Three Textures

															// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[18]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}

		if (TextureImage[0])								// If Texture Exists
		{
			if (TextureImage[0]->data)						// If Texture Image Exists
			{
				free(TextureImage[0]->data);				// Free The Texture Image Memory
			}

			free(TextureImage[0]);							// Free The Image Structure
		}

		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit



		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if (TextureImage[0] = LoadBMP("texture/Exit.bmp"))//data/bricksred.bmp")) //"Data/Wall.bmp"))
		{
			Status = TRUE;									// Set The Status To TRUE

			glGenTextures(1, &texture[19]);					// Create Three Textures

															// Create MipMapped Texture
			glBindTexture(GL_TEXTURE_2D, texture[19]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}
		//// Texture for CPU upper layer


		// Bind the texture

		//texture[4] = LoadTexture("copper.bmp");
		//texture[5] = LoadTexture("gc_slot_tex.bmp");
		//texture[7] = LoadTexture("pci_slot_tex.bmp");
		//texture[6] = LoadTexture("ic_tex.bmp");
		//texture[8] = LoadTexture("metal_tex.bmp");
		//texture[9] = LoadTexture("corei7.bmp");

		mbModel = Motherboard(); // initialize motherboard model
		mbModel.mbTexture[0] = texture[4];
		mbModel.mbTexture[1] = texture[5];
		mbModel.mbTexture[3] = texture[10];	// set black texture for pci slots
		mbModel.mbTexture[4] = texture[6];
		mbModel.mbTexture[5] = texture[8];
		//mbModel.mbTexture[6] = texture[9];


		psModel = PowerSupply();	// initialize Power supply model
		psModel.psTexture[0] = texture[11];
		psModel.psTexture[1] = texture[12];
		psModel.psTexture[2] = texture[13];
		psModel.psTexture[3] = texture[14];

		if (TextureImage[0])							// If Texture Exists
		{
			if (TextureImage[0]->data)					// If Texture Image Exists
			{
				free(TextureImage[0]->data);			// Free The Texture Image Memory
			}
			free(TextureImage[0]);						// Free The Image Structure
		}

		return Status;									// Return The Status
	}

	// Draw ants
	GLvoid buildelements() {
		capacitorModel->pos.y = -14;
		capacitorModel->pos.z = 120;
		capacitorModel->scale = 10;

		capacitorModel->pos.x = 120;
		capacitorModel->Draw();
		capacitorModel->pos.x = 140;
		capacitorModel->Draw();
		capacitorModel->pos.x = 160;
		capacitorModel->Draw();
		capacitorModel->pos.x = 180;
		capacitorModel->Draw();
		capacitorModel->pos.x = 200;
		capacitorModel->Draw();
		capacitorModel->pos.x = 220;
		capacitorModel->Draw();
		capacitorModel->pos.x = 240;
		capacitorModel->Draw();
		capacitorModel->pos.x = 260;
		capacitorModel->Draw();
		capacitorModel->pos.x = 280;
		capacitorModel->Draw();

		capacitorModel->pos.z = 110;
		capacitorModel->pos.x = 120;
		capacitorModel->Draw();
		capacitorModel->pos.x = 140;
		capacitorModel->Draw();
		capacitorModel->pos.x = 160;
		capacitorModel->Draw();
		capacitorModel->pos.x = 180;
		capacitorModel->Draw();
		capacitorModel->pos.x = 200;
		capacitorModel->Draw();
		capacitorModel->pos.x = 220;
		capacitorModel->Draw();
		capacitorModel->pos.x = 240;
		capacitorModel->Draw();
		capacitorModel->pos.x = 260;
		capacitorModel->Draw();
		capacitorModel->pos.x = 280;
		capacitorModel->Draw();

		capacitorModel->pos.z = 400;
		capacitorModel->pos.x = 120;
		capacitorModel->Draw();
		capacitorModel->pos.x = 140;
		capacitorModel->Draw();
		capacitorModel->pos.x = 160;
		capacitorModel->Draw();
		capacitorModel->pos.x = 180;
		capacitorModel->Draw();
		capacitorModel->pos.x = 200;
		capacitorModel->Draw();
		capacitorModel->pos.x = 220;
		capacitorModel->Draw();
		capacitorModel->pos.x = 240;
		capacitorModel->Draw();
		capacitorModel->pos.x = 260;
		capacitorModel->Draw();
		capacitorModel->pos.x = 280;
		capacitorModel->Draw();

		capacitorModel->pos.z = 410;
		capacitorModel->pos.x = 120;
		capacitorModel->Draw();
		capacitorModel->pos.x = 140;
		capacitorModel->Draw();
		capacitorModel->pos.x = 160;
		capacitorModel->Draw();
		capacitorModel->pos.x = 180;
		capacitorModel->Draw();
		capacitorModel->pos.x = 200;
		capacitorModel->Draw();
		capacitorModel->pos.x = 220;
		capacitorModel->Draw();
		capacitorModel->pos.x = 240;
		capacitorModel->Draw();
		capacitorModel->pos.x = 260;
		capacitorModel->Draw();
		capacitorModel->pos.x = 280;
		capacitorModel->Draw();




		tree1->pos.z = 240;
		tree2->pos.z = 250;
		tree3->pos.z = 260;

		tree1->pos.x = 120;
		tree1->Draw();
		tree2->pos.x = 120;
		tree2->Draw();
		tree3->pos.x = 120;
		tree3->Draw();

		tree1->pos.z = 240;
		tree2->pos.z = 250;
		tree3->pos.z = 260;

		tree1->pos.x = 450;
		tree1->Draw();
		tree2->pos.x = 450;
		tree2->Draw();
		tree3->pos.x = 450;
		tree3->Draw();





		/*
		This fuction contains all the required
		functionality to draw motherboard components
		*/
		drawMotherbordComponents();

		/*
		This fuction contains all the required
		functionality to draw power supply components
		*/
		drawPowerSupplyComponents();


	}

	GLvoid drawPowerSupplyComponents() {

		glPushMatrix();
		glTranslatef(0, 2000, 0);

		// Draw feuse on the board
		for (GLuint z = 0; z < 5; z++) {
			glPushMatrix();
			glTranslatef(MAX_Cells / 4 * 0.4, 5, MAX_Cells / 4 * 0.45 + z * 23);
			glScalef(2.5, 2.5, 2.5);
			psModel.feuse();
			glPopMatrix();
		}

		// Draw small 
		for (GLuint x = 0; x < 3; x++) {
			glPushMatrix();
			glTranslatef(MAX_Cells / 4 * 0.4 + x * 17, 0, MAX_Cells / 4 * 0.2);
			psModel.smallCapacitor();
			glPopMatrix();
		}

		// Draw small and big capacitors
		for (GLuint x = 0; x < 3; x++) {
			glPushMatrix();
			glTranslatef(MAX_Cells / 4 * 0.3 + x * 20, 0, MAX_Cells / 4 * 0.9);
			psModel.bigCapacitor();
			glPopMatrix();
		}

		// Draw small ICs
		for (GLuint x = 0; x < 3; x++) {
			for (GLuint z = 0; z < 8; z++) {
				glPushMatrix();
				glTranslatef(MAX_Cells / 4 * 0.8 + x*+3, 2, MAX_Cells / 4 * 0.3 + z * 10);
				psModel.drawIntegratedCircuit();
				glPopMatrix();
			}
		}


		// Draw Transformer
		glPushMatrix();
		glTranslatef(MAX_Cells / 4 * 0.5 , 5, MAX_Cells / 4 * 0.5 );
		psModel.drawTransformer();
		glPopMatrix();

		glColor4b(1, 1, 1, 1);
		glPopMatrix();
	}

	// This function is responsible for 
	// drawing motherboard components 

	GLvoid drawMotherbordComponents() {

		// Move up to the next level
		glPushMatrix();
		glTranslatef(0, 1000, 0);

		// Draw Ram Slots
		glPushMatrix();
		glTranslatef(MAX_Cells *0.6, 0, MAX_Cells *0.4);
		glRotatef(90, 0, 1, 0);
		glScalef(MAX_Cells*0.08, MAX_Cells*0.05, MAX_Cells*0.1);
		mbModel.ramSlots();
		glPopMatrix();

		// Draw Rom IC
		glPushMatrix();
		glTranslatef(MAX_Cells *0.6, 0, MAX_Cells *0.4);
		glRotatef(90, 0, 1, 0);
		glScalef(MAX_Cells*0.08, MAX_Cells*0.05, MAX_Cells*0.1);
		mbModel.rom();
		glPopMatrix();

		// Draw South Bridge
		glPushMatrix();
		glTranslatef(MAX_Cells *0.6, 0, MAX_Cells *0.4);
		glRotatef(90, 0, 1, 0);
		glScalef(MAX_Cells*0.08, MAX_Cells*0.05, MAX_Cells*0.1);
		glTranslatef(-3, 0, 2);
		glScalef(0.7, 0.7, 0.7);
		mbModel.bridge();
		glPopMatrix();

		// Draw Graphics Card Slot
		glPushMatrix();
		glTranslatef(MAX_Cells *0.3, 0, MAX_Cells *0.15);
		glRotatef(90, 0, 1, 0);
		glScalef(MAX_Cells*0.1, MAX_Cells*0.05, MAX_Cells*0.08);
		mbModel.graphicsCardSlot();
		glPopMatrix();

		// Draw PCI Slots
		glPushMatrix();
		glTranslatef(MAX_Cells *0.3, 0, MAX_Cells *0.2);
		glRotatef(90, 0, 1, 0);
		glScalef(MAX_Cells*0.1, MAX_Cells*0.05, MAX_Cells*0.08);
		mbModel.pciSlots();
		glPopMatrix();

		// Draw IO Ports 
		glPushMatrix();
		glTranslatef(MAX_Cells *0.24, 0, MAX_Cells *0.43);
		glRotatef(90, 0, 1, 0);
		glScalef(MAX_Cells*0.1, MAX_Cells*0.05, MAX_Cells*0.08);
		mbModel.IOPorts();
		glPopMatrix();

		// Draw North Bridge  
		glPushMatrix();
		glTranslatef(MAX_Cells *0.5, 0, MAX_Cells *0.5);
		glRotatef(90, 0, 1, 0);
		glScalef(MAX_Cells*0.1, MAX_Cells*0.05, MAX_Cells*0.08);
		mbModel.bridge();
		glPopMatrix();

		// Draw Motherboard Power connectors   
		glPushMatrix();
		glTranslatef(MAX_Cells *0.75, 0, MAX_Cells *0.4);
		glRotatef(90, 0, 1, 0);
		glScalef(MAX_Cells*0.1, MAX_Cells*0.05, MAX_Cells*0.08);
		mbModel.motherboardPowerConnector();
		glPopMatrix();

		// Draw CPU Model
		glPushMatrix();
		glTranslatef(MAX_Cells *0.5, 0, MAX_Cells *0.45);
		glRotatef(90, 0, 1, 0);
		glScalef(MAX_Cells*0.1, MAX_Cells*0.05, MAX_Cells*0.08);
		mbModel.CPU();
		glPopMatrix();

		// Draw Some Capacitors Over Cpu
		for (int x = 0; x <= 90; x += 30) {
			capacitorModel->pos.x = MAX_Cells*0.35 + x;
			capacitorModel->pos.z = MAX_Cells*0.08;
			capacitorModel->Draw();
		}


		glPopMatrix();
	}

	// This function will generate a ant at specific location
	void BuildAnta(FLOAT x, FLOAT y, FLOAT z, int number) {
		ANT->scale = 0.3;
		if (notdie[number]) {
			ANT->pos.y = y;
			ANT->pos.x = x;
			ANT->pos.z = z;
			ANT->Draw();

		}
		//if (number >= 6) {	// these ants are in the second level

		//}
	}

	GLvoid BuildAnts() {

		BuildAnta(120, 4, 200, 0);
		BuildAnta(160, 4, 400, 1);
		BuildAnta(350, 4, 160, 2);
		BuildAnta(400, 4, 240, 3);
		BuildAnta(256 + 25, 4, 256 + 30, 4);
		BuildAnta(256 - 25, 4, 256 + 30, 5);


		BuildAnta(120, 1004, 200, 6);
		BuildAnta(160, 1004, 400, 7);
		BuildAnta(350, 1004, 160, 8);
		BuildAnta(400, 1004, 240, 9);




	}


	void isdie(GLdouble x, GLdouble y, GLdouble z) {
		if (ytrans2>0 && ytrans2<1000)

		if (y >= 0 && y <= 10) {
			if (x > 110 && x < 130 && z>190 && z < 210)
				notdie[0] = false;
			if (x > 150 && x < 170 && z>390 && z < 410)
				notdie[1] = false;
			if (x > 340 && x < 360 && z>150 && z < 170)
				notdie[2] = false;
			if (x > 390 && x < 410 && z>230 && z < 250)
				notdie[3] = false;
			if (x > 256 + 15 && x < 256 + 35 && z>256 + 19 && z < 256 + 39)
				notdie[4] = false;
			if (x > 256 - 35 && x < 256 - 15 && z>256 + 19 && z < 256 + 39)
				notdie[5] = false;


		}

		if (y >= 0 && y <= 10) {
			if (ytrans2>1000 && ytrans2<2000)

			if (x > 110 && x < 130 && z>190 && z < 210)
				notdie[6] = false;
			if (x > 150 && x < 170 && z>390 && z < 410)
				notdie[7] = false;
			if (x > 340 && x < 360 && z>150 && z < 170)
				notdie[8] = false;
			if (x > 390 && x < 410 && z>230 && z < 250)
				notdie[9] = false;

		}
	}



	GLvoid BuildLists()
	{
		ROOM = glGenLists(1);									// Generate 2 Different Lists
		glNewList(ROOM, GL_COMPILE);							// Start With The Box List

		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glColor4d(1, 1, 1, 1.f);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		// Layer 1 Represent Graphics Card
		glBegin(GL_QUADS);
		glTexCoord2d(35, 35);  glVertex3d(MAX_Cells, 0, MAX_Cells);
		glTexCoord2d(35, 0);  glVertex3d(MAX_Cells, 0, 0);
		glTexCoord2d(0, 0);  glVertex3d(0, 0, 0);
		glTexCoord2d(0, 35);  glVertex3d(0, 0, MAX_Cells);
		glEnd();

		// Layer 2 Represent Motherboard
		glBegin(GL_QUADS);
		glTexCoord2d(35, 35);  glVertex3d(MAX_Cells, 1000, MAX_Cells);
		glTexCoord2d(35, 0);  glVertex3d(MAX_Cells, 1000, 0);
		glTexCoord2d(0, 0);  glVertex3d(0, 1000, 0);
		glTexCoord2d(0, 35);  glVertex3d(0, 1000, MAX_Cells);
		glEnd();

		// Layer 3 Represent Power Supply
		glBindTexture(GL_TEXTURE_2D, texture[11]);
		glDisable(GL_BLEND);
		glBegin(GL_QUADS);
		glColor4d(0, 1, 0, 1.f);
		glTexCoord2d(10, 10);  glVertex3d(MAX_Cells / 4, 2000, MAX_Cells / 4);
		glTexCoord2d(10, 0);  glVertex3d(MAX_Cells / 4, 2000, 0);
		glTexCoord2d(0, 0);  glVertex3d(0, 2000, 0);
		glTexCoord2d(0, 10);  glVertex3d(0, 2000, MAX_Cells / 4);
		glEnd();
		glEnable(GL_BLEND);

		// Layer 4 Represent Keyboard
		glBegin(GL_QUADS);
		glTexCoord2d(35, 35);  glVertex3d(MAX_Cells, 3000, MAX_Cells);
		glTexCoord2d(35, 0);  glVertex3d(MAX_Cells, 3000, 0);
		glTexCoord2d(0, 0);  glVertex3d(0, 3000, 0);
		glTexCoord2d(0, 35);  glVertex3d(0, 3000, MAX_Cells);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2d(35, 35);  glVertex3d(MAX_Cells, 4000, MAX_Cells);
		glTexCoord2d(35, 0);  glVertex3d(MAX_Cells, 4000, 0);
		glTexCoord2d(0, 0);  glVertex3d(0, 4000, 0);
		glTexCoord2d(0, 35);  glVertex3d(0, 4000, MAX_Cells);
		glEnd();

		// buildelements();

		//BuildAnt();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindTexture(GL_TEXTURE_2D, texture[3]);

		glColor4d(1, 1, 1, 1);

		glBegin(GL_QUADS);
		glTexCoord2d(1, 1);  glVertex3d(MAX_Cells / 2 + 26, 8, MAX_Cells / 2 + 26);
		glTexCoord2d(1, 0);  glVertex3d(MAX_Cells / 2 + 26, 8, MAX_Cells / 2 - 26);
		glTexCoord2d(0, 0);  glVertex3d(MAX_Cells / 2 - 26, 8, MAX_Cells / 2 - 26);
		glTexCoord2d(0, 1);  glVertex3d(MAX_Cells / 2 - 26, 8, MAX_Cells / 2 + 26);
		glEnd();

		glColor4d(.75f, .75f, .75f, 1);

		glBegin(GL_QUADS);
		glTexCoord2d(1, 1);  glVertex3d(MAX_Cells / 2 + 26, 8, MAX_Cells / 2 - 26);
		glTexCoord2d(1, 0);  glVertex3d(MAX_Cells / 2 + 26, 0, MAX_Cells / 2 - 26);
		glTexCoord2d(0, 0);  glVertex3d(MAX_Cells / 2 - 26, 0, MAX_Cells / 2 - 26);
		glTexCoord2d(0, 1);  glVertex3d(MAX_Cells / 2 - 26, 8, MAX_Cells / 2 - 26);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2d(1, 1);  glVertex3d(MAX_Cells / 2 + 26, 8, MAX_Cells / 2 + 26);
		glTexCoord2d(1, 0);  glVertex3d(MAX_Cells / 2 + 26, 0, MAX_Cells / 2 + 26);
		glTexCoord2d(0, 0);  glVertex3d(MAX_Cells / 2 - 26, 0, MAX_Cells / 2 + 26);
		glTexCoord2d(0, 1);  glVertex3d(MAX_Cells / 2 - 26, 8, MAX_Cells / 2 + 26);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2d(1, 1);  glVertex3d(MAX_Cells / 2 - 26, 8, MAX_Cells / 2 + 26);
		glTexCoord2d(1, 0);  glVertex3d(MAX_Cells / 2 - 26, 0, MAX_Cells / 2 + 26);
		glTexCoord2d(0, 0);  glVertex3d(MAX_Cells / 2 - 26, 0, MAX_Cells / 2 - 26);
		glTexCoord2d(0, 1);  glVertex3d(MAX_Cells / 2 - 26, 8, MAX_Cells / 2 - 26);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2d(1, 1);  glVertex3d(MAX_Cells / 2 + 26, 8, MAX_Cells / 2 + 26);
		glTexCoord2d(1, 0);  glVertex3d(MAX_Cells / 2 + 26, 0, MAX_Cells / 2 + 26);
		glTexCoord2d(0, 0);  glVertex3d(MAX_Cells / 2 + 26, 0, MAX_Cells / 2 - 26);
		glTexCoord2d(0, 1);  glVertex3d(MAX_Cells / 2 + 26, 8, MAX_Cells / 2 - 26);
		glEnd();

		glColor4d(.2f, .2f, .2f, 1);

		glBegin(GL_QUADS);
		glTexCoord2d(1, 1);  glVertex3d(MAX_Cells / 2 + 26, 0, MAX_Cells / 2 + 26);
		glTexCoord2d(1, 0);  glVertex3d(MAX_Cells / 2 + 26, 0, MAX_Cells / 2 - 26);
		glTexCoord2d(0, 0);  glVertex3d(MAX_Cells / 2 - 26, 0, MAX_Cells / 2 - 26);
		glTexCoord2d(0, 1);  glVertex3d(MAX_Cells / 2 - 26, 0, MAX_Cells / 2 + 26);
		glEnd();


		glEndList();
	}
	/*تابع الاصتدام الي يعالج داخله كل الحالات*/



	inline bool DetectCollision(GLdouble &cx, GLdouble &cy, GLdouble &cz, GLdouble padding)
	{
		bool Status = false;

		// Process Collision Detection for layer 3 Graphics Card
		// Which has a width of MAX_Cells and height (z) of MAX_Cells / 2
		if (cy > 1999 && cy < 2999) {

			if (cz > MAX_Cells / 4 - padding)
			{
				cz = MAX_Cells / 4 - padding;

				Status = true;
			}
			else if (cz < 0 + padding)
			{
				cz = 0 + padding;

				Status = true;
			}

			if (cx > MAX_Cells / 4 - padding)
			{
				cx = MAX_Cells / 4 - padding;

				Status = true;
			}
			else if (cx < 0 + padding)
			{
				cx = 0 + padding;

				Status = true;
			}

			return Status;
		}

		DetectCollisionitems();

		if (cx > MAX_Cells - padding)
		{
			cx = MAX_Cells - padding;

			Status = true;
		}
		else if (cx < 0 + padding)
		{
			cx = 0 + padding;

			Status = true;
		}

		if (cy < 0 + padding)
		{
			cy = 0 + padding;

			Status = true;
		}

		if (cz > MAX_Cells - padding)
		{
			cz = MAX_Cells - padding;

			Status = true;
		}
		else if (cz < 0 + padding)
		{
			cz = 0 + padding;

			Status = true;
		}



		return Status;
	}
	/*
	cx,cy,cz موقعك بالكاميرا
	px,pz (المركز)موقع الجسم
	sx,sz طول الجسم و عرضه
	padding بعدك عن الجسم منشان ما تصير قريب من الجسم
	*/
	/*inline bool DetectCollision2(GLdouble &cx, GLdouble &cy, GLdouble &cz, GLdouble padding )
	{
	bool Status = false;
	if (cx > MAX_Cells2-padding)
	{
	cx = MAX_Cells2-padding;

	Status = true;
	}
	else if (cx < 0+padding)
	{
	cx = 0+padding;

	Status = true;
	}

	/*if (cy > MAX_Cells/4-padding)
	{
	cy = MAX_Cells/4-padding;

	Status = true;
	}
	else if (cy < 0+padding)
	{
	cy = 0+padding;

	Status = true;
	}*/

	/* if (cz > MAX_Cells2-padding)
	{
	cz = MAX_Cells2-padding;

	Status = true;
	}
	else if (cz < 0+padding)
	{
	cz = 0+padding;

	Status = true;
	}
	}
	*/

	// This collision detextion code for layer 1
	inline bool DetectCollisionitem1(GLdouble &cx, GLdouble &cy, GLdouble &cz, GLdouble px, GLdouble pz, GLdouble sx, GLdouble sz, GLdouble padding) {
		bool Status = false;
		if (cy > 0 && cy < 999)
			if (cx<px + sx + padding &&cx > px - sx - padding  &&cz<pz + sz + padding &&cz > pz - sz - padding) {

				if (cx <px + sx + padding && cx > px + sx - padding)
				{
					cx = px + sx + padding;

				}
				else if (cx > px - sx - padding && cx < px - sx + padding)
				{
					cx = px - sx - padding;

				}
				if (cz <pz + sz + padding && cz > pz + sz - padding)
				{
					cz = pz + sz + padding;

				}
				else if (cz > pz - sz - padding && cz < pz - sz + padding)
				{
					cz = pz - sz - padding;

				}
				Status = true;
			}

		return Status;

	}

	// This collision detextion code for layer 2
	inline bool DetectCollisionitem2(GLdouble &cx, GLdouble &cy, GLdouble &cz, GLdouble px, GLdouble pz, GLdouble sx, GLdouble sz, GLdouble padding) {
		bool Status = false;
		if (cy >= 999 && cy <= 1999)
			if (cx<px + sx + padding &&cx > px - sx - padding  &&cz<pz + sz + padding &&cz > pz - sz - padding) {

				if (cx <px + sx + padding && cx > px + sx - padding)
				{
					cx = px + sx + padding;

				}
				else if (cx > px - sx - padding && cx < px - sx + padding)
				{
					cx = px - sx - padding;

				}
				if (cz <pz + sz + padding && cz > pz + sz - padding)
				{
					cz = pz + sz + padding;

				}
				else if (cz > pz - sz - padding && cz < pz - sz + padding)
				{
					cz = pz - sz - padding;

				}
				Status = true;
			}

		return Status;

	}

	// This collision detextion code for layer 3
	inline bool DetectCollisionitem3(GLdouble &cx, GLdouble &cy, GLdouble &cz, GLdouble px, GLdouble pz, GLdouble sx, GLdouble sz, GLdouble padding) {
		bool Status = false;
		if (cy > 1999 && cy < 2999)
			if (cx<px + sx + padding &&cx > px - sx - padding  &&cz<pz + sz + padding &&cz > pz - sz - padding) {

				if (cx <px + sx + padding && cx > px + sx - padding)
				{
					cx = px + sx + padding;

				}
				else if (cx > px - sx - padding && cx < px - sx + padding)
				{
					cx = px - sx - padding;

				}
				if (cz <pz + sz + padding && cz > pz + sz - padding)
				{
					cz = pz + sz + padding;

				}
				else if (cz > pz - sz - padding && cz < pz - sz + padding)
				{
					cz = pz - sz - padding;

				}
				Status = true;
			}

		return Status;

	}

	// This collision detextion code for layer 4
	inline bool DetectCollisionitem4(GLdouble &cx, GLdouble &cy, GLdouble &cz, GLdouble px, GLdouble pz, GLdouble sx, GLdouble sz, GLdouble padding) {
		bool Status = false;
		if (cy > 3999 && cy < 4999)
			if (cx<px + sx + padding &&cx > px - sx - padding  &&cz<pz + sz + padding &&cz > pz - sz - padding) {

				if (cx <px + sx + padding && cx > px + sx - padding)
				{
					cx = px + sx + padding;

				}
				else if (cx > px - sx - padding && cx < px - sx + padding)
				{
					cx = px - sx - padding;

				}
				if (cz <pz + sz + padding && cz > pz + sz - padding)
				{
					cz = pz + sz + padding;

				}
				else if (cz > pz - sz - padding && cz < pz - sz + padding)
				{
					cz = pz - sz - padding;

				}
				Status = true;
			}

		return Status;

	}

	// This collision detextion code for layer 5
	inline bool DetectCollisionitem5(GLdouble &cx, GLdouble &cy, GLdouble &cz, GLdouble px, GLdouble pz, GLdouble sx, GLdouble sz, GLdouble padding) {
		bool Status = false;
		if (cy > 4999 && cy < 5999)
			if (cx<px + sx + padding &&cx > px - sx - padding  &&cz<pz + sz + padding &&cz > pz - sz - padding) {

				if (cx <px + sx + padding && cx > px + sx - padding)
				{
					cx = px + sx + padding;

				}
				else if (cx > px - sx - padding && cx < px - sx + padding)
				{
					cx = px - sx - padding;

				}
				if (cz <pz + sz + padding && cz > pz + sz - padding)
				{
					cz = pz + sz + padding;

				}
				else if (cz > pz - sz - padding && cz < pz - sz + padding)
				{
					cz = pz - sz - padding;

				}
				Status = true;
			}

		return Status;

	}
	/*معالجة صدم العناصر و يتم استدعاءه بالتابع الرئيسي الي فوق*/
	inline bool DetectCollisionitems() {
		int padding = 5;
		bool Status = false;
		DetectCollisionitem1(xtrans2, ytrans2, ztrans2, 220, 115, 90, 18, padding);
		DetectCollisionitem1(xtrans2, ytrans2, ztrans2, 220, 390, 90, 20, padding);
		DetectCollisionitem1(xtrans2, ytrans2, ztrans2, 120, 250, 20, 10, padding);
		DetectCollisionitem1(xtrans2, ytrans2, ztrans2, 450, 250, 20, 10, padding);
		DetectCollisionitem1(xtrans2, ytrans2, ztrans2, 256, 256, 40, 40, padding);



		if (notdie[0])
			DetectCollisionitem1(xtrans2, ytrans2, ztrans2, 120, 200, 4, 6, 1);
		if (notdie[1])
			DetectCollisionitem1(xtrans2, ytrans2, ztrans2, 160, 400, 4, 6, 1);
		if (notdie[2])
			DetectCollisionitem1(xtrans2, ytrans2, ztrans2, 350, 160, 4, 6, 1);
		if (notdie[3])
			DetectCollisionitem1(xtrans2, ytrans2, ztrans2, 400, 240, 4, 6, 1);
		if (notdie[4])
			DetectCollisionitem1(xtrans2, ytrans2, ztrans2, 512 + 25, 512 + 30, 4, 6, 1);
		if (notdie[5])
			DetectCollisionitem1(xtrans2, ytrans2, ztrans2, 512 - 25, 512 + 30, 4, 6, 1);



		/// TODO: Need to be more accurate collision
		DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 142, 180, 40, 15, padding);
		DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 412, 290, 20, 20, padding);
		DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 405, 367, 30, 30, padding);
		DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 500, 180, 20, 40, padding);
		DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 500, 90, 20, 40, padding);
		DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 400, 112, 40, 100, padding);
		DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 255, 290, 35, 50, padding);

		DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 97, 292, 75, 60, padding);


		DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 7, 75, 15, 75, padding);

		DetectCollisionitem2(xtrans2, ytrans2, ztrans2, (MAX_Cells *0.6) - 50, (MAX_Cells *0.4) - 125, 40, 60, padding);


		if (notdie[6])
			DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 120, 200, 4, 6, 1);
		if (notdie[7])
			DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 160, 400, 4, 6, 1);
		if (notdie[8])
			DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 350, 160, 4, 6, 1);
		if (notdie[9])
			DetectCollisionitem2(xtrans2, ytrans2, ztrans2, 400, 240, 4, 6, 1);

		return Status;

	}




	void Menu()
	{
		if (PlayAgain)
		{
			alpha1 += .025f;
			alpha2 -= .010f;
			alpha3 -= .010f;
			if (alpha1 >   .75f) alpha1 = .75f;
			if (alpha2 < .5f) alpha2 = .5f;
			if (alpha3 < .5f) alpha3 = .5f;
			alpha1ap += .5f - alpha1a;
			alpha1a += alpha1ap / 250;
			alpha2a = 0; alpha2ap = 0; alpha3a = 0; alpha3ap = 0;
		}
		else if (Options)
		{
			alpha1 -= .010f;
			alpha2 += .025f;
			alpha3 -= .010f;
			if (alpha1 < .5f) alpha1 = .5f;
			if (alpha2 >  .75f) alpha2 = .75f;
			if (alpha3 < .5f) alpha3 = .5f;
			alpha2ap += .5f - alpha2a;
			alpha2a += alpha2ap / 250;
			alpha1a = 0; alpha1ap = 0; alpha3a = 0; alpha3ap = 0;
		}
		else if (Exit)
		{
			alpha1 -= .010f;
			alpha2 -= .010f;
			alpha3 += .025f;
			if (alpha1 < .5f) alpha1 = .5f;
			if (alpha2 < .5f) alpha2 = .5f;
			if (alpha3 > .75f) alpha3 = .75f;
			alpha3ap += .5f - alpha3a;
			alpha3a += alpha3ap / 250;
			alpha1a = 0; alpha1ap = 0; alpha2a = 0; alpha2ap = 0;
		}

		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);

		int scalemenu = 2;

		menuZ -= .1;
		if (menuZ < -9) menuZ = -9;

		glLoadIdentity();
		glTranslatef(0, 0, menuZ - 1);



		glBindTexture(GL_TEXTURE_2D, texture[18]);
		glColor4f(1, 1, 1, (alpha1 + alpha1a) / 2);
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(1, 1); glVertex3f(1.0*scalemenu, (.4 + .4)*scalemenu, 0);
		glTexCoord2f(1, 0); glVertex3f(1.0*scalemenu, .4*scalemenu, 0);
		glTexCoord2f(0, 1); glVertex3f(-1.0*scalemenu, (.4 + .4)*scalemenu, 0);
		glTexCoord2f(0, 0); glVertex3f(-1.0*scalemenu, .4*scalemenu, 0);
		glEnd();


		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glColor4f(1, 1, 1, (alpha2 + alpha2a) / 2);
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(1, 1); glVertex3f(1.0*scalemenu, .4*scalemenu, 0);
		glTexCoord2f(1, 0); glVertex3f(1.0*scalemenu, 0, 0);
		glTexCoord2f(0, 1); glVertex3f(-1.0*scalemenu, .4*scalemenu, 0);
		glTexCoord2f(0, 0); glVertex3f(-1.0*scalemenu, 0, 0);
		glEnd();



		glBindTexture(GL_TEXTURE_2D, texture[19]);
		glColor4f(1, 1, 1, (alpha3 + alpha3a) / 2);
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(1, 1); glVertex3f(1.0*scalemenu, (.4 - .4)*scalemenu, 0);
		glTexCoord2f(1, 0); glVertex3f(1.0*scalemenu, (0 - .4)*scalemenu, 0);
		glTexCoord2f(0, 1); glVertex3f(-1.0*scalemenu, (.4 - .4)*scalemenu, 0);
		glTexCoord2f(0, 0); glVertex3f(-1.0*scalemenu, (0 - .4)*scalemenu, 0);
		glEnd();


		glEnable(GL_DEPTH_TEST);
	}







};

Room obj;



GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	WIDTH = width;
	HEIGHT = height;
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// Calculate The Aspect Ratio Of The Window
	glLoadIdentity();									// Reset The Modelview Matrix
	gluPerspective(60.0f, (GLdouble)width / (GLdouble)height, 1.0f, 1250.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

//float arr [4] ={1.0,1.0,1.0,-1};

GLdouble Time1;
GLdouble Time2;
GLdouble DiffTime;
GLdouble StartTime;

// initialize Lighting properties
GLfloat light_position[] = { xtrans2, ytrans2, ztrans2, 1.0 };
GLfloat light_ambient_color[] = { 1, 1, 1, 1.0 };
GLfloat light_diffuse_color[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular_color[] = { 1.0, 1.0, 1.0, 1.0 };

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{     // glEnable(GL_LIGHTING);
	  // glEnable(GL_LIGHT5);

	// Add lighting properties to the light0
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_specular_color);


	/// TODO: Enable Lighting here
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);

	capacitorModel = new Model_3DS();
	capacitorModel->Load("Capacitor-.3ds");

	tree1 = new Model_3DS();
	tree1->Load("1.3ds");
	tree2 = new Model_3DS();
	tree2->Load("2.3ds");
	tree3 = new Model_3DS();
	tree3->Load("3.3ds");

	ANT = new Model_3DS();
	ANT->Load("ANT.3DS");



	GLTexture cap;
	cap.LoadBMP("cap.bmp");
	capacitorModel->Materials[1].tex = cap;
	tree2->Materials[1].tex = cap;
	tree3->Materials[1].tex = cap;
	GLTexture ant;
	ant.LoadBMP("black.bmp");
	ANT->Materials[0].tex = ant;
	ANT->Materials[1].tex = ant;



	if (!obj.LoadGLTextures())								// Jump To Texture Loading Routine
		return false;

	obj.BuildLists();

	glEnable(GL_TEXTURE_2D);					// Enable Texture Mapping
	glClearColor(0, 0, 0, 1.0f);				// Black Background
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	obj.TimerInit(); //initialize timer
					 // BuildFont();   
	StartTime = obj.TimerGetTime() / 1000;
	return TRUE;										// Initialization Went OK
}

inline int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	obj.DetectCollision(xtrans2, ytrans2, ztrans2, 0);

	/*للحركة*/
	XP *= 0.8f;  //سرعة المشي
	ZP *= 0.8f;
	xtrans2 += XP / 10;
	ztrans2 += ZP / 10;

	xtrans = -xtrans2;
	ztrans = -ztrans2;




	/*لسرعة تحريك الماوس*/
	zprot *= .9f;
	_heading += zprot;
	heading = mouse_3d_x + _heading;

	yrot = heading;

	sceneroty = 360.0f - yrot;

	glLoadIdentity();

	glRotated(mouse_3d_y, 1.f, 0, 0);//الحركة فوق و تحت
	glRotated(sceneroty, 0, 1.f, 0);//الحركة يمين و يسار 

	glTranslated(xtrans, -ytrans2, ztrans);  //الحركة 

	glCallList(ROOM);
	obj.BuildAnts();
	obj.buildelements();
	// Determine if you have fired a weapon
	if (isFire)
	{
		PlaySound("rifle.wav", NULL, SND_ASYNC | SND_FILENAME);
		shots_fired++;
		if (shots_fired > 45 - 1) shots_fired = 0;
		isFireComplete = false;
		isFire = false;

		/*مكان المقذوف*/
		fire_x = -xtrans;
		fire_y = 10;
		fire_z = -ztrans;

		fire_xp = -(GLdouble)sin(heading*piover180) / 5;
		fire_yp = -(GLdouble)tan(mouse_3d_y*piover180) / 5;
		fire_zp = -(GLdouble)cos(heading*piover180) / 5;

	}
	int fire_counter = 0;

	// Begin calculations for the projectile
	while (!isFireComplete)
	{
		fire_counter++;
		fire_x += fire_xp;
		fire_y += fire_yp;
		fire_z += fire_zp;

		obj.isdie(fire_x, fire_y, fire_z);
		if (obj.DetectCollision(fire_x, fire_y, fire_z, 0))
		{
			isFireComplete = true;
			if (true)
			{


			}

		}
		else if (fire_counter > 10000)
		{
			isFireComplete = true;
		}
	}




	glEnable(GL_DEPTH_TEST);

	// Crosshair  
	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();
	glTranslated(0.0f, 0.0f, -35.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[15]);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 1); glVertex2f(1, 1);
	glTexCoord2d(1, 0); glVertex2f(1, -1);
	glTexCoord2d(0, 0); glVertex2f(-1, -1);
	glTexCoord2d(0, 1); glVertex2f(-1, 1);
	glEnd();

	glEnable(GL_DEPTH_TEST);


	//  ESTABLISH A FPS FRAMERATE COUNTER

	Time2 = obj.TimerGetTime() / 1000;
	DiffTime = obj.ABS(Time2 - Time1);
	while (DiffTime < .015f) // .015 = 66 frames per second
	{
		Sleep(1);
		Time2 = obj.TimerGetTime() / 1000;
		DiffTime = obj.ABS(Time2 - Time1);
	}
	Time1 = obj.TimerGetTime() / 1000;


	return TRUE;										// Keep Going
}
GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{



	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	HINSTANCE	hInstance;				// Holds The Instance Of The Application
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style


	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;						// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	// Windows Style
	}

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,			// Extended Style For The Window
		"OpenGL",			// Class Name
		title,				// Window Title
		dwStyle,			// Window Style
		0, 0,				// Window Position
		width, height,		// Selected Width And Height
		NULL,				// No Parent Window
		NULL,				// No Menu
		hInstance,			// Instance
		NULL)))				// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	if (uMsg == WM_MOUSEMOVE)
	{
		if (LOWORD(lParam) > 370) SetCursorPos(10, (int)mouse_y), mouse_wrap_x--;
		else if (LOWORD(lParam) < 10) SetCursorPos(370, (int)mouse_y), mouse_wrap_x++;

		if (HIWORD(lParam) > 370) SetCursorPos((int)mouse_x, 10), mouse_wrap_x--;
		else if (HIWORD(lParam) < 10) SetCursorPos((int)mouse_x, 370), mouse_wrap_x++;

		if (obj.ABS(mouse_x - LOWORD(lParam)) > 300)
		{
			if (mouse_x > 360 / 2)
				mouse_3d_x += ((mouse_x - 360) - LOWORD(lParam)) / sensitivity;
			else if (LOWORD(lParam) > 360 / 2)
				mouse_3d_x += (mouse_x - (LOWORD(lParam) - 360)) / sensitivity;
		}
		else
		{
			mouse_3d_x += (mouse_x - LOWORD(lParam)) / sensitivity;
		}

		if (mouse_3d_x > 360) mouse_3d_x = 0;
		else if (mouse_3d_x < 0) mouse_3d_x = 360;

		if (invert_mouse)
		{
			if (obj.ABS(mouse_y - HIWORD(lParam)) > 300)
			{
				if (mouse_y > 360 / 2)
					mouse_3d_y -= (HIWORD(lParam) - (mouse_y - 360)) / sensitivity;
				else if (LOWORD(lParam) > 360 / 2)
					mouse_3d_y -= ((HIWORD(lParam) - 360) - mouse_y) / sensitivity;
			}
			else
			{
				mouse_3d_y -= (HIWORD(lParam) - mouse_y) / sensitivity;
			}
		}
		else
		{
			if (obj.ABS(mouse_y - HIWORD(lParam)) > 300)
			{
				if (mouse_y > 360 / 2)
					mouse_3d_y -= ((mouse_y - 360) - HIWORD(lParam)) / sensitivity;
				else if (LOWORD(lParam) > 360 / 2)
					mouse_3d_y -= (mouse_y - (HIWORD(lParam) - 360)) / sensitivity;
			}
			else
			{
				mouse_3d_y -= (mouse_y - HIWORD(lParam)) / sensitivity;
			}
		}

		if (mouse_3d_x > 360) mouse_3d_x = 0;
		else if (mouse_3d_x < 0) mouse_3d_x = 360;

		if (mouse_3d_y > 85) mouse_3d_y = 85;
		else if (mouse_3d_y < -85) mouse_3d_y = -85;

		mouse_x = LOWORD(lParam);
		mouse_y = HIWORD(lParam);
	}

	else if (uMsg == WM_LBUTTONDOWN)
	{
		if (!(is_shock_rifle))
			isFire = true;
	}
	else if (uMsg == WM_ACTIVATE)							// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))					// Check Minimization State
		{
			active = TRUE;						// Program Is Active
		}
		else
		{
			active = FALSE;						// Program Is No Longer Active
		}

	}

	else if (uMsg == WM_SYSCOMMAND)							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:					// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?

			return 0;							// Prevent From Happening
		}
	}

	else if (uMsg == WM_CLOSE)								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
	}

	else if (uMsg == WM_KEYDOWN)							// Is A Key Being Held Down?
	{
		keys[wParam] = TRUE;					// If So, Mark It As TRUE
	}

	else if (uMsg == WM_KEYUP)								// Has A Key Been Released?
	{
		keys[wParam] = FALSE;					// If So, Mark It As FALSE
	}

	else if (uMsg == WM_SIZE)								// Resize The OpenGL Window
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
	}


	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int is_Fired = 0;

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{

	MSG		msg;									// Windows Message Structure

													// Ask The User Which Screen Mode They Prefer  

	fullscreen = true;

	if (!CreateGLWindow("OUR GAMES", 1366, 768, 32, fullscreen))
	{
		return 0;
	}

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done = TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{

				if ((!notdie[0] && !notdie[1] && !notdie[2] && !notdie[3] && !notdie[4] && !notdie[5] && !notdie[6] && !notdie[7] && !notdie[8] && !notdie[9]))
					MENU = true;
				if (MENU) {
					if (win)
						PlaySound("YouWin.wav", NULL, SND_ASYNC | SND_FILENAME);
					obj.Menu();
					win = false;
				}
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)

				is_Fired--;
				if (is_Fired < 0) is_Fired = 0;
				if (MENU)
				{

					if (keys[VK_UP] && !up)
					{
						PlaySound("type.wav", NULL, SND_ASYNC);
						up = true;
						item--;
						if (item < 1) item = 3;
					}
					if (!keys[VK_UP])
					{
						up = false;
					}
					if (keys[VK_DOWN] && !dn)
					{
						PlaySound("type.wav", NULL, SND_ASYNC);
						dn = true;
						item++;
						if (item > 3) item = 1;
					}
					if (!keys[VK_DOWN])
					{
						dn = false;
					}
					if (keys[VK_RETURN])
					{
						rn = true;
						Selection = true;
						if (PlayAgain) {
							xtrans2 = MAX_Cells *0.6 - 20;
							ytrans2 = 10;
							ztrans2 = MAX_Cells *0.4 - 20;
							MENU = !MENU;
							for (int i = 0; i < 10; i++)notdie[i] = true;
						}

						else if (Exit)
							done = true;
						else if (Options)
							MENU = !MENU;

						win = true;
					}
					if (!keys[VK_RETURN])
					{
						rn = false;
					}


					switch (item)
					{
					case 1: PlayAgain = true, Options = false, Exit = false; break;
					case 2: PlayAgain = true, Options = false, Exit = false; break;
					case 3: PlayAgain = false, Options = false, Exit = true; break;
					}

					//SwapBuffers(hDC);					// Swap Buffers (Double Buffering)

				}
				else
				{
					if (keys[VK_UP])  // Move forwards
					{
						if (ytrans2 > 1999 && ytrans2 < 2999) {
							XP -= (GLdouble)sin(heading*piover180) * 2.5f;
							ZP -= (GLdouble)cos(heading*piover180) * 2.5f;
						}
						else {

							XP -= (GLdouble)sin(heading*piover180) * 5.0f;
							ZP -= (GLdouble)cos(heading*piover180) * 5.0f;
						}
					}
					else if (keys['W'])  // Move forwards
					{
						if (ytrans2 > 1999 && ytrans2 < 2999) {
							XP -= (GLdouble)sin(heading*piover180) * 2.5f;
							ZP -= (GLdouble)cos(heading*piover180) * 2.5f;
						}
						else {
							XP -= (GLdouble)sin(heading*piover180) * 5.0f;
							ZP -= (GLdouble)cos(heading*piover180) * 5.0f;
						}
					}

					if (keys[VK_DOWN]) // Move backwards
					{
						if (ytrans2 > 1999 && ytrans2 < 2999) {
							XP += (GLdouble)sin(heading*piover180) * 2.5f;
							ZP += (GLdouble)cos(heading*piover180) * 2.5f;
						}
						else {

							XP += (GLdouble)sin(heading*piover180) * 5.0f;
							ZP += (GLdouble)cos(heading*piover180) * 5.0f;
						}
					}
					else if (keys['S']) // Move backwards
					{
						if (ytrans2 > 1999 && ytrans2 < 2999) {
							XP += (GLdouble)sin(heading*piover180) * 2.5f;
							ZP += (GLdouble)cos(heading*piover180) * 2.5f;
						}
						else {

							XP += (GLdouble)sin(heading*piover180) * 5.0f;
							ZP += (GLdouble)cos(heading*piover180) * 5.0f;
						}
					}

					if (keys['A'])  // strafe left
					{
						if (ytrans2 > 1999 && ytrans2 < 2999) {
							XP += (GLdouble)sin((heading - 90)*piover180) * 2.5f;
							ZP += (GLdouble)cos((heading - 90)*piover180) * 2.5f;
						}
						else {

							XP += (GLdouble)sin((heading - 90)*piover180) * 5.0f;
							ZP += (GLdouble)cos((heading - 90)*piover180) * 5.0f;
						}
					}

					if (keys['D']) // strafe right
					{
						if (ytrans2 > 1999 && ytrans2 < 2999) {
							XP += (GLdouble)sin((heading + 90)*piover180) * 2.5f;
							ZP += (GLdouble)cos((heading + 90)*piover180) * 2.5f;
						}
						else {

							XP += (GLdouble)sin((heading + 90)*piover180) * 5.0f;
							ZP += (GLdouble)cos((heading + 90)*piover180) * 5.0f;
						}
					}

					if (keys['1'])   // cpu
					{
						xtrans2 = MAX_Cells / 3;
						ztrans2 = MAX_Cells / 1.5f;
						ytrans2 = 10;
					}

					if (keys['2']) // motherboard
					{
						xtrans2 = MAX_Cells *0.25;
						ztrans2 = MAX_Cells *0.25f;
						ytrans2 = 1010;

					}
					if (keys['3'])  // ps
					{
						xtrans2 = MAX_Cells / 3;
						ztrans2 = MAX_Cells / 1.5f;
						ytrans2 = 2010;
					}
					if (keys['4'])  // monitor
					{
						xtrans2 = MAX_Cells / 3;

						ztrans2 = MAX_Cells / 1.5f;
						ytrans2 = 3010;
					}
					if (keys['5'])  // ram
					{
						xtrans2 = MAX_Cells / 3;

						ztrans2 = MAX_Cells / 1.5f;
						ytrans2 = 4010;
					}


					if (keys[VK_SPACE])
					{
						if (is_Fired == 0)
						{
							is_Fired = 7;  // 1 shot every 7 frames.
							isFire = true;
						}
						else if ((is_shock_rifle))
						{
							isFire = true;
						}
					}

					if (keys[VK_LEFT]) // Turn left
					{
						zprot += .5f;
					}
					else if (keys[VK_RIGHT]) // Turn right
					{
						zprot -= .5f;
					}


				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);						// Exit The Program
}
