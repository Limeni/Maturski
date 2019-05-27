#include <bits/stdc++.h>

using namespace std;
int x[210],y[210];
vector<double> oP,oN;
double eps=0.0000001;
inline long long crossProduct(long long a, long long b, long long c)
{
    return ((x[b] - x[a]) * (y[c] - y[a]) - (y[b] - y[a]) * (x[c] - x[a]));
}

double P;
double sol=0;
inline long long abss(long long x)
{
    if(x<0)return -x;
    return x;
}
inline void update(double newsol)
{
    //printf("%lf\n",newsol);
    double olddiff=abss(sol-P);
    double newdiff=abss(newsol-P);
    if(abss(olddiff-newdiff)<eps)sol=max(newsol,olddiff);
    else if(olddiff>newdiff)
        sol=newsol;
}
int main()
{
    int n;
    scanf("%d%lf",&n,&P);
    for(int i=0; i<n; i++)
        scanf("%d%d",&x[i],&y[i]);
    for(int da=0; da<n; da++)
        for(int db=da+1; db<n; db++)
        {
            oP.clear();
            oN.clear();
            for(int dc=0; dc<n; dc++)
            {
                if(dc==da)continue;
                if(dc==db)continue;
                long long cross=crossProduct(da,db,dc);
                double a=abs(cross)/2.0;
                //printf("area: %lf orient: %lf\n",a,left(da,db,dc));
                if(a<eps)continue;
                bool orient=cross>0;
                if(orient)oP.push_back(a);
                else oN.push_back(a);
            }
            sort(oP.begin(),oP.end());
            sort(oN.begin(),oN.end());
            /*
                        for(int i=0; i<oN.size(); i++)
            {
                double leftarea=P-oN[i];
                if(leftarea<0)continue;
                int idx=lower_bound(oP.begin(),oP.end(),leftarea)-oP.begin();
                if(idx<oP.size())update(oP[idx]+oN[i]);
                if(idx-1>=0)update(oP[idx-1]+oN[i]);
            }
            */
            int idx=oP.size()-1;
            for(int i=0; i<oN.size(); i++)
            {
                while(idx>0&&oN[i]+oP[idx]>P)idx--;
                if(idx<oP.size())update(oP[idx]+oN[i]);
                if(idx-1>=0)update(oP[idx-1]+oN[i]);
                if(idx+1<oP.size())update(oP[idx+1]+oN[i]);
            }
            //printf("_________________\n");
        }
    printf("%.2lf\n",sol);
    return 0;
}
