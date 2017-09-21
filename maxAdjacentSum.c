/* I'm new to algorithms/programming , so even this one required me some time to conceive */
/* thanks to the teacher */

/*Max Sum of a Subsegment*/
/* scanning from left to right: register both the temporary max sum and the sum,
  when the sum is <0 what is on the left is not useful to what is on the right, so discard it,
  setting the sum to 0 and eventually successively reconding the new max sum*/
int max_adj_sum(int *v,int n){
 int sum=0,max=0,i;
 for(i=0;i<n;i++){
  sum+=v[i];
  if(sum<0)sum=0;
  else if(sum>max)max=sum;
 }
 return max;
}
