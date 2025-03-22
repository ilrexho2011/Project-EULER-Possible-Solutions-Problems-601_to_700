#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

long double traveltime(long double x1, long double x2, long double x3, long double x4, long double x5, long double x6)
{
    long double result=0.1L*sqrt(3750-2500*sqrt(2.0L)+x1*x1+(50*sqrt(2.0L)-50)*x1);
    result+=sqrt((x2-x1+20)*(x2-x1)+200)/9.0L+sqrt((x3-x2+20)*(x3-x2)+200)/8.0L;
    result+=sqrt((x4-x3+20)*(x4-x3)+200)/7.0L+sqrt((x5-x4+20)*(x5-x4)+200)/6.0L;
    result+=0.2L*sqrt((x6-x5+20)*(x6-x5)+200)+0.1L*sqrt(3750-2500*sqrt(2.0L)+x6*x6-(50*sqrt(2.0L)-50)*x6);
    return result;
}

int main()
{
    vector<long double> F(6,0), x(6,0), cprime(5,0), dprime(6,0), xCorrection(6,0);
    // cprime and dprime come from the tridiagonal matrix algorithm on Wikipedia
    // xCorrection is x(n)-x(n+1) for Newton's method
    vector<vector <long double> > jacobian(6,F);
    int i,j;
    cout.precision(13);
    cout << "Time traveled for initial guess = " << traveltime(x[0],x[1],x[2],x[3],x[4],x[5]) << endl;
    for(i=1;i<=100;i++)
    {
        // Calculate F(x)
        F[0]=0.1L*(x[0]+25*sqrt(2.0L)-25)/sqrt(3750-2500*sqrt(2.0L)+x[0]*x[0]+(50*sqrt(2.0L)-50)*x[0])-(x[1]-x[0]+10)/9.0L/sqrt((x[1]-x[0]+20)*(x[1]-x[0])+200);
        F[1]=(x[1]-x[0]+10)/9.0L/sqrt((x[1]-x[0]+20)*(x[1]-x[0])+200)-(x[2]-x[1]+10)/8.0L/sqrt((x[2]-x[1]+20)*(x[2]-x[1])+200);
        F[2]=(x[2]-x[1]+10)/8.0L/sqrt((x[2]-x[1]+20)*(x[2]-x[1])+200)-(x[3]-x[2]+10)/7.0L/sqrt((x[3]-x[2]+20)*(x[3]-x[2])+200);
        F[3]=(x[3]-x[2]+10)/7.0L/sqrt((x[3]-x[2]+20)*(x[3]-x[2])+200)-(x[4]-x[3]+10)/6.0L/sqrt((x[4]-x[3]+20)*(x[4]-x[3])+200);
        F[4]=(x[4]-x[3]+10)/6.0L/sqrt((x[4]-x[3]+20)*(x[4]-x[3])+200)-(x[5]-x[4]+10)/5.0L/sqrt((x[5]-x[4]+20)*(x[5]-x[4])+200);
        F[5]=0.1L*(x[5]-25*sqrt(2.0L)+25)/sqrt(3750-2500*sqrt(2.0L)+x[5]*x[5]-(50*sqrt(2.0L)-50)*x[5])+(x[5]-x[4]+10)/5.0L/sqrt((x[5]-x[4]+20)*(x[5]-x[4])+200);
        // Calculate non-zero entries of the Jacobian at x
        jacobian[0][0]=(187.5L-125*sqrt(2.0L))/pow(3750-2500*sqrt(2.0L)+x[0]*x[0]+(50*sqrt(2.0L)-50)*x[0],1.5L);
        jacobian[1][0]=jacobian[0][1]=-100.0L/9.0L/pow((x[1]-x[0]+20)*(x[1]-x[0])+200,1.5L);
        jacobian[0][0]-=jacobian[1][0];
        jacobian[2][1]=-12.5L/pow((x[2]-x[1]+20)*(x[2]-x[1])+200,1.5L);
        jacobian[1][1]=-jacobian[1][0]-jacobian[2][1];
        jacobian[3][2]=-100.0L/7.0L/pow((x[3]-x[2]+20)*(x[3]-x[2])+200,1.5L);
        jacobian[2][2]=-jacobian[2][1]-jacobian[3][2];
        jacobian[4][3]=jacobian[3][4]=-100.0L/6.0L/pow((x[4]-x[3]+20)*(x[4]-x[3])+200,1.5L);
        jacobian[3][3]=-jacobian[3][2]-jacobian[4][3];
        jacobian[5][4]=jacobian[4][5]=-20.0L/pow((x[5]-x[4]+20)*(x[5]-x[4])+200,1.5L);
        jacobian[4][4]=-jacobian[4][3]-jacobian[5][4];
        jacobian[5][5]=(187.5L-125*sqrt(2.0L))/pow(3750-2500*sqrt(2.0L)+x[5]*x[5]-(50*sqrt(2.0L)-50)*x[5],1.5L)-jacobian[4][5];
        // Solve Jacobian times xCorrection equals F(x) using tridiagonal matrix algorithm
        cprime[0]=jacobian[0][1]/jacobian[0][0];
        for(j=1;j<=4;j++) cprime[j]=jacobian[j][j+1]/(jacobian[j][j]-jacobian[j][j-1]*cprime[j-1]);
        dprime[0]=F[0]/jacobian[0][0];
        for(j=1;j<=5;j++) dprime[j]=(F[j]-jacobian[j][j-1]*dprime[j-1])/(jacobian[j][j]-jacobian[j][j-1]*cprime[j-1]);
        xCorrection[5]=dprime[5];
        for(j=4;j>=0;j--) xCorrection[j]=dprime[j]-cprime[j]*xCorrection[j+1];
        // System is solved, update x
        for(j=0;j<=5;j++) x[j]-=xCorrection[j];
        cout << "After " << i << " iterations, time traveled = " << traveltime(x[0],x[1],x[2],x[3],x[4],x[5]) << endl;
    }
    return 0;
}