#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define f first
#define s second
#define pii pair<int,int>
#define Point pair<ll,ll>
#define forn(a,b,c) for(int a=b;a<=c;a++)
#define ford(a,b,c) for(int a=b;a>=c;a--)
const int N=1e5+5;
pair<Point,Point> a[N];
pair<Point,ll>k[N];
int ans[N],n,m;
ll cross(Point a,Point b){
    return a.f*b.s-a.s*b.f;
}
double lineDist(ll xk,ll yk,ll x1,ll y1,ll x2,ll y2){
    Point ka={xk-x1,yk-y1},kb={xk-x2,yk-y2};
    double area=1.0*abs(cross(ka,kb));
    double dist=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    return area/dist;
}
bool check(ll xk,ll yk,ll r,ll x1,ll y1,ll x2,ll y2){
    double dist=lineDist(xk,yk,x1,y1,x2,y2);
    if(dist<=r){
        return true;
    }
    return false;
}
int query(pair<Point,Point>p){
    int lo=0,hi=m;
    ll x1=p.f.f,y1=p.f.s,x2=p.s.f,y2=p.s.s;
    while(lo<hi){
        int mid=(hi+lo+1)/2;
        ll xk=k[mid].f.f,yk=k[mid].f.s,r=k[mid].s;
        if(!check(xk,yk,r,x1,y1,x2,y2))
            lo=mid;
        else
            hi=mid-1;
    }
    //printf("lo:%d hi:%d\n",lo,hi);
    return lo+1;
}
int main()
{
    /*Point A{0,0},B{5,0},K{5,6};
    printf("dist:%.6f\n",lineDist(K.f,K.s,A.f,A.s,B.f,B.s));
    */
    scanf("%d",&n);
    forn(i,1,n){
        scanf("%lld%lld%lld%lld",&a[i].f.f,&a[i].f.s,&a[i].s.f,&a[i].s.s);
    }
    scanf("%d",&m);
    forn(i,1,m){
        scanf("%lld%lld%lld",&k[i].f.f,&k[i].f.s,&k[i].s);
    }
    forn(i,1,n){
        int curr=query(a[i]);
        //printf("i:%d curr:%d\n",i,curr);
        ans[curr]++;
    }
    forn(i,1,m){
        ans[i]+=ans[i-1];
    }
    forn(i,1,m){
        printf("%d\n",ans[i]);
    }
    return 0;
}
