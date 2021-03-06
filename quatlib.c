#include <stdio.h>
#include <math.h>
#include "matlib.h"

/*_____________________________Quat to Rotation_________________________ */
void Quat2Rot(const float *quat, float *rotMat){
	*(rotMat)   = pow(*(quat),2.0) -  pow(*(quat+1),2.0) -  pow(*(quat+2),2.0)  +  pow(*(quat+3),2.0)  ; 
	*(rotMat+1) = 2*((*(quat)) * (*(quat+1)) + (*(quat+2)) * (*(quat+3)));  
	*(rotMat+2) = 2*((*(quat+1)) * (*(quat+2)) - (*(quat+1)) * (*(quat+3)));  
 
	*(rotMat+3) = 2*( (*(quat+1)) * (*(quat)) - (*(quat+2)) * (*(quat+3)));   
	*(rotMat+4) = -pow(*(quat),2.0) + pow(*(quat+1), 2.0) - pow(*(quat+2), 2.0) + pow(*(quat+3), 2.0) ; 
	*(rotMat+5) = 2*( (*(quat+1)) * (*(quat+2)) + (*(quat)) * (*(quat+3)));   

	*(rotMat+6) = 2*((*(quat+2)) * (*(quat)) + (*(quat+1)) * (*(quat+3)) );   
	*(rotMat+7) = 2*((*(quat+2)) * (*(quat+1)) - (*(quat)) * (*(quat+3)));   
	*(rotMat+8) = -pow(*(quat), 2.0) - pow(*(quat+1), 2.0) + pow(*(quat+2), 2.0) + pow(*(quat+3), 2.0) ;
}


/*_______________________ Rotation to Euler Angles________________________*/
void Rot2Euler(const float *rotMat, float *eulerAngles){
	float sinth = -(*(rotMat+6));
	if (sinth > 1) {
		sinth = 1;
	} 
	else if (sinth < -1) {
		sinth = -1;
	}

	float theta = asin(sinth);
	float costh = sqrt(1 - sinth * sinth);

	float phi, psi;

	if (costh < 1.0e-6){
		phi = atan2((*(rotMat+1)), (*(rotMat+4)));
		psi = 0;
	} 
	else {
		phi = atan2((*(rotMat+7)), (*(rotMat+8)));
   	psi = atan2((*(rotMat+3)), (*(rotMat)));
	}
	
	*(eulerAngles)   = phi; 	// [-pi, pi]
	*(eulerAngles+1) = theta; // [-pi/2, pi/2]
	*(eulerAngles+2) = psi; 	// [-pi/2, pi/2]
}


/*Quaternion Multiplication */
void QuatMultiply(const float *ipVec1, const float *ipVec2, float *opVec){
  *(opVec)   = (*ipVec1) * (*(ipVec2))   - (*(ipVec1+1)) *  (*(ipVec2+1)) - (*(ipVec1+2)) * (*(ipVec2+2)) - (*(ipVec1+3)) * (*(ipVec2+3));
 
  *(opVec+1) = (*ipVec1) * (*(ipVec2+1)) + (*(ipVec2))   *  (*(ipVec1+1)) + (*(ipVec1+2)) * (*(ipVec2+3)) - (*(ipVec2+2)) * (*(ipVec1+3));

  *(opVec+2) = (*ipVec1) * (*(ipVec2+2)) + (*(ipVec2))   *  (*(ipVec1+2)) - (*(ipVec1+1)) * (*(ipVec2+3)) + (*(ipVec2+1)) * (*(ipVec1+3));

  *(opVec+3) = (*ipVec1) * (*(ipVec2+3)) + (*(ipVec2))   *  (*(ipVec1+3)) + (*(ipVec1+1)) * (*(ipVec2+2)) - (*(ipVec2+1)) * (*(ipVec1+2));

}


void Euler2Quat(const float angle[], float *quat){
	float t0 = cos(angle[2] * 0.5f);
	float t1 = sin(angle[2] * 0.5f);
	float t2 = cos(angle[0] * 0.5f);
	float t3 = sin(angle[0] * 0.5f);
	float t4 = cos(angle[1] * 0.5f);
	float t5 = sin(angle[1] * 0.5f);

	*(quat)   = t0 * t2 * t4 + t1 * t3 * t5;
	*(quat+1) = t0 * t3 * t4 - t1 * t2 * t5;
	*(quat+2) = t0 * t2 * t5 + t1 * t3 * t4;
	*(quat+3) = t1 * t2 * t4 - t0 * t3 * t5;
 

}

void Quat2Euler(const float *quat, float *angle){
	float ysqr = (*(quat+2)) * (*(quat+2));

	// roll (x-axis rotation)
	float t0 = +2.0f * ((*(quat)) * (*(quat+1)) + (*(quat+2)) * (*(quat+3)));
	float t1 = +1.0f - 2.0f * ((*(quat+1)) * (*(quat+1)) + ysqr);
	*angle = atan2(t0, t1);

	// pitch (y-axis rotation)
	float t2 = +2.0f * ((*(quat)) * (*(quat+2)) - (*(quat+3)) * (*(quat+1)));
	t2 = t2 > 1.0f ? 1.0f : t2;
	t2 = t2 < -1.0f ? -1.0f : t2;
	*(angle+1) = asin(t2);

	// yaw (z-axis rotation)
	float t3 = +2.0f * ((*(quat)) * (*(quat+3)) + (*(quat+1)) * (*(quat+2)));
	float t4 = +1.0f - 2.0f * (ysqr + (*(quat+3)) * (*(quat+3)));  
	*(angle+2) = atan2(t3, t4);

}

/* Rodrigues to Quaternion*/
void Rodrigues(const float *rodrigus, float *quat){
  unsigned int rodrigusSize[2] = {3, 1};
  float norm =  NormofMatrix((float *) rodrigus, rodrigusSize);
	*(quat) 	= norm;
	*(quat+1) = (*(rodrigus))/norm;
	*(quat+2) = (*(rodrigus+1))/norm;
	*(quat+3) = (*(rodrigus+2))/norm; 

}

/* Euler Integration Quaternion */
void IntegrateEuler(const float *quat_prv, const float *omega, const float dt, float *quat_updated){
	float omega_quat[4][1] = {{0.0}, {*(omega)}, {*(omega+1)}, {*(omega+2)}};
  QuatMultiply((float *) quat_prv, (float *) omega_quat, (float *) quat_updated);
  *(quat_updated)   = *(quat_prv) + 0.5 * dt * (*(quat_updated));
  *(quat_updated+1) = *(quat_prv+1)+ 0.5 * dt * (*(quat_updated+1));
  *(quat_updated+2) = *(quat_prv+2)+ 0.5 * dt * (*(quat_updated+2));
  *(quat_updated+3) = *(quat_prv+3)+ 0.5 * dt * (*(quat_updated+3));

}



