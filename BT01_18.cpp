#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	double dis;
	dis=sqrt((a-c)*(a-c)+(b-d)*(b-d));
	cout << dis;
	return 0;
}
