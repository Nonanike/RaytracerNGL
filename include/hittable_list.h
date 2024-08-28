/// Modified from
/// Peter Shirley (August 8 2023). Ray Tracing in One Weekend [online]
/// [Accessed 2024]. Available from: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#ifndef HITTABLE_LIST_H_
#define HITTABLE_LIST_H_

#include <memory>
#include <vector>
#include "Material.h"
#include "hittable.h"

using std::make_shared;

class HittableList : public Hittable
        {
        public:
            std::vector<std::shared_ptr<Hittable>> objects;

            HittableList() {}
            HittableList(std::shared_ptr<Hittable> object) {add(object);}

            void clear() {objects.clear();}

            void add(std::shared_ptr<Hittable> object)
            {
                objects.push_back(object);
            }

            bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec)
            {
                HitRecord temp_rec;
                bool hitAnything = false;
                auto closestSoFar = t_max;

                for (const auto& object : objects)
                    {
                    if (object->hit(r, t_min, closestSoFar, temp_rec))
                        {
                        hitAnything = true;
                        closestSoFar = temp_rec.t;
                        rec = temp_rec;
                        }
                    }

                return hitAnything;
            }
        };
#endif