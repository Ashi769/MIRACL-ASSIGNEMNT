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
big div1(big a,big b){
	big c,d,t,a1;
	c=mirvar(0);
	d=mirvar(0);
	t=mirvar(0);
	a1=mirvar(0);
	copy(b,t);
	copy(a,a1);
	divide(a1,t,t);
	
	return a1;
}
big temp(big x,big n,big d){
	big z=mirvar(0);
	big z1=mirvar(1);
	big z2=mirvar(2);
	big ret=mirvar(56);
	if(mr_compare(n,z)==0){
         //printf("yes\n");
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

		//otnum(n,stdout);
		// printf("yes1\n");
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

		//otnum(n,stdout);
		//printf("yes2\n");
		//otnum(n,stdout);
		//otnum(n_1,stdout);
		big ret2=mirvar(0);
		ret2=div1(ret,d);

		return ret2;

	}
	

}
//bob only need alice's public key and his private key and prime number p
big bobActual(big Cp,big CalicePublic,big CbobPrivate){
	
	big p=mirvar(0);
	big alicePublic=mirvar(0);
	big bobPrivate=mirvar(0);
	copy(Cp,p);
	copy(CalicePublic,alicePublic);
	copy(CbobPrivate,bobPrivate);

	big e=mirvar(0);
	e=temp(CalicePublic,CbobPrivate,p);
	return e;
}
//alice only need bob's public key and his private key and prime number p
big aliceActual(big Cp,big CBobPublic,big CalicePrivate){
	big p=mirvar(0);
	big bobPublic=mirvar(0);
	big alicePrivate=mirvar(0);
	copy(Cp,p);
	copy(CBobPublic,bobPublic);
	copy(CalicePrivate,alicePrivate);
	big e=mirvar(0);
	e=temp(bobPublic,alicePrivate,p);
	return  e;

}


void main(){

	big a, b, c,base,p,bobPublic,alicePublic;
	
	/* base 10, 5000 digits per big */
	miracl *mip=mirsys(5000,10);

	/*Initialize variables*/
	a=mirvar(0);
	b=mirvar(0);
	c=mirvar(0);
	base=mirvar(9949);
	p=mirvar(9811);
	alicePublic=mirvar(0);
	bobPublic=mirvar(0);

	base=geneRatePrime();
	p=geneRatePrime();

   
	/*Initializes internal random number system. */
	long seed = 23422;
	irand(seed);


	/*Generate two big random numbers a and b in base 10, each consisting pf 150 digits */
	bigdig(155,10,a);
	bigdig(155,10,b);
	bigdig(155,10,c);
	
	
	printf("a = ");
	otnum(a,stdout);
	printf("b = ");
	otnum(b,stdout);
	printf("base=");
	otnum(base,stdout);
	printf("p=");
    otnum(p,stdout);
	
	
    //printf("(a^b)mod c=");
    big a1,b1;
    a1=mirvar(0);
    b1=mirvar(0);
    copy(a,a1);
    copy(b,b1);

    alicePublic=temp(base,a1,p);
    bobPublic=temp(base,b1,p);
    printf("public key of Alice=");
    otnum(alicePublic,stdout);
    printf("public key of Bob=");
    otnum(bobPublic,stdout);
    printf("bob's actual key=");
    otnum(bobActual(p,alicePublic,b),stdout);    //bob only need alice's public key and his private key and prime number p
    printf("alice's actual key=");
    otnum(aliceActual(p,bobPublic,a),stdout);     //alice only need bob's public key and his private key and prime number p
   
    
	

}