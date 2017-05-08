#include "SceneGraphApp.h"

int main() {
	
	auto app = new SceneGraphApp();
	app->run("AIE", 1024, 768, false);
	delete app;

	return 0;
}