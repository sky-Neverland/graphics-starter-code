#include "rayTracer.hpp"

const int numSamples = 1024;
const int maxDepth = 20;
Image RayTracer::takePicture(Scene &scene, int camIndex)
{
    Image output;
    Camera cam = (*scene.cameras[camIndex]);
    output.width = cam.width;
    output.height = cam.height;
    for (int i = 0; i < output.width; i++)
    {
        for (int j = 0; j < output.height; j++)
        {
            Color c;
            output.pixels.push_back(c);
        }
    }

    //Start at the top right corner. Go left to right, top to bottom
    for (int j = (cam.height - 1); j >= 0; j--)
    {
        for (int i = 0; i < (cam.width); i++)
        {
            Color c = output.getPixel(i, j);
            for (int k = 0; k < numSamples; k++)
            {
                float u = static_cast<float>(rand()) / RAND_MAX;
                float v = static_cast<float>(rand()) / RAND_MAX;

                ray eyeRay = cam.getEyeRay(i + u, j + v);

                Hit hit;
                hit = this->traceRay(scene, eyeRay, hit, 0);

                c.r += hit.color.r;
                c.g += hit.color.g;
                c.b += hit.color.b;
            }
            c.r = sqrt(c.r/numSamples);
            c.g = sqrt(c.g/numSamples); 
            c.b = sqrt(c.b/numSamples);
            output.setPixel(i, j, c);
        }
    }

    return output;
}

Hit RayTracer::traceRay(Scene &scene, ray &eyeRay, Hit &hit, int depth)
{
    Hit closest = hit;
    for (Geometry *item : scene.items)
    {
        Hit current = item->trace(eyeRay);
        if (current.t < closest.t)
        {
            closest = current;
        }
    }
    this->findShade(scene, closest, depth);
    return closest;
}

void RayTracer::findShade(Scene &scene, Hit &hit, int depth)
{
    // missed
    if (hit.t > 1e10)
    {
        hit.color = scene.backgroundColor;
        hit.brightness = scene.ambientLight;
    }
    // hit
    else
    {
        Color color = hit.material->getColor(hit.modelSpacePos);
        ray scatteredRay = hit.material->scatter(hit.inRay, hit.pos, hit.normal);
        if (depth > maxDepth)
            return;
        Hit scatteredHit;
        scatteredHit = this->traceRay(scene, scatteredRay, scatteredHit, depth + 1);
        if (scatteredHit.brightness > 0)
        {
            hit.color.r += color.r * scatteredHit.color.r * scatteredHit.brightness;
            hit.color.g += color.g * scatteredHit.color.g * scatteredHit.brightness;
            hit.color.b += color.b * scatteredHit.color.b * scatteredHit.brightness;
        }
    }
}