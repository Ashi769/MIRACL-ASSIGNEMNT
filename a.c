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
big gcd(big a, big b) 
{   big z; 
	z=mirvar(0);
	
    if (mr_compare(a,z)==0){
    	
        return b; 
    }
    return gcd(div1(b,a), a); 
}

void main(){

	big a, b, c;
	
	/* base 10, 5000 digits per big */
	miracl *mip=mirsys(5000,10);

	/*Initialize variables*/
	a=mirvar(0);
	b=mirvar(0);
	c=mirvar(0);
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
	
    printf("gcd of  a and b=");
    otnum(gcd(a,b),stdout);
	

}