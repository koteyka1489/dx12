#pragma once


typedef struct
{
    float x, y, z, w;
} Quat1; /* Quat1ernion */

enum Quat1Part
{
    X,
    Y,
    Z,
    W
};
typedef float HMatrix[4][4]; /* Right-handed, for column vectors */
typedef Quat1 EulerAngles;    /* (x,y,z)=ang 1,2,3, w=order code  */



/*** Order type constants, constructors, extractors ***/
/* There are 24 possible conventions, designated by:    */
/*	  o EulAxI = axis used initially		    */
/*	  o EulPar = parity of axis permutation		    */
/*	  o EulRep = repetition of initial axis as last	    */
/*	  o EulFrm = frame from which axes are taken	    */
/* Axes I,J,K will be a permutation of X,Y,Z.	    */
/* Axis H will be either I or K, depending on EulRep.   */
/* Frame S takes axes from initial static frame.	    */
/* If ord = (AxI=X, Par=Even, Rep=No, Frm=S), then	    */
/* {a,b,c,ord} means Rz(c)Ry(b)Rx(a), where Rz(c)v	    */
/* rotates v around Z by c radians.			    */
#define EulFrmS 0
#define EulFrmR 1
#define EulFrm(ord) ((unsigned)(ord) & 1)
#define EulRepNo 0
#define EulRepYes 1
#define EulRep(ord) (((unsigned)(ord) >> 1) & 1)
#define EulParEven 0
#define EulParOdd 1
#define EulPar(ord) (((unsigned)(ord) >> 2) & 1)
/* this code is merely a quick (and legal!) way to set arrays, EulSafe being 0,1,2,0 */
#define EulSafe "\000\001\002\000"
#define EulNext "\001\002\000\001"
#define EulAxI(ord) ((int)(EulSafe[(((unsigned)(ord) >> 3) & 3)]))
#define EulAxJ(ord) ((int)(EulNext[EulAxI(ord) + (EulPar(ord) == EulParOdd)]))
#define EulAxK(ord) ((int)(EulNext[EulAxI(ord) + (EulPar(ord) != EulParOdd)]))
#define EulAxH(ord) ((EulRep(ord) == EulRepNo) ? EulAxK(ord) : EulAxI(ord))
/* EulGetOrd unpacks all useful information about order simultaneously. */
#define EulGetOrd(ord, i, j, k, h, n, s, f)                                                                                                \
    {                                                                                                                                      \
        unsigned o = (unsigned)ord;                                                                                                        \
        f = o & 1;                                                                                                                         \
        o >>= 1;                                                                                                                           \
        s = o & 1;                                                                                                                         \
        o >>= 1;                                                                                                                           \
        n = o & 1;                                                                                                                         \
        o >>= 1;                                                                                                                           \
        i = EulSafe[o & 3];                                                                                                                \
        j = EulNext[i + n];                                                                                                                \
        k = EulNext[i + 1 - n];                                                                                                            \
        h = s ? k : i;                                                                                                                     \
    }
