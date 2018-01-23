/* Vectors */
/* Problem Source: codeforces 102E */
/* Solution License: contact Michele Miccinesi */

#include <stdio.h>
#include <stdlib.h>

int main(){
	long long a1, a2, b1, b2, c1, c2, D, m[4], n[4];
	scanf("%lld%lld%lld%lld%lld%lld", &a1, &a2, &b1, &b2, &c1, &c2);
	if( c1==0 && c2==0 ){
		if( (a1==b1 && a2==b2)||(a1==-b1 && a2==-b2)||(a1==b2 && a2==-b1)||(a1==-b2 && a2==b1) )
			printf("YES\n");
		else 
			printf("NO\n");
		return 0; 
	}
	D = c1*c1+c2*c2;
	m[0]=(b1+a1)*c1+(b2+a2)*c2;
	n[0]=(b1+a1)*c2-(b2+a2)*c1;
	m[1]=(b1-a1)*c1+(b2-a2)*c2;
	n[1]=(b1-a1)*c2-(b2-a2)*c1;
	m[2]=(b1-a2)*c1+(b2+a1)*c2;
	n[2]=(b1-a2)*c2-(b2+a1)*c1;
	m[3]=(b1+a2)*c1+(b2-a1)*c2;
	n[3]=(b1+a2)*c2-(b2-a1)*c1;
	if( ((m[0]%D)||(n[0]%D))&&((m[1]%D)||(n[1]%D))&&((m[2]%D)||(n[2]%D))&&((m[3]%D)||(n[3]%D)) )
		printf("NO\n");
	else 	
		printf("YES\n");

	return 0;
}
