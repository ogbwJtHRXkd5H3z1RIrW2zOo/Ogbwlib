#include "Ogbwlib.h"
#include "matrix.h"


Vector Matrix_mult33xVect(Matrix33 m, Vector v) {
    return (Vector) {
            (m.m11*v.x + m.m12*v.y + m.m13*v.z),
            (m.m21*v.x + m.m22*v.y + m.m23*v.z),
            (m.m31*v.x + m.m32*v.y + m.m33*v.z)
    };
}

Quaternion Matrix_mult43xVect(Matrix43 m, Vector v) {
    return (Quaternion) {
            (m.m11*v.x + m.m12*v.y + m.m13*v.z),
            (m.m21*v.x + m.m22*v.y + m.m23*v.z),
            (m.m31*v.x + m.m32*v.y + m.m33*v.z),
            (m.m41*v.x + m.m42*v.y + m.m43*v.z)
    };
}

Vector Matrix_mult34xQuat(Matrix34 m, Quaternion q) {
    return (Vector) {
            (m.m11*q.q0 + m.m12*q.q1 + m.m13*q.q2 + m.m14*q.q3),
            (m.m21*q.q0 + m.m22*q.q1 + m.m23*q.q2 + m.m24*q.q3),
            (m.m31*q.q0 + m.m32*q.q1 + m.m33*q.q2 + m.m34*q.q3)
    };
}

Quaternion Matrix_mult44xQuat(Matrix44 m, Quaternion q) {
    return (Quaternion) {
            (m.m11*q.q0 + m.m12*q.q1 + m.m13*q.q2 + m.m14*q.q3),
            (m.m21*q.q0 + m.m22*q.q1 + m.m23*q.q2 + m.m24*q.q3),
            (m.m31*q.q0 + m.m32*q.q1 + m.m33*q.q2 + m.m34*q.q3),
            (m.m41*q.q0 + m.m42*q.q1 + m.m43*q.q2 + m.m44*q.q3)
    };
}


Matrix33 Matrix_mult33x33(Matrix33 m1, Matrix33 m2) {
    return (Matrix33) {
            (m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31),
            (m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32),
            (m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33),
            (m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31),
            (m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32),
            (m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33),
            (m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31),
            (m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32),
            (m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33)
    };
}

Matrix33 Matrix_mult34x43(Matrix34 m1, Matrix43 m2) {
    return (Matrix33) {
            (m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31 + m1.m14*m2.m41),
            (m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32 + m1.m14*m2.m42),
            (m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33 + m1.m14*m2.m43),
            (m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31 + m1.m24*m2.m41),
            (m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32 + m1.m24*m2.m42),
            (m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33 + m1.m24*m2.m43),
            (m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31 + m1.m34*m2.m41),
            (m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32 + m1.m34*m2.m42),
            (m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33 + m1.m34*m2.m43)
    };
}

Matrix34 Matrix_mult34x44(Matrix34 m1, Matrix44 m2) {
    return (Matrix34) {
            (m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31 + m1.m14*m2.m41),
            (m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32 + m1.m14*m2.m42),
            (m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33 + m1.m14*m2.m43),
            (m1.m11*m2.m14 + m1.m12*m2.m24 + m1.m13*m2.m34 + m1.m14*m2.m44),
            (m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31 + m1.m24*m2.m41),
            (m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32 + m1.m24*m2.m42),
            (m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33 + m1.m24*m2.m43),
            (m1.m21*m2.m14 + m1.m22*m2.m24 + m1.m23*m2.m34 + m1.m24*m2.m44),
            (m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31 + m1.m34*m2.m41),
            (m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32 + m1.m34*m2.m42),
            (m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33 + m1.m34*m2.m43),
            (m1.m31*m2.m14 + m1.m32*m2.m24 + m1.m33*m2.m34 + m1.m34*m2.m44)
    };
}

