/***********************************************************************************************

* 								Drona Aviation

********************************************************************************


/* 3 X 3 matrix mutiplication, mat A and B as inputs and C = A X B */

void MatMul3by3(const float **matA, const float **matB, float **matC)

/* Determinant of mat A */

float MatDet3by3(const float **matA) 
/* 3 X 3 matrix addition, mat A and B as inputs and C = A + B */

void MatAdd3by3(const float **matA, const float **matB, float **matC)

/* Transpose of 3X3 mat A */

void MatTrans3by3(const float **matA, float **matB)


/* 3 X 3 matrix inverse */

void MatInv3by3(const float **matA, float **matB)


/* 2 X 2 matrix multiplication */

void MatMul2by2(const float **matA, const float **matB, float **matC)


/* 2 X 2 matrix determinant */

float MatDet2by2(const float **matA) 


/* 2 X 2 matrix addition, mat A and B as inputs and C = A + B */

void MatAdd2by2(const float **matA, const float **matB, float **matC)


/* Transpose of 2 X 2 mat A */

void MatTrans2by2(const float **matA, float **matB)

/* 2X2 matrix inverse */

void MatInv2by2(const float **matA, float **matB)


/* Matrix multiplied by scalar */

void MatScalarMult(const float **matA, const unsigned int row, const unsigned int col,const float scalar, float **matB)

/*Sum of two Matrices*/
void MatrixSum(const float **ipMat1, const float **ipMat2, const int8_t row, const int8_t col, float **opMat)


/*_______________ Quat to Rotation */
float** Quat2Rot(const float *quat)


/*________________ Rotation to Euler Angles_____________________*/
float* Rot2Euler(const float **rotMat)


/*Normalize Vector */
void NormArray(float *vec, const int8_t size)

/*Calculate Cross Skew Matrix */
float** crossSkew(const float *vec)

/*Quaternion Multiplication */
void QuatMultiply(const float ipVec1, const float ipVec2, float *opVec)

/* Euler Integration Quaternion */
void IntegrateEuler(
void KFpredict(float *gyroScope)
