#ifndef BVH_H
#define BVH_H

#include "vec3.h"
#include "hittable_list.h"
#include "ray.h"

class BVH : public hittable {
public:
    
    struct BVHNode {
        point3 aabbMin;
        point3 aabbMax;

        int leftChild;
        int rightChild;

        int firstPrim;
        int primCount;

        bool isLeaf;
    };

    BVHNode bvhNode[5 * 2 - 1];
    uint rootNodeIdx = 0;
    hittable_list& world;
    uint nodes_used = 1;

    // Constructor
    BVH(hittable_list& world) : world(world) {
        BuildBVH();
    }

private:

    void BuildBVH()
    {
        BVHNode& root = bvhNode[rootNodeIdx];

        root.firstPrim = 0;
        root.primCount = world.objects.size();

        root.leftChild = 0;
        root.rightChild = 0;

        root.isLeaf = false;

        UpdateNodeBounds(rootNodeIdx);
        Subdivide(rootNodeIdx);
    }


    void UpdateNodeBounds(uint nodeIdx)
    {
        BVHNode& node = bvhNode[nodeIdx];

        for (uint i = 0; i < node.primCount; i++)
        {
            uint primIdx = node.firstPrim + i;

            auto obj = world.objects[primIdx];
            
            node.aabbMin = min(node.aabbMin, obj->get_min());
            node.aabbMax = max(node.aabbMax, obj->get_max());
        }
    }


    void Subdivide(uint nodeIdx) {
        BVHNode& node = bvhNode[nodeIdx];

        // Only one sphere -> leaf
        if (node.primCount <= 2)
        {
            node.isLeaf = true;
            return;
        }

        node.isLeaf = false;

        // Find longest axis
        point3 extent =
            node.aabbMax - node.aabbMin;

        int axis = 0;
        if (extent.y() > extent.x()) axis = 1;
        if (extent.z() > extent[axis]) axis = 2;

        float split_pos = node.aabbMin[axis] + extent[axis] * 0.5f;
       
        int i = node.firstPrim;
        int j = i + node.primCount - 1;

        while (i <= j) {
            auto obj = world.objects[i];

            if (obj->get_center()[axis] < split_pos)
            {
                i++;
            }
            else
            {
                std::swap(
                    world.objects[i],
                    world.objects[j]);

                j--;
            }
        }

        uint leftCount =
            i - node.firstPrim;


        // Prevent empty child
        if (leftCount == 0 || leftCount == node.primCount)
        {
            return;
        }

        // Allocate children
        uint leftChildIdx = nodes_used++;
        uint rightChildIdx = nodes_used++;


        node.leftChild = leftChildIdx;
        node.rightChild = rightChildIdx;


        // Left child
        BVHNode& left =
            bvhNode[leftChildIdx];

        left.firstPrim =
            node.firstPrim;

        left.primCount =
            leftCount;

        // right child
        BVHNode& right =
            bvhNode[rightChildIdx];

        right.firstPrim = i;
        right.primCount = node.primCount - leftCount;

        node.primCount = 0;
        UpdateNodeBounds(leftChildIdx);
        UpdateNodeBounds(rightChildIdx);

        // Recursively subdivide
        Subdivide(leftChildIdx);
        Subdivide(rightChildIdx);
    }

    bool IntersectAABB(const ray& ray, point3 aabMin, point3 aabMax, hit_record& rec) {
        float tx0 = (aabMin.x() - ray.origin().x()) / ray.direction().x();
        float tx1 = (aabMax.x() - ray.origin().x()) / ray.direction().x();
        float tmin = std::min( tx0, tx1 ), tmax = std::max( tx0, tx1 );

        float ty0 = (aabMin.y() - ray.origin().y()) / ray.direction().y();
        float ty1 = (aabMax.y() - ray.origin().y()) / ray.direction().y();
        
        tmin = std::max(tmin, std::min(ty0, ty1));
        tmax = std::min(tmax, std::max(ty0, ty1));

        float tz0 = (aabMin.z() - ray.origin().z()) / ray.direction().z();
        float tz1 = (aabMax.z() - ray.origin().z()) / ray.direction().z();
       
        tmin = std::max(tmin, std::min(tz0, tz1));
        tmax = std::min(tmax, std::max(tz0, tz1));

        return (tmax > tmin && tmin < rec.t && tmax > 0);
    }

    void IntersectBVH(const ray& ray, interval ray_t, hit_record& rec, const uint nodeIdx) {

        BVHNode& node = bvhNode[nodeIdx];

        if (!IntersectAABB(ray, node.aabbMin, node.aabbMax, rec)) return;

        if (node.isLeaf) {
            for (size_t i = 0; i < node.primCount; i++) 
            {
                if (world.objects[node.firstPrim + i]->hit(ray, interval(ray_t.min, rec.closest_so_far), rec)) {
                    rec.hit_anything = true;
                    rec.closest_so_far = rec.t;
                }
            }
        } else {
            IntersectBVH(ray, ray_t, rec, node.leftChild);
            IntersectBVH(ray, ray_t, rec, node.rightChild);
        }
    }
    
    bool hit(const ray& r, interval ray_t, hit_record& rec) override { 
      rec.hit_anything = false;
      rec.closest_so_far = ray_t.max;

      IntersectBVH(r, ray_t, rec, rootNodeIdx);

      return rec.hit_anything;
    }

    point3 get_center() override {
      return {};
    }

    point3 get_max() override {
      return {};
    }

    point3 get_min() override {
      return {};
    }
};

#endif