Matrix34 Matrix_mult33x34(Matrix33 m1, Matrix34 m2) {
    return (Matrix34) {
            (m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31),
            (m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32),
            (m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33),
            (m1.m11*m2.m14 + m1.m12*m2.m24 + m1.m13*m2.m34),
            (m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31),
            (m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32),
            (m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33),
            (m1.m21*m2.m14 + m1.m22*m2.m24 + m1.m23*m2.m34),
            (m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31),
            (m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32),
            (m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33),
            (m1.m31*m2.m14 + m1.m32*m2.m24 + m1.m33*m2.m34)
    };
}

Matrix43 Matrix_mult44x43(Matrix44 m1, Matrix43 m2) {
    return (Matrix43) {
            (m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31 + m1.m14*m2.m41),
            (m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32 + m1.m14*m2.m42),
            (m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33 + m1.m14*m2.m43),
            (m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31 + m1.m24*m2.m41),
            (m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32 + m1.m24*m2.m42),
            (m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33 + m1.m24*m2.m43),
            (m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31 + m1.m34*m2.m41),
            (m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32 + m1.m34*m2.m42),
            (m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33 + m1.m34*m2.m43),
            (m1.m41*m2.m11 + m1.m42*m2.m21 + m1.m43*m2.m31 + m1.m44*m2.m41),
            (m1.m41*m2.m12 + m1.m42*m2.m22 + m1.m43*m2.m32 + m1.m44*m2.m42),
            (m1.m41*m2.m13 + m1.m42*m2.m23 + m1.m43*m2.m33 + m1.m44*m2.m43)
    };
}

Matrix43 Matrix_mult43x33(Matrix43 m1, Matrix33 m2) {
    return (Matrix43) {
            (m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31),
            (m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32),
            (m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33),
            (m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31),
            (m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32),
            (m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33),
            (m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31),
            (m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32),
            (m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33),
            (m1.m41*m2.m11 + m1.m42*m2.m21 + m1.m43*m2.m31),
            (m1.m41*m2.m12 + m1.m42*m2.m22 + m1.m43*m2.m32),
            (m1.m41*m2.m13 + m1.m42*m2.m23 + m1.m43*m2.m33)
    };
}

Matrix44 Matrix_mult44x44(Matrix44 m1, Matrix44 m2) {
    return (Matrix44) {
            (m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31 + m1.m14*m2.m41),
            (m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32 + m1.m14*m2.m42),
            (m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33 + m1.m14*m2.m43),
            (m1.m11*m2.m14 + m1.m12*m2.m24 + m1.m13*m2.m34 + m1.m14*m2.m44),
            (m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31 + m1.m24*m2.m41),
            (m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32 + m1.m24*m2.m42),
            (m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33 + m1.m24*m2.m43),
            (m1.m21*m2.m14 + m1.m22*m2.m24 + m1.m23*m2.m34 + m1.m24*m2.m44),
            (m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31 + m1.m34*m2.m41),
            (m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32 + m1.m34*m2.m42),
            (m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33 + m1.m34*m2.m43),
            (m1.m31*m2.m14 + m1.m32*m2.m24 + m1.m33*m2.m34 + m1.m34*m2.m44),
            (m1.m41*m2.m11 + m1.m42*m2.m21 + m1.m43*m2.m31 + m1.m44*m2.m41),
            (m1.m41*m2.m12 + m1.m42*m2.m22 + m1.m43*m2.m32 + m1.m44*m2.m42),
            (m1.m41*m2.m13 + m1.m42*m2.m23 + m1.m43*m2.m33 + m1.m44*m2.m43),
            (m1.m41*m2.m14 + m1.m42*m2.m24 + m1.m43*m2.m34 + m1.m44*m2.m44)
    };
}

Matrix44 Matrix_mult43x34(Matrix43 m1, Matrix34 m2) {
    return (Matrix44) {
            (m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31),
            (m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32),
            (m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33),
            (m1.m11*m2.m14 + m1.m12*m2.m24 + m1.m13*m2.m34),
            (m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31),
            (m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32),
            (m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33),
            (m1.m21*m2.m14 + m1.m22*m2.m24 + m1.m23*m2.m34),
            (m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31),
            (m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32),
            (m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33),
            (m1.m31*m2.m14 + m1.m32*m2.m24 + m1.m33*m2.m34),
            (m1.m41*m2.m11 + m1.m42*m2.m21 + m1.m43*m2.m31),
            (m1.m41*m2.m12 + m1.m42*m2.m22 + m1.m43*m2.m32),
            (m1.m41*m2.m13 + m1.m42*m2.m23 + m1.m43*m2.m33),
            (m1.m41*m2.m14 + m1.m42*m2.m24 + m1.m43*m2.m34)
    };
}

