#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstring>
#include <ctime>
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair
#define ldb long double
const int N=100050;
const ldb eps=1e-10;
struct Point
{
    ldb x,y;
    Point(ldb a=0, ldb b=0){ x=a,y=b;}
    ldb operator ^ (Point b) const { return (x-b.x)*(x-b.x)+(y-b.y)*(y-b.y);}
} P[N],t[4];
int sol=N;
void Try(Point s, int n)
{
    int i,ans=0;ldb h=max(max(s^t[0],s^t[1]),max(s^t[2],s^t[3]));
    for(i=1;i<=n;i++) if((s^P[i])+eps<h) ans++;
    sol=min(sol,ans);
}
void TryM(int m, int X, int Y, int a, int b, int n)
{
    int i,j;
    ldb x=(ldb)a/m;
    ldb y=(ldb)b/m;
    Point s;
    for(i=m/2;i<=m;i++) for(j=m/2;j>=0;j--)
    {
        if(n==2) if(clock()>0.49*CLOCKS_PER_SEC) break;
        else if(clock()>0.4*CLOCKS_PER_SEC) break;
        s.x=x*i+X;
        s.y=-y*i+Y;
        Try(s,n);
    }
    for(i=m/2;i>=0;i--) for(j=m/2;j<=m;j++)
    {
        if(n==2) if(clock()>0.49*CLOCKS_PER_SEC) break;
        else if(clock()>0.4*CLOCKS_PER_SEC) break;
        s.x=x*i+X;
        s.y=-y*i+Y;
        Try(s,n);
    }
}
int main()
{
    int x,y,a,b,i,j,X,Y,n;
    scanf("%i %i %i %i %i",&n,&X,&Y,&a,&b);
    for(i=1;i<=n;i++) scanf("%i %i",&x,&y),P[i].x=x,P[i].y=y;
    Point s;s.x=(ldb)a/2+X;s.y=-(ldb)b/2+Y;
    //Point t;t.x=X;t.y=Y;
    t[0].x=X;t[0].y=Y;
    t[1].x=X+a;t[1].y=Y;
    t[2].x=X;t[2].y=Y-b;
    t[3].x=X+a;t[3].y=Y-b;
    Try(s,n);
    s.x=X;s.y=Y;
    Try(s,n);
    s.x=X+a;
    Try(s,n);
    s.y=Y-b;
    Try(s,n);
    s.x=(ldb)a/2+X;
    s.y=Y;
    Try(s,n);
    s.y=Y-b;
    Try(s,n);
    s.x=X;
    s.y=-(ldb)b/2+Y;
    Try(s,n);
    s.x=X+a;
    Try(s,n);
    if(n==2) TryM(100000,X,Y,a,b,n);
    //else TryM(100,X,Y,a,b,n);
    printf("%i\n",sol);
    return 0;
}
