#include <stdio.h>
#include "miracl.h"
#include <stdbool.h>



big div1(big a,big b){
	big c,d,t;
	c=mirvar(0);
	d=mirvar(0);
	t=mirvar(0);
	copy(b,t);
	divide(a,t,t);
	return a;
}


big temp(big x,big n,big d){
	big z=mirvar(0);
	big z1=mirvar(1);
	big z2=mirvar(2);
	big ret=mirvar(56);
	if(mr_compare(n,z)==0){
		return z1;
	}
	big tempn=mirvar(0);
	copy(n,tempn);
	
	if(mr_compare(div1(tempn,z2),z)==0){
		big n2=mirvar(0);
		big sq=mirvar(0);
		divide(n,z2,n2);
		sq=temp(x,n2,d);
		big sq2=mirvar(0);
		sq2=div1(sq,d);
		big ret=mirvar(0);
		multiply(sq2,sq2,ret);
		big ret2=mirvar(0);
		ret2=div1(ret,d);
		return ret2;


	}else{
		big n_1=mirvar(0);
		subtract(n,z1,n_1);

		big sq=mirvar(0);
		sq=temp(x,n_1,d);
		big sq2=mirvar(0);
		sq2=div1(sq,d);

		big ret=mirvar(0);
		multiply(x,sq2,ret);
		big ret2=mirvar(0);
		ret2=div1(ret,d);

		return ret2;

	}
}




big gcdExtended(big a, big b, big *x, big *y)  
{  
    big z=mirvar(0);  
    if (mr_compare(a,z)==0)  
    {  
        *x = mirvar(0);  
        *y = mirvar(1);  
        return b;  
    }  
    big a1=mirvar(0);
    big b1=mirvar(0);
    copy(a,a1);
    copy(b,b1);
    big x1=mirvar(0);
    big y1=mirvar(0); // To store results of recursive call  
    big gcd=mirvar(0);
    gcd= gcdExtended(div1(b,a), a, &x1, &y1);  
    big c,d,e,f;
    c=mirvar(0);
    d=mirvar(0);
    e=mirvar(0);
    f=mirvar(0);
    divide(b1,a1,d);
    multiply(d,x1,c);
    subtract(y1,c,e);
    *x=e;
    *y=x1;

    return gcd;  
} 


void print(big val){
	otnum(val,stdout);
}


void finalize(big a,big b,big c,big one_val,big x){
	if (mr_compare(c,one_val) != 0)
	{
		printf("Error\n");
		return;
	}
	big p = mirvar(a);
	big q = mirvar(b);
	big x_b = mirvar(x);
	divide(x_b,b,a);
	add(x_b,b,x_b);
	divide(x_b,b,a);
	divide(p,q,c);
	printf("multiplicative inverse = ");
	print(x_b);
	printf("512-bit prime modulus using Miller-Rabin algorithm) = ");
	print(q);
}

typedef struct st
{
    int r;
    big d;
}st;


int val_pow_exp(int val, unsigned int exp) 
{   
    if (exp == 0){
        return 1; 
    }
    else if (exp % 2 == 0){
        int temp= val_pow_exp(val, exp / 2);
        temp=temp * val_pow_exp(val, exp / 2);
        return temp; 
    }
    else{
        int temp= val * val_pow_exp(val, exp / 2);
        temp=temp*val_pow_exp(val, exp / 2); 
        return temp;
    }
} 


st* shubh(big* N)  
{
    st* data = (st*)malloc(sizeof(st));
    big d = mirvar(0); 
    int r = 1;
    int base = 2;
    while(1)
    {
        if(subdivisible(*N,val_pow_exp(base,r)))
            r++;
        else
        {
            r = r - 1;  
            subdiv(*N,val_pow_exp(base,r),d); 
            break;
        }
    }
    data->r = r;
    data->d = d;
    
    return data;
}

bool primTest(big* num)
{
  
    if(getdig(*num,0) % 2 == 0)
    {   
          return false;
    }
    else 
    {
        big N = mirvar(0);   
        decr(*num,1,N);

        st* data = shubh(&N);

      
        int i = 0;
       

        big a = mirvar(0);   
        big UPPER_LIMIT = mirvar(0); 
        decr(N,1,UPPER_LIMIT);

        big x = mirvar(0); 
        big z1 = mirvar(1); 

        while(i<= 10000)
        {
            i=i+1;

          
            bigrand(UPPER_LIMIT,a);  
            incr(a,1,a);

            powmod(a,data->d,*num,x);
            if(fcomp(x,z1) == 0 || fcomp(x,N) == 0)
                continue;
            
            int counter = 0;
            bool maybePrime = false;
            while(counter < (data->r - 1))
            {
                power(x,2,*num,x);
                if(fcomp(x,N) == 0)
                {
                    maybePrime = true;
                    break;
                }
                counter++;
            }

            if(maybePrime)  
                continue;
            else
            {
               
                return false;
            }
        }
        
        return true;
    }
    
}
big geneRatePrime(){
    big r1=mirvar(0);
     int trials = 0;
    while(1)
    {
        trials++;
      
        r1 = mirvar(0);
      
        bigdig(155,10,r1);

        bool status = primTest(&r1);
        if(status){
            return r1;
        }
    }
    
}
void main()
{
    miracl* mir = mirsys(5000,10);
    long seed = 12121;
	irand(seed);


	big alpha = mirvar(0), n = mirvar(0);
    big let_say_prime = mirvar(0);

	bigdig(150,10,alpha);
	bigdig(512,2,n);
    copy(geneRatePrime(),let_say_prime);
    otnum(let_say_prime,stdout);
    printf("\n");

    big expo = mirvar(0);
	copy(temp(alpha,n,let_say_prime),expo);

	printf("Exponentiation = ");
	otnum(expo,stdout);


	big a=mirvar(0);copy(let_say_prime,a);
	big b=mirvar(0);copy(expo,b);
	big c=mirvar(0);
	big x=mirvar(0),y=mirvar(0);
	copy(gcdExtended(a,b,&x,&y),c);
	big one_val = mirvar(1);
	finalize(a,b,c,one_val,x);
    return 0;
}
