#MCMC
bayesmcustomConstant.keep = 1             #keep every keepth draw for MCMC routines
bayesmcustomConstant.nprint = 100         #print the remaining time on every nprint'th draw
bayesmcustomConstant.RRScaling = 2.38     #Roberts and Rosenthal optimal scaling constant
bayesmcustomConstant.w = .1               #fractional likelihood weighting parameter

#Priors
bayesmcustomConstant.A = .01              #scaling factor for the prior precision matrix
bayesmcustomConstant.nuInc = 3            #Increment for nu
bayesmcustomConstant.a = 5                #Dirichlet parameter for mixture models
bayesmcustomConstant.nu.e = 3.0           #degrees of freedom parameter for regression error variance prior
bayesmcustomConstant.nu = 3.0             #degrees of freedom parameter for Inverted Wishart prior
bayesmcustomConstant.agammaprior = .5     #Gamma prior parameter
bayesmcustomConstant.bgammaprior = .1     #Gamma prior parameter

#DP
bayesmcustomConstant.DPalimdef=c(.01,10)  #defines support of 'a' distribution
bayesmcustomConstant.DPnulimdef=c(.01,3)  #defines support of nu distribution
bayesmcustomConstant.DPvlimdef=c(.1,4)    #defines support of v distribution
bayesmcustomConstant.DPIstarmin = 1       #expected number of components at lower bound of support of alpha
bayesmcustomConstant.DPpower = .8         #power parameter for alpha prior
bayesmcustomConstant.DPalpha = 1.0        #intitalized value for alpha draws
bayesmcustomConstant.DPmaxuniq = 200      #storage constraint on the number of unique components
bayesmcustomConstant.DPSCALE = TRUE       #should data be scaled by mean,std deviation before posterior draws
bayesmcustomConstant.DPgridsize = 20      #number of discrete points for hyperparameter priors

#Mathematical Constants
bayesmcustomConstant.gamma = .5772156649015328606

#BayesBLP
bayesmcustomConstant.BLPVOmega = matrix(c(1,0.5,0.5,1),2,2)  #IW prior parameter of correlated shocks in IV bayesBLP
bayesmcustomConstant.BLPtol = 1e-6