// Algorithm_search_substring.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include  <vector>
#include "iostream"
using namespace std;
int naive(string t, string p){
	int n = t.length();
	int m = p.length();
	int flag = 0;
	for (int i = 0; i <= n - m; i++) {
		for (int j = i; j < i+m; j++) {
			if (t[j] == p[j - i])
			{
				flag++;
			}
			else 
			{
				flag = 0;
			}
			/*cout << "flag = " << flag << "\n";
			cout <<"i = "<< i<<"\n";
			cout <<"j = " <<j << "\n";
			cout <<"t[j] = "<< t[j]<<"\n";
			cout << "p[j - i] = " << p[j - i]<<"\n";*/
			if (flag == m)
			{
				return i;
			}
		}
		
	}
	return -1;
}

int KMP(string t, string p) {
	int n = t.length();
	int m = p.length();

	int *d = new int[m];
	d[0] = 0;
	for (int i = 1, j = 0; i < m; i++) {
		while (j > 0 && p[j] != p[i])
			j = d[j - 1];
		if (p[j] == p[i])
			j++;
		d[i] = j;	
	}
	for (int i = 0, j = 0; i < n; i++) {
		while (j > 0 && p[j] != t[i])
			j = d[j - 1];
		if (p[j] == t[i])
			j++;
		if (j == m)
		{
			delete d;
			return i - j + 1;
		}
	}
	delete d;
	return -1;
}

int RK(string t, string p, int q) {
	int n = t.length();
	int m = p.length();
	int d = 222;
	int n1 = 0;
	int m1 = 0;
	int h = 13;
	int j, i;
	for (int i = 0; i < m - 1; i++)
		h = (h*d) % q;
	for (i = 0; i < m; i++)
	{
	n1 = (d*n1 + t[i]) % q;
	m1 = (d*m1 + p[i]) % q;
	}
	for (i = 0; i <= n - m; i++) {
		if (n1 == m1) {
			for (j = 0; j < m; j++) {
				if (t[i + j] != p[j])
					break;
			}
			if (j == m)
				return i;
		}
		if (i < n - m) {
			n1 = (d*(n1 - t[i] * h) + t[i + m]) % q;
			if (n1 < 0)
				n1 = n1 + q;
		}
	}

}
void main()
{
	string s1 = "sbsb  sa sb sa sb";
	string s2 = "sa";
	int q = 73;
	cout <<"naive = "<<naive(s1, s2)<<"\n";
	cout <<"KMP = "<< KMP(s1, s2)<<"\n";
	cout << "RK = " << RK(s1, s2, q) << "\n";
	system("pause");
}

