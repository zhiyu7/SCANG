// [[Rcpp::depends(RcppArmadillo)]]

#include <RcppArmadillo.h>
#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;

// [[Rcpp::export]]
double CCT_pval(arma::vec x, arma::vec weights)
{
	double cct_stat = 0.0;
	double pval = 0.0;

	bool lower = false;
	bool logp = false;

	weights = weights/sum(weights);

	int n = x.size();
	int k ;


	for(k = 0;k < n;k++)
	{
		if(x(k) < 1e-16)
		{
			cct_stat = cct_stat + weights(k)/x(k)/PI;
		}else
		{
			cct_stat = cct_stat + weights(k)*tan((0.5-x(k))*PI);
		}
	}

	if (cct_stat > 1e+15)
	{
        pval = (1/cct_stat)/PI;
    }else
	{
		pval = R::pcauchy(cct_stat,0.0,1.0,lower,logp);
    }

	return pval;

}




