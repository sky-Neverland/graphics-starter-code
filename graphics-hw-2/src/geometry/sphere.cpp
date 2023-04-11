#include "sphere.hpp"

//implement these two functions
Hit Sphere::trace(ray & inRay) {
    vec4 origin = (this->worldToModel).transform(inRay.origin);
    vec4 dir = (this->worldToModel).transform(inRay.direction);

    ray ray(origin, dir);

    vec4 center(0,0,0,1);

    Hit hit;
    vec4 r2s = center - ray.origin;
    float L2 = r2s.length_squared();
    if (L2 <= 1.0)
    {
        return hit;
    }
    float tcaS = ray.direction.dot(r2s);
    if (tcaS < 0.0)
    {
        return hit;
    }
    float DL2 = ray.direction.length_squared();
    float tca2 = (tcaS * tcaS) / DL2;
    float LM2 = L2 - tca2;
    if (LM2 > 1.0)
    {
        return hit;
    }

    float L2hc = 1.0 - LM2;
    float t0 = tcaS / DL2 - sqrt(L2hc / DL2);
    hit.t = t0;
    hit.pos = inRay.origin + (inRay.direction * t0);
    hit.modelSpacePos = origin + (dir * t0);
    hit.normal = this->getNormal(hit.modelSpacePos, ray);
    hit.inRay = inRay;

    return hit;
}

vec4 Sphere::getNormal(vec4 &pos, ray &inRay)
{
    vec4 normVec(pos);
    normVec = this->normalToWorld.transform(normVec);
    normVec.w = 0;
    normVec.normalize();
    return normVec;
}