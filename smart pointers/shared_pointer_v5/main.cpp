// Shared Pointer vs Weak Pointer
//
// http://www.umich.edu/~eecs381/examples/std_smart_pointer_demos/shared_vs_weak_ptr_demo.cpp

/* Comparison of shared_ptr and weak_ptr as
returned values from functions. Also, demo
of testing for expired object.
*/


#include <iostream>
#include <memory>

using namespace std;

class Thing {
public:
	Thing() : i (++count) {cout << "Thing " << i << " creation" << endl;}
	~Thing () {cout << "Thing " << i << " destruction" << endl;}
	int get() const {return i;}
private:
	int i;
	static int count;
};

int Thing::count = 0;

//return a weak pointer
weak_ptr<Thing> return_weak(){
	shared_ptr<Thing> p (new Thing);
	std::cout <<"in return_weak: Thing " << p->get()<<std::endl;
	weak_ptr<Thing> wp = p;
	return wp;
}

//create a Thing, but return a shared_ptr to it
shared_ptr<Thing> return_shared(){
	shared_ptr<Thing> p (new Thing);
	std::cout << "in return_shared: Thing "<< p->get() << std::endl;
	return p;
}

//check the weak_ptr to see if the Thing is still there
//in two diferents ways
void is_it_there(weak_ptr<Thing> wp){
	if(wp.expired())
	   std::cout << "it is expired" << std::endl;
	else
	   std::cout << "it is not expired"<< std::endl;

	shared_ptr<Thing> p = wp.lock();
	
	if(!p)
	  std::cout << "it is gone!" << std::endl;
	else
	  std::cout << "it is Thing" << std::endl;

	//no return expired variables
}

int main()
{
	shared_ptr<Thing>p (new Thing);
	cout <<"in main: thing " << p->get()<<endl;

	weak_ptr<Thing> wp1 = return_weak();
	cout <<"->before is_it_there"<< endl;
	is_it_there(wp1);

	p = return_shared();
	weak_ptr<Thing> wp2 = p;
	cout <<"->before is_it_there"<< endl;
	is_it_there(wp2);

	cout << "End " << endl;
	return 0;
}
