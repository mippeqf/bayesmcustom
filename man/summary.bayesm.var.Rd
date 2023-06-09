\name{summary.bayesmcustom.var}
\alias{summary.bayesmcustom.var}

\title{Summarize Draws of Var-Cov Matrices}

\description{
\code{summary.bayesmcustom.var} is an S3 method to summarize marginal distributions given an array of draws
}

\usage{\method{summary}{bayesmcustom.var}(object, names, burnin = trunc(0.1 * nrow(Vard)), tvalues, QUANTILES = FALSE , ...)}

\arguments{
  \item{object    }{ \code{object} (herafter, \code{Vard}) is an array of draws of a covariance matrix }
  \item{names     }{ optional character vector of names for the columns of \code{Vard}}
  \item{burnin    }{ number of draws to burn-in (def: \eqn{0.1*nrow(Vard)})}
  \item{tvalues   }{ optional vector of "true" values for use in simulation examples }
  \item{QUANTILES }{ logical for should quantiles be displayed (def: \code{TRUE})}
  \item{...       }{ optional arguments for generic function }
}

\details{
Typically, \code{summary.bayesmcustom.var} will be invoked by a call to the generic summary function as in \code{summary(object)} where \code{object} is of class \code{bayesmcustom.var}. Mean, Std Dev, Numerical Standard error (of estimate of posterior mean), relative numerical efficiency (see \code{numEff}), and effective sample size are displayed.  If \code{QUANTILES=TRUE}, quantiles of marginal distirbutions in the columns of \code{Vard} are displayed.  \cr

\code{Vard} is an array of draws of a covariance matrix stored as vectors.  Each row is a different draw. \cr

The posterior mean of the vector of standard deviations and the correlation matrix are also displayed
}

\author{Peter Rossi, Anderson School, UCLA, \email{perossichi@gmail.com}.}

\seealso{ \code{\link{summary.bayesmcustom.mat}}, \code{\link{summary.bayesmcustom.nmix}}}

\examples{
\dontrun{out=rmnpGibbs(Data,Prior,Mcmc); summary(out$sigmadraw)}
}

\keyword{ univar }

