#include <bits/stdc++.h>
#define MAX_N 200005
using namespace std;
struct Point{
    long long x, y;
    int original_index;
} A[MAX_N], hull[MAX_N];
long long twice_poly_area; 
int n;
int hull_size;
int hull_index[MAX_N];
bool on_hull[MAX_N];
stack<Point> S;
void swap_points(int i, int j){
    int a=hull[i].x, b=hull[i].y, c=hull[i].original_index;
    hull[i].x=hull[j].x;
    hull[i].y=hull[j].y;
    hull[i].original_index=hull[j].original_index;
    hull[j].x=a;
    hull[j].y=b;
    hull[j].original_index=c;
}
bool cmp(Point P, Point Q){
    long long r=( P.x - hull[0].x ) * ( Q.y - hull[0].y ) - ( P.y - hull[0].y ) * ( Q.x - hull[0].x );
    return ( r > 0 ) || ( r==0 && abs( P.x - hull[0].x ) < abs( Q.x - hull[0].x ) );
}
void graham(){
    int min=0;
    for(int i=0; i<n; ++i){
        if( hull[i].y < hull[min].y || ( hull[i].y == hull[min].y && hull[i].x < hull[min].x)){
            min=i;
        }
    }
    swap_points(0, min);
    sort(hull + 1, hull + n, cmp);
    int m=1;
    for(int i=1; i<n; ++i){
        while( i<n-1 && ( hull[i].x - hull[0].x ) * ( hull[i + 1].y - hull[0].y ) == ( hull[i].y - hull[0].y ) * ( hull[i + 1].x - hull[0].x ) )
        i++;
        hull[m++]=hull[i];
    }
    while(!S.empty())S.pop();
    S.push(hull[0]);
    S.push(hull[1]);
    S.push(hull[2]);
    for(int i=3; i<m; ++i){
        Point p2=S.top();
        S.pop();
        Point p1=S.top();
        Point p3=hull[i];
        while( ( p2.x - p1.x ) * ( p3.y - p1.y) < (p2.y - p1.y) * ( p3.x - p1.x ) ){
            p2=p1;
            S.pop();
            p1=S.top();
        }
        S.push(p2);
        S.push(p3);
    }
    S.push(hull[0]);
    hull_size=S.size()-1;
    for(int i=hull_size; i>=0; --i){
        hull[i]=S.top();
        S.pop();
    }
}


int main() {
    memset(hull_index, -1, sizeof(hull_index));
    cin>>n;
    for(int i=0; i<n; ++i){
        scanf("%lld%lld", &A[i].x, &A[i].y);
        hull[i].x=A[i].x;
        hull[i].y=A[i].y;
        hull[i].original_index=A[i].original_index=i;
    }
    A[n]=A[0];
    twice_poly_area=0;
    for(int i=0; i<n; ++i){
        twice_poly_area+=A[i].x*A[i+1].y-A[i].y*A[i+1].x;
    }
    twice_poly_area=abs(twice_poly_area);
    graham();
    double min_area=-1;
    for(int k=0; k<hull_size; ++k){
        if( abs(hull[k].original_index-hull[k+1].original_index)<2 || abs(hull[k].original_index-hull[k+1].original_index)==n-1){
            Point pl= hull[ (k-1+hull_size)%hull_size ];
            Point pr= hull[ (k+2)%hull_size ];
            if( (pl.x-hull[k].x)*(pr.y-hull[k+1].y)>(pl.y-hull[k].y)*(pr.x-hull[k+1].x) ){
                double a11 = hull[k].y - pl.y;
                double a12 = pl.x - hull[k].x;
                double a21 = hull[k+1].y - pr.y;
                double a22 = pr.x - hull[k+1].x;
                double c1 = pl.x * hull[k].y - pl.y * hull[k].x;
                double c2 = pr.x * hull[k+1].y - pr.y * hull[k+1].x;
                double det=a11*a22-a12*a21;
                double Tx = c1 * ( a22 / det ) - c2 * ( a12 / det );
                double Ty = c2 * ( a11 / det ) - c1 * ( a21 / det );
                double area=(hull[k+1].x - hull[k].x)*(Ty-hull[k].y)-(hull[k+1].y - hull[k].y)*(Tx-hull[k].x);
                if(min_area<0 || min_area>area)min_area=area;
            }
        }
    }
    if(min_area<0)
    printf("-1");
    else
    printf("%f", (min_area - twice_poly_area)/2.0);
    return 0;
}
