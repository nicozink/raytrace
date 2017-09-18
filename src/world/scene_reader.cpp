#include "scene_reader.h"

// Project Includes

#include "material/flat_color.h"
#include "material/texture.h"

#include "object/sphere.h"
#include "object/sphere_light.h"
#include "object/triangle.h"
#include "object/plane.h"
#include "object/point_light.h"

#include <resource/image_utilities.h>

// Library includes
#include <json/json.h>

void SceneReader::ReadScene(std::string path, Scene& scene)
{
	JSON json = JSON::ParseFile(path + "scene.json");

	std::map<std::string, Material*> materials_map;

	JSON_Value materials = json["materials"];

	for (int i = 0; i < materials.size(); ++i)
	{
		JSON_Value material = materials[i];

		double k_diffuse = material["k_diffuse"].get<double>();
		double k_specular = material["k_specular"].get<double>();
		double spec_shiny = material["spec_shiny"].get<double>();

		if (material["type"].get<std::string>() == "texture")
		{
			Image image = ImageUtilities::load_png(path + material["file"].get<std::string>());

			Material* texture = new Texture(image, k_diffuse, k_specular, spec_shiny);
			scene.materials.push_back(texture);

			materials_map[material["name"].get<std::string>()] = texture;
		}
		else if (material["type"].get<std::string>() == "flat_color")
		{
			JSON_Value json_color = material["color"];
			Color color(json_color[0].get<double>(), json_color[1].get<double>(), json_color[2].get<double>());

			Material* flat_colour = new FlatColor(color, k_diffuse, k_specular, spec_shiny);
			scene.materials.push_back(flat_colour);

			materials_map[material["name"].get<std::string>()] = flat_colour;
		}
	}

	JSON_Value lights = json["lights"];

	for (int i = 0; i < lights.size(); ++i)
	{
		JSON_Value light = lights[i];

		JSON_Value json_color = light["color"];
		Color color(json_color[0].get<double>(), json_color[1].get<double>(), json_color[2].get<double>());

		JSON_Value json_position = light["position"];
		Vector3d position(json_position[0].get<double>(), json_position[1].get<double>(), json_position[2].get<double>());

		if (light["type"].get<std::string>() == "sphere_light")
		{
			double radius = light["radius"].get<double>();

			Light* sphere_light = new SphereLight(position, radius, color);
			scene.lights.push_back(sphere_light);
		}
		else if (light["type"].get<std::string>() == "point_light")
		{
			Light* point_light = new PointLight(position, color);
			scene.lights.push_back(point_light);
		}
	}

	JSON_Value objects = json["objects"];

	for (int i = 0; i < objects.size(); ++i)
	{
		JSON_Value object = objects[i];

		std::string material_string = object["material"].get<std::string>();
		Material* material = materials_map[material_string];

		if (object["type"].get<std::string>() == "sphere")
		{
			JSON_Value json_position = object["position"];
			Vector3d position(json_position[0].get<double>(), json_position[1].get<double>(), json_position[2].get<double>());

			double radius = object["radius"].get<double>();

			Traceable* sphere = new Sphere(position, radius, material);
			scene.traceables.push_back(sphere);
		}
		else if (object["type"].get<std::string>() == "triangle")
		{
			JSON_Value verts = object["verts"];
			
			JSON_Value json_v1 = verts[0];
			Vector3d v1(json_v1[0].get<double>(), json_v1[1].get<double>(), json_v1[2].get<double>());

			JSON_Value json_v2 = verts[1];
			Vector3d v2(json_v2[0].get<double>(), json_v2[1].get<double>(), json_v2[2].get<double>());

			JSON_Value json_v3 = verts[2];
			Vector3d v3(json_v3[0].get<double>(), json_v3[1].get<double>(), json_v3[2].get<double>());

			bool single_sided = object["single_sided"].get<bool>();

			Traceable* triangle = new Triangle(v1, v2, v3, material, single_sided);
			scene.traceables.push_back(triangle);
		}
		else if (object["type"].get<std::string>() == "plane")
		{
			JSON_Value json_position = object["position"];
			Vector3d position(json_position[0].get<double>(), json_position[1].get<double>(), json_position[2].get<double>());

			JSON_Value json_normal = object["normal"];
			Vector3d normal(json_normal[0].get<double>(), json_normal[1].get<double>(), json_normal[2].get<double>());

			Traceable* plane = new Plane(position, normal, material);
			scene.traceables.push_back(plane);
		}
	}

	JSON_Value sky_box = json["skybox"];

	scene.sky_box = new CubeMap(
		path + sky_box["right"].get<std::string>(),
		path + sky_box["left"].get<std::string>(),
		path + sky_box["up"].get<std::string>(),
		path + sky_box["down"].get<std::string>(),
		path + sky_box["front"].get<std::string>(),
		path + sky_box["back"].get<std::string>());
}
