#include <bits/stdc++.h>
using namespace std;

long long stima(int n, int* h) {
	for (int i=0;i<n;i++) h[i] -= i;

	nth_element(h, h+n/2, h+n);

	long long value = h[n/2];

	long long res = 0;
	for (int i=0;i<n;i++) {
		res += abs(h[i]-value);
	}
	return res;
}
