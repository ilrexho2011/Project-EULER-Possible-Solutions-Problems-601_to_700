#include <iostream>
#include <vector>
#include <cmath>

#include <utility>
#include <algorithm>
#include <future>
using namespace std;

long long bla(long long offset)
{
    long long N = 1000;
    vector <char> nw(N+1, 0);
    long long sum=0;

    for (long long chunk=offset; chunk < 1000; chunk+=4  )
    {
        if (chunk%100==0){
            cout<<chunk<<" "<<sum<<endl;
        }

        fill(begin(nw), end(nw), 0); //we moved to the next chunk, close all doors
        long long first = N*chunk+1 ;
        long long last = N*(chunk+1);
        for (long long a=1; 2*a*a<=last; a++){
            long long b= max<long long>(sqrt(first-a*a),a+1);
            while (a*a+b*b<first) b++;
            for (; a*a+b*b<=last; b++){
                sum+= 1-2*nw[a*a+b*b-first+1];
                nw[a*a+b*b-first+1]=1-nw[a*a+b*b-first+1];
            }
        }
        /*for (long long a=1; 2*a*a<=last; a++){ // another way to close all dors 
            long long b= max<long long>(sqrt(first-a*a),a+1);
            while (a*a+b*b<first) b++;
            for (; a*a+b*b<=last; b++){
                nw[a*a+b*b-first+1]=1-nw[a*a+b*b-first+1];
            }
        }*/
    }
    return sum;
}
    int main()
    {
        auto w0 = std::async(std::launch::async, bla, 0);
        auto w1 = std::async(std::launch::async, bla, 1);
        auto w2 = std::async(std::launch::async, bla, 2);
        auto w3 = std::async(std::launch::async, bla, 3);

        long long sum = w0.get()+w1.get()+w2.get()+w3.get();

        cout<<endl<<sum<<endl;
    }