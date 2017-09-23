/*
Copyright © 2012, Nico Zink
All rights reserved.
*/

#include "render.h"

// Local Includes
#include "osl/osl_shader.h"
#include "render/batch_render.h"
#include "resource/image.h"
#include "resource/image_utilities.h"
#include "world/camera.h"
#include "world/scene.h"

// Project Includes
#include <json/json.h>

// External Includes
#include <iostream>
#include <string>

// Runs the main program.
int run(std::vector<std::string> args)
{
	JSON config = JSON::ParseFile(std::string("config.json"));
	std::string resources_root = config["resources"].get<std::string>();
	std::string workspace_root = config["workspace"].get<std::string>();
	std::string output_root = config["output"].get<std::string>();

	OSL_Shader shader = OSL_Shader::ParseFile(workspace_root + "test_shader.osl");

	const int X_MAX = 800;
	const int Y_MAX = 600;
	const int SPP = 16;

	Image img(X_MAX, Y_MAX);

	Camera camera(X_MAX, Y_MAX, SPP);
	Scene scene(workspace_root);
	
	BatchRender render(img, camera, scene);
	render.run();
	
	ImageUtilities::save_png(img, output_root + "out.png");
	
	return 0;
}
