#pragma once

#include "material.h"

class FlatColor : public Material
{
public:
    
    FlatColor(Color color, double k_diffuse, double k_specular, double spec_shiny);
    
    Surface get_surface(double u, double v) const override;
    
private:
    
    Color color;
    
    double k_diffuse;
    
    double k_specular;
    
    double spec_shiny;
};
