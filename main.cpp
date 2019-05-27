#include <bits/stdc++.h>

using namespace std;
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}//konstruktor
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }//provera rasporeda po x,pa zatim y osi
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }//provera jednakosti
	P operator+(P p) const { return P(x+p.x, y+p.y); }//sabiranje vektora
	P operator-(P p) const { return P(x-p.x, y-p.y); }//oduzimanje vektora
	P operator*(T d) const { return P(x*d, y*d); }//mnozenje skalarom
	P operator/(T d) const { return P(x/d, y/d); }//deljenje skalarom
	T dot(P p) const { return x*p.x + y*p.y; }//skalarni porizvod
	T cross(P p) const { return x*p.y - y*p.x; }//vektorski proizvod
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }//vektorski proizvod dva translirana vektora
	T dist2() const { return x*x + y*y; }//kvadrat udaljenosti od koordinatnog pocetka
	double dist() const { return sqrt((double)dist2()); }//udaljenost od koordinatnog pocetka
	double angle() const { return atan2(y, x); }//ugao u odnosu na koordinatni pocetak u intervalu [-pi,pi]
	P unit() const { return *this/dist(); } //normiranje vektora(postavljanje udaljenosti od koordinatnog pocetka na 1
	P perp() const { return P(-y, x); } //rotacija za 90 stepeni(tj. vektor normalan na pocetni sa istim intenzitetom)
	P normal() const { return perp().unit(); }//vektor normalan na pocetni za intenzitetom 1(vektor normale)
	P rotate(double a) const {
	    return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }//rotacija za a radijana oko koordinatnog pocetka
};
template<class P>
bool onLine(const P& s, const P& e, const P& p) {
	P ds = p-s, de = p-e;
	return ds.cross(de) == 0;
}
template<class P>
bool onSegment(const P& s, const P& e, const P& p) {
	P ds = p-s, de = p-e;
	return ds.cross(de) == 0 && ds.dot(de) <= 0;
}
template<class P>
double lineDist(const P& a, const P& b, const P& p) {
	return abs((double)(b-a).cross(p-a)/(b-a).dist());
}
typedef Point<double> P;
double segDist(P& s, P& e, P& p) {
	if ((p-s).dot(e-s)<=0) return (p-s).dist();
	else if((p-e).dot(s-e)<=0)return (p-e).dist();
	else return lineDist(s,e,p);
}
template<class P>
int lineIntersection(const P& s1, const P& e1, const P& s2,
		const P& e2, P& r) {
	if ((e1-s1).cross(e2-s2)) {
		r = s2-(e2-s2)*(e1-s1).cross(s2-s1)/(e1-s1).cross(e2-s2);
		return 1;
	} else
		return -((e1-s1).cross(s2-s1)==0 || s2==e2);
}
template<class P>
int segmentIntersection(const P& s1, const P& e1, const P& s2,
		const P& e2, P& r) {
	if ((e1-s1).cross(e2-s2)) {
		r = s2-(e2-s2)*(e1-s1).cross(s2-s1)/(e1-s1).cross(e2-s2);
		if(onSegment(s1,e1,r)&&onSegment(s2,e2,r))
            return 1;
        else
            return 0;
	} else
		return -((e1-s1).cross(s2-s1)==0&&(onSegment(s1,e1,s2)||onSegment(s1,e1,e2)));
}
template<class P>
int sideOf(const P& s, const P& e, const P& p) {
    //vraca 1 ako je p levo od s u odnosu na e, 0 ako su kolinearne i -1 inace
	auto a = (e-s).cross(p-s);
	return (a > 0) - (a < 0);
}
template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
    //isto kao i gornja funkcija u okviru nekih granica preciznosti (za double)
	auto a = (e-s).cross(p-s);
	double l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}
