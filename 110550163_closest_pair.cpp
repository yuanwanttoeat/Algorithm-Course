#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;

struct point
{
    double x, y;
}points[100005];

bool compX(const point &a, const point &b)
{
    return a.x < b.x;
}

bool compY(const point &a, const point &b)
{
    return a.y < b.y;
}

double dist(point a, point b)
{
    return sqrt(pow(a.x-b.x,2) + pow(a.y-b.y,2));
}

double bruteForce(int ft, int ed)
{
    double mn = 40000;
    for(int i=ft;i<=ed;i++){
        for(int j=i+1;j<=ed;j++){
            double d = dist(points[i], points[j]);
            if(d < mn)
                mn = d;
        }
    }
    return mn;
}

double stripClosest(point strip[], int sz, double d)
{
    double min_d = d;

    sort(strip, strip+sz, compY);

    for(int i=0;i<sz;i++){
        for(int j=i+1;j<min(i+9, sz); j++){
            double tmp = dist(strip[i], strip[j]);
            if(tmp < min_d)
                min_d = tmp;
        }
    }

    return min_d;
}

double divide(int ft, int ed)
{
    int n = ed-ft+1;
    if(n <= 3)
        return bruteForce(ft, ed);

    int mid = (ft+ed)/2;
    point mid_p = points[mid];

    double dl= divide(ft, mid);
    double dr = divide(mid+1, ed);

    double d=dl;
    if(dr < dl)
        d = dr;

    point strip[n];
    int j=0;
    for(int i=ft;i<=ed;i++){
        if(points[i].x <= mid_p.x+d && points[i].x >= mid_p.x-d){
            strip[j]=points[i];
            j++;
        }
    }

    return min(d, stripClosest(strip, j, d));
}

int main()
{
    int T, n;
    cin>>T;

    while(T--){
        cin>>n;
        for(int m=0;m<n;m++){
            cin>>points[m].x>>points[m].y;
        }
        sort(points, points+n, compX);

        cout<<setprecision(7);
        cout<<divide(0, n-1)<<endl;

    }


    return 0;
}
