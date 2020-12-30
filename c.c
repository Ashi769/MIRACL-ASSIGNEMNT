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


	/*Generate two big random numbers a and b in base 10, each consisting pf 150 digits */
	bigdig(155,10,a);
	bigdig(155,10,b);
	bigdig(155,10,c);
	
	
	printf("a = ");
	otnum(a,stdout);
	printf("b = ");
	otnum(b,stdout);
	printf("c = ");
	otnum(c,stdout);
	
    printf("(a^b)mod c=");
   
    otnum(temp(a,b,c),stdout);
	

}