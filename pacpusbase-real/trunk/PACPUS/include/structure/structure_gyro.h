

#ifndef __structure_gyro_h__
#define __structure_gyro_h__


typedef struct{
  // les mesures sont prises par rapport au point C
  // position de la centrale inertielle

  // angle de lacet (rad) dans le repere de la masse suspendue
  float psi_s ;
  // vitesse de lacet (rad.s-1) dans le repere de la masse suspendue
  float p_psi_s;
}data_gyroKVH;


#endif // structure_gyro_h__
