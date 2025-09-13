#include <boost/bimap.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/set_of.hpp>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>

const uint64_t M = 4503599627370517ull;
const uint64_t k = 1504170715041707ull;
const uint64_t ki= 3451657199285664ull;
const uint64_t kim=(M-ki)%M;
const uint64_t change=20000000ull;

uint64_t seeksmart(uint64_t total,uint64_t latest) {

  typedef boost::bimaps::bimap<
    boost::bimaps::set_of<uint64_t,std::less<uint64_t>>,
    boost::bimaps::set_of<uint64_t,std::less<uint64_t>>
    > bimap_t;

  bimap_t steps;

  uint64_t i=kim;
  for (uint64_t a=1;a<latest;++a,i=(i+kim)%M) {
    steps.insert(bimap_t::value_type(i,a));
  }

  while (latest>1 && !steps.empty()) {
    const bimap_t::left_map::const_iterator it=steps.left.begin();
    const uint64_t i=it->first;
    const uint64_t a=it->second;
    assert(a<latest);
    latest=latest-a;
    std::cout << "  " << latest << std::endl;
    total+=latest;
    const bimap_t::right_map::iterator zap=steps.right.find(latest);
    assert(zap!=steps.right.end());
    steps.right.erase(zap,steps.right.end());
  }
  
  return total;
}

uint64_t seekbf() {
  uint64_t total=0;
  uint64_t latest=M;
  uint64_t current=k;
    
  while (true) {
    if (current<latest) {
      std::cout << "  " << current << std::endl;
      total+=current;
      latest=current;
    } else if (latest<change) {
      std::cout << "  Change"  << std::endl;
      return seeksmart(total,latest);
    } else {
      current=(current+k)%M;
    }
  }
}

int main(int,char**) {

  std::cout << seekbf()<< std::endl;
  
  return 0;
}