/**
    Projet C++
    maillage.hpp
    Purpose: Extend the class Mesh2d

    @author Kenneth Assogba & Michaelis Dotse
    @version 1.1 27/01/20 
*/

#include "EF2d-base.hpp"

/**
    Class fille de Mesh2d avec les methodes du projet
*/
class Maillage : public Mesh2d
{
public:
    Maillage(const char *filename) : Mesh2d(filename) {}

    /**
    Recherche du triangle adjacent a l'arrete oppose a un sommet (Optimal).

    @param numTriangle le numero du triangle.
    @param numLocSommet le numero local du sommet dans le triangle.
    @return le triangle K' adjacent a numTriangle par l'arête numLocSommet.
    */
    int AdjSimplexOnOppositeVertex(int numTriangle, int numLocSommet);

    /**
    Recherche du triangle contenant un point donne (Algo1)

    @param P le point.
    @param K le numero du triangle de depart.
    @return le triangle contenant P.
    */
    int SimplexContainPoint(const R2 &P, int K = 0);

    /**
    Version recurcive de l'Algo 1

    @param P le point.
    @param K le numero du triangle de depart.
    @return le triangle contenant P.
    */
    int SimplexContainPointRecursive(const R2 &P, int K = 0);

    /**
    Pour deux maillages Th (courant) et Thp, recherche d'un triangle dans Th contenant les sommets de Thp
    Dans le cas d'un cercle, le rayon de Thp doit etre inferieur a celui de Th.

    @param Thp le maillage dont on cherche les points.
    @return un tableau donnant les triangles.
    */
    int *MeshInSimplex(Mesh2d const &Thp);
};