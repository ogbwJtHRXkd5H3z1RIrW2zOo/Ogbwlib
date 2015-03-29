
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

Matrix33 Matrix_mult33x33(Matrix33 m1, Matrix33 m2) {
    return (Matrix33) {
            m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31,
            m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32,
            m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33,
            m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31,
            m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32,
            m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33,
            m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31,
            m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32,
            m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33
    };
}

Matrix33 Matrix_mult34x43(Matrix34 m1, Matrix43 m2) {
    return (Matrix33) {
            m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31 + m1.m14*m2.m41,
            m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32 + m1.m14*m2.m42,
            m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33 + m1.m14*m2.m43,
            m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31 + m1.m24*m2.m41,
            m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32 + m1.m24*m2.m42,
            m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33 + m1.m24*m2.m43,
            m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31 + m1.m34*m2.m41,
            m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32 + m1.m34*m2.m42,
            m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33 + m1.m34*m2.m43
    };
}

Matrix34 Matrix_mult34x44(Matrix34 m1, Matrix44 m2) {
    return (Matrix34) {
            m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31 + m1.m14*m2.m41,
            m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32 + m1.m14*m2.m42,
            m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33 + m1.m14*m2.m43,
            m1.m11*m2.m14 + m1.m12*m2.m24 + m1.m13*m2.m34 + m1.m14*m2.m44,
            m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31 + m1.m24*m2.m41,
            m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32 + m1.m24*m2.m42,
            m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33 + m1.m24*m2.m43,
            m1.m21*m2.m14 + m1.m22*m2.m24 + m1.m23*m2.m34 + m1.m24*m2.m44,
            m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31 + m1.m34*m2.m41,
            m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32 + m1.m34*m2.m42,
            m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33 + m1.m34*m2.m43,
            m1.m31*m2.m14 + m1.m32*m2.m24 + m1.m33*m2.m34 + m1.m34*m2.m44
    };
}

Matrix34 Matrix_mult33x34(Matrix33 m1, Matrix34 m2) {
    return (Matrix34) {
            m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31,
            m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32,
            m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33,
            m1.m11*m2.m14 + m1.m12*m2.m24 + m1.m13*m2.m34,
            m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31,
            m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32,
            m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33,
            m1.m21*m2.m14 + m1.m22*m2.m24 + m1.m23*m2.m34,
            m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31,
            m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32,
            m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33,
            m1.m31*m2.m14 + m1.m32*m2.m24 + m1.m33*m2.m34
    };
}

Matrix43 Matrix_mult44x43(Matrix44 m1, Matrix43 m2) {
    return (Matrix43) {
            m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31 + m1.m14*m2.m41,
            m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32 + m1.m14*m2.m42,
            m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33 + m1.m14*m2.m43,
            m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31 + m1.m24*m2.m41,
            m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32 + m1.m24*m2.m42,
            m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33 + m1.m24*m2.m43,
            m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31 + m1.m34*m2.m41,
            m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32 + m1.m34*m2.m42,
            m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33 + m1.m34*m2.m43,
            m1.m41*m2.m11 + m1.m42*m2.m21 + m1.m43*m2.m31 + m1.m44*m2.m41,
            m1.m41*m2.m12 + m1.m42*m2.m22 + m1.m43*m2.m32 + m1.m44*m2.m42,
            m1.m41*m2.m13 + m1.m42*m2.m23 + m1.m43*m2.m33 + m1.m44*m2.m43
    };
}

Matrix43 Matrix_mult43x33(Matrix43 m1, Matrix33 m2) {
    return (Matrix43) {
            m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31,
            m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32,
            m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33,
            m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31,
            m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32,
            m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33,
            m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31,
            m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32,
            m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33,
            m1.m41*m2.m11 + m1.m42*m2.m21 + m1.m43*m2.m31,
            m1.m41*m2.m12 + m1.m42*m2.m22 + m1.m43*m2.m32,
            m1.m41*m2.m13 + m1.m42*m2.m23 + m1.m43*m2.m33
    };
}

