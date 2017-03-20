/*#include "step_algorithm.hpp"
////////////////////////////////////////////////////////////////////////////////////////////////
StepAlgorithm::StepAlgorithm() 
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
LifeAlgorithm::LifeAlgorithm() : StepAlgorithm()
{
}


int LifeAlgorithm::step ( Matrix< Cell >& M ) 
{ 
    #pragma omp parallel for
    for(unsigned i = 0; i < M.getHeight(); i++)
        for (unsigned j = 0; j < M.getWidth(); j++)
            M.at(i, j).updatePrevType();

    #pragma omp parallel for
    for(int i = 1; i < (int)M.getHeight() - 1; i++)
        for (int j = 1; j < (int)M.getWidth() - 1; j++)
            if (M.at(i, j).getPrevType() == Cell::cell_type_t::Clear) {
                int s = 0;
                for (int di = -1; di <= 1; di++)
                    for (int dj = -1; dj <= 1; dj++)
                        s += (M.at(i + di, j + dj).getPrevType() == Cell::cell_type_t::Live ? 1 : 0);
                if (s == 3) 
                    M.at(i, j).setType(Cell::cell_type_t::Live);
            }
            else {
                int s = 0;
                for (int di = -1; di <= 1; di++)
                    for (int dj = -1; dj <= 1; dj++)
                        s += (M.at(i + di, j + dj).getPrevType() == Cell::cell_type_t::Live ? 1 : 0);
                s -= 1;
                if (s < 2 || s > 3)
                    M.at(i, j).setType(Cell::cell_type_t::Clear);
            }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////
*/