Vector Matrix_addVect(Vector v1, Vector v2) {
    return (Vector) {
            v1.x+v2.x,
            v1.y+v2.y,
            v1.z+v2.z
    };
}

Quaternion Matrix_addQuat(Quaternion q1, Quaternion q2) {
    return (Quaternion) {
            q1.q0+q2.q0,
            q1.q1+q2.q1,
            q1.q2+q2.q2,
            q1.q3+q2.q3
    };
}

Matrix33 Matrix_add33(Matrix33 m1, Matrix33 m2) {
    return (Matrix33) {
            m1.m11+m2.m11, m1.m12+m2.m12, m1.m13+m2.m13,
            m1.m21+m2.m21, m1.m22+m2.m22, m1.m23+m2.m23,
            m1.m31+m2.m31, m1.m32+m2.m32, m1.m33+m2.m33
    };
}

Matrix34 Matrix_add34(Matrix34 m1, Matrix34 m2) {
    return (Matrix34) {
            m1.m11+m2.m11, m1.m12+m2.m12, m1.m13+m2.m13, m1.m14+m2.m14,
            m1.m21+m2.m21, m1.m22+m2.m22, m1.m23+m2.m23, m1.m24+m2.m24,
            m1.m31+m2.m31, m1.m32+m2.m32, m1.m33+m2.m33, m1.m34+m2.m34
    };
}

Matrix43 Matrix_add43(Matrix43 m1, Matrix43 m2) {
    return (Matrix43) {
            m1.m11+m2.m11, m1.m12+m2.m12, m1.m13+m2.m13,
            m1.m21+m2.m21, m1.m22+m2.m22, m1.m23+m2.m23,
            m1.m31+m2.m31, m1.m32+m2.m32, m1.m33+m2.m33,
            m1.m41+m2.m41, m1.m42+m2.m42, m1.m43+m2.m43
    };
}

Matrix44 Matrix_add44(Matrix44 m1, Matrix44 m2) {
    return (Matrix44) {
            m1.m11+m2.m11, m1.m12+m2.m12, m1.m13+m2.m13, m1.m14+m2.m14,
            m1.m21+m2.m21, m1.m22+m2.m22, m1.m23+m2.m23, m1.m24+m2.m24,
            m1.m31+m2.m31, m1.m32+m2.m32, m1.m33+m2.m33, m1.m34+m2.m34,
            m1.m41+m2.m41, m1.m42+m2.m42, m1.m43+m2.m43, m1.m44+m2.m44
    };
}

Vector Matrix_subVect(Vector v1, Vector v2) {
    return (Vector) {
            v1.x-v2.x,
            v1.y-v2.y,
            v1.z-v2.z
    };
}

Quaternion Matrix_subQuat(Quaternion q1, Quaternion q2) {
    return (Quaternion) {
            q1.q0-q2.q0,
            q1.q1-q2.q1,
            q1.q2-q2.q2,
            q1.q3-q2.q3
    };
}

Matrix33 Matrix_sub33(Matrix33 m1, Matrix33 m2) {
    return (Matrix33) {
            m1.m11-m2.m11, m1.m12-m2.m12, m1.m13-m2.m13,
            m1.m21-m2.m21, m1.m22-m2.m22, m1.m23-m2.m23,
            m1.m31-m2.m31, m1.m32-m2.m32, m1.m33-m2.m33
    };
}

Matrix34 Matrix_sub34(Matrix34 m1, Matrix34 m2) {
    return (Matrix34) {
            m1.m11-m2.m11, m1.m12-m2.m12, m1.m13-m2.m13, m1.m14-m2.m14,
            m1.m21-m2.m21, m1.m22-m2.m22, m1.m23-m2.m23, m1.m24-m2.m24,
            m1.m31-m2.m31, m1.m32-m2.m32, m1.m33-m2.m33, m1.m34-m2.m34
    };
}

Matrix43 Matrix_sub43(Matrix43 m1, Matrix43 m2) {
    return (Matrix43) {
            m1.m11-m2.m11, m1.m12-m2.m12, m1.m13-m2.m13,
            m1.m21-m2.m21, m1.m22-m2.m22, m1.m23-m2.m23,
            m1.m31-m2.m31, m1.m32-m2.m32, m1.m33-m2.m33,
            m1.m41-m2.m41, m1.m42-m2.m42, m1.m43-m2.m43
    };
}

Matrix44 Matrix_sub44(Matrix44 m1, Matrix44 m2) {
    return (Matrix44) {
            m1.m11-m2.m11, m1.m12-m2.m12, m1.m13-m2.m13, m1.m14-m2.m14,
            m1.m21-m2.m21, m1.m22-m2.m22, m1.m23-m2.m23, m1.m24-m2.m24,
            m1.m31-m2.m31, m1.m32-m2.m32, m1.m33-m2.m33, m1.m34-m2.m34,
            m1.m41-m2.m41, m1.m42-m2.m42, m1.m43-m2.m43, m1.m44-m2.m44
    };
}

Vector Matrix_addScalarVect(Vector v, float r) {
    return (Vector) {
            v.x+r,
            v.y+r,
            v.z+r
    };
}

Quaternion Matrix_addScalarQuat(Quaternion q, float r) {
    return (Quaternion) {
            q.q0+r,
            q.q1+r,
            q.q2+r,
            q.q3+r
    };
}

Matrix33 Matrix_addScalar33(Matrix33 m, float r) {
    return (Matrix33) {
            m.m11+r, m.m12+r, m.m13+r,
            m.m21+r, m.m22+r, m.m23+r,
            m.m31+r, m.m32+r, m.m33+r
    };
}

Matrix34 Matrix_addScalar34(Matrix34 m, float r) {
    return (Matrix34) {
            m.m11+r, m.m12+r, m.m13+r, m.m14+r,
            m.m21+r, m.m22+r, m.m23+r, m.m24+r,
            m.m31+r, m.m32+r, m.m33+r, m.m34+r
    };
}

Matrix43 Matrix_addScalar43(Matrix43 m, float r) {
    return (Matrix43) {
            m.m11+r, m.m12+r, m.m13+r,
            m.m21+r, m.m22+r, m.m23+r,
            m.m31+r, m.m32+r, m.m33+r,
            m.m41+r, m.m42+r, m.m43+r
    };
}

Matrix44 Matrix_addScalar44(Matrix44 m, float r) {
    return (Matrix44) {
            m.m11+r, m.m12+r, m.m13+r, m.m14+r,
            m.m21+r, m.m22+r, m.m23+r, m.m24+r,
            m.m31+r, m.m32+r, m.m33+r, m.m34+r,
            m.m41+r, m.m42+r, m.m43+r, m.m44+r
    };
}

Vector Matrix_multScalarVect(Vector m, float r) {
    return (Vector) {
            m.x*r,
            m.y*r,
            m.z*r
    };
}

Quaternion Matrix_multScalarQuat(Quaternion m, float r) {
    return (Quaternion) {
            m.q0*r,
            m.q1*r,
            m.q2*r,
            m.q3*r
    };
}

Matrix33 Matrix_multScalar33(Matrix33 m, float r) {
    return (Matrix33) {
            m.m11*r, m.m12*r, m.m13*r,
            m.m21*r, m.m22*r, m.m23*r,
            m.m31*r, m.m32*r, m.m33*r
    };
}

Matrix34 Matrix_multScalar34(Matrix34 m, float r) {
    return (Matrix34) {
            m.m11*r, m.m12*r, m.m13*r, m.m14*r,
            m.m21*r, m.m22*r, m.m23*r, m.m24*r,
            m.m31*r, m.m32*r, m.m33*r, m.m34*r
    };
}

Matrix43 Matrix_multScalar43(Matrix43 m, float r) {
    return (Matrix43) {
            m.m11*r, m.m12*r, m.m13*r,
            m.m21*r, m.m22*r, m.m23*r,
            m.m31*r, m.m32*r, m.m33*r,
            m.m41*r, m.m42*r, m.m43*r
    };
}

