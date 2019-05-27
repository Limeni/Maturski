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
double minimumBoundingBox(vector<P> h){
    int sz=h.size();
    if(sz==4){
        P e;
        if(!lineIntersection(h[0],h[1],h[2],h[3],e)&&!lineIntersection(h[0],h[3],h[1],h[2],e)&&
        abs(asin(abs((h[1]-h[0]).cross(h[3]-h[0])/((h[1]-h[0]).dist()*(h[3]-h[0]).dist()))-1))<=0.00001){
            return (h[1]-h[0]).dist()*(h[3]-h[0]).dist();
        }
    }
    int ida=0,idb=0,idc=0,idd=0;
    for(int i=0;i<sz;i++){
        if(h[i].y<h[ida].y){ida=i;}
        if(h[i].x>h[idb].x){idb=i;}
        if(h[i].y>h[idc].y){idc=i;}
        if(h[i].x<h[idd].x){idd=i;}
    }
    double angle=0;
    P a1=P(h[idb].x,h[ida].y),b1=P(h[idb].x,h[idc].y),c1=P(h[idd].x,h[idc].y),d1=P(h[idd].x,h[ida].y);
    P a2,b2,c2,d2,a,b,c,d;
   /* cout<<"ida:"<<ida<<endl;
    cout<<"h[ida]:"<<h[ida].x<<" "<<h[ida].y<<endl;
    cout<<"idb:"<<idb<<endl;
    cout<<"h[idb]:"<<h[idb].x<<" "<<h[idb].y<<endl;
    cout<<"idc:"<<idc<<endl;
    cout<<"h[idc]:"<<h[idc].x<<" "<<h[idc].y<<endl;
    cout<<"idd:"<<idd<<endl;
    cout<<"h[idd]:"<<h[idd].x<<" "<<h[idd].y<<endl;
    cout<<"a1:"<<a1.x<<" "<<a1.y<<endl;
    cout<<"b1:"<<b1.x<<" "<<b1.y<<endl;
    cout<<"c1:"<<c1.x<<" "<<c1.y<<endl;
    cout<<"d1:"<<d1.x<<" "<<d1.y<<endl;
    */
    double pmin=(h[idc].y-h[ida].y)*(h[idb].x-h[idd].x),curr;
    //double eps=0.000001;
    while(angle<3.15){
        a=h[ida];b=h[idb];c=h[idc];d=h[idd];
        double tetaa=asin(abs((a1-a).cross(h[next(ida,sz)]-a)/((a1-a).dist()*(h[next(ida,sz)]-a).dist())));//ugao A1AAnx;
        double tetab=asin(abs((b1-b).cross(h[next(idb,sz)]-b)/((b1-b).dist()*(h[next(idb,sz)]-b).dist())));//ugao B1BBnx;
        double tetac=asin(abs((c1-c).cross(h[next(idc,sz)]-c)/((c1-c).dist()*(h[next(idc,sz)]-c).dist())));//ugao C1CCnx;
        double tetad=asin(abs((d1-d).cross(h[next(idd,sz)]-d)/((d1-d).dist()*(h[next(idd,sz)]-d).dist())));//ugao D1DDnx;
        double tetamin=min(min(tetaa,tetab),min(tetac,tetad));
        //if(max(max(tetaa,tetab),max(tetac,tetad))<=eps){cout<<"ye"<<endl;break;}
        /*cout<<"a1:"<<a1.x<<" "<<a1.y<<endl;
        cout<<"a:"<<a.x<<" "<<a.y<<endl;
        cout<<"tetaa:"<<tetaa<<endl;
        cout<<"tetab:"<<tetab<<endl;
        cout<<"tetac:"<<tetac<<endl;
        cout<<"tetad:"<<tetad<<endl;
        cout<<"tetamin:"<<tetamin<<endl;
        */
        if(tetamin==tetaa){
            a2=h[next(ida,sz)];
            b2=b+(a-h[next(ida,sz)]).perp();
            c2=c+(a-h[next(ida,sz)]);
            d2=d+(a-h[next(ida,sz)]).perp();
            ida=next(ida,sz);
          /*  cout<<"a2:"<<a2.x<<" "<<a2.y<<endl;
            cout<<"b2:"<<b2.x<<" "<<b2.y<<endl;
            cout<<"c2:"<<c2.x<<" "<<c2.y<<endl;
            cout<<"d2:"<<d2.x<<" "<<d2.y<<endl;
            */
        }
        if(tetamin==tetab){
            a2=a+(b-h[next(idb,sz)]).perp();
            b2=h[next(idb,sz)];
            c2=c+(b-h[next(idb,sz)]).perp();
            d2=d+(b-h[next(idb,sz)]);
            idb=next(idb,sz);
        }
        if(tetamin==tetac){
            a2=a+(c-h[next(idc,sz)]);
            b2=b+(c-h[next(idc,sz)]).perp();
            c2=h[next(idc,sz)];
            d2=d+(c-h[next(idc,sz)]).perp();
            idc=next(idc,sz);
        }
        if(tetamin==tetad){
            a2=a+(d-h[next(idd,sz)]).perp();
            d2=b+(d-h[next(idd,sz)]);
            c2=c+(d-h[next(idd,sz)]).perp();
            d2=h[next(idd,sz)];
            idd=next(idd,sz);
        }
        lineIntersection(a,a2,b,b2,a1);
        lineIntersection(b,b2,c,c2,b1);
        lineIntersection(c,c2,d,d2,c1);
        lineIntersection(d,d2,a,a2,d1);
        curr=(a1-b1).dist()*(a1-d1).dist();
       /* cout<<"a1:"<<a1.x<<" "<<a1.y<<endl;
        cout<<"b1:"<<b1.x<<" "<<b1.y<<endl;
        cout<<"c1:"<<c1.x<<" "<<c1.y<<endl;
        cout<<"d1:"<<d1.x<<" "<<d1.y<<endl;
        */
        pmin=min(pmin,curr);
        angle+=tetamin;
    }
    return pmin;
}
int main()
{
    return 0;
}
