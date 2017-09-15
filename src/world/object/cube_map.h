#pragma once

#include "primitive/color.h"
#include "primitive/ray.h"
#include "resource/image.h"

#include <string>

class CubeMap
{
public:
    
	CubeMap(std::string pos_x, std::string neg_x, std::string pos_y, std::string neg_y, std::string pos_z, std::string neg_z);
    
    ~CubeMap();
    
    Color get_color(const Ray& r);
    
private:
    
	Image pos_x;
	Image neg_x;
	Image pos_y;
	Image neg_y;
	Image pos_z;
	Image neg_z;
};
