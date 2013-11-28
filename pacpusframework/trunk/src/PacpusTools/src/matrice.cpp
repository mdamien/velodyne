// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
/// @author  Jean Laneurit <firstname.surname@utc.fr>
/// @date    April, 2010
// %pacpus:license}

#include <Pacpus/PacpusTools/matrice.h>

#include <cstdlib>
#include <iostream>

using ::std::cout;
using ::std::endl;

// Le constructeur :
matrice::matrice()
{
    n = 0;
    m = 0;
}
matrice::matrice(unsigned short int nl, unsigned short int nc)
{
    n = nl;
    m = nc;
    lignes = new ligne[n];
    for (unsigned short int i=0; i<n; ++i) {
        lignes[i] = new double[m];
    }
}

void matrice::Alloue(unsigned short int nl, unsigned short int nc)
{
    n = nl;
    m = nc;
    lignes = new ligne[n];
    for (unsigned short int i=0; i<n; ++i)
        lignes[i] = new double[m];
}

matrice::matrice(unsigned short int nl, unsigned short int nc, t_m type)
{
    n = nl;
    m = nc;
    lignes = new ligne[n];
    for (unsigned short int i=0; i<n; ++i)
        lignes[i] = new double[m];

    switch(type)
    {
    case ONES :
    {
        for (unsigned short int i=0; i<n; ++i) // Initialisation avec des 1
            for (unsigned short int j=0; j<m; ++j)
                lignes[i][j] = 1;
        break;
    }
    case ZEROS :
    {
        for (unsigned short int i=0; i<n; ++i) // Initialisation avec des 0
            for (unsigned short int j=0; j<m; ++j)
                lignes[i][j] = 0;
        break;
    }
    case IDENTITY :
    {
        if (n==m)
        {
            for (unsigned short int i=0; i<n; ++i)
            { // Initialisation en matrice identit�
                for (unsigned short int j=0; j<m; ++j)
                    lignes[i][j] = 0;
                lignes[i][i] = 1;
            }
        }
        else
        {
            cout<<"Matrice identit� doit �tre carr�";
            exit(0);
        }
        break;
    }
    }
}

// Le constructeur de copie :
matrice::matrice(const matrice &source)
{
    m = source.m;
    n = source.n;
    lignes = new ligne[n];   // Alloue.
    for (unsigned short int i=0; i<n; ++i)
    {
        lignes[i] = new double[m];
        for (unsigned short int j=0; j<m; ++j)  // Copie.
            lignes[i][j] = source.lignes[i][j];
    }
}

// Le destructeur :
matrice::~matrice(void)
{
    if (n!=0 && m!=0) {
        for (unsigned short int i=0; i<n; ++i)
            delete[] lignes[i];
        delete[] lignes;
    }
}

// L'op�rateur d'affectation :
matrice &matrice::operator=(const matrice &source)
{
    if (&source != this)
    {
        if (source.n!=n || source.m!=m)   // V�rifie lesdimensions.
        {
            if (n!=0 && m!=0) {
                for (unsigned short int i=0; i<n; ++i)
                    delete[] lignes[i];
                delete[] lignes;              // D�truit...
            }
            m = source.m;
            n = source.n;
            lignes = new ligne[n];        // et r�alloue.
            for (unsigned short i=0; i<n; ++i) lignes[i] = new double[m];
        }
        for (unsigned short int i=0; i<n; ++i) // Copie.
            for (unsigned short int j=0; j<m; ++j)
                lignes[i][j] = source.lignes[i][j];
    }
    return *this;
}

matrice &matrice::operator=(double x) {
    if (!n && !m) {
        cout << " =double : taille matrice inconnue";
        exit(0);
    }
    for (unsigned short int i=0; i<n; ++i) // Copie.
        for (unsigned short int j=0; j<m; ++j)
            lignes[i][j] = x;
    return *this;
}


// operateur m1 += m2;
matrice &matrice::operator+=(const matrice &source) {
    if (&source != this)
    {
        if (source.n!=n || source.m!=m)   // V�rifie lesdimensions.
        {
            cout << "addition : dimensions matrice incompatibles\n";
            exit(0);
        }
        for (unsigned short int i=0; i<n; ++i) // Addition
            for (unsigned short int j=0; j<m; ++j)
                lignes[i][j] =  lignes[i][j]+source.lignes[i][j];
    }
    return *this;
}

