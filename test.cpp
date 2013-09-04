#include "RefBase.h"
using namespace android;
class A:public RefBase
{
	int a;

public:
	A():a(3)
	{
		cout << "welcome to A" << endl;
	}
	void p()
	{
		cout << "p:" << a << endl;
	}
	~A()
	{
		cout << "welcome to ~A" << endl;
	}
};

int main()
{
	sp<A> spA= new A;
	wp<A> wpA(spA);
	sp<A> spB = new A;
	cout << "dd";
	spB = spA;
//	A* pB = new A;
//	sp<A> spB(pB);
//	wp<A> wpB(pB);
	//pB = pA;
	return 0;
}
