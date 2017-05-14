#include "_3DTestingGroundsApp.h"
#include <GLFW/glfw3.h>

int main() {
	// Create instance of glfw to modify window
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);		// Can not be resized

	auto app = new _3DTestingGroundsApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}              