/* EulOrd creates an order value between 0 and 23 from 4-tuple choices. */
#define EulOrd(i, p, r, f) (((((((i) << 1) + (p)) << 1) + (r)) << 1) + (f))
/* Static axes */
#define EulOrdXYZs EulOrd(X, EulParEven, EulRepNo, EulFrmS)
#define EulOrdXYXs EulOrd(X, EulParEven, EulRepYes, EulFrmS)
#define EulOrdXZYs EulOrd(X, EulParOdd, EulRepNo, EulFrmS)
#define EulOrdXZXs EulOrd(X, EulParOdd, EulRepYes, EulFrmS)
#define EulOrdYZXs EulOrd(Y, EulParEven, EulRepNo, EulFrmS)
#define EulOrdYZYs EulOrd(Y, EulParEven, EulRepYes, EulFrmS)
#define EulOrdYXZs EulOrd(Y, EulParOdd, EulRepNo, EulFrmS)
#define EulOrdYXYs EulOrd(Y, EulParOdd, EulRepYes, EulFrmS)
#define EulOrdZXYs EulOrd(Z, EulParEven, EulRepNo, EulFrmS)
#define EulOrdZXZs EulOrd(Z, EulParEven, EulRepYes, EulFrmS)
#define EulOrdZYXs EulOrd(Z, EulParOdd, EulRepNo, EulFrmS)
#define EulOrdZYZs EulOrd(Z, EulParOdd, EulRepYes, EulFrmS)
/* Rotating axes */
#define EulOrdZYXr EulOrd(X, EulParEven, EulRepNo, EulFrmR)
#define EulOrdXYXr EulOrd(X, EulParEven, EulRepYes, EulFrmR)
#define EulOrdYZXr EulOrd(X, EulParOdd, EulRepNo, EulFrmR)
#define EulOrdXZXr EulOrd(X, EulParOdd, EulRepYes, EulFrmR)
#define EulOrdXZYr EulOrd(Y, EulParEven, EulRepNo, EulFrmR)
#define EulOrdYZYr EulOrd(Y, EulParEven, EulRepYes, EulFrmR)
#define EulOrdZXYr EulOrd(Y, EulParOdd, EulRepNo, EulFrmR)
#define EulOrdYXYr EulOrd(Y, EulParOdd, EulRepYes, EulFrmR)
#define EulOrdYXZr EulOrd(Z, EulParEven, EulRepNo, EulFrmR)
#define EulOrdZXZr EulOrd(Z, EulParEven, EulRepYes, EulFrmR)
#define EulOrdXYZr EulOrd(Z, EulParOdd, EulRepNo, EulFrmR)
#define EulOrdZYZr EulOrd(Z, EulParOdd, EulRepYes, EulFrmR)

static EulerAngles Eul_(float ai, float aj, float ah, int order);
static Quat1 Eul_ToQuat1(EulerAngles ea);
static void Eul_ToHMatrix(EulerAngles ea, HMatrix M);
static EulerAngles Eul_FromHMatrix(HMatrix M, int order);
static EulerAngles Eul_FromQuat1(Quat1 q, int order);

/**** EulerAngles.c - Convert Euler angles to/from matrix or quat ****/
/* Ken Shoemake, 1993 */
#include <math.h>
#include <float.h>

EulerAngles Eul_(float ai, float aj, float ah, int order)
{
    EulerAngles ea;
    ea.x = ai;
    ea.y = aj;
    ea.z = ah;
    ea.w = (float)order;
    return (ea);
}
/* Construct quaternion from Euler angles (in radians). */
Quat1 Eul_ToQuat1(EulerAngles ea)
{
    Quat1 qu;
    float a[3], ti, tj, th, ci, cj, ch, si, sj, sh, cc, cs, sc, ss;
    int i, j, k, h, n, s, f;
    EulGetOrd(ea.w, i, j, k, h, n, s, f);
    if (f == EulFrmR)
    {
        float t = ea.x;
        ea.x = ea.z;
        ea.z = t;
    }
    if (n == EulParOdd) ea.y = -ea.y;
    ti = ea.x * 0.5f;
    tj = ea.y * 0.5f;
    th = ea.z * 0.5f;
    ci = cosf(ti);
    cj = cosf(tj);
    ch = cosf(th);
    si = sinf(ti);
    sj = sinf(tj);
    sh = sinf(th);
    cc = ci * ch;
    cs = ci * sh;
    sc = si * ch;
    ss = si * sh;
    if (s == EulRepYes)
    {
        a[i] = cj * (cs + sc); /* Could speed up with */
        a[j] = sj * (cc + ss); /* trig identities. */
        a[k] = sj * (cs - sc);
        qu.w = cj * (cc - ss);
    }
    else
    {
        a[i] = cj * sc - sj * cs;
        a[j] = cj * ss + sj * cc;
        a[k] = cj * cs - sj * sc;
        qu.w = cj * cc + sj * ss;
    }
    if (n == EulParOdd) a[j] = -a[j];
    qu.x = a[X];
    qu.y = a[Y];
    qu.z = a[Z];
    return (qu);
}

