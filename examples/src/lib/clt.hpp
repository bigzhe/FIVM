#ifndef CHOWLIUTREEBUILDER_HPP
#define CHOWLIUTREEBUILDER_HPP

#include <unordered_map>

template <size_t SZ>
struct ChowLiuTreeBuilder
{

    // MI matrix
    double mi_matrix[SZ][SZ]; // to store the matrix
    

    // for UnionFind
    int parent[SZ];
    int rank[SZ];
    int num_sets;

    // cache the group by results
    std::unordered_map<uint32_t, uint32_t> C[SZ]; // a vector of hash maps
    // std::unordered_map<uint32_t, uint32_t> Cy;


    // chow liu tree
    std::vector<std::pair<double, std::pair<int, int>>> tree_edges;


    ChowLiuTreeBuilder()
    {
        memset(mi_matrix, 0, sizeof(mi_matrix)); // initialize the matrix to 0
        
        // initialize the UnionFind
        memset(parent, 0, sizeof(parent));
        memset(rank, 0, sizeof(rank));

        for (size_t i = 0; i < SZ; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
        num_sets = SZ;

    }
    
    // find the root of the set that x belongs to
    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // path compression
        return parent[x];
    }
    
    // union the sets that x and y belong to
    void union_sets(int x, int y)
    {
        int root_x = find(x);
        int root_y = find(y);
        
        if (root_x == root_y) // already in the same set
            return;
        
        if (rank[root_x] > rank[root_y]) {
            parent[root_y] = root_x; // attach root_y to root_x
            rank[root_x] += rank[root_y]; // update the rank of root_x
        } else {
            parent[root_x] = root_y; // attach root_x to root_y
            rank[root_y] += rank[root_x]; // update the rank of root_y
        }
        num_sets--;
    }
    
    // check if x and y are in the same set
    bool is_same_set(int x, int y)
    {
        return find(x) == find(y);
    }

    // build the chow liu tree from the MI matrix
    // using Kruskal's algorithm
    void build_chow_liu_tree()
    {
        // sort the edges in the MI matrix in descending order
        std::vector<std::pair<double, std::pair<int, int>>> edges;
        for (size_t i = 0; i < SZ; i++)
        {
            for (size_t j = i+1; j < SZ; j++)
            {
                edges.push_back(std::make_pair(mi_matrix[i][j], std::make_pair(i, j)));
            }
        }
        std::sort(edges.begin(), edges.end(), std::greater<std::pair<double, std::pair<int, int>>>());
        

        // build the chow liu tree
        for (size_t i = 0; i < edges.size(); i++)
        {
            int u = edges[i].second.first;
            int v = edges[i].second.second;
            if (!is_same_set(u, v))
            {
                // add the edge to the tree
                tree_edges.push_back(edges[i]);
                
                // union the sets that u and v belong to
                union_sets(u, v);
            }
        }
    }
    
    // print the chow liu tree
    void print_chow_liu_tree()
    {
        std::cout << std::endl << "Chow Liu Tree (<attr1> -- <attr2>: <weight>)" << std::endl;
        for (size_t i = 0; i < tree_edges.size(); i++)
        {
            std::cout << tree_edges[i].second.first << " -- " << tree_edges[i].second.second << ": " << tree_edges[i].first << std::endl;
        }
    }
    

    // build the MI matrix from the cofactor
    // the MI matrix is a SZ x SZ matrix
    // assume all variables are categorical
    void build_mi_matrix(const RingCofactorGeneral<0, 0, SZ> cofactor)
    {

        long count = cofactor.count;

        // cache the group by results
        for (size_t i = 0; i < SZ; i++)
        {
            // Cx[i].clear(); // do i need to clear the hash map?
            for (size_t j = 0; j < cofactor.relation_array[i].tuples.size(); j++)
            {
                uint32_t key = cofactor.relation_array[i].tuples[j].key;
                uint32_t value = cofactor.relation_array[i].tuples[j].value;
                C[i][key] = value;
            }
        }

        size_t idx_XY = 0; // index of the qudratic item for X, Y in the relation array
        // for each variable X
        for (size_t X = 0; X < SZ; X++)
        {
            // for each variable Y
            for (size_t Y = X; Y < SZ; Y++)
            {

                if (X == Y)
                {
                    // for keys of C[X] 
                    for (auto it = C[X].begin(); it != C[X].end(); it++)
                    {
                        uint32_t key = it->first;
                        uint32_t value = it->second;
                        mi_matrix[X][Y] += 1.0 * value / count * log2(count / value);
                    }
                }
                else 
                {
                    // index of X, Y in the relation array
                    const Dictionary *quadratic_XY = &cofactor.relation_array[SZ + idx_XY++]; 
                
                    // compute the MI between feactures X and Y
                    // for each pair of values x, y of X, Y
                    for (size_t i = 0; i < quadratic_XY->tuples.size(); i++)
                    {
                        // x, y in dom(X) x dom(Y)
                        const Tuple *tuple_xy = &quadratic_XY->tuples[i];
                        double Cxy = tuple_xy->value;
                        uint32_t x = tuple_xy->slots[0];
                        uint32_t y = tuple_xy->slots[1];

                        // compute the MI
                        mi_matrix[X][Y] += 1.0 * Cxy / count * log2(Cxy * count / (C[X][x] * C[Y][y]));

                    }

                }

                // symmetric
                mi_matrix[Y][X] = mi_matrix[X][Y];
            }
        }
    }
    
};

#endif /* CHOWLIUTREEBUILDER_HPP */