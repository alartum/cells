#include "step_algorithm.hpp"
////////////////////////////////////////////////////////////////////////////////////////////////
StepAlgorithm::StepAlgorithm() 
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
RandomMoving::RandomMoving ( sf::Vector2i fSize ) : StepAlgorithm(), fSize(fSize) {
}

int RandomMoving::action ( std::vector< Object* >& M ) {
    std::uniform_int_distribution< int > distr(-2, 2);
    std::random_device rd;
    std::mt19937 generator(rd());
    
    std::vector< sf::Vector2f > ds(M.size());
    for (auto & v: ds)
        v.x = 0, v.y = 0;
    
    for (int i = 0; i + 1 < (int)M.size(); i++) 
        for (int j = i + 1; j < (int)M.size(); j++) {
            Grass* pt1 = (Grass*)M[i];
            Grass* pt2 = (Grass*)M[j];
            
            sf::Vector2f V(pt2->gLocation.x - pt1->gLocation.x, pt2->gLocation.y - pt1->gLocation.y);
            double norm = sqrt(V.x*V.x + V.y*V.y);
            V.x = V.x / norm / norm;
            V.y = V.y / norm / norm;
            
            if (pt1->gRadius > pt2->gRadius) {               
                if (V.x != 0)
                    ds[i].x += V.x, ds[j].x += V.x;
                if (V.y != 0)
                    ds[i].y += 2 * V.y, ds[j].y += 2 * V.y; 
            }
            else if (pt1->gRadius < pt2->gRadius) {
                if (V.x != 0)
                    ds[i].x -= 2 * V.x, ds[j].x -= 2 * V.x;
                if (V.y != 0)
                    ds[i].y -= V.y, ds[j].y -= V.y;
            }
        }
    for (auto & v: ds) {
        double norm = sqrt(v.x*v.x + v.y*v.y);
        v.x /= (norm + 0.0001);
        v.y /= (norm + 0.0001);
        //std::cout << v.x << " " << v.y << std::endl;
    }
    
    for (int i = 0; i < (int)M.size(); i++) {
        Grass* pt = (Grass*)M[i];
        pt->gLocation.x += (int)(ds[i].x * 10 / sqrt(pt->gRadius + 1));
        pt->gLocation.y += (int)(ds[i].y * 10 / sqrt(pt->gRadius + 1));
        
        if (pt->gLocation.x >= fSize.x)
            pt->gLocation.x = fSize.x;
        if (pt->gLocation.y >= fSize.y)
            pt->gLocation.y = fSize.y;
        if (pt->gLocation.x < 0)
            pt->gLocation.x = 0;
        if (pt->gLocation.y < 0)
            pt->gLocation.y = 0;
    }
        
    for (int i = 0; i < (int)M.size(); i++) 
        for (int j = 0; j < (int)M.size(); j++) {
            Grass* pt1 = (Grass*)M[i];
            Grass* pt2 = (Grass*)M[j];
            if (pt1->gRadius > pt2->gRadius && pt1->isIntersect(*pt2)) {
                double newR = sqrt(pt2->gRadius * pt2->gRadius + pt1->gRadius * pt1->gRadius);
                delete pt2;
                M.erase(M.begin() + j);
                j -= 1;
                pt1->gRadius = newR;
            }
        }
        
    return M.size();
}


////////////////////////////////////////////////////////////////////////////////////////////////