template<class P>
bool cmp(P a,P b){
    int x=sideOf(a,b,P(0,0));
    if(x==1)return true;
    if(x==0)return a.dist()<b.dist();
    if(x==-1)return false;
}
template<class P>
void Sort(vector<P>& arr){
    P mn=arr[0];vector<P> arr2;
    for(int i=1;i<arr.size();i++){
        if((arr[i].y<mn.y)||(arr[i].y==mn.y&&arr[i].x>mn.x)){
            mn=arr[i];
        }
    }
    for(int i=0;i<arr.size();i++){
        if(arr[i].x!=mn.x||arr[i].y!=mn.y){
            arr2.push_back(arr[i]-mn);
        }
    }
    sort(arr2.begin(),arr2.end(),cmp<P>);
    arr2.insert(arr2.begin(),mn);
    for(int i=1;i<arr2.size();i++){
        arr2[i]=arr2[i]+arr2[0];
    }
    arr=arr2;
}
template<class P>
P nextToTop(stack<P>& s){
    P p=s.top();
    s.pop();
    P res=s.top();
    s.push(p);
    return res;
}
template<class P>
vector<P> convexHull(vector<P>& arr){
    stack<P> s;
    s.push(arr[0]);s.push(arr[1]);
    for(int i=2;i<arr.size();i++){
        if(sideOf(nextToTop(s),s.top(),arr[i])==0){
            s.pop();s.push(arr[i]);
            continue;
        }
        while(sideOf(nextToTop(s),s.top(),arr[i])!=1){
            s.pop();
        }
        s.push(arr[i]);
    }
    vector<P> arr2;
    while(!s.empty()){
        arr2.insert(arr2.begin(),s.top());
        s.pop();
    }
    return arr2;
}
template<class T>
T area2(vector<Point<T>>& v){
    T a=v.back().cross(v[0]);
    for(int i=0;i<v.size()-1;i++){
        a+=v[i].cross(v[i+1]);
    }
    return a;
}
template<class T>
T area(vector<Point<T>>& v){return abs(area2(v))/2;}
typedef Point<double> P;
Point<double> polygonCenter(vector<P>& v) {
	auto i = v.begin(), end = v.end(), j = end-1;
	Point<double> res{0,0}; double A = 0;
	for (; i != end; j=i++) {
		res = res + (*i + *j) * j->cross(*i);
		A += j->cross(*i);
	}
	return res / A / 3;
}
template<class It, class P>
bool insidePolygon(It begin, It end, const P& p,
		bool strict = true) {
	int n = 0; //broj preseka poluprave od p do (inf,p.y) sa duzima u mnogouglu
	for (It i = begin, j = end-1; i != end; j = i++) {
		//ako je p na ivici mnogougla
		if (onSegment(*i, *j, p)) return !strict;
		//povecavamo n ako duz u mnogouglu sece polupravu iz p
		n += (max(i->y,j->y) > p.y && min(i->y,j->y) <= p.y &&
				((*j-*i).cross(p-*i) > 0) == (i->y <= p.y));
	}
	return n&1; //ako je broj preseka neparan, tacka pripada mnogouglu
}
template<class P>
int insideHull2(const vector<P>& H, int L, int R, const P& p) {
	int len = R - L;
	if (len == 2) {
		int sa = sideOf(H[0], H[L], p);
		int sb = sideOf(H[L], H[L+1], p);
		int sc = sideOf(H[L+1], H[0], p);
		if (sa < 0 || sb < 0 || sc < 0) return 0;
		if (sb==0 || (sa==0 && L == 1) || (sc == 0 && R == H.size()))
			return 1;
		return 2;
	}
	int mid = L + len / 2;
	if (sideOf(H[0], H[mid], p) >= 0)
		return insideHull2(H, mid, R, p);
	return insideHull2(H, L, mid+1, p);
}
template<class P>
int insideHull(const vector<P>& hull, const P& p) {
	if (hull.size() < 3) return onSegment(hull[0], hull.back(), p);
	else return insideHull2(hull, 1, hull.size(), p);
}
typedef Point<double> P;
vector<P> polygonCut(const vector<P>& poly, P s, P e) {
	vector<P> res;
	for(int i=0;i<poly.size();i++) {
		P cur = poly[i], prev = i ? poly[i-1] : poly.back();
		bool side = s.cross(e, cur) < 0;
		if (side != (s.cross(e, prev) < 0)) {
			res.emplace_back();
			lineIntersection(s, e, cur, prev, res.back());
		}
		if (side)
			res.push_back(cur);
	}
	return res;
}
int next(int i,int sz){return (i+1)%sz;}
template<class T>
T ar(Point<T> a,Point<T> b,Point<T> c){
    return abs((a-b).cross(a-c))/2;
}
template<class P>
vector<pair<int,int>> antipodalPairs(vector<P>& h){
    vector<pair<int,int>> v;
    int sz=h.size();
    int i0=h.size()-1;
    int i=0;
    int j=next(i,sz);
    while(ar(h[i],h[next(i,sz)],h[next(j,sz)])>ar(h[i],h[next(i,sz)],h[j])){
        j=next(j,sz);
    }
    int j0=j;
    while(j!=next(i0,sz)){
        i=next(i,sz);
        v.push_back({i,j});
        while(ar(h[i],h[next(i,sz)],h[next(j,sz)])>ar(h[i],h[next(i,sz)],h[j])){
            j=next(j,sz);
            if(!(i==j0&&j==i0)){
                v.push_back({i,j});
            }
            else{
                return v;
            }
        }
        if(ar(h[i],h[next(i,sz)],h[next(j,sz)])==ar(h[i],h[next(i,sz)],h[j])){
            if(i!=j0||j!=i0){
                v.push_back({i,next(j,sz)});
            }
            else{
                v.push_back({next(i,sz),j});
            }
        }
    }
    return v;
}
template<class P>
double polygonDiameter(vector<P> h){
    vector<pair<int,int>>app=antipodalPairs(h);
    double mx=0,curr;
    for(auto& x:app){
        curr=(h[x.first]-h[x.second]).dist();
        mx=max(mx,curr);
    }
    return mx;
}
template<class P>
double polygonWidth(vector<P> h){
    vector<pair<int,int>>app=antipodalPairs(h);
    int sz=h.size();
    vector<vector<int>>g(sz);
    double mn=1e9,curr;
    for(int i=0;i<app.size();i++){
        g[app[i].first].push_back(app[i].second);
        g[app[i].second].push_back(app[i].first);
    }
    for(int i=0;i<sz;i++){
        for(int x=0;x<g[i].size();x++){
            if(next(g[i][x],sz)==g[i][(x+1)%g[i].size()]){
                curr=lineDist(h[g[i][x]],h[g[i][(x+1)%g[i].size()]],h[i]);
                mn=min(mn,curr);
            }
        }
    }
    return mn;
}

int main()
{
    return 0;
}
