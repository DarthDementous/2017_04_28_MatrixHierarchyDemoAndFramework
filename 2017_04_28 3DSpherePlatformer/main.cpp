#include "_3DSpherePlatformerApp.h"

int main() {
	
	auto app = new _3DSpherePlatformerApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}