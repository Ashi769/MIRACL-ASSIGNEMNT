#include <stdio.h>
#include "/home/prakhar/Desktop/NS/MIRACL/miracl.h"

big square_and_multiply(big a, big bip, big n)
{
	int nob = logb2(bip);
	int binary[nob];
	big zero = mirvar(0);
	big one = mirvar(1);
	int i = 0;
	big b = mirvar(1);
	copy(bip,b);
	while(1)
	{
		big two = mirvar(2);
		if (mr_compare(b,zero) == 0)
		{
			break;
		}
		big copy_b = mirvar(0);
		copy(b,copy_b);
		divide(copy_b,two,b);
		if (mr_compare(copy_b,zero) == 0)
			binary[i] = 0;
		else if (mr_compare(copy_b,one) == 0)
			binary[i] = 1;
		i = i+1;
	}

	big result = mirvar(1);
	big temp = mirvar(0);

	for (int j = nob-1; j>=0; j--)
	{
		multiply(result,result,result);
		divide(result,n,temp);

		if (binary[j] == 1)
		{
			multiply(result,a,result);
			divide(result,n,temp);
		}
	}

	return result;
}

int Miller_Rabin_primality_test(big n, big k)
{

	big d = mirvar(0);
	big zero = mirvar(0);
	big one = mirvar(1);
	big two = mirvar(2);
	big n_1 = mirvar(0);
	big r = mirvar(0);

	copy(n,n_1);
	subtract(n_1,one,n_1);
	subtract(n,one,d);

	while(1)
	{
		big aux = mirvar(0);
		copy(d,aux);
		big au2 = mirvar(0);
		divide(aux,two,au2);
		if (mr_compare(aux,zero) != 0)
		{
			break;
		}
		copy(au2,d);
		add(r,one,r);
	}
	big copy_k = mirvar(0);
	copy(k,copy_k);
	while(1)
	{
		if (mr_compare(copy_k,zero) == 0)
		{
			break;
		}
		big a = mirvar(0);
		do
		{
			big n_2 = mirvar(0);
			subtract(n,two,n_2);
			bigrand(n_2,a);

		}while(mr_compare(a,zero) == 0 || mr_compare(a,one) == 0);
		big x = mirvar(0);
		x = square_and_multiply(a,d,n);
		if (mr_compare(x,one) == 0 || mr_compare(x,n_1) == 0)
		{
			subtract(copy_k,one,copy_k);
			continue;
		}
		big copy_r = mirvar(0);
		copy(r,copy_r);
		int flag = 0;
		while(mr_compare(copy_r,one) != 0 && mr_compare(copy_r,zero) != 0)
		{
			x = square_and_multiply(x,two,n);
			if (mr_compare(x,n_1) == 0)
			{
				flag = 1;
				break;
			}
			subtract(copy_r,one,copy_r);
		}
		label:
		if (flag == 1)
		{
			subtract(copy_k,one,copy_k);
			continue;
		}
		return 0;
	}
	return 1;
}

big extended_eucledian(big a, big b, big x, big y)
{
	big z = mirvar(0);
	big copy_a = mirvar(0);
	big copy_b = mirvar(0);
	copy(a,copy_a);
	copy(b,copy_b);

	if (mr_compare(a,z) == 0)
	{
		convert(0,x);
		convert(1,y);
		return b;
	}
	else
	{
		big x1 = mirvar(0);
		big y1 = mirvar(0);

		big d = mirvar(0);
		big e = mirvar(0);
		copy(b,e);
		divide(e,a,d);

		big gcd = mirvar(0);
		gcd = extended_eucledian(e,a,x1,y1);

		divide(copy_b,copy_a,d);
		multiply(d,x1,d);
		subtract(y1,d,x);
		copy(x1,y);
		return gcd;
	}
}

void main()
{
	big k,one,two,three,zero,p,q;

	miracl *mip=mirsys(2000,10);
	p = mirvar(23);
	q = mirvar(5);
	k = mirvar(100);
	zero = mirvar(0);
	one = mirvar(1);
	two = mirvar(2);
	three = mirvar(3);
	long seed = time(NULL);
	irand(seed);

	int status = 0;

	do
	{
		bigdig(512,2,p);
		bigdig(10,2,k);

		if (mr_compare(p,zero) == 0 || mr_compare(p,one) == 0)
		{
			status = 0;
		}
		else if (mr_compare(p,two) == 0 || mr_compare(p,three) == 0)
		{
			status = 1;
		}
		else
		{
			status = Miller_Rabin_primality_test(p,k);
		}
	}while(status != 1);

	do
	{
		bigdig(512,2,q);
		bigdig(10,2,k);

		if (mr_compare(q,zero) == 0 || mr_compare(q,one) == 0)
		{
			status = 0;
		}
		else if (mr_compare(q,two) == 0 || mr_compare(q,three) == 0)
		{
			status = 1;
		}
		else
		{
			status = Miller_Rabin_primality_test(q,k);
		}
	}while((status != 1) && mr_compare(q,p) != 0);

	mip->IOBASE=16;

	FILE *opr, *opb;

	opr = fopen("Private_Q5.key","wt");
	opb = fopen("Public_Q5.key","wt");

	printf("Prime numbers Generated\np (Private) = ");
	cotnum(p,stdout);
	cotnum(p,opr);
	printf("q (Private) = ");
	cotnum(q,stdout);
	cotnum(q,opr);

	big n = mirvar(0);
	multiply(p,q,n);

	printf("n (Public) = ");
	cotnum(n,stdout);
	cotnum(n,opb);
	printf("Key Length = %d\n",logb2(n));

	subtract(p,one,p);
	subtract(q,one,q);
	big phi_n = mirvar(0);
	multiply(p,q,phi_n);
	printf("Phi(n) (Private) = ");
	cotnum(phi_n,stdout);
	cotnum(phi_n,opr);

	big gcd = mirvar(0);
	big copy_phi_n = mirvar(0);
	copy(phi_n,copy_phi_n);
	big x = mirvar(0);
	big y = mirvar(0);
	big e = mirvar(11);

	do
	{
		bigrand(copy_phi_n,e);
		gcd = extended_eucledian(e,copy_phi_n,x,y);
	}while(mr_compare(e,zero) == 0 || mr_compare(e,one) == 0 || mr_compare(gcd,one) != 0);
	printf("e (Public Key) = ");
	cotnum(e,opb);
	cotnum(e,stdout);

	big d = mirvar(0);

	copy(x,d);
	divide(d,phi_n,p);
	add(d,phi_n,d);
	divide(d,phi_n,p);
	printf("d (Private Key) = ");
	cotnum(d,stdout);
	cotnum(d,opr);
	fclose(opb);
	fclose(opr);
}