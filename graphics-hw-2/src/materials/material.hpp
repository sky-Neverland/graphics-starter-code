#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "../defines.hpp"
#include "../math/vec4.hpp"
#include "../color.hpp"
#include "../math/ray.hpp"
#include <cmath>

//not needed for this assignment
class Material
{
public:
    virtual ~Material() {}
};

#endif