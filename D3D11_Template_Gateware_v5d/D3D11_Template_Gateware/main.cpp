// Sample of Gateware Middleware utilizing D3D11, designed as a potential template project for Project & Portfolio IV students.
// Gateware is an easy to use set of multi-platfrom Middleware libraries, however we are Still in BETA so expect a few bugs here & there.
// In this template we use Gateware to create a window & attatch a D3D11 surface to it.
// Other things you could use Gateware for: OpenGL, SoundFX, Music, Keyboard & Mouse Input, File I/O, Logging, 3D Math & more to come!
// Gateware was built by your fellow Full Sail students under mentor supervision, you may also use it during final project! 
// Author: Lari H Norri, Full Sail University [Template Version 0.5 Alpha 7/23/2018]
// Special Thanks: All current, prior and future Gateware developers!
#define _CRT_SECURE_NO_WARNINGS 

// Main Gateware Interface for window creation, check out the included documentation folder on how to use Gateware to the fullest!
#include "Gateware Redistribution R5d/Interface/G_System/GWindow.h" // Gateware is open-source & uses the MIT license!
// This example template directly references gateware source code to compile for simplicity & portability.
// However... Gateware also supports linking using both static & dynamic libraries if you prefer. 

// Include Our DX11 Class for drawing
#include "LetsDrawSomeStuff.h" // 90% of Gateware is cross-platform, the stuff in this file is not just FYI. (see GOpenGLSurface instead)

// Gateware namespaces here

using namespace GW;
using namespace CORE;
using namespace SYSTEM;

// Main entry point
int main()
{
	//ShowCursor(FALSE);
	srand((unsigned int)time(NULL));
	// Handle to our new window, be sure to DecrementCount to free memory
	GWindow* myWindow = nullptr;
	// Our class that contains all D3D11 related Code
	LetsDrawSomeStuff* myDrawSystem = nullptr;
	// Create new window
	if (G_SUCCESS(CreateGWindow(100, 100, 1024, 768, GWindowStyle::WINDOWEDBORDERED, &myWindow)))
	{
		// Create our Draw system now that we have a window, this will also open our window
		myDrawSystem = new LetsDrawSomeStuff(myWindow);
		// main loop, assumes window has already been opened
		GW::SYSTEM::GWindowInputEvents lastEvent;
		while (G_SUCCESS(myWindow->GetLastEvent(lastEvent)) && 
				lastEvent != GW::SYSTEM::GWindowInputEvents::DESTROY)
		{
			// process platform specific window events
			if (G_FAIL(myWindow->ProcessWindowEvents()))
				break; // nope...

			if(lastEvent == GW::SYSTEM::GWindowInputEvents::RESIZE)
				myDrawSystem->UpdateProjection();

			// Before or after events are processed lets do some drawing
			myDrawSystem->timer.Signal();
			myDrawSystem->ManageUserInput();
			myDrawSystem->Render();
		}
		// Free drawing system and all internal elements
		delete myDrawSystem; 
		myDrawSystem = nullptr;
		// free window
		myWindow->DecrementCount();
	}
    return 0;
}
// *The GWindow class also posts its own events, you can derive from the class GListener to listen for specific API events if desired*