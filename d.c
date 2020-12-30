#include "/home/ashish/Desktop/LEST/MIRACL/miracl.h" 
#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


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
void main(){
    miracl *mip=mirsys(5000,10);
    big myNum=mirvar(0);
    myNum=geneRatePrime();
    otnum(myNum,stdout);
    return;
}