Matrix44 Matrix_multScalar44(Matrix44 m, float r) {
    return (Matrix44) {
            m.m11*r, m.m12*r, m.m13*r, m.m14*r,
            m.m21*r, m.m22*r, m.m23*r, m.m24*r,
            m.m31*r, m.m32*r, m.m33*r, m.m34*r,
            m.m41*r, m.m42*r, m.m43*r, m.m44*r
    };
}

Matrix33 Matrix_divScalar33(Matrix33 m, float r) {
    return (Matrix33) {
            m.m11/r, m.m12/r, m.m13/r,
            m.m21/r, m.m22/r, m.m23/r,
            m.m31/r, m.m32/r, m.m33/r
    };
}

Matrix34 Matrix_divScalar34(Matrix34 m, float r) {
    return (Matrix34) {
            m.m11/r, m.m12/r, m.m13/r, m.m14/r,
            m.m21/r, m.m22/r, m.m23/r, m.m24/r,
            m.m31/r, m.m32/r, m.m33/r, m.m34/r
    };
}

Matrix43 Matrix_divScalar43(Matrix43 m, float r) {
    return (Matrix43) {
            m.m11/r, m.m12/r, m.m13/r,
            m.m21/r, m.m22/r, m.m23/r,
            m.m31/r, m.m32/r, m.m33/r,
            m.m41/r, m.m42/r, m.m43/r
    };
}

Matrix44 Matrix_divScalar44(Matrix44 m, float r) {
    return (Matrix44) {
            m.m11/r, m.m12/r, m.m13/r, m.m14/r,
            m.m21/r, m.m22/r, m.m23/r, m.m24/r,
            m.m31/r, m.m32/r, m.m33/r, m.m34/r,
            m.m41/r, m.m42/r, m.m43/r, m.m44/r
    };
}


Matrix33 Matrix_transpose33(Matrix33 m) {
    return (Matrix33) {
            m.m11, m.m21, m.m31,
            m.m12, m.m22, m.m32,
            m.m13, m.m23, m.m33
    };
}

Matrix43 Matrix_transpose34(Matrix34 m) {
    return (Matrix43) {
            m.m11, m.m21, m.m31,
            m.m12, m.m22, m.m32,
            m.m13, m.m23, m.m33,
            m.m14, m.m24, m.m34
    };
}

Matrix34 Matrix_transpose43(Matrix43 m) {
    return (Matrix34) {
            m.m11, m.m21, m.m31, m.m41,
            m.m12, m.m22, m.m32, m.m42,
            m.m13, m.m23, m.m33, m.m43
    };
}

Matrix44 Matrix_transpose44(Matrix44 m) {
    return (Matrix44) {
            m.m11, m.m21, m.m31, m.m41,
            m.m12, m.m22, m.m32, m.m42,
            m.m13, m.m23, m.m33, m.m43,
            m.m14, m.m24, m.m34, m.m44
    };
}


float Matrix_det33(Matrix33 m) {
    return m.m11*m.m22*m.m33 +
            m.m12*m.m23*m.m31 +
            m.m13*m.m21*m.m32 -
            m.m11*m.m23*m.m32 -
            m.m12*m.m21*m.m33 -
            m.m13*m.m22*m.m31;
}

Matrix33 Matrix_inv33(Matrix33 m) {
    S32 det = Matrix_det33(m);
    return (Matrix33) {
        (m.m22*m.m33 - m.m23*m.m32)/det,  (m.m32*m.m13 - m.m12*m.m33)/det,  (m.m12*m.m23 - m.m22*m.m13)/det,
        (m.m23*m.m31 - m.m21*m.m33)/det,  (m.m11*m.m33 - m.m13*m.m31)/det,  (m.m21*m.m13 - m.m11*m.m23)/det,
        (m.m21*m.m32 - m.m31*m.m22)/det,  (m.m31*m.m12 - m.m11*m.m32)/det,  (m.m11*m.m22 - m.m12*m.m21)/det
    };
}
