/* Little Girl and Max XOR */
/* Problem Source: codeforces 276D */
/* Solution License: contact Michele Miccinesi */
/* Proof: starting from leading bits, while they are equal we can't do nothing, but after that,
   just decrease the greater or viceversa */

#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);

	uint64_t a, b;
	std::cin >> a >> b;
	a^=b;
	std::cout << ((((((a|=(a>>1))|=(a>>2))|=(a>>4))|=(a>>8))|=(a>>16))|=(a>>32)) << std::endl;;
 
	return 0;
}
