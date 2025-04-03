#include <math.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

int main(){
  clock_t t1,t2;
  t1 = clock();
  long res=0;
  long N;
  long final,init,back,root;

  N = pow(10,6);
  
  for(long a_star=2;a_star<pow(N,1.0/2.0);a_star++){
    if(a_star % 1000000 == 0){
      t2 = clock();
      cout << "a_star = " << a_star << "  time = " <<
	((float)t2-(float)t1)/CLOCKS_PER_SEC << "\n";
    }
    for(int e=2;e<=log(N)/log(a_star);e++){
      root = (int)(pow((float)a_star,1.0/((float)e))+.1);
      if((pow(root,e) == a_star) or (pow(a_star,e)+a_star > N)){
	continue;
      }

      // powers lists values that could be included in a MPS
      vector <long> powers(1,a_star);
      while(pow(powers.back(),e)+a_star<= N){
	powers.push_back(pow(powers.back(),e));
      }

      // iterate over all possible choices of a_f, a_0, and a_b
      for(int j=0;j<powers.size();j++){
	final = powers[j];  //a_f
	for(int k=0;k<=j;k++){
	  init = powers[k];  // a_0
	  for(int q=0;q<=j;q++){
	    back = powers[q];   // a_b
	    if(pow(final,e)+back > N)
	      break;
	    res += 1;
	  }
	}
      }	
    }
  }
  cout << "res = " << res << "\n";

  t2 = clock();
  cout << "time = " << ((float)t2-(float)t1)/CLOCKS_PER_SEC << "\n";
  return 0;
}