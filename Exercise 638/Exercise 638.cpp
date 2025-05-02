#include <iostream>

//a^b mod m
uint64_t pow(uint64_t a, uint64_t b, uint64_t m){
    if(b == 0) return 1;
    if(b == 1) return a%m;
    
    uint64_t t = pow(a, b/2, m);
    if(b%2 == 0) return (t*t)%m;
    else return (a*((t*t)%m))%m;
}

int main(){
    int p = 1000000007;
    
    int sum = 0;
    
    int powten = 1; //10^q
    for(int q=1; q<=7; q++){
        powten *= 10;
        int *qfact = new int[2*(powten+q)+1];
        
        //compute the q-factorials [n]!_q mod p for 0 <= n <= 2(10^k + k) using the recursive formula
        //[n+1]!_q = [n]!_q * [n+1]_q and [n+1]_q = [n]_q + q^n
        
        uint64_t qn = 1; //q^n
        uint64_t nq = 0; //[n]_q
        qfact[0] = 1;
        for(int n=1; n<=2*(powten+q); n++){
            nq = (nq + qn)%p;
            qn = (qn * q)%p;
            
            qfact[n] = ((uint64_t)qfact[n-1] * nq)%p;
        }
        
        //compute the q-binomial coefficient (2a,a)_q where a = 10^q + q
        uint64_t qbin = qfact[2*(powten+q)]; //[2a]!_q
        uint64_t x = pow(qfact[powten+q], p-2, p); //x^-1 = x^(p-2) mod p by FLT since p is prime
        
        //divide by ([a]!_q)^2
        qbin = (qbin*x)%p;
        qbin = (qbin*x)%p;
        
        sum = (sum + qbin)%p;
        
        delete[] qfact;
    }
    
    std::cout << sum << "\n" << std::flush;
}