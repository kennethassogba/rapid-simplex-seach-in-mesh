/**
    Projet C++
    main.cpp
    Purpose: Test the implement methods

    @author Kenneth Assogba & Michaelis Dotse
    @version 1.1 27/01/20 
*/

//c++ -Wall main.cpp maillage.cpp EF2d-base.cpp -o main
//ou
//make main
//./main square-5.msh square-10.msh
//./main Th-50-1.msh Th-100-0.9.msh
#include "maillage.hpp"
#include <chrono>

int main(int argc, const char **argv)
{
    assert(argc > 1);
    Maillage Th(argv[1]);

    //Question 2
    int k = 10, a = 2;
    int SimplexOppose = Th.AdjSimplexOnOppositeVertex(k, a);
    cout << "Le triangle oppose a (k=" << k << ",a=" << a << ") est " << SimplexOppose << endl;

    //Question 3
    R2 P(0.5, 0.5);
    auto Q3t1 = std::chrono::high_resolution_clock::now();
    int Algo1 = Th.SimplexContainPoint(P);
    auto Q3t2 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(Q3t2 - Q3t1).count();

    cout << "Un triangle contenant P=(" << P.x << ',' << P.y << ") est " << Algo1 << endl;

    //Recurcif
    int Algo1rec = Th.SimplexContainPointRecursive(P);
    cout << "Un triangle contenant P=(" << P.x << ',' << P.y << ") est " << Algo1rec << endl;

    //Question 4
    if (argc > 2)
    {
        Maillage Thp(argv[2]);
        auto Q4t1 = std::chrono::high_resolution_clock::now();
        int *tab = Th.MeshInSimplex(Thp);
        auto Q4t2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(Q4t2 - Q4t1).count();

        for (int i = 0; i < Thp.nv; ++i)
        {
            if (tab[i] == -1)
                cout << "Le sommet " << i << " de " << argv[2] << " n'est pas dans le maillage " << argv[1] << endl;
            else
                cout << "Le sommet " << i << " de " << argv[2] << " est contenu dans le triangle " << tab[i] << " de " << argv[1] << endl;
        }
        cout << "Temps d'execution de l'algo final = " << duration2 << " microsecondes" << endl;
    }
    cout << "Temps d'execution de l'algo1 = " << duration1 << " microsecondes" << endl;

    return 0;
}