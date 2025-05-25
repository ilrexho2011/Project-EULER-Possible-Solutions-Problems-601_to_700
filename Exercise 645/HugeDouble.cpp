class HugeDouble { 
public:
   // The number hold is m*2^exp2, where m in { (-2,-1] , [1,2) , 0 } 
   __int64 exp2;
   double  m;

   // STATIC VARIABLES AND FUNCTIONS
   static double* powersOf2;
   static double* powersOfHalf;
   static double* initializePowersOf2();
   static double* initializePowersOfHalf();

   // CONSTRUCTORS
   HugeDouble();
   HugeDouble(HugeDouble const & orig);
   HugeDouble(int n);
   HugeDouble(double x);

   // OPERATORS
   HugeDouble & operator=(const HugeDouble & orig);
   bool operator<(const HugeDouble & comp) const;
   HugeDouble operator+(const HugeDouble & toAdd) const;
   HugeDouble operator-() const;
   HugeDouble operator*(const HugeDouble & h) const;
   HugeDouble operator*(const double d);
   HugeDouble operator*(const int i);
   friend HugeDouble operator*(const double d, const HugeDouble & h);
   HugeDouble operator/(const HugeDouble & factor) const;
   HugeDouble operator/(const int i);
   friend ostream & operator<<(ostream & out, const HugeDouble & c);

   // MATH FUNCTIONS
   inline int sign() const { if (m>0) return 1; else if (m==0) return 0; else return -1; }
   int toInt() const;
   double toDouble() const;

   // GENERAL FUNCTIONS
   void normalize(); // Set the matissa in [1,2) , 0 , or (-2,-1]
   string toString()        const; // Returns m*2^e
   string toDecimalString() const; // Returns m*10^e
};



#include "HugeDouble.h"

// initialization of static variables
double * HugeDouble::powersOf2    = HugeDouble::initializePowersOf2();
double * HugeDouble::powersOfHalf = HugeDouble::initializePowersOfHalf();


double* HugeDouble::initializePowersOf2() {
   int i;
   powersOf2 = new double[64];
   powersOf2[0] = 1.0;
   for (i=1; i<64; i++) {
      powersOf2[i] = 2.0*powersOf2[i-1];
   }
   return powersOf2;
}


double* HugeDouble::initializePowersOfHalf() {
   int i;
   powersOfHalf = new double[64];
   powersOfHalf[0] = 1.0;
   for (i=1; i<64; i++) {
      powersOfHalf[i] = 0.5*powersOfHalf[i-1];
   }
   return powersOfHalf;
}


// HugeDouble CONSTRUCTORS
HugeDouble::HugeDouble() {
   exp2 = 0;
   m    = 0.0;
}


HugeDouble::HugeDouble(HugeDouble const & orig) {
   exp2 = orig.exp2;
   m    = orig.m;
}


HugeDouble::HugeDouble(int n) {
   exp2 = 0;
   m    = n;
   normalize();
}


HugeDouble::HugeDouble(double x) {
   exp2 = 0;
   m    = x;
   normalize();
}


// HugeDouble OPERATORS


HugeDouble & HugeDouble::operator=(const HugeDouble & orig) {
   exp2 = orig.exp2;
   m    = orig.m;
   return *this;
}


bool HugeDouble::operator<(const HugeDouble & comp) const {
   int s = sign();
   int dif = s - comp.sign();
   if (dif>0) return false; // this>=0, comp<=0
   if (dif<0) return true; // this<=0, comp>=0
   if (s==0) { 
      return false; // this=0, comp=0
   }else if (s==1) {
      // this and comp are positive
      if (exp2<comp.exp2) return true;
      if (exp2>comp.exp2) return false;
      if (m   <comp.m   ) return true;
      return false;
   }else{
      // this and comp are negative
      if (exp2<comp.exp2) return false;
      if (exp2>comp.exp2) return true;
      if (m   <comp.m   ) return false;
      return true;
   }
}


