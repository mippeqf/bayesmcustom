#include "bayesmcustom.h"
 
//SUPPORT FUNCTIONS SPECIFIC TO MAIN FUNCTION--------------------------------------------------------------------------------------
vec HaltonSeq(int pn, int r, int burnin, bool rand){

// Keunwoo Kim 10/28/2014

// Purpose: 
//    create a random Halton sequence

// Arguments:
//    pn: prime number
//    r: number of draws
//    burnin: number of initial burn
//    rand: if TRUE, add a random scalor to sequence

// Output: 
//    a vector of Halton sequence, size r
 
  int t;
  vec add;
  
  // start at 0
  vec seq = zeros<vec>(r+burnin+1);
  // how many numbers I have drawn so far.
  // I have 1 draw (0) now.
  int index = 1;
  // if done==1, it is done.
  int done = 0;
  int factor = pn;
  do{		
		for (t=0; t<pn-1; t++){
      if (done==0){
        add = seq(span(0, index-1)) + ones<vec>(index)*(t+1)/factor;
        if ((t+2)*index-1>r+burnin){
          seq(span((t+1)*index, r+burnin)) = add(span(0, r+burnin-(t+1)*index));
          done = 1;
        }else{
          seq(span((t+1)*index, (t+2)*index-1)) = add;
          if ((t+2)*index==r+burnin+1){
            done = 1;
          }
        }
      }
		}		
		factor = factor*pn;
    index = index*pn;
	}while (done==0);

  // exclude the first 0 and some initial draws
  seq = seq(span(burnin+1,burnin+r));	
  
  if (rand==TRUE){
    // make it random
    seq = seq + runif(1)[0];
    for (int i=0; i<r; i++){
      if (seq[i]>=1) seq[i] = seq[i]-1;
    }
  }
	return (seq);
}

bool IsPrime(int number){

// Keunwoo Kim 5/14/2015

// This function is to check whether a number is prime or not.
// This is used for setting default prime numbers.

  for (int f=2; f<number; f++){
    if (number%f==0 && f!=number){
      return false;
    }
  }
  return true;
}

double ghk_oneside(vec const& L, vec const& trunpt, vec const& above, int r, bool HALTON, vec const& pn, int burnin){
//
// routine to implement ghk with a region defined by truncation only on one-side
// if above=1, then we truncate component i from above at point trunpt[i-1]
// L is lower triangular root of Sigma
// random vector is assumed to have zero mean
// n is number of draws to use in GHK	
//
  int i, j, k;
  double mu, tpz, u, prod, pa, pb, arg;
    
  int dim = trunpt.size();
  vec z = zeros<vec>(dim);  
  double res = 0;
  
  // choose R::runif vs. Halton draws
  vec udraw(r*dim);
  mat udrawHalton(dim, r);
  if (HALTON){
    for (j=0; j<dim; j++){
      udrawHalton(j, span::all) = trans(HaltonSeq(pn[j], r, burnin, TRUE));
    }
    udraw = vectorise(udrawHalton);
  }else{
    for (i=0; i<r*dim; i++){
      udraw[i] = runif(1)[0];
    }    
  }
  
  // main integration
  for (i=0; i<r; i++){
    prod = 1.0;
    for (j=0; j<dim; j++){
      mu = 0.0; 
      for (k=0; k<j; k++){
        mu = mu + L[k*dim+j] * z[k];
      }
      tpz = (trunpt[j]-mu) / L[j*dim+j];
      if (above[j]>0){
        pa = 0.0;
        pb = R::pnorm(tpz,0,1,1,0);
      }else{
        pb = 1.0;
        pa = R::pnorm(tpz,0,1,1,0);
      }
      prod = prod * (pb-pa);      
      u = udraw[i*dim+j];
      arg = u*pb + (1.0-u)*pa;
      if (arg > .999999999) arg=.999999999;
      if (arg < .0000000001) arg=.0000000001;
      z[j] = R::qnorm(arg,0,1,1,0);
    }
    res = res + prod;
  }
  res = res / r;  
  return (res);  
}

//MAIN FUNCTION---------------------------------------------------------------------------------------
// [[Rcpp::export]]
vec ghkvec(mat const& L, vec const& trunpt, vec const& above, int r, bool HALTON=true, 
                vec pn=IntegerVector::create(0)){

// Keunwoo Kim 5/14/2015

// Purpose: 
//      routine to call ghk_oneside for n different truncation points stacked in to the
//      vector trunpt -- puts n results in vector res

// Arguments:
//      L: lower Cholesky root of cov. matrix
//      trunpt: vector of truncation points
//      above: truncation above(1) or below(0)
//      r: number of draws
//      HALTON: TRUE or FALSE. If FALSE, use R::runif random number generator.
//      pn: prime number used in Halton sequence.
//      burnin: number of initial burnin of draws. Only applied when HALTON is TRUE. (not used any more)

// Output: 
//      a vector of integration values


  int dim = above.size();
  int n = trunpt.size()/dim;

  //
  // handling default arguments
  //
  // generate prime numbers
  if (HALTON==true && pn[0]==0){
    Rcout << "Halton sequence is generated by the smallest prime numbers: \n";
    Rcout << "   ";
    pn = zeros<vec>(dim);
    
    int cand = 2;
    int which = 0;
    while (pn[dim-1]==0){      
      if (IsPrime(cand)){
        pn[which] = cand;
        which = which + 1;        
        Rprintf("%d ", cand);
      }
      cand = cand + 1;
    }
    Rcout << "\n";
  }
  // burn-in
  //if (HALTON==true && burnin==NA_INTEGER){    
  //  burnin = max(pn);
  //  Rprintf("Initial %d (= max of prime numbers) draws are burned. \n", burnin);
  //}
  int burnin = 0;
  
  vec res(n);
  for (int i=0; i<n; i++){    
    res[i] = ghk_oneside(vectorise(L), trunpt(span(i*dim, (i+1)*dim-1)), above, r, HALTON, pn, burnin);
  }  
  return (res);
}
