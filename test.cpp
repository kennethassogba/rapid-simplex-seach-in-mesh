/**
    Projet C++
    test.cpp
    Purpose: Unit and performance Test

    @author Kenneth Assogba & Michaelis Dotse
    @version 1.1 27/01/20 
*/
//c++ -Wall test.cpp maillage.cpp EF2d-base.cpp -o test
//ou
//make testt
//./test
#include <fstream>
#include <chrono>
#include "maillage.hpp"

int main(int argc, const char **argv)
{
    //Unit test
    //Pour verifier, afficher les deux maillages avec Freefem
    const char *sq5 = "square-5.msh";
    const char *sq10 = "square-10.msh";
    Maillage square5(sq5);
    Maillage square10(sq10);

    int *tab = square5.MeshInSimplex(square10);
    for (int i = 0; i < square10.nv; ++i)
    {
        cout << "Le sommet " << i << " de square-10 est contenu dans le triangle " << tab[i] << " de square-5" << endl;
    }

    //Perf Test
    //Tracer avec gnuplot
    //plot "perf" w l
    const char *sTh = "Th-50-1.msh";
    Maillage Th(sTh);
    const char *sThp[5] = {"Th-100-0.9.msh", "Th-200-0.9.msh", "Th-300-0.9.msh", "Th-400-0.9.msh", "Th-500-0.9.msh"};
    ofstream of("perf");
    for (int i = 0; i < 5; ++i)
    {
        Maillage Thp(sThp[i]);
        auto t1 = std::chrono::high_resolution_clock::now();
        Th.MeshInSimplex(Thp);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        of << (i + 1) * 100 << " " << duration << "\n"; // duree en fonction du nombre de points sur le bord
        // of << Thp.nv << " " << duration << "\n"; // duree en fonction du nombre de points du maillage
    }
    of.close();

    return 0;
}
