\name{wfct}
\alias{wfct}
\encoding{UTF-8}
\title{Weighting function that can be supplied to the \code{weights} argument
  of \code{\link{nlsLM}} or \code{\link{nls}}}
\description{
  \code{wfct} can be supplied to the \code{weights} argument of
  \code{\link{nlsLM}} or \code{\link{nls}}, and facilitates specification of
  weighting schemes.
}

\usage{
wfct(expr)
}

\arguments{
  \item{expr}{An expression specifying the weighting scheme
    as described in the Details section below.}
}

\details{
  The weighting function can take 5 different variable definitions and
  combinations thereof:
 \itemize{
   \item  the name of the predictor (independent) variable
   \item the name of the response (dependent) variable
   \item error: if replicates \eqn{y_{ij}}{y_{ij}}
   exist, the error \eqn{\sigma(y_{ij})}{sigma_{ij}}
   \item fitted: the fitted values \eqn{\hat{y}_i}{hat{y}_i} of the model
   \item resid: the residuals \eqn{y_i - \hat{y}_i}{y_i - hat{y}_i} of the model
       }
For the last two, the model is fit unweighted, fitted values and
residuals are extracted and the model is refit by the defined weights.
}

\value{The results of evaluation of \code{expr} in a new
  environment, yielding the vector of weights to be applied.  
 
}
\author{Andrej-Nikolai Spiess}

\seealso{\code{\link{nlsLM}}, \code{\link{nls}}}

\examples{

### Examples from 'nls' doc ###
## note that 'nlsLM' below may be replaced with calls to 'nls'
Treated <- Puromycin[Puromycin$state == "treated", ]

## Weighting by inverse of response 1/y_i:
nlsLM(rate ~ Vm * conc/(K + conc), data = Treated,
start = c(Vm = 200, K = 0.05), weights = wfct(1/rate))

## Weighting by square root of predictor \sqrt{x_i}:
nlsLM(rate ~ Vm * conc/(K + conc), data = Treated,
start = c(Vm = 200, K = 0.05), weights = wfct(sqrt(conc)))

## Weighting by inverse square of fitted values 1/\hat{y_i}^2:
nlsLM(rate ~ Vm * conc/(K + conc), data = Treated,
start = c(Vm = 200, K = 0.05), weights = wfct(1/fitted^2))

## Weighting by inverse variance 1/\sigma{y_i}^2:
nlsLM(rate ~ Vm * conc/(K + conc), data = Treated,
start = c(Vm = 200, K = 0.05), weights = wfct(1/error^2))

}
\keyword{nonlinear}
\keyword{optimize}
\keyword{regression}
