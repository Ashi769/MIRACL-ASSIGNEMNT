#include "/home/ashish/Desktop/LEST/MIRACL/miracl.h" 
#include <stdio.h>

big div1(big a,big b){
	big c,d,t;
	c=mirvar(0);
	d=mirvar(0);
	t=mirvar(0);
	copy(b,t);
	divide(a,t,t);
	
	return a;
}

big gcdExtended(big a, big b, big *x, big *y)  
{  
    // Base Case
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
void main(){

	big a, b, c,x,y;
	
	/* base 10, 5000 digits per big */
	miracl *mip=mirsys(5000,10);

	/*Initialize variables*/
	a=mirvar(0);
	b=mirvar(0);
	c=mirvar(0);
	x=mirvar(0);
	y=mirvar(0);
	int d=(int)a;
	
   
	/*Initializes internal random number system. */
	long seed = 23422;
	irand(seed);

	getchar();

	/*Generate two big random numbers a and b in base 10, each consisting pf 150 digits */
	bigdig(155,10,a);
	bigdig(155,10,b);
	
	/*Output the Random Numbers to screen*/
	printf("a = ");
	otnum(a,stdout);
	printf("b = ");
	otnum(b,stdout);
	

	otnum(gcdExtended(a, b, &x, &y),stdout);
	
	
	
    
	

}