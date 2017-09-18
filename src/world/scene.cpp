#include "scene.h"

// Local includes

#include "scene_reader.h"

// Project includes

#include <math/vector3d.h>

#include <primitive/color.h>
#include <primitive/color_accumulator.h>

// External includes

#include <cmath>
#include <json/json.h>
#include <random>

static std::uniform_real_distribution<double> unif(0.0, 1.0);
static std::default_random_engine re;

Scene::Scene(std::string path)
{
	SceneReader::ReadScene(path, *this);
}

Scene::~Scene()
{
	for (auto& light : lights)
	{
		delete light;
	}

	for (auto& material : materials)
	{
		delete material;
	}

	for (auto& traceable : traceables)
	{
		delete traceable;
	}
	
	if (sky_box != nullptr)
	{
		delete sky_box;
	}
}

Color Scene::trace(const Ray r, int depth, int max_depth) const
{    
	Intersection i;

	if (find_intersection(r, i))
	{
		Color c(0.0, 0.0, 0.0);

		Surface s = i.get_surface();

		const int AREA_LIGHT_SAMPLES = 32;

		for (auto& light : lights)
		{
			int light_samples_count = 1;
			bool randomized_light_samples = false;
			
			if (depth == 0 && light->get_light_type() == LightType::AreaLight)
			{
				light_samples_count = AREA_LIGHT_SAMPLES;
				randomized_light_samples = true;
			}

			ColorAccumulator light_accumulator;
			
			for (int ls = 0; ls < light_samples_count; ++ls)
			{
				Color light_color(0.0, 0.0, 0.0);
				
				Ray light_ray = light->get_ray_to_light(r.get_position(i.distance), randomized_light_samples);

				if (!find_intersection(light_ray))
				{
					if (s.k_diffuse > 0.0)
					{
						double diff_dot = i.normal.dot(light_ray.direction());

						if (diff_dot > 0.0)
						{
							light_color = light_color + s.color * diff_dot * s.k_diffuse;
						}
					}
					
					if (s.k_specular > 0.0)
					{
						double diff_dot = i.normal.dot(light_ray.direction());
						
						Vector3d reflection = i.normal * 2.0 * diff_dot - light_ray.direction();
						double spec_dot = (r.direction() * -1.0).dot(reflection);
					
						if (spec_dot > 0.0)
						{
							light_color = light_color + Color(1.0, 1.0, 1.0, 1.0) * pow(spec_dot, s.spec_shiny) * s.k_specular;
						}
					}
				}
				
				light_accumulator.add(light_color);
			}
			
			c = c + light_accumulator.average(light_samples_count);
		}
		
		if (s.k_specular > 0.0 && depth < max_depth)
		{
			const int REFLECTION_SAMPLES = 32;
			int reflection_samples_count = 1;
			
			if (depth == 0)
			{
				reflection_samples_count = REFLECTION_SAMPLES;
			}
			
			ColorAccumulator light_accumulator;
			
			double diff_dot = i.normal.dot(r.direction());
			Vector3d reflection = r.direction() - i.normal * 2.0 * diff_dot;
			
			for (int rs = 0; rs < reflection_samples_count; ++rs)
			{
				Vector3d random_reflection = reflection;
				
				if (reflection_samples_count > 1)
				{
					double a = unif(re);
					double b = unif(re);
					
					double theta = acos(pow((1.0 - a), s.spec_shiny));
					double phi = 2 * M_PI * b;
					
					double x = sin(phi) * cos(theta) / 16;
					double y = sin(phi) * sin(theta) / 16;
					
					Vector3d u = reflection.cross(i.normal);
					Vector3d v = reflection.cross(u);
					
					random_reflection = reflection + u * x + v * y;
					random_reflection.normalise();
				}
				
				Ray r_reflect(r.get_position(i.distance), random_reflection);

				light_accumulator.add(trace(r_reflect, depth + 1, max_depth) * s.k_specular);
			}
			
			c = c + light_accumulator.average(reflection_samples_count);
		}

		return c;
	}
	else if (sky_box != nullptr)
	{
		return sky_box->get_color(r);
	}

	return Color(0.0, 0.0, 0.0);
}

bool Scene::find_intersection(const Ray &r) const
{
	const double MIN_DIST = 0.001;

	for (auto& traceable : traceables)
	{
		if (traceable->trace(r, MIN_DIST))
		{
			return true;
		}
	}

	return false;
}

bool Scene::find_intersection(const Ray &r, Intersection &i) const
{
	const double MIN_DIST = 0.001;

	for (auto& traceable : traceables)
	{
		if (traceable->trace(r, i, MIN_DIST))
		{
			return true;
		}
	}

	return false;
}
