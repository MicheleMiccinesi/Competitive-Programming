/*I always write down only the functions which return the solutions, given some parser which collect necessary input data*/

/* Trapping Rain Water */
/* Version 0 */
/* Its a combination of 2 Leaders in Array.. This is a ridundant way of doing it . Thanks to guy that insisted that
   it is O(n) with (hidden) multiplying constant 2 */
unsigned int wtr_qnt0(unsigned int *w,unsigned int n){
 if( n < 3 )return 0;
 unsigned int wq=0;    //water quantity
 /* maxs is the water level */
 unsigned int *maxs=(unsigned int *)malloc(n*sizeof(unsigned int));
 maxs[0]=w[0];
 maxs[n-1]=w[n-1];
 unsigned int i_MAX=0, i=1;        //index of absolute max
 //Filling waterlevel
 for(i=1;i<n-1;i++) {
  if(w[i] >= maxs[i-1]) maxs[i]=w[i_MAX=i];
  else maxs[i]=maxs[i-1];
 }
 for(i=n-2;i>i_MAX;i--) {
  if(w[i] >= maxs[i+1]) maxs[i]=w[i];
  else maxs[i]=maxs[i+1];
 }
 //subtracting bricks
 for(i=1;i<n-1;i++) wq += maxs[i] - w[i];
 free(maxs);
 return wq;
}


/* Version 1 */
/* water level in position i is determined by the lowest between the max on the left and the one on the right
   so, scanning from left, we can register the max brick met up to that point; this up to the abs max;
   the same scanning from right. So it is better to scan both from left and from right at the same time to save on
   the multiplying constant hidden in O(n); and we save also on absmax and i_max variables */
unsigned int wtr_qnt1(unsigned int *w,unsigned int n){
 if( n < 3 )return 0;
 /* maxs is the water level */
 unsigned int *maxs=(unsigned int *)malloc(n*sizeof(unsigned int));
 maxs[0]=w[0];
 maxs[n-1]=w[n-1];
 unsigned int l=1,r=n-2;
 unsigned int wq=0;    //water quantity
 while( l <= r ){
  if( maxs[l-1] <= maxs[r+1] ){
   if( maxs[l-1] < w[l] ) maxs[l] = w[l];
   else maxs[l] = maxs[l-1];
   l++;
  }
  else {
   if( maxs[r+1] < w[r] ) maxs[r] = w[r];
   else maxs[r] = maxs[r+1];
   r--;
  }
 }
 for(l=1;l<n-1;l++) wq += maxs[l] - w[l];
 free(maxs);
 return wq;
}

/* Minimal Version
   Scanning both from left and from right at the same time
   it isn't necessary to memorize water level! */
unsigned int wtr_qnt2(unsigned int *w,unsigned int n){
 if( n < 3 )return 0;
 unsigned int maxR=0,maxL=0;    //max height of the wall currently met coming resp. from Right and from Left
 unsigned int l=0,r=n-1;    //current position of the reading from right and from left
 unsigned int wq=0;        //quantity of water on indices [0 .. l] + [r .. n-1]
 while( r >= l ){
// if maxL<=maxR the water level is decided by maxL, so we should check if the brick in l
// is higher (it would change next water levels, possibly also in r if new maxL > maxR)
// of course we cannot say anything about the level in r because we still don't know if there is
// a brick >= maxR !
  if( maxL <= maxR ){
   if( w[l] > maxL ) maxL = w[l];
   else wq += maxL - w[l];
   l++;
  }
// and viceversa
  else {
   if( w[r] > maxR ) maxR = w[r];
   else wq += maxR - w[r];
   r--;
  }
 }
 return wq;
}