/* Construct matrix from Euler angles (in radians). */
void Eul_ToHMatrix(EulerAngles ea, HMatrix M)
{
    float ti, tj, th, ci, cj, ch, si, sj, sh, cc, cs, sc, ss;
    int i, j, k, h, n, s, f;
    EulGetOrd(ea.w, i, j, k, h, n, s, f);
    if (f == EulFrmR)
    {
        float t = ea.x;
        ea.x = ea.z;
        ea.z = t;
    }
    if (n == EulParOdd)
    {
        ea.x = -ea.x;
        ea.y = -ea.y;
        ea.z = -ea.z;
    }
    ti = ea.x;
    tj = ea.y;
    th = ea.z;
    ci = cosf(ti);
    cj = cosf(tj);
    ch = cosf(th);
    si = sinf(ti);
    sj = sinf(tj);
    sh = sinf(th);
    cc = ci * ch;
    cs = ci * sh;
    sc = si * ch;
    ss = si * sh;
    if (s == EulRepYes)
    {
        M[i][i] = cj;
        M[i][j] = sj * si;
        M[i][k] = sj * ci;
        M[j][i] = sj * sh;
        M[j][j] = -cj * ss + cc;
        M[j][k] = -cj * cs - sc;
        M[k][i] = -sj * ch;
        M[k][j] = cj * sc + cs;
        M[k][k] = cj * cc - ss;
    }
    else
    {
        M[i][i] = cj * ch;
        M[i][j] = sj * sc - cs;
        M[i][k] = sj * cc + ss;
        M[j][i] = cj * sh;
        M[j][j] = sj * ss + cc;
        M[j][k] = sj * cs - sc;
        M[k][i] = -sj;
        M[k][j] = cj * si;
        M[k][k] = cj * ci;
    }
    M[W][X] = M[W][Y] = M[W][Z] = M[X][W] = M[Y][W] = M[Z][W] = 0.f;
    M[W][W] = 1.f;
}

/* Convert matrix to Euler angles (in radians). */
EulerAngles Eul_FromHMatrix(HMatrix M, int order)
{
    EulerAngles ea;
    int i, j, k, h, n, s, f;
    EulGetOrd(order, i, j, k, h, n, s, f);
    if (s == EulRepYes)
    {
        float sy = sqrtf(M[i][j] * M[i][j] + M[i][k] * M[i][k]);
        if (sy > 16 * FLT_EPSILON)
        {
            ea.x = atan2f(M[i][j], M[i][k]);
            ea.y = atan2f(sy, M[i][i]);
            ea.z = atan2f(M[j][i], -M[k][i]);
        }
        else
        {
            ea.x = atan2f(-M[j][k], M[j][j]);
            ea.y = atan2f(sy, M[i][i]);
            ea.z = 0;
        }
    }
    else
    {
        float cy = sqrtf(M[i][i] * M[i][i] + M[j][i] * M[j][i]);
        if (cy > 16 * FLT_EPSILON)
        {
            ea.x = atan2f(M[k][j], M[k][k]);
            ea.y = atan2f(-M[k][i], cy);
            ea.z = atan2f(M[j][i], M[i][i]);
        }
        else
        {
            ea.x = atan2f(-M[j][k], M[j][j]);
            ea.y = atan2f(-M[k][i], cy);
            ea.z = 0;
        }
    }
    if (n == EulParOdd)
    {
        ea.x = -ea.x;
        ea.y = -ea.y;
        ea.z = -ea.z;
    }
    if (f == EulFrmR)
    {
        float t = ea.x;
        ea.x = ea.z;
        ea.z = t;
    }
    ea.w = (float)order;
    return (ea);
}

/* Convert quaternion to Euler angles (in radians). */
EulerAngles Eul_FromQuat1(Quat1 q, int order)
{
    HMatrix M;
    float Nq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    float s = (Nq > 0.f) ? (2.f / Nq) : 0.f;
    float xs = q.x * s, ys = q.y * s, zs = q.z * s;
    float wx = q.w * xs, wy = q.w * ys, wz = q.w * zs;
    float xx = q.x * xs, xy = q.x * ys, xz = q.x * zs;
    float yy = q.y * ys, yz = q.y * zs, zz = q.z * zs;
    M[X][X] = 1.f - (yy + zz);
    M[X][Y] = xy - wz;
    M[X][Z] = xz + wy;
    M[Y][X] = xy + wz;
    M[Y][Y] = 1.f - (xx + zz);
    M[Y][Z] = yz - wx;
    M[Z][X] = xz - wy;
    M[Z][Y] = yz + wx;
    M[Z][Z] = 1.f - (xx + yy);
    M[W][X] = M[W][Y] = M[W][Z] = M[X][W] = M[Y][W] = M[Z][W] = 0.f;
    M[W][W] = 1.f;
    return (Eul_FromHMatrix(M, order));
}