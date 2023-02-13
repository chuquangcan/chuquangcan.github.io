#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int n, sum=0;
	cin >> n;
	int a[n];
	for (int i=0; i<n; i++)
	{
		cin >> a[i];
		sum=sum+a[i];
	}
	int max = a[0];
	int min = a[0];
	for (int i=0; i<n; i++)
	{
		if (a[i]>max)
			max = a[i];
		if (a[i]<min)
			min = a[i]; 
	}
	cout << "mean: " << double (sum)/n << endl;
	cout << "max: " << max << endl;
	cout << "min: " << min << endl;
}
