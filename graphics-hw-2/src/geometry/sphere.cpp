#include "sphere.hpp"

//implement these two functions
Hit Sphere::trace(ray & inRay) {
    vec4 origin = (this->worldToModel).transform(inRay.origin);
    vec4 dir = (this->worldToModel).transform(inRay.direction);

    ray ray(origin, dir);

    vec4 center(0,0,0,1);

    Hit hit;
   
    return hit;
}

vec4 Sphere::getNormal(vec4 & pos, ray & inRay) {
    vec4 normVec(0, 0, 0, 0);

    return normVec;
}