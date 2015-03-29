#ifndef MATRICES_H
#define	MATRICES_H

typedef struct {
    float m11, m12, m13, m21, m22, m23, m31, m32, m33;
} Matrix33;

typedef struct {
    float m11, m12, m13, m21, m22, m23, m31, m32, m33, m41, m42, m43;
} Matrix43;

typedef struct {
    float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34;
} Matrix34;

typedef struct {
    float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;
} Matrix44;

typedef struct {
    float  x, y, z;
} Vector;

typedef struct {
    float q0, q1, q2, q3;
} Quaternion;




Vector Matrix_mult33xVect(Matrix33 m, Vector v);
Quaternion Matrix_mult43xVect(Matrix43 m, Vector v);
Vector Matrix_mult34xQuat(Matrix34 m, Quaternion q);
Quaternion Matrix_mult44xQuat(Matrix44 m, Quaternion q);
Matrix33 Matrix_mult33x33(Matrix33 m1, Matrix33 m2);
Matrix33 Matrix_mult34x43(Matrix34 m1, Matrix43 m2);
Matrix34 Matrix_mult34x44(Matrix34 m1, Matrix44 m2);
Matrix34 Matrix_mult33x34(Matrix33 m1, Matrix34 m2r);
Matrix43 Matrix_mult44x43(Matrix44 m1, Matrix43 m2);
Matrix43 Matrix_mult43x33(Matrix43 m1, Matrix33 m2);
Matrix44 Matrix_mult44x44(Matrix44 m1, Matrix44 m2);
Matrix44 Matrix_mult43x34(Matrix43 m1, Matrix34 m2);

Vector Matrix_addVect(Vector v1, Vector v2);
Quaternion Matrix_addQuat(Quaternion q1, Quaternion q2);
Matrix33 Matrix_add33(Matrix33 m1, Matrix33 m2);
Matrix34 Matrix_add34(Matrix34 m1, Matrix34 m2);
Matrix43 Matrix_add43(Matrix43 m1, Matrix43 m2);
Matrix44 Matrix_add44(Matrix44 m1, Matrix44 m2);

Vector Matrix_subVect(Vector v1, Vector v2);
Quaternion Matrix_subQuat(Quaternion q1, Quaternion q2);
Matrix33 Matrix_sub33(Matrix33 m1, Matrix33 m2);
Matrix34 Matrix_sub34(Matrix34 m1, Matrix34 m2);
Matrix43 Matrix_sub43(Matrix43 m1, Matrix43 m2);
Matrix44 Matrix_sub44(Matrix44 m1, Matrix44 m2);

Vector Matrix_addScalarVect(Vector v, float r);
Quaternion Matrix_addScalarQuat(Quaternion q, float r);
Matrix33 Matrix_addScalar33(Matrix33 m, float r);
Matrix34 Matrix_addScalar34(Matrix34 m, float r);
Matrix43 Matrix_addScalar43(Matrix43 m, float r);
Matrix44 Matrix_addScalar44(Matrix44 m, float r);

Vector Matrix_multScalarVect(Vector m, float r);
Quaternion Matrix_multScalarQuat(Quaternion m, float r);
Matrix33 Matrix_multScalar33(Matrix33 m, float r);
Matrix34 Matrix_multScalar34(Matrix34 m, float r);
Matrix43 Matrix_multScalar43(Matrix43 m, float r);
Matrix44 Matrix_multScalar44(Matrix44 m, float r);

Matrix33 Matrix_divScalar33(Matrix33 m, float r);
Matrix34 Matrix_divScalar34(Matrix34 m, float r);
Matrix43 Matrix_divScalar43(Matrix43 m, float r);
Matrix44 Matrix_divScalar44(Matrix44 m, float r);

Matrix33 Matrix_transpose33(Matrix33 m);
Matrix43 Matrix_transpose34(Matrix34 m);
Matrix34 Matrix_transpose43(Matrix43 m);
Matrix44 Matrix_transpose44(Matrix44 m);

float Matrix_det33(Matrix33 m);

Matrix33 Matrix_inv33(Matrix33 m);



#define Matrix_print33(mat)        UART1_printf(#mat " = [%.2f,%.2f,%.2f ; %.2f,%.2f,%.2f ; %.2f,%.2f,%.2f]\r\n", mat.m11, mat.m12, mat.m13, mat.m21, mat.m22, mat.m23, mat.m31, mat.m32, mat.m33);
#define  Matrix_print43(mat)       UART1_printf(#mat " = [%.2f,%.2f,%.2f ; %.2f,%.2f,%.2f ; %.2f,%.2f,%.2f ; %.2f,%.2f,%.2f]\r\n", mat.m11, mat.m12, mat.m13, mat.m21, mat.m22, mat.m23, mat.m31, mat.m32, mat.m33, mat.m41, mat.m42, mat.m43);
#define  Matrix_print34(mat)       UART1_printf(#mat " = [%.2f,%.2f,%.2f,%.2f ; %.2f,%.2f,%.2f,%.2f ; %.2f,%.2f,%.2f,%.2f]\r\n", mat.m11, mat.m12, mat.m13, mat.m14, mat.m21, mat.m22, mat.m23, mat.m24, mat.m31, mat.m32, mat.m33, mat.m34);
#define  Matrix_print44(mat)       UART1_printf(#mat " = [%.2f,%.2f,%.2f,%.2f ; %.2f,%.2f,%.2f,%.2f ; %.2f,%.2f,%.2f,%.2f ; %.2f,%.2f,%.2f,%.2f]\r\n", mat.m11, mat.m12, mat.m13, mat.m14, mat.m21, mat.m22, mat.m23, mat.m24, mat.m31, mat.m32, mat.m33, mat.m34, mat.m41, mat.m42, mat.m43, mat.m44);
#define  Matrix_printVect(v)         UART1_printf(#v " = [%.2f,%.2f,%.2f]\r\n", , v.x, v.y, v.z);
#define  Matrix_printQuat(q)     UART1_printf(#q " = [%.2f,%.2f,%.2f,%.2f]\r\n", q.q0, q.q1, q.q2, q.q3);






#endif	/* MATRICES_H */

