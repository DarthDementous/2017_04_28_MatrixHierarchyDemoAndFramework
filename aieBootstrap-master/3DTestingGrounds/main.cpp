#include "_3DTestingGroundsApp.h"

int main() {
	
	auto app = new _3DTestingGroundsApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}