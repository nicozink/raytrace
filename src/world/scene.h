#pragma once

#include "object/cube_map.h"
#include "object/light.h"
#include "object/traceable.h"

#include <primitive/color.h>
#include <primitive/ray.h>

#include <vector>

class Scene
{
public:

    Scene(std::string path);

    ~Scene();

    Color trace(const Ray r, int depth = 0, int max_depth = 10) const;

private:

    bool find_intersection(const Ray &r) const;
    
    bool find_intersection(const Ray &r, Intersection &i) const;
    
    std::vector<Light*> lights;

    std::vector<Material*> materials;
    
    std::vector<Traceable*> traceables;
	
	CubeMap* sky_box;

	friend class SceneReader;
};
