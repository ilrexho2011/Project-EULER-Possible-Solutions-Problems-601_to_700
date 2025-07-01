#include <iostream>
#include <vector>

using namespace std;

const uint64_t SEAT=10000000000000000ULL;
const int KNIGHTS=83; // The 83rd fibonacci number

int main()
{
    vector<uint64_t> fibonacci(KNIGHTS+2,0), segment;
    vector<int> sums;
    // Segment starts with a table of 5 knights.  This will change once we zoom in further
    // Sums stores the sum of each adjacent pair as a Fibonacci index
    int i,j,currentSum;
    uint64_t currentSeat,segLength,left,right;
    fibonacci[1]=1;
    for(i=2;i<=KNIGHTS+1;i++) fibonacci[i]=fibonacci[i-1]+fibonacci[i-2];
    segment.push_back(4);
    segment.push_back(1);
    segment.push_back(2);
    segment.push_back(3);
    segment.push_back(5);
    sums.push_back(5);
    sums.push_back(4); // F(4)=3;
    sums.push_back(5);
    sums.push_back(6);
    currentSeat=fibonacci[77];
    /* The above  has been precalculated for F(83) knights, currently representing
    the position of knight 4 relative to the king. */
    i=0;
    do
    {
        segLength=0;
        if(KNIGHTS+1-sums[i]>2)
        {
            segLength=2*fibonacci[KNIGHTS-sums[i]];
            if((KNIGHTS-sums[i])%2==1) segLength-=2;
        }
        if(currentSeat+segLength+1<=SEAT)
        // It's not in this segment.  Check the next
        {
            currentSeat+=segLength+1;
            i++;
            // This is the only branch that can end the loop in the case of equality
        }
        else
        {
            //It is in this segment.  Explore deeper
            left=segment[i];
            right=segment[i+1];
            currentSum=sums[i];
            sums.clear();
            sums.push_back(currentSum+2);
            sums.push_back(currentSum+3);
            sums.push_back(currentSum+2);
            segment.clear();
            segment.push_back(left);
            segment.push_back(fibonacci[sums[0]]-left);
            segment.push_back(fibonacci[sums[2]]-right);
            segment.push_back(right);
            i=0;
            /*cout << "Current segment = {";
            for(j=0;j<segment.size();j++)
            {
                cout << segment[j];
                if(j!=segment.size()-1) cout << ",";
            }
            cout << "}, current seat = " << currentSeat << endl;*/
        }
    }while(currentSeat<SEAT);
    cout << segment[i] << endl;
    // cout << fibonacci[KNIGHTS] << endl;
    return 0;
}