HugeDouble HugeDouble::operator+(const HugeDouble & toAdd) const {
   HugeDouble sum;
   if (exp2 >= toAdd.exp2) {
      if (exp2 < toAdd.exp2+64) {
         sum.m    = m + toAdd.m * powersOfHalf[exp2 - toAdd.exp2];
         sum.exp2 = exp2;
         sum.normalize();
         return sum;
      }else{
         // toAdd is too small compared with this
         sum = *this;
         return sum;
      }
   }else{
      if (toAdd.exp2 < exp2+64) {
         sum.m    = toAdd.m + m * powersOfHalf[toAdd.exp2 - exp2];
         sum.exp2 = toAdd.exp2;
         sum.normalize();
         return sum;
      }else{
         // this is too small compared with toAdd
         sum = toAdd;
         return sum;
      }
   }
}


HugeDouble HugeDouble::operator-() const {
   HugeDouble result;
   result.exp2 = exp2;
   result.m    = -m;
   return result;
}


HugeDouble HugeDouble::operator*(const HugeDouble & factor) const {
   HugeDouble product;
   product.m    = m    * factor.m   ;
   product.exp2 = exp2 + factor.exp2;
   product.normalize();
   return product;
}


HugeDouble HugeDouble::operator*(const double d) {
   HugeDouble product;
   product.m = m * d;
   product.exp2 = exp2;
   product.normalize();
   return product;
}


HugeDouble HugeDouble::operator*(const int i) {
   HugeDouble product;
   product.m = m * i;
   product.exp2 = exp2;
   product.normalize();
   return product;
}


HugeDouble operator*(const double d, const HugeDouble & h) { 
   HugeDouble product;
   product.m = h.m * d;
   product.exp2 = h.exp2;
   product.normalize();
   return product;
}


HugeDouble HugeDouble::operator/(const HugeDouble & factor) const {
   HugeDouble product;
   product.m    = m    / factor.m   ;
   product.exp2 = exp2 - factor.exp2;
   product.normalize();
   return product;
}


HugeDouble HugeDouble::operator/(const int i) {
   HugeDouble product;
   product.m = m / i;
   product.exp2 = exp2;
   product.normalize();
   return product;
}


ostream & operator<<(ostream & out, const HugeDouble & c) {
   out << c.toDecimalString();
   return out;
}


// Returns the value as an integer. Beware, this will fail if number
// is large enough that it doesn't fit in an int.
int HugeDouble::toInt() const {
   int i;
   double result;

   result = m;
   for (i=0; i<exp2; i++) {
      result = 2.0*result;
   }
   return (int)(result + 0.5);
}


// Returns the value as a double. Beware, this will fail if number
// is large enough that it doesn't fit in an int.
double HugeDouble::toDouble() const {
   int i;
   double result;

   result = m;
   if (exp2 >= 0) {
      for (i=0; i<exp2; i++) {
         result = 2.0*result;
      }
   }else{
      for (i=0; i<-exp2; i++) {
         result = 0.5*result;
      }   
   }
   return result;
}


// HugeDouble general functions


void HugeDouble::normalize() {
   if (m==0.0) {
      exp2 = 0;
   }else if (m>=2.0) {
      while (m>=2.0) {
         m = 0.5*m;
         exp2++;
      }
   }else if (m<=-2.0) {
      while (m<=-2.0) {
         m = 0.5*m;
         exp2++;
      }
   }else if (m>0.0) {
      while (m<1.0) {
         m = 2.0*m;
         exp2--;
      }
   }else{
      while (m>-1.0) {
         m = 2.0*m;
         exp2--;
      }
   }
}


string HugeDouble::toString() const {
   char buffer[30];
   sprintf_s(buffer, 30, "%16.14f*2^%d", m, exp2);
   return buffer;
}


string HugeDouble::toDecimalString() const {
   if (m==0) return "0";
   char buffer[30];
   double loge  = (log(fabs(m)) + (double)exp2 * log(2.0));
   int    exp10 = (int)floor(loge / log(10.0));
   double m10   = exp( loge - (double)exp10 * log(10.0));
   if (m<0) {
      sprintf_s(buffer, 30, "-%12.10f*10^%d", m10, exp10);
   }else{
      sprintf_s(buffer, 30, "%13.10f*10^%d", m10, exp10);
   }     
   return buffer;
}