Matrix44 Matrix_mult44x44(Matrix44 m1, Matrix44 m2) {
    return (Matrix44) {
            m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31 + m1.m14*m2.m41,
            m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32 + m1.m14*m2.m42,
            m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33 + m1.m14*m2.m43,
            m1.m11*m2.m14 + m1.m12*m2.m24 + m1.m13*m2.m34 + m1.m14*m2.m44,
            m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31 + m1.m24*m2.m41,
            m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32 + m1.m24*m2.m42,
            m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33 + m1.m24*m2.m43,
            m1.m21*m2.m14 + m1.m22*m2.m24 + m1.m23*m2.m34 + m1.m24*m2.m44,
            m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31 + m1.m34*m2.m41,
            m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32 + m1.m34*m2.m42,
            m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33 + m1.m34*m2.m43,
            m1.m31*m2.m14 + m1.m32*m2.m24 + m1.m33*m2.m34 + m1.m34*m2.m44,
            m1.m41*m2.m11 + m1.m42*m2.m21 + m1.m43*m2.m31 + m1.m44*m2.m41,
            m1.m41*m2.m12 + m1.m42*m2.m22 + m1.m43*m2.m32 + m1.m44*m2.m42,
            m1.m41*m2.m13 + m1.m42*m2.m23 + m1.m43*m2.m33 + m1.m44*m2.m43,
            m1.m41*m2.m14 + m1.m42*m2.m24 + m1.m43*m2.m34 + m1.m44*m2.m44
    };
}

