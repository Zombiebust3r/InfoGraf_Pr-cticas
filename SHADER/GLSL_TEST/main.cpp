//=============================================================================
// Sample Application for GLEW, and cwc Application/Window class using freeglut
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include <time.h>
#include "glsl.h"

//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   GLuint ProgramObject;
   GLint locColor;
   GLint locScale;
   clock_t time0,time1;
   float timer5;  // timer counting 0...1 in 5 seconds

public:
	myWindow(){}

	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //<Simple Timer>
      // This is a very simple implementation of a timer.
      // the variable timer5 counts from 0.0f to 1.0f in 5 seconds.
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      if (delta > 0.00005f)
      {
         time0 = clock();
         timer5 += delta;
         if (timer5>5.0f) timer5 = 0.0f; 
      }
      //</Simple Timer>

      if (shader) 
      {
         shader->begin();
         glUniform1f(locScale, timer5 / 5.0f);
         glUniform4f(locColor, timer5 / 5.0f, 0.0, 0.0, 1.0);
      }

      glutSolidSphere(1.0,32,32);
      //glutSolidTeapot(1.0);
      if (shader) shader->end();

      glutSwapBuffers();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
         locScale = glGetUniformLocation(ProgramObject, "uScale");
         locColor = glGetUniformLocation(ProgramObject, "uColor");
         
         if (locScale == -1)
            std::cout << "Warning: can't find uniform variable uScale!\n";

         if (locColor == -1)
            std::cout << "Warning: can't find uniform variable uColor!\n";

      }

      time0 = clock();
      timer5 = 0.0f;

	}

	virtual void OnResize(int w, int h) {}
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		} 
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
		if (cAscii == 'f')
		{
			SetFullscreen(true);
		}
		else if (cAscii == 'w')
		{
			SetFullscreen(false);
		}
	};
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

