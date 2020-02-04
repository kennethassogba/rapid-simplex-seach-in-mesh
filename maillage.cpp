/**
    Projet C++
    maillage.cpp
    Purpose: Extend the class Mesh2d

    @author Kenneth Assogba & Michaelis Dotse
    @version 1.1 27/01/20 
*/

#include "maillage.hpp"
#include <algorithm>

/**
    Recherche du triangle adjacent a l'arrete oppose a un sommet (Optimal).

    @param numTriangle le numero du triangle.
    @param numLocSommet le numero local du sommet dans le triangle.
    @return le triangle K' adjacent a numTriangle par l'arête numLocSommet.
    */
int Maillage::AdjSimplexOnOppositeVertex(int numTriangle, int numLocSommet)
{
    //On verifie que a=0,1,2
    assert(numLocSommet == 0 || numLocSommet == 1 || numLocSommet == 2);
    //Les deux autres sommets dans le sens trigo
    int j0 = (*this)(numTriangle, (numLocSommet + 1) % 3);
    int j1 = (*this)(numTriangle, (numLocSommet + 2) % 3);

    bool finded = false;
    int t = 0;

    while (t < nt && finded == false)
    {
        if (t != numTriangle)
        {
            for (int a = 0; a < 3; ++a)
            {
                int i0 = (*this)(t, (a + 1) % 3);
                int i1 = (*this)(t, (a + 2) % 3);
                if ((i0 == j0 && i1 == j1) || (i0 == j1 && i1 == j0))
                {
                    finded = true;
                    break;
                }
            }
        }
        t++;
    }

    if (finded)
        return t - 1;
    else
        return -1;
}

/**
    Recherche du triangle contenant un point donne (Algo1)

    @param P le point.
    @param K le numero du triangle de depart.
    @return le triangle contenant P.
    */
int Maillage::SimplexContainPoint(const R2 &P, int K)
{
    assert(K >= 0 && K <= nt);
    bool finded = false;

    while (finded == false)
    {
        R2 v[3];
        for (int i = 0; i < 3; ++i)
            v[i] = (*this)[K][i];

        //int Kp=K;
        int m = 0, nextT = 0;
        while (m < 3)
        {
            double mes = det(v[m], v[(m + 1) % 3], P) * 0.5;
            if (mes < 0)
            {
                nextT = AdjSimplexOnOppositeVertex(K, (m + 2) % 3);
                if (nextT != -1)
                {
                    K = nextT;
                    break;
                }
            }
            m++;
        }

        //Decommenter pour afficher les differentes etapes de l'algorithme et aussi decommenter la ligne int Kp=K
        /*
        if(m==3){
        	if(t==-1)
        		cout <<"Le point P=(" << P.x << ',' << P.y << ") n'est pas dans le maillage "<<endl;
        	else
        		cout <<"Le point P=(" << P.x << ',' << P.y << ") est dans le triangle "<<K<< endl;
        }else
        	cout << "Le point P=(" << P.x << ',' << P.y << ") n'est pas dans le triangle "<<Kp<<". On passe au triangle " <<K<< endl;
        */

        //Si le point est dans 1 triangle (3 aires positives)
        //ou si le point n'est pas dans le maillage
        if (m == 3)
        {
            finded = true;
            if (nextT == -1)
                return -1; //Point exterieur
        }
    }
    return K;
}

/**
    Version recurcive de l'Algo 1

    @param P le point.
    @param K le numero du triangle de depart.
    @return le triangle contenant P.
    */
int Maillage::SimplexContainPointRecursive(const R2 &P, int K)
{
    assert(K >= 0 && K <= nt);
    double aires[3];
    double mes = 0;
    for (int a = 0; a < 3; ++a)
    {
        //Coordonnees du sommet a et de son successeur
        R2 A1 = (*this)[K][a];
        R2 A2 = (*this)[K][(a + 1) % 3];
        //Aire signee(a,(a+1)%3,P)
        mes = det(A1, A2, P) * 0.5;
        aires[a] = mes;
    }

    if (aires[0] >= 0 && aires[1] >= 0 && aires[2] >= 0)
    {
        return K;
    }
    else
    {
        //Il y a au moins une aire negative, prenons la plus petite
        double min = aires[0];
        int imin = 0;
        for (int i = 1; i < 3; i++)
        {
            if (aires[i] < min)
            {
                min = aires[i];
                imin = i;
            }
        }

        int ap = (imin + 2) % 3;                            //Point oppose a l'arrete imin
        int Kp = (*this).AdjSimplexOnOppositeVertex(K, ap); //Triangle adjacent a l'arrete imin
        return (*this).SimplexContainPoint(P, Kp);          //Appel de la fonction avec K'
    }
}

/**
    Pour deux maillages Th (courant) et Thp, recherche d'un triangle dans Th contenant les sommets de Thp
    Dans le cas d'un cercle, le rayon de Thp doit etre inferieur a celui de Th.
    Si un point n'est contenu dans aucun triangle, on retourne -1.

    @param Thp le maillage dont on cherche les points.
    @return un tableau donnant les triangles.
    */
int *Maillage::MeshInSimplex(Mesh2d const &Thp)
{
    int *tt = new int[Thp.nv];
    std::fill_n(tt, Thp.nv, -1); //initialise tt a -1
    int Kd = 0, K1 = 0;
    for (int k = 0; k < Thp.nt; ++k)
    {
        for (int a = 0; a < 3; ++a)
        {
            if (tt[Thp(k, a)] == -1)
            {
                R2 P = Thp[k][a];
                K1 = (*this).SimplexContainPoint(P, Kd);
                tt[Thp(k, a)] = K1;
                if (K1 != -1)
                    Kd = K1;
            }
        }
    }
    return tt;
}