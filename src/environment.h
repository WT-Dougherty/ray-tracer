#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Matter.h"
#include "primaryheader.h"

class Environment : public Matter
{
public:
    std::vector<Matter *> objects;

    Environment() {}
    Environment(Matter *object) { objects.push_back(object); }

    void clear() { objects.clear(); }
    void add(Matter *object) { objects.push_back(object); }

    inline bool hit(const Ray &r, double rayTmin, double rayTmax, HitRecord &rec) const override
    {
        HitRecord tempRec;
        bool hitbool = false;
        double closest = rayTmax;

        for (const Matter *object : objects)
        {
            if (object->hit(r, rayTmin, rayTmax, tempRec))
            {
                hitbool = true;
                closest = tempRec.t;
                rec = tempRec;
            }
        }
        return hitbool;
    }
};

#endif /* environment.h */
