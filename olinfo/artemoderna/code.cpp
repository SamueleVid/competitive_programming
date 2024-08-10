#include <vector>

using namespace std;

bool ordina(int n, vector<int> v, vector<int> &l) {
	
	vector<int> check;
	int start = 0;
	int prec = 1e9;
	for (int i=0;i<n;i++) {
		if (v[i]>prec) {
			for (int j=i-1;j>=start;j--) {
				check.push_back(v[j]);
			}
		 
			l.push_back(i-start);
			start = i;
		}
		prec = v[i];
	}
	for (int j=n-1;j>=start;j--) {
		check.push_back(v[j]);
	}
		
	l.push_back(n-start);
	
	prec = -1e9;
	for (int i=0;i<n;i++) {
		if (check[i] < prec) return false;
		prec = check[i];
	}
	

	return true;
}
