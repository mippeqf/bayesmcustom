\name{plot.bayesmcustom.hcoef}
\alias{plot.bayesmcustom.hcoef}
\concept{MCMC}
\concept{S3 method}
\concept{plot}
\concept{hierarchical model}

\title{Plot Method for Hierarchical Model Coefs}

\description{
\code{plot.bayesmcustom.hcoef} is an S3 method to plot 3 dim arrays of hierarchical coefficients. Arrays are of class \code{bayesmcustom.hcoef} with dimensions: cross-sectional unit \eqn{x} coef \eqn{x} MCMC draw. 
}

\usage{\method{plot}{bayesmcustom.hcoef}(x,names,burnin,...)}

\arguments{
  \item{x      }{ An object of S3 class, \code{bayesmcustom.hcoef} }
  \item{names  }{ a list of names for the variables in the hierarchical model}
  \item{burnin }{ no draws to burnin (def: \eqn{0.1*R})}
  \item{...    }{ standard graphics parameters }
}

\details{
Typically, \code{plot.bayesmcustom.hcoef} will be invoked by a call to the generic plot function as in \code{plot(object)} where object is of class \code{bayesmcustom.hcoef}. All of the \code{bayesmcustom} hierarchical routines return draws of hierarchical coefficients in this class (see example below).  One can also simply invoke \code{plot.bayesmcustom.hcoef} on any valid 3-dim array as in \code{plot.bayesmcustom.hcoef(betadraws)}.
  \cr
  \cr
\code{plot.bayesmcustom.hcoef} is also exported for use as a standard function, as in \code{plot.bayesmcustom.hcoef(array)}.
}

\author{ Peter Rossi, Anderson School, UCLA, \email{perossichi@gmail.com}.}

\seealso{ \code{\link{rhierMnlRwMixture}},\code{\link{rhierLinearModel}},
          \code{\link{rhierLinearMixture}},\code{\link{rhierNegbinRw}} }

\examples{
\dontrun{out=rhierLinearModel(Data,Prior,Mcmc); plot(out$betadraws)}
}

\keyword{hplot}
