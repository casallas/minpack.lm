#include <R.h>
#include <Rdefines.h>

typedef struct opt_struct {
    SEXP par;
    SEXP fcall;
    SEXP jcall;
    SEXP env;
    double ftol;
    double xtol;
    double gtol;
    double epsfcn;
    double *diag;
    double factor;
} opt_struct, *OptStruct;

extern int niter;
extern OptStruct OS;

void fcn_lmder(int *m, int *n, double *par, double *fvec, double *fjac, int *ldfjac,
               int *iflag)
{
    int i, j;
    SEXP sexp_fvec, sexp_fjac;

/*    Rprintf("fcn-lmder calling...\n");   */
    for (i = 0; i < *n; i++) {
        if (!R_FINITE(par[i]))
            error("non-finite value supplied by lmder!");
        NUMERIC_POINTER(VECTOR_ELT(OS->par, i))[0] = par[i];
    }

    if (*iflag == 0) {
        Rprintf("Iter =%4d", niter);
        for (i = 0; i < *n; i++)
            Rprintf(" % 10g", par[i]);
        Rprintf("\n");

        return;
    }

    if (*iflag == 1) {
        SETCADR(OS->fcall, OS->par);
        PROTECT(sexp_fvec = eval(OS->fcall, OS->env));

        for (i = 0; i < *m; i++)
            fvec[i] = NUMERIC_POINTER(sexp_fvec)[i];

        UNPROTECT(1);

        niter++;

        return;
    }
    if (*iflag == 2) {
        SETCADR(OS->jcall, OS->par);
        PROTECT(sexp_fjac = eval(OS->jcall, OS->env));

        for (j = 0; j < *n; j++)
            for (i = 0; i < *m; i++)
                fjac[(*ldfjac)*j + i] = NUMERIC_POINTER(sexp_fjac)[(*m)*j + i];

        UNPROTECT(1);

        return;
    }
}