// operateur m1 -= m2;
matrice &matrice::operator-=(const matrice &source) {
    if (&source != this)
    {
        if (source.n!=n || source.m!=m)   // V�rifie lesdimensions.
        {
            cout << "soustraction : dimensions matrice incompatibles\n";
            exit(0);
        }
        for (unsigned short int i=0; i<n; ++i) // Addition
            for (unsigned short int j=0; j<m; ++j)
                lignes[i][j] =lignes[i][j]-source.lignes[i][j];
    }
    return *this;
}

// Addition :
matrice matrice::operator+(const matrice &m1) const
{

    if (m1.n!=n || m1.m!=m)   // V�rifie lesdimensions.
    {
        cout << "addition : dimensions matrice incompatibles\n";
        exit(0);
    }
    matrice tmp(n,m);
    for (unsigned short int i=0; i<n; i++)   // Double boucle.
        for (unsigned short int j=0; j<m; j++)
            tmp.lignes[i][j] = lignes[i][j]+m1.lignes[i][j];
    return tmp;
}

// Soustraction :
matrice matrice::operator-(const matrice &m1) const
{  
    if (m1.n!=n || m1.m!=m)   // V�rifie lesdimensions.
    { 
        cout << "soustraction : dimensions matrice incompatibles\n";
        exit(0);
    } 
    matrice tmp(n,m);
    for (unsigned short int i=0; i<n; i++)  // Double boucle.
        for (unsigned short int j=0; j<m; j++)
            tmp.lignes[i][j]=lignes[i][j]-m1.lignes[i][j];
    return tmp;
}

// Multiplication :
matrice matrice::operator*(const matrice &m1) const
{  

    if (m1.n!=m)   // V�rifie lesdimensions.
    { 
        cout << "multiplication : dimensions matrice incompatibles\n";
        exit(0);
    } 
    matrice tmp(n,m1.m);
    for (unsigned short int i=0; i<n; i++)  // Double boucle.
        for (unsigned short int j=0; j<m1.m; j++)
        {
            tmp.lignes[i][j]=0.;               // Produit scalaire.
            for (unsigned short int k=0; k<m; k++)
                tmp.lignes[i][j] += lignes[i][k]*m1.lignes[k][j];
        }
    return tmp;
}

//Addition avec un scalaire 
matrice &matrice::operator+=(double x) { 
    for (unsigned short int i=0; i<n; i++)  // Double boucle.
        for (unsigned short int j=0; j<m; j++)
            lignes[i][j] += x;
    return *this;
}

//soustraction avec un scalaire 
matrice &matrice::operator-=(double x) {
    for (unsigned short int i=0; i<n; i++)  // Double boucle.
        for (unsigned short int j=0; j<m; j++)
            lignes[i][j] -= x;
    return *this;
}

//Addition matrice avec scalaire
matrice matrice::operator+(double x)const{ 
    matrice tmp(n,m);
    for (unsigned short int i=0; i<n; i++)  // Double boucle.
        for (unsigned short int j=0; j<m; j++)
            tmp.lignes[i][j]=lignes[i][j]+x;
    return tmp;
}

//Soustraction matrice avec scalaire
matrice matrice::operator-(double x)const{
    matrice tmp(n,m);
    for (unsigned short int i=0; i<n; i++)  // Double boucle.
        for (unsigned short int j=0; j<m; j++)
            tmp.lignes[i][j] = lignes[i][j]-x;
    return tmp;
}

//Produit matrice avec scalaire
matrice matrice::operator*(double x)const{
    matrice tmp(n,m);
    for (unsigned short int i=0; i<n; i++)  // Double boucle.
        for (unsigned short int j=0; j<m; j++)
            tmp.lignes[i][j] = lignes[i][j]*x;
    return tmp;
}

//Division matrice par un scalaire
matrice matrice::operator/(double x)const{
    matrice tmp(n,m);
    for (unsigned short int i=0; i<n; i++)  // Double boucle.
        for (unsigned short int j=0; j<m; j++)
            tmp.lignes[i][j] = lignes[i][j]/x;
    return tmp;
}

//Transpose
matrice matrice::T()
{  
    matrice tmp(m,n);
    for (unsigned short int i=0; i<n; i++)  // Double boucle.
        for (unsigned short int j=0; j<m; j++)
            tmp.lignes[j][i]=lignes[i][j];
    return tmp;
}

