#ifndef QUATLIB_H
#define QUATLIB_H

/*_____________________________Quat to Rotation_________________________ */
void Quat2Rot(const float *quat, float *rotMat);

/*_______________________ Rotation to Euler Angles________________________*/
void Rot2Euler(const float *rotMat, float *eulerAngles);

/*_______________________Quaternion Multiplication________________________ */
void QuatMultiply(const float *ipVec1, const float *ipVec2, float *opVec);

/*_______________________Euler to Quaternion______________________________ */
void Euler2Quat(const float angle[], float *quat);

/*________________ Rodrigues Representation to Quaternion_________________ */
void Rodrigues(const float *rodrigus, float *quat);

/*________________ Euler Integration Quaternion____________________________ */
void IntegrateEuler(const float *quat_prv, const float *omega, const float dt, float *quat_updated);
#endif
