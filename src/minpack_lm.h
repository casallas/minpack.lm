#ifndef MINPACK_LM_HEADER_INCLUDED
#define MINPACK_LM_HEADER_INCLUDED 1

typedef struct opt_struct {
    SEXP par;
    SEXP fcall;
    SEXP jcall;
    SEXP env;
    double ftol;
    double ptol;
    double gtol;
    double epsfcn;
    double *diag;
    double factor;
} opt_struct, *OptStruct;

void fcn_lmdif(int *m, int *n, double *par, double *fvec, int *iflag, double *rss);
void fcn_lmder(int *m, int *n, double *par, double *fvec, double *fjac, int *ldfjac, int *iflag, double *rss);
void F77_NAME(lmdif)(void (*fcn_lmdif)(int *m, int *n, double *par, double *fvec, int *iflag, double *rss),
                     int *m, int *n, double *par, double *fvec,
                     double *ftol, double *ptol, double *gtol, int *maxfev, int *maxiter, 
                     double *epsfcn, double *diag, int *mode, double *factor,
                     int *nprint, int *info, int *nfev, double *fjac,
                     int *ldfjac, int *ipvt, double *qtf,
                     double *wa1, double *wa2, double *wa3, double *wa4);
		    void F77_NAME(lmder)(void (*fcn_lmder)(int *m, int *n, double *par, double *fvec, double *fjac, int *ldfjac, int *iflag, double *rss),
                     int *m, int *n, double *par, double *fvec,
                     double *fjac, int *ldfjac,
                     double *ftol, double *ptol, double *gtol,
                     int *maxfev, int *maxiter, double *diag, int *mode,
                     double *factor, int *nprint, int *info,
                     int *nfev, int *njev, int *ipvt,
                     double *qtf, double *wa1, double *wa2,
                     double *wa3, double *wa4);
char *fcn_message(char*, int, int, int);

void transpose(double *x, int nrx, int ncx, double *y);
void matprod  (double *x, int nrx, int ncx, double *y, int nry, int ncy, double *z);
void crossprod(double *x, int nrx, int ncx, double *y, int nry, int ncy, double *z);
SEXP getListElement(SEXP list, char *str);
double *real_vector(int n);
int  *int_vector(int n);

SEXP nls_lm(SEXP par_arg, SEXP fn, SEXP jac, SEXP control, SEXP rho);

extern int niter;
extern OptStruct OS;

#endif  /* MINPACK_LM_HEADER_INCLUDED */
