#include "matrix.h"
#include "vector.h"

// Generates a 4x4 identity matrix
mat4_t mat4_identity(void) {
    /*  
        | 1 0 0 0 |
        | 0 1 0 0 |
        | 0 0 1 0 |
        | 0 0 0 1 | 
    */
    mat4_t m = {{
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    }};
    return m;
}

mat4_t mat4_make_scale(float sx, float sy, float sz) {
    /*  
        | sx   0   0   0 |
        |  0  sy   0   0 |
        |  0   0  sz   0 |
        |  0   0   0   1 |
    */
    mat4_t m = mat4_identity();
    m.m[0][0] = sx;
    m.m[1][1] = sy;
    m.m[2][2] = sz;
    return m;
}

vec4_t mat4_mul_vec4(mat4_t m, vec4_t v) {
    /*  
        | m11   m12   m13   m14 |     |x|
        | m21   m22   m23   m24 |  *  |y|
        | m31   m32   m33   m34 |     |z|
        | m41   m42   m43   m44 |     |1|
    */
    vec4_t result;
    result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.z;
    result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.z;
    result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.z;
    result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.z;
    return result;
}
