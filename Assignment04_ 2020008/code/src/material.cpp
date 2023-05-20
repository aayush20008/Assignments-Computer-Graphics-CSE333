#include "world.h"
#include <glm/glm.hpp>
#include <math.h>
#include <bits/stdc++.h>
#include "material.h"

Color Material::shade(const Ray& incident, const bool isSolid) const
{
	
	Color a(0), s(0), d(0);
	LightSource* lsr = world -> lightSourceList[0];
	Vector3D nor = incident.getNormal(), v = incident.getDirection()*(-1),lightps = lsr -> getPosition();
	Vector3D ldr = unitVector(lightps - incident.getPosition());
	Color ints = lsr -> getIntensity();
	Vector3D half_vec = unitVector(ldr + v);

	a = ka*color*ints;
	s = ints*ks*color*pow(glm::max((double)0,dotProduct(nor,half_vec)),n);
	
	Ray shadow(incident.getPosition() + 0.1*ldr,ldr);
	world -> firstIntersection(shadow);

	if(shadow.didHit()){
		return (a + s);
	}
	d = ints*kd*color*(glm::max((double)0,dotProduct(nor,ldr)));
	return (a + s + d );

}
