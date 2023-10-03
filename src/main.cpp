
#include "ofMain.h"
#include "ofApp.h"


#ifdef TARGET_WIN32

#define IDI_ICON1 101

#endif

//========================================================================
int main( ){

    //Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
    ofGLWindowSettings settings;
    settings.setSize(750, 210);
    settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

    auto window = ofCreateWindow(settings);

#ifdef TARGET_WIN32
    HWND hwnd = ofGetWin32Window();
	// Load and set the application icon
	HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon); // Set the large icon
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon); // Set the small icon
#endif
    ofRunApp(window, std::make_shared<ofApp>());
    ofRunMainLoop();

}
