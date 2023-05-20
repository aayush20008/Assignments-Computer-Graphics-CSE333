#include "world.h"

using namespace std;

float World::firstIntersection(Ray& ray)
{
	for(int i=0; i<objectList.size(); i++)
		objectList[i]->intersect(ray);
	return ray.getParameter();
}

Color World::shade_ray(Ray& ray)
{
	firstIntersection(ray);
	if(ray.didHit())
		return (ray.intersected())->shade(ray);
	return background;
}