//Inversion
//#define SWAP(a,b) {float temp=(a);(a)=(b);(b)=temp;}
#define ABS(x) ((x)<0 ? (-(x)) : (x))
matrice matrice::I()
{  
    matrice tmp = *this ;
    unsigned short int   *indxc,*indxr,*ipiv;
    unsigned short int    i,j,k,l,ll,icol=0,irow=0;
    double   big,dum,pivinv;

    indxc = new unsigned short int[n+1];
    indxr = new unsigned short int[n+1];
    ipiv  = new unsigned short int[n+1];

    for (j=1;j<=n;j++) ipiv[j]=0;
    for (i=1;i<=n;i++) {
        big=0.0;
        for (j=1;j<=n;j++) {
            if (ipiv[j] != 1) {
                for (k=1;k<=n;k++) {
                    if (ipiv[k] == 0) {
                        if (ABS(tmp.lignes[j-1][k-1]) >= big) {
                            big=ABS(tmp.lignes[j-1][k-1]) ;
                            irow=j;
                            icol=k;
                        }
                    } else if (ipiv[k] > 1) cout << "inversion : matrice singuli�re -type 1-";
                }
            }
        }
        ++(ipiv[icol]);
        if (irow != icol) {
            for (l=1;l<=n;l++) {
                std::swap(tmp.lignes[irow-1][l-1], tmp.lignes[icol-1][l-1]);
            }
        }
        indxr[i]=irow;
        indxc[i]=icol;
        if (tmp.lignes[icol-1][icol-1] == 0.0) cout << "inversion : matrice signuli�re -type 2-";
        pivinv=1.0/tmp.lignes[icol-1][icol-1];
        tmp.lignes[icol-1][icol-1]=1.0;
        for (l=1;l<=n;l++) tmp.lignes[icol-1][l-1] *= pivinv;
        for (ll=1;ll<=n;ll++) {
            if (ll != icol) {
                dum=tmp.lignes[ll-1][icol-1];
                tmp.lignes[ll-1][icol-1]=0.0;
                for (l=1;l<=n;l++) tmp.lignes[ll-1][l-1] -= tmp.lignes[icol-1][l-1]*dum;
            }
        }
    }
    for (l=n;l>=1;l--) {
        if (indxr[l] != indxc[l]) {
            for (k=1;k<=n;k++) {
                std::swap(tmp.lignes[k-1][indxr[l]-1],tmp.lignes[k-1][indxc[l]-1]);
            }
        }
    }
    delete []ipiv ;
    delete []indxr ;
    delete []indxc ;
    return tmp ;
}
//#undef SWAP
#undef ABS

// Op�rateur d'acc�s en �criture:
double &matrice::operator()(unsigned short int i,unsigned short int j)
{  
    if ((i-1<0) || (j-1<0) || (i-1>n) || (j-1>m)) { // v�rifie les indices
        cout << "�criture : indice incorrect " << i << "x" << j << '\n' ;
        exit(0);
    }
    return lignes[i-1][j-1];
} 

double &matrice::operator()(unsigned short int i)
{  
    if (i-1<0 || i-1>n*m) {
        cout << "lecture : indice incorrect" << i <<'\n' ;
        exit(0);
    }
    return **(lignes+i-1);
}

// Op�rateur d'acc�s en lecture:
double matrice::operator()(unsigned short int i, unsigned short int j) const
{  
    if ((i-1<0) || (j-1<0) || (i-1>n) || (j-1>m)) { // v�rifie les indices
        cout << "lecture : indice incorrect" << i << "x" << j<< '\n' ;
        exit(0);
    }
    return lignes[i-1][j-1];
} 

double matrice::operator()(unsigned short int i) const
{  
    if (i-1<0 || i-1>n*m) {
        cout << "lecture : indice incorrect" << i <<'\n' ;
        exit(0);
    }
    return **(lignes+i-1);
}

// Affiche la matrice
void matrice::print(const char *nom) {
    cout << "" << nom << " est une matrice[" << n << "x" << m << "]" << endl  ;

    for (unsigned short int i=0; i<n; ++i) {
        for (unsigned short int j=0; j<m; ++j) {
            cout << lignes[i][j] <<'\t';
        }
        cout << endl;
    }
    cout << endl ;
}
