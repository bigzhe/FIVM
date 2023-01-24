#ifndef CHOWLIUTREEBUILDER_HPP
#define CHOWLIUTREEBUILDER_HPP

template <size_t SZ>
struct ChowLiuTreeBuilder
{

    double mi_matrix[SZ][SZ]; // to store the matrix

    ChowLiuTreeBuilder()
    {
        memset(mi_matrix, 0, sizeof(mi_matrix)); // initialize the matrix to 0
    }

    // build the MI matrix from the cofactor
    // the MI matrix is a SZ x SZ matrix
    // assume all variables are categorical
    void build_mi_matrix(const RingCofactorGeneral<0, 0, SZ> cofactor)
    {

        long count = cofactor.count;

        size_t idx_XY = 0; // index of the qudratic item for X, Y in the relation array
        // for each variable X
        for (size_t X = 0; X < SZ; X++)
        {
            // get SUM(1) GB feature X
            const Dictionary *linear_X = &cofactor.relation_array[X];

            // for each variable Y
            for (size_t Y = X; Y < SZ; Y++)
            {

                // get SUM(1) GB feature Y
                const Dictionary *linear_Y = &cofactor.relation_array[Y];
                
                                        
                // index of X, Y in the relation array
                const Dictionary *quadratic_XY = nullptr; // when X == Y, quadratic_XY is not used
                if (X != Y)
                    quadratic_XY = &cofactor.relation_array[SZ + idx_XY++]; 

                // compute the MI between feactures X and Y
                // for each value x of X
                for (size_t x = 0; x < linear_X->tuples.size(); x++)
                {
                    // x in dom(X)
                    const Tuple *tuple_x = &linear_X->tuples[x];
                    
                    // when X == Y, tuple_x == tuple_y = tuple_xy
                    if (X == Y)
                    {
                        mi_matrix[X][Y] += 1.0 * tuple_x->value / count * log2(count / tuple_x->value);
                        continue;
                    }

                    // for each value y of Y
                    for (size_t y = 0; y < linear_Y->tuples.size(); y++)
                    {
                        // y in dom(Y)
                        const Tuple *tuple_y = &linear_Y->tuples[y];

                        // find the tuple in quadratic_XY with the same key as tuple_x ++ tuple_y 
                        // for loop to find the key
                        for (size_t m = 0; m < quadratic_XY->tuples.size(); m++)
                        {
                            const Tuple *tuple_xy = &quadratic_XY->tuples[m];
                            if (tuple_xy->slots[0] == tuple_x->key && tuple_xy->slots[1] == tuple_y->key)
                            {
                                // compute the MI
                                mi_matrix[X][Y] += 1.0 * tuple_xy->value / count * log2(tuple_xy->value * count / (tuple_x->value * tuple_y->value));
                                break;
                            }
                        }
                    }
                }

                // symmetric
                mi_matrix[Y][X] = mi_matrix[X][Y];
            }
        }
    }
    
    // TODO: build the chow liu tree from the MI matrix
    void build_chow_liu_tree()
    {
        
    }
};

#endif /* CHOWLIUTREEBUILDER_HPP */