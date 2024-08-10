#include <bits/stdc++.h>
#define ll long long
#pragma GCC optimize("Ofast")
using namespace std;

struct node{
	ll value=0;
	node* sx;
	node* dx;
};

node arr[5000000];
int pt=0;
node* new_node() {
	node* nuovo = arr+pt;
	pt++;
	nuovo->value = 0;
	return nuovo;
};

vector<node*>pers;

void build(node* nodo, int lb, int rb) {
	if (rb-lb==1) return;
	node* sx = new_node();
	node* dx = new_node();
	build(sx, lb, (rb+lb)/2);
	build(dx, (rb+lb)/2,rb);
	nodo->sx = sx;
	nodo->dx = dx;
}

node* add(node* nodo, int lb, int rb, int currlb, int currrb, int x) {
	if (currrb<=lb||rb<=currlb) return nodo;
	node* nuovo = new_node();
	nuovo->value = nodo->value;
	
	if ((currrb-currlb)==1) {
		nuovo->value += x;
		return nuovo;
	}
	
	nuovo->sx = add(nodo->sx, lb, rb, currlb, (currlb+currrb)/2, x);
	nuovo->dx = add(nodo->dx, lb, rb, (currlb+currrb)/2, currrb, x);
	nuovo->value = nuovo->sx->value + nuovo->dx->value;

	return nuovo;
}

int query(node* nodo, int lb, int rb, int currlb, int currrb) {
	if (currrb<=lb||rb<=currlb) return 0;

	if (lb<=currlb&&currrb<=rb) {
		return nodo->value;
	}
	int res = 0;
	res += query(nodo->sx, lb, rb, currlb, (currlb+currrb)/2);
	res += query(nodo->dx, lb, rb, (currlb+currrb)/2, currrb);
	
	return res;
}

int n;

void init(int n) {
	node* orig = new_node();
	build(orig,0,n);
	
	pers.push_back(orig);
	::n=n;
}

void log(vector<int>& added, vector<int>& removed) {
	vector<node*>curr;
	curr.push_back(pers.back());
	for (auto x:added) curr.push_back(add(curr.back(),x,x+1,0,n,1));
	for (auto x:removed) curr.push_back(add(curr.back(),x,x+1,0,n,-1));

	pers.push_back(curr.back());
	return;
}

int answer(int d, int x) {
	return query(pers[d], x, n, 0, n);
}
