#include "bayesmcustom.h"
#include <iostream>

int main()
{
    // Argument init
    int R = 100000;
    int keep = 1;
    int nprint = 100;
    int n = 100;
    int p = 2;
    int k = 5;
    ivec const y(n, fill::randu);
    mat const X(n, k, fill::randu);
    vec const beta0(k, fill::zeros);
    mat const sigma0 = eye(p, p);
    double nu = p + 3;
    mat const V = eye(p, p) * nu;
    vec const betabar(k, fill::zeros);
    mat const A = eye(k, k) * 0.01;

    // out = rmvpGibbs_rcpp_loop();

    std::cout << "Hi";
}