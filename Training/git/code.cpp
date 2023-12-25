#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct node{
	long long value = 0;
	long long lazy = 0;
	node* sx = nullptr;
	node* dx = nullptr;
};

int last=0;
node arr[11500000];

node* nuovo_nodo() {
    node* res = arr+last;
    last ++;
    return res;
}

node* clone(node* nodo) {
	node* new_nodo = nuovo_nodo();
	new_nodo->value = nodo->value;
	new_nodo->lazy = nodo->lazy;
	new_nodo->sx = nodo->sx;
	new_nodo->dx = nodo->dx;
	return new_nodo;
}

vector<node*>old_versions;

void push_lazy(node* nodo, int l, int r) {
	if (nodo->lazy == 0) return;
	nodo->value += nodo->lazy * (r - l);
    if (nodo->sx != nullptr) {
        node* new_sx = clone(nodo->sx);
        new_sx->lazy += nodo->lazy;
        nodo->sx = new_sx;
    }
	
    if (nodo->dx != nullptr) {
        node* new_dx = clone(nodo->dx);
        new_dx->lazy += nodo->lazy;
        nodo->dx = new_dx;
    }
    nodo->lazy = 0;
}

node* update(int cl, int cr, int l, int r, node* nodo, int x) {
	push_lazy(nodo, cl, cr);
	
	// se fuori ignora
	if (cr <= l || r <= cl) return nodo;

	// creo nuovo nodo
	node* new_nodo = clone(nodo);

	// se tutto dentro
	if (l <= cl && cr <= r) {
		new_nodo->lazy += x;
		push_lazy(new_nodo, cl, cr);
		return new_nodo;
	}
	
	// se intersezione allora aggiungo al nodo il valore dell'intersezione	
	// e scendo ai figli
	new_nodo->sx = update(cl,(cl+cr)/2,l,r,new_nodo->sx, x);
	new_nodo->dx = update((cl+cr)/2,cr,l,r,new_nodo->dx, x);
	new_nodo->value = new_nodo->sx->value + new_nodo->dx->value;
	return new_nodo;
}

node* reset(int cl, int cr, int l, int r, node* oldnodo, node* newnodo) {
	// oldnodo e newnodo hanno stesso l e r, rappresentano solo versioni diverse.
	push_lazy(oldnodo, cl, cr);
	push_lazy(newnodo, cl, cr);
	
	// se fuori ritorna quello nuovo
	if (cr <= l || r <= cl) return newnodo;

	// se tutto dentro ritorna quello vecchio
	if (l <= cl && cr <= r) {
		return oldnodo;
	}

	// devo stare attento ai valori della lazy su questo
	node* new_nodo = nuovo_nodo();
	new_nodo->lazy = 0;
	
	// e scendo ai figli
	new_nodo->sx = reset(cl,(cl+cr)/2,l,r,oldnodo->sx,newnodo->sx);
	new_nodo->dx = reset((cl+cr)/2,cr,l,r,oldnodo->dx,newnodo->dx);
	new_nodo->value = new_nodo->sx->value + new_nodo->dx->value;

	return new_nodo;
}

long long sum(int cl, int cr, int l, int r, node* nodo) {
	// se fuori ignora
	if (cr <= l || r <= cl) return 0;
	
	// pusho per avere il vero valore
	push_lazy(nodo, cl, cr);
	
	// se tutto dentro
	if (l <= cl && cr <= r) {
		return nodo->value;
	}
	long long res = 0;
	// se parzialmente
	res += sum(cl,(cl+cr)/2,l,r,nodo->sx);
	res += sum((cl+cr)/2,cr,l,r,nodo->dx);

	return res;
}

node* crea(int l, int r, vector<int>&a) {
	node* nodo = nuovo_nodo();
	if ((r-l)==1) {
		nodo->value=a[l];
		return nodo;
	}
	node* sx = crea(l,(l+r)/2,a);
	node* dx = crea((l+r)/2,r,a);
	nodo->value = sx->value + dx->value;
	nodo->sx = sx;
	nodo->dx = dx;
	return nodo; 
}

int n;

void inizia(int n, vector<int> a) {
    ::n=n;
	node* nodo = crea(0,n,a);
	old_versions.push_back(nodo);
}

void incrementa(int l, int r, int x) {
	old_versions.push_back(update(0,n,l,r,old_versions.back(),x));
}
void resetta(int l, int r, int v) {
	old_versions.push_back(reset(0,n,l,r,old_versions[v],old_versions.back()));
}
long long somma(int l, int r) {
	return sum(0,n,l,r,old_versions.back());
}
