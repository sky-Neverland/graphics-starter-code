#include "camera.hpp"
#include "geometry/geometry.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"

class Scene {
public:
    std::vector<Geometry*> items;
    std::vector<Camera*> cameras;
};