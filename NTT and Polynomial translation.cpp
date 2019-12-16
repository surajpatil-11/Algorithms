// Source : https://www.codechef.com/viewsolution/28370219

// Given a polynomial p(x) find p(x+t)  
//   f(x) = 3*x^2 + 5*x + 6 then find f(x+2) ? 



#include <bits/stdc++.h>
using namespace std;
#define ll long long int

const int M=998244353, G=3;

ll pm(ll b, int p) {
	ll r=1;
	while(p) {
		if(p&1)
			r=r*b%M;
		b=b*b%M;
		p/=2;
	}
	return r;
}

struct ntt { // ntt -> number theoritic transform
	ll rt[1<<20];
	void fi(int n) {
		rt[n/2]=1;
		rt[n/2+1]=pm(G, (M-1)/n);
		for(int i=n/2+2; i<n; ++i)
			rt[i]=rt[i-1]*rt[n/2+1]%M;
		for(int i=n/2; --i; )
			rt[i]=rt[2*i];
	}
	void ac(vector<ll> &a) {
		int n=a.size();
		for(int i=0, j=0; i<n; ++i) {
			if(i>j)
				swap(a[i], a[j]);
			for(int k=n/2; (j^=k)<k; k/=2);
		}
		for(int st=1; 2*st<=n; st*=2) {
			for(int i=0; i<n; i+=2*st) {
				for(int j=i; j<i+st; ++j) {
					ll z=rt[j-i+st]*a[j+st]%M;
					a[j+st]=a[j]-z;
					if(a[j+st]<0)
						a[j+st]+=M;
					a[j]+=z;
					if(a[j]>=M)
						a[j]-=M;
				}
			}
		}
	}
};
ntt nt;

ll iv[(1<<20)+1];

vector<ll> mult(vector<ll> v, vector<ll> w) { // multiply 2 polynomial v and w 
	int s=v.size()+w.size()-1, t=1;
	while(t<s)
		t*=2;
	v.resize(t);
	w.resize(t);
	nt.ac(v);
	nt.ac(w);
	for(int i=0; i<t; ++i)
		v[i]=v[i]*w[i]%M*iv[t]%M;
	reverse(v.begin()+1, v.end());
	nt.ac(v);
	while(v.back()==0)
		v.pop_back();
	return v;
}


vector<ll> trans(vector<ll> v, ll t) {
	vector<ll> a(v.size()), b(v.size()), r(v.size());
	ll f=1, fi=1, tp=1;
	for(int i=0; i<v.size(); ++i) {
		if(i) {
			f=f*i%M;
			fi=fi*iv[i]%M;
			tp=tp*t%M;
		}
		a[v.size()-1-i]=f*v[i]%M;
		b[i]=tp*fi%M;
	}
	vector<ll> c=mult(a, b);
	fi=1;
	for(int i=0; i<v.size(); ++i) {
		if(i)
			fi=fi*iv[i]%M;
		r[i]=c[v.size()-1-i]*fi%M;
	}
	return r;
}


int main()
{
    //  f(x) = 3*x^2 + 5*x + 6 then f(x+2) = 3*x^2 + 17*x + 28
    
    nt.fi(1<<20);
	iv[1]=1;
	for(int i=2; i<=1<<20; ++i)
		iv[i]=M-M/i*iv[M%i]%M;
    
    vector <ll> poly(3);
    poly[0] = 6 ;
    poly[1] = 5 ;
    poly[2] = 3 ;
    vector <ll> result = trans(poly,2);
    for(ll val : result) cout << val << " " ;

    return 0;
}

// Problem : https://www.codechef.com/DEC19A/problems/BINOFEV


