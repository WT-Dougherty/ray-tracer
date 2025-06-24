#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "matter.h"
#include "primaryheader.h"

class environment : public matter {
public:
    std::vector < matter* > objects;

    environment() {}
    environment(matter* object) { objects.push_back(object); }

    void Clear() { objects.clear(); }
    void Add(matter* object) { objects.push_back(object); }
    
    inline bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override
    {
        hit_record temp_rec;
        bool hitbool = false;
        double closest = ray_tmax;

        for (const matter* object : objects)
        {
            if ( object->hit(r, ray_tmin, ray_tmax, temp_rec) )
            {
                hitbool = true;
                closest = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hitbool;
    }
};

#endif /* environment.h */