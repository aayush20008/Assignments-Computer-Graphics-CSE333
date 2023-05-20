
#include "object.h"
#include "ray.h"
#include <iostream>
#include <glm/glm.hpp>
#include "vector3D.h"
#include "color.h"

class Triangle : public Object
{
private:
	
	Vector3D p1;
    Vector3D p2;
    Vector3D p3;

public:
	Triangle(const Vector3D& _point1,const Vector3D& _point2,const Vector3D& _point3, Material* mat):
		Object(mat)
	{
        p1 = _point1;
        p2 = _point2;
        p3 = _point3;
		isSolid = true;

	}
	
	virtual bool intersect(Ray& r) const {
        Vector3D e = r.getOrigin();
        Vector3D d = r.getDirection();
        glm::mat3 A  {p1[0]-p2[0],p1[0]-p3[0],d[0],
                       p1[1]-p2[1],p1[1]-p3[1],d[1],
                       p1[2]-p2[2],p1[2]-p3[2],d[2]};
        glm ::mat3 beta_mat {p1[0]-e[0],p1[0]-p3[0],d[0],
                       p1[1]-e[1],p1[1]-p3[1],d[1],
                       p1[2]-e[2],p1[2]-p3[2],d[2]};
        glm::mat3 gamma_mat {p1[0]-p2[0],p1[0]-e[0],d[0],
                       p1[1]-p2[1],p1[1]-e[1],d[1],
                       p1[2]-p2[2],p1[2]-e[2],d[2]};
        glm::mat3 t_mat {p1[0]-p2[0],p1[0]-p3[0],p1[0]-e[0],
                       p1[1]-p2[1],p1[1]-p3[1],p1[1]-e[1],
                       p1[2]-p2[2],p1[2]-p3[2],p1[2]-e[2]};

        double beta = glm::determinant(beta_mat)/glm::determinant(A);
        double gamma = glm::determinant(gamma_mat)/glm::determinant(A);
        double t = glm::determinant(t_mat)/glm::determinant(A);

        Vector3D v1,v2;
        v1=p2-p1;
        v2 = p3-p1;
        Vector3D norm = crossProduct(v1,v2);
        norm.normalize();
        if(beta > 0 && gamma >0 && (gamma + beta)<1){
            // std::cout << beta << " "<< gamma <<" " << t << std::endl;
            r.setParameter(t,this);
            r.setNormal(norm);
            return true;
        }
        
        return false;
    }
};
