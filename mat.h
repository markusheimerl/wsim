#ifndef MAT_H
#define MAT_H

#define VEC_SUB(a,b,r) { (r)[0]=(a)[0]-(b)[0]; (r)[1]=(a)[1]-(b)[1]; (r)[2]=(a)[2]-(b)[2]; }
#define VEC_DOT(a,b) ((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VEC_CROSS(a,b,r) { (r)[0]=(a)[1]*(b)[2]-(a)[2]*(b)[1]; (r)[1]=(a)[2]*(b)[0]-(a)[0]*(b)[2]; (r)[2]=(a)[0]*(b)[1]-(a)[1]*(b)[0]; }
#define VEC_NORM(v) { double l=sqrt(VEC_DOT(v,v)); if(l>0){ (v)[0]/=l; (v)[1]/=l; (v)[2]/=l; } }
#define VEC_SCALE(v,s,r) { (r)[0]=(v)[0]*(s); (r)[1]=(v)[1]*(s); (r)[2]=(v)[2]*(s); }
#define VEC_ADD(a,b,r) { (r)[0]=(a)[0]+(b)[0]; (r)[1]=(a)[1]+(b)[1]; (r)[2]=(a)[2]+(b)[2]; }

void matrix_identity(double m[4][4]) {
    memset(m, 0, 16 * sizeof(double));
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0;
}

void matrix_multiply(double a[4][4], double b[4][4], double result[4][4]) {
    double temp[4][4] = {0};
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                temp[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    memcpy(result, temp, 16 * sizeof(double));
}

void matrix_translate(double m[4][4], double x, double y, double z) {
    double t[4][4] = {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    };
    matrix_multiply(m, t, m);
}

void matrix_scale(double m[4][4], double s) {
    double scale[4][4] = {
        {s, 0, 0, 0},
        {0, s, 0, 0},
        {0, 0, s, 0},
        {0, 0, 0, 1}
    };
    matrix_multiply(m, scale, m);
}

void matrix_rotate_y(double m[4][4], double angle) {
    double c = cos(angle);
    double s = sin(angle);
    double r[4][4] = {
        {c,  0, s, 0},
        {0,  1, 0, 0},
        {-s, 0, c, 0},
        {0,  0, 0, 1}
    };
    matrix_multiply(m, r, m);
}

#endif /* GIF_H */