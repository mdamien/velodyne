// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Firstname Surname <firstname.surname@utc.fr>
/// @date    Month, Year
/// @version $Id: rng.hpp 76 2013-01-10 17:05:10Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Random number generators.
///
/// Detailed description.

#ifndef __BOOST_RNG__
#define __BOOST_RNG__

#include <boost/random.hpp>
#include <boost/math/distributions.hpp>
#include <ctime>

namespace math {

namespace rng {

/// This class is basic normal random number generator
///
/// @tparam RealType describe number precision, e.g. @c float, @c double
/// @tparam PRNG describe pseudo random number generator
/// @see boost::random
template <class RealType, class PRNG>
class normal_generator
{
public:
    /// Default construtor
    normal_generator()
        : engine(time(NULL))
        , generator(engine,boost::normal_distribution<RealType>(0,1))
    {}

    /// Construtor
    ///
    /// @param dist a normal distribution
    /// @see boost::distributions
    normal_generator(const boost::math::normal_distribution<RealType> & dist)
        : engine(time(NULL))
        , generator(engine,boost::normal_distribution<RealType>(dist.mean(),dist.sigma()))
    {}

    /// Constructor
    ///
    /// @param mean mean of the normal distribution 
    /// @param sigma standard deviation of the normal distribution
    normal_generator(const RealType & mean ,const RealType & sigma)
        : engine(time(NULL))
        , generator(engine,boost::normal_distribution<RealType>(mean(),sigma()))
    {}

    /// Get a random number
    RealType operator()()
    {
        return generator();
    }

    /// Set normal distribution
    ///
    /// @param dist : a normal distribution
    /// @see boost::distributions
    void distribution( const boost::math::normal_distribution<RealType> & dist)
    { 
        generator.dist= boost::normal_distribution<RealType>(dist.mean(),dist.standard_deviation());
    }

    /// Set normal distrubution
    ///
    /// @param mean : mean of the normal distribution 
    /// @param sigma : satndard deviation of the normal distribution
    void distribution( const RealType & mean ,const RealType & sigma) { 
        generator.distribution()= boost::normal_distribution<RealType>(mean,sigma);
    }

private:
    /// pseudorandom number generator
    PRNG engine; 

    /// the normal random number generator
    boost::variate_generator<PRNG, boost::normal_distribution<RealType> > generator;
};

/// Defines normal random number generator as a Mersenne Twister 19937 with double-precision numbers
typedef class normal_generator<double, boost::mt19937> normal_rng;

/// This class is basic uniform random number generator.
///
/// @tparam RealType describe number precision, e.g. @c float, @c double
/// @tparam PRNG describe pseudo random number generator
/// @see boost::random
template <class RealType, class PRNG>
class uniform_generator
{
public:
    /// Default construtor
    uniform_generator()
        : engine(time(NULL))
        , generator(engine, boost::uniform_real<RealType>(0,1))
    {}

    /// Construtor
    /// @param dist a uniform distribution
    /// @see boost::distributions
    uniform_generator(const boost::math::uniform_distribution<RealType> & dist)
        : engine(time(NULL))
        , generator(engine, boost::uniform_real<RealType>(dist.lower(),dist.upper()))
    {}
    
    /// Constructor
    ///
    /// @param lower the lower value of the uniform distribution
    /// @param upper the upper value of the uniform distribution
    uniform_generator(const RealType & lower , const RealType & upper)
        : engine(time(NULL))
        , generator(engine, boost::uniform_real<RealType>(lower,upper))
    {}

    /// Get a random number
    RealType operator()()
    {
        return generator();
    }

    /// Set uniform distribution
    ///
    /// @param dist a normal distribution
    /// @see boost::distributions
    void distribution( const boost::math::uniform_distribution<RealType> & dist)
    {
        generator.dist()= boost::uniform_real<RealType>(dist.lower(),dist.upper());
    }

    /// Set uniform distribution
    ///
    /// @param lower the lower value of the uniform distribution
    /// @param upper the upper value of the uniform distribution
    void distribution( const RealType & lower , const RealType & upper)
    {
        generator.dist()= boost::uniform_real<RealType>(lower,upper);
    }

private:
    /// @brief pseudo random number generator
    PRNG engine;
    /// @brief the uniform random number generator
    boost::variate_generator<PRNG, boost::uniform_real<RealType> > generator;
};

/// Defines uniform random number generator as a Mersenne Twister 19937 with double-precision numbers
typedef class uniform_generator<double, boost::mt19937> uniform_rng;

/// This class is basic triangular random number generator
///
/// @tparam RealType describe number precision, e.g. @c float, @c double
/// @tparam PRNG describe pseudo random number generator ( see boost random)
template <class RealType, class PRNG>
class triangle_generator
{
public: 
    /// Default construtor
    triangle_generator()
        : engine(time(NULL))
        , generator(engine, boost::triangle_distribution<RealType>(-1,0,1))
    {}

    /// Construtor
    ///
    /// @param dist : a traingle distribution
    /// @see boost distributions
    triangle_generator(const boost::math::triangular_distribution<RealType> & dist)
        : engine(time(NULL))
        ,generator(engine, boost::triangle_distribution<RealType>(dist.lower(),dist.upper()))
    {}

    /// Constructor
    ///
    /// @param lower the lower value of the uniform distribution 
    /// @param mode the mode value of the uniform distribution 
    /// @param upper the upper value of the uniform distribution
    triangle_generator(const RealType & lower, const RealType & mode ,const RealType & upper)
        : engine(time(NULL))
        , generator(engine, boost::triangle_distribution<RealType>(lower,mode,upper))
    {}

    /// Get a random number
    RealType operator()()
    {
        return generator();
    }

    /// Set triangle distribution
    /// @param dist a normal distribution
    /// @see boost::distributions
    void distribution( const boost::math::triangular_distribution<RealType> & dist)
    {
        generator.dist()= boost::triangle_distribution<RealType>(dist.lower(),dist.mode(),dist.upper());
    }

    /// Set triangle distribution
    /// @param lower    the lower value of the uniform distribution 
    /// @param mode     the mode value of the uniform distribution 
    /// @param upper    the upper value of the uniform distribution
    void distribution( const RealType & lower, const RealType & mode ,const RealType & upper)
    {
        generator.dist()= boost::triangle_distribution<RealType>(lower,mode,upper);
    }

private :
    /// pseudorandom number generator
    PRNG engine;
    /// the triangle random number generator
    boost::variate_generator<PRNG, boost::triangle_distribution<RealType> > generator;
};

typedef class triangle_generator<double, boost::mt19937> triangle_rng;

} // namespace rng
} // namespace math

#endif // __BOOST_RNG__
