#include "shape.h"

namespace yart {

  class Ray;

  namespace geometry {

    class Sphere : public Shape<Sphere> {
    private:
      float radius = 1.0f;

    public:
      Sphere(Eigen::Vector4f _origin, float _radius);
      Sphere(float _radius);
      ~Sphere();

      std::vector<Intersection<Sphere>> intersections(const Ray& ray);

      friend std::ostream& operator<<(std::ostream& out, const Sphere& sphere);
    };

  }  // namespace geometry

}  // namespace yart