Matrix44 Matrix_mult43x34(Matrix43 m1, Matrix34 m2) {
    return (Matrix44) {
            m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31,
            m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32,
            m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33,
            m1.m11*m2.m14 + m1.m12*m2.m24 + m1.m13*m2.m34,
            m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31,
            m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32,
            m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33,
            m1.m21*m2.m14 + m1.m22*m2.m24 + m1.m23*m2.m34,
            m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31,
            m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32,
            m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33,
            m1.m31*m2.m14 + m1.m32*m2.m24 + m1.m33*m2.m34,
            m1.m41*m2.m11 + m1.m42*m2.m21 + m1.m43*m2.m31,
            m1.m41*m2.m12 + m1.m42*m2.m22 + m1.m43*m2.m32,
            m1.m41*m2.m13 + m1.m42*m2.m23 + m1.m43*m2.m33,
            m1.m41*m2.m14 + m1.m42*m2.m24 + m1.m43*m2.m34
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
    return (Matrix33) {
            m1.m11+m2.m11, m1.m12+m2.m12, m1.m13+m2.m13, m1.m14+m2.m14,
            m1.m21+m2.m21, m1.m22+m2.m22, m1.m23+m2.m23, m1.m24+m2.m24,
            m1.m31+m2.m31, m1.m32+m2.m32, m1.m33+m2.m33, m1.m34+m2.m34,
            m1.m41+m2.m41, m1.m42+m2.m42, m1.m43+m2.m43, m1.m44+m2.m44
    };
}

Matrix33 Matrix_addFloat33(Matrix33 m, float r) {
    return (Matrix33) {
            m.m11+r, m.m12+r, m.m13+r,
            m.m21+r, m.m22+r, m.m23+r,
            m.m31+r, m.m32+r, m.m33+r
    };
}

Matrix34 Matrix_addFloat34(Matrix34 m, float r) {
    return (Matrix34) {
            m.m11+r, m.m12+r, m.m13+r, m.m14+r,
            m.m21+r, m.m22+r, m.m23+r, m.m24+r,
            m.m31+r, m.m32+r, m.m33+r, m.m34+r
    };
}

Matrix43 Matrix_addFloat43(Matrix43 m, float r) {
    return (Matrix43) {
            m.m11+r, m.m12+r, m.m13+r,
            m.m21+r, m.m22+r, m.m23+r,
            m.m31+r, m.m32+r, m.m33+r,
            m.m41+r, m.m42+r, m.m43+r
    };
}

Matrix44 Matrix_addFloat44(Matrix44 m, float r) {
    return (Matrix33) {
            m.m11+r, m.m12+r, m.m13+r, m.m14+r,
            m.m21+r, m.m22+r, m.m23+r, m.m24+r,
            m.m31+r, m.m32+r, m.m33+r, m.m34+r,
            m.m41+r, m.m42+r, m.m43+r, m.m44+r
    };
}

Matrix33 Matrix_multFloat33(Matrix33 m, float r) {
    return (Matrix33) {
            m.m11*r, m.m12*r, m.m13*r,
            m.m21*r, m.m22*r, m.m23*r,
            m.m31*r, m.m32*r, m.m33*r
    };
}

Matrix34 Matrix_multFloat34(Matrix34 m, float r) {
    return (Matrix34) {
            m.m11*r, m.m12*r, m.m13*r, m.m14*r,
            m.m21*r, m.m22*r, m.m23*r, m.m24*r,
            m.m31*r, m.m32*r, m.m33*r, m.m34*r
    };
}

Matrix43 Matrix_multFloat43(Matrix43 m, float r) {
    return (Matrix43) {
            m.m11*r, m.m12*r, m.m13*r,
            m.m21*r, m.m22*r, m.m23*r,
            m.m31*r, m.m32*r, m.m33*r,
            m.m41*r, m.m42*r, m.m43*r
    };
}

Matrix44 Matrix_multFloat44(Matrix44 m, float r) {
    return (Matrix33) {
            m.m11*r, m.m12*r, m.m13*r, m.m14*r,
            m.m21*r, m.m22*r, m.m23*r, m.m24*r,
            m.m31*r, m.m32*r, m.m33*r, m.m34*r,
            m.m41*r, m.m42*r, m.m43*r, m.m44*r
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
    return m.m11*m.m22*m.m33 + m.m12*m.m23*m.m31 + m.m13*m.m21*m.m32 - m.m11*m.m23*m.m32 - m.m12*m.m21*m.m33 - m.m13*m.m22*m.m31;
}

Matrix33 Matrix_inv33(Matrix33 m) {
    float det = Matrix_det33(m);
    return (Matrix33) {
        (m.m22*m.m33 - m.m23*m.m32)/det,  (m.m32*m.m13 - m.m12*m.m33)/det,  (m.m12*m.m23 - m.m22*m.m13)/det,
        (m.m23*m.m31 - m.m21*m.m33)/det,  (m.m11*m.m33 - m.m13*m.m31)/det,  (m.m21*m.m13 - m.m11*m.m23)/det,
        (m.m21*m.m32 - m.m31*m.m22)/det,  (m.m31*m.m12 - m.m11*m.m32)/det,  (m.m11*m.m22 - m.m12*m.m21)/det
    };
}




void Matrix_invSym66(Matrix33 B, Matrix33 C, Matrix33 D, Matrix33* out11, Matrix33* out21, Matrix33* out22) {
    Matrix33 B_1 = Matrix_inv33(B);
    Matrix33 CB_1 = Matrix_mult33x33(C, B_1);
    Matrix33 CT = Matrix_transpose33(C);
    Matrix33 S = Matrix_add33(D, Matrix_multFloat33(Matrix_mult33x33(CB_1, CT),-1));
    Matrix33 S_1 = Matrix_inv33(S);
    Matrix33 S_1CB_1 = Matrix_mult33x33(S_1, CB_1);

    *out11 = Matrix_add33(B_1, Matrix_mult33x33(B_1, Matrix_mult33x33(CT, S_1CB_1)));
    *out21 = Matrix_multFloat33(S_1CB_1, -1);
    *out22 = S_1;
}