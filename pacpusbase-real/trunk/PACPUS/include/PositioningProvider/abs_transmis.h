/****************************************************************************/
/* Projet SY27 : Filtrage Particulaire                                      */
/*                                                                          */
/* Suiveur: Philippe Bonnifait                                              */
/* Date: Autonme 2005                                                       */
/*                                                                          */
/* Auteurs:                                                                 */
/*     Adrien Sanglier                                                      */
/*     Cyril Nahon                                                          */
/*                                                                          */
/* Licence: GNU/GPL 2                                                       */
/****************************************************************************/


#ifndef __ABS_H_TRANSMIS__
#define __ABS_H_TRANSMIS__

#include <windows.h>

typedef struct{        

	    float dist_parc_ar_d, dist_parc_ar_g;

}donnees_abs;

typedef struct{        

	    float dist_parc_ar_d, dist_parc_ar_g;
		float vitesse;

}donnees_abs_zy;


#endif
