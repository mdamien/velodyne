// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Jean Laneurit <firstname.surname@utc.fr>
/// @date    April, 2010
/// @version $Id: matrice.h 91 2013-05-19 10:32:48Z gdherbom $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Matrix algebra functions.
///
/// Detailed description.

#ifndef MATRIX_H
#define MATRIX_H

typedef enum
{
    ONES,
    ZEROS,
    IDENTITY
} t_m;

/// Simple matrix.
/// @todo Documentation
class matrice
{
    typedef double *ligne;
    ligne *lignes;
    unsigned short int n;   // Nombre de lignes (1erparamètre).
    unsigned short int m;   // Nombre de colonnes (2èmeparamètre).

public:
    /// Ctor
    matrice();
    /// Ctor
    matrice(unsigned short int nl, unsigned short int nc);
    /// Ctor
    matrice(unsigned short int nl, unsigned short int nc,t_m type);
    /// Copy ctor
    matrice(const matrice &source); //constructeur par copie
    /// Dtor
    virtual ~matrice(void);

    /// Allocates matrix data
    /// @todo Rename
    void Alloue(unsigned short int nl, unsigned short int nc);

    /// Assignment operator for matrix operand
    matrice &operator=(const matrice &m);//m=m1
    /// Assignment operator for scalar operand
    matrice &operator=(double x); //m=x
    /// Conversion operator to double
    /// @todo FIXME
    operator double() const
    {
        return **lignes;
    }

    /// @todo Documentation
    matrice &operator+=(const matrice &m); //m+=m1
    /// @todo Documentation
    matrice &operator-=(const matrice &m); //m-=m1

    /// @todo Documentation
    matrice operator+(const matrice &m1) const; //m=m1+m2
    /// @todo Documentation
    matrice operator-(const matrice &m1) const; //m=m1-m2
    /// @todo Documentation
    matrice operator*(const matrice &m1) const; //m=m1*m2

    /// @todo Documentation
    matrice &operator+=(double x); //m+=x
    /// @todo Documentation
    matrice &operator-=(double x); //m-=x

    /// @todo Documentation
    matrice operator+(double x)const; //m+x
    /// @todo Documentation
    matrice operator-(double x)const; //m-x
    /// @todo Documentation
    matrice operator*(double x)const; //m*x
    /// @todo Documentation
    matrice operator/(double x)const; //m/x

    /// @todo Documentation
    friend matrice operator+(double x,matrice m1) {return m1+x ;} // x+m ;
    /// @todo Documentation
    friend matrice operator-(double x,matrice m1) {return m1-x ;} // x-m ;
    /// @todo Documentation
    friend matrice operator*(double x,matrice m1) {return m1*x ;} // x*m ;

    /// Matrix transpose.
    matrice T();
    /// Matrix inverse.
    matrice I();

    /// @todo Documentation
    double &operator()(unsigned short int i, unsigned short int j); // ecriture m(i,j)=x
    /// @todo Documentation
    double operator()(unsigned short int i, unsigned short int j) const; //lecture x=m(i,j)
    /// @todo Documentation
    double &operator()(unsigned short int i); // ecriture m(i)=x
    /// @todo Documentation
    double operator()(unsigned short int i) const; //lecture x=m(i)

    /// @todo Documentation
    void print(const char *nom);
};

#endif // MATRIX_H
