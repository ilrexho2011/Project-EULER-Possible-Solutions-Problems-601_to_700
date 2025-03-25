#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace chrono;

double exp(const double& n, const unsigned int& e){
  return e == 0 ? 1 : n * exp(n,e-1);
}

string dec2rom(const unsigned int& n){
  if(0 == n)
    return "";
  if(999 < n)
    return "M" + dec2rom(n-1000);
  if(899 < n)
    return "CM" + dec2rom(n-900);
  if(499 < n)
    return "D" + dec2rom(n-500);
  if(399 < n)
    return "CD" + dec2rom(n-400);
  if(99 < n)
    return "C" + dec2rom(n-100);
  if(89 < n)
    return "XC" + dec2rom(n-90);
  if(49 < n)
    return "L" + dec2rom(n-50);
  if(39 < n)
    return "XL" + dec2rom(n-40);
  if(9 < n)
    return "X" + dec2rom(n-10);
  if(9 == n)
    return "IX";
  if(4 < n)
    return "V" + dec2rom(n-5);
  if(4 == n)
    return "IV";
  return "I" + dec2rom(n-1);
}

unsigned int rom2dec(const string& str){
  if(str.length() == 0)
    return 0;
  if('M' == str.front())
    return 1000 + rom2dec(string(str.begin()+1,str.end()));
  if(str.find("CM") != string::npos)
    return 900 + rom2dec(string(str.begin()+2,str.end()));
  if('D' == str.front())
    return 500 + rom2dec(string(str.begin()+1,str.end()));
  if(str.find("CD") != string::npos)
    return 400 + rom2dec(string(str.begin()+2,str.end()));
  if('C' == str.front())
    return 100 + rom2dec(string(str.begin()+1,str.end()));
  if(str.find("XC") != string::npos)
    return 90 + rom2dec(string(str.begin()+2,str.end()));
  if('L' == str.front())
    return 50 + rom2dec(string(str.begin()+1,str.end()));
  if(str.find("XL") != string::npos)
    return 40 + rom2dec(string(str.begin()+2,str.end()));
  if('X' == str.front())
    return 10 + rom2dec(string(str.begin()+1,str.end()));
  if(str.find("IX") != string::npos)
    return 9;
  if('V' == str.front())
    return 5 + rom2dec(string(str.begin()+1,str.end()));
  if(str.find("IV") != string::npos)
    return 4;
  return 1 + rom2dec(string(str.begin()+1,str.end()));
}

bool isValid(const string& str, const char& c){
  if(str.length() == 0)
    return true;
  return (string(str + c).compare(dec2rom(rom2dec(str + c))) == 0);
}

double branch(const string& str = ""){
  vector< char > pool = {'M','D','C','L','X','V','I'};
  if(str.begin() == str.end() || str.back() == 'M')
    pool.erase(pool.begin());
  vector< string > cont;
  double e = rom2dec(str);
  double p = 1;
  for(auto&& i : pool){
    if(isValid(str,i))
      cont.push_back(str + i);
  }
  for(auto&& i : cont){
    e += 7 * branch(i);
    p += 7;
  }
  return e/p;
}

int main(int argc, char* argv[]){
  steady_clock::time_point ti = steady_clock::now();

  cout << fixed;
  cout << setprecision(8);
  string str = "";
  double prev = 0;
  double cur = 0;
  do{
    prev = cur;
    cur += .86 * branch(str) * exp(.14,str.length());
    str += 'M';
  }while(cur - prev > 0.00000001);
  cout << cur << endl;

  steady_clock::time_point tf = steady_clock::now();
  duration< double > t = duration_cast< duration< double > > (tf-ti);
  cout << t.count() << "s" << endl;
}