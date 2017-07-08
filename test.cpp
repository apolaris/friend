/*
 * test.cpp
 *
 *  Created on: 2017年3月19日
 *      Author: lsn
 */

#include "arrayList.cpp"
#include "chain.cpp"
#include <numeric>//accumulate
#include <algorithm>
using std::cout;
using std::endl;

//类模版可以自动（隐式）实例化，也可以手动（显式）实例化
//隐式实例化只实例化所有的声明语句、用到的成员的函数和所有的虚函数

//手动（显式）实例化目的：
//1 加快编译速度
//2 会产生一个完整的类，帮助检查错误。

//以下为手动（显式）实例化的写法，去掉后，main中的arrayList<int> y(2), z;就采用隐式实例化

//template class arrayList<int>;//显式实例化一个arrayList<int>
//template class chain<int>;

/*
//解释为什么书上的erase最后不能调用析构函数
struct test{
	static int count;
	test(){
		list = new int[10];
		sno = ++count;
		cout <<"ctor of "<<sno<<" :  ";
	};
	test(test& right){
		sno = ++count;
		list = new int[10];
		cout <<"copy ctor of  "<<sno<<" from " << right.sno<<"  :  ";
	};

	~test(){
		cout <<"dtor of "<<sno<<"  :  ";
		delete [] list;
	};
	void output() const{
		cout<<sno<<"  :  ";
	};

	test& operator=(const test& right){//改成引用，否则会引发调用copy constructor
		cout <<"assignment   "<<sno<<" from " << right.sno<<"  :  ";
		return *this;
	};
	bool operator!=(const test& right) const{
		return  list != right.list;
	}

	bool operator==(const test& right) const{
		return  list == right.list;
	}

	int * list;
	int sno;
};

int test::count = 0;


std::ostream& operator<<(std::ostream& out, const test& x){
	x.output();
	return out;
}

int main(){

	arrayList<test> y;

	cout<<endl;

	y.insert(0,test());

	cout<<endl;
	//cout<<y<<endl;
	y.insert(1,test());

	cout<<endl;
	//cout <<y<<endl;
	y.erase(0);
	cout <<"num of test="<<test::count <<endl;

}

*/

/*
int main(){
//测试arrayList

	  // test constructor
	   linearList<double> *x = new arrayList<double>(20);
	   arrayList<int> y(2), z;


	   // test capacity
	   cout << "Capacity of x, y and z = "
	        << ((arrayList<double>*) x)->capacity() << ", "
	        << y.capacity() << ", "
	        << z.capacity() << endl;
	           // test size
	   cout << "Initial size of x, y, and z = "
	        << x->size() << ", "
	        << y.size() << ", "
	        << z.size() << endl;

	   // test empty
	   if (x->empty())
		   cout << "x is empty" << endl;
	   else
		   cout << "x is not empty" << endl;
	   if (y.empty())
		   cout << "y is empty" << endl;
	   else
		   cout << "y is not empty" << endl;

	      // test insert
	   y.insert(0, 2);
	   y.insert(1, 6);
	   y.insert(0, 1);
	   y.insert(2, 4);
	   y.insert(3, 5);
	   y.insert(2, 3);
	   cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	   cout << "Size of y = " << y.size() << endl;
	   cout << "Capacity of y = " << y.capacity() << endl;
	   if (y.empty())
		   cout << "y is empty" << endl;
	   else
		   cout << "y is not empty" << endl;
	   y.output(cout);
	   cout << endl << "Testing overloaded <<" << endl;
	   cout << y << endl;

	      // test indexOf
	   int index = y.indexOf(4);
	   if (index < 0)
		   cout << "4 not found" << endl;
	   else
		   cout << "The index of 4 is " << index << endl;

	   index = y.indexOf(7);
	   if (index < 0)
		   cout << "7 not found" << endl;
	   else
		   cout << "The index of 7 is " << index << endl;

	   // test get
	   cout << "Element with index 0 is " << y.get(0) << endl;
	   cout << "Element with index 3 is " << y.get(3) << endl;


	      // test erase
	   y.erase(1);
	   cout << "Element 1 erased" << endl;
	   cout << "The list is "  << y << endl;
	   y.erase(2);
	   cout << "Element 2 erased" << endl;
	   cout << "The list is "  << y << endl;

	   cout << "Size of y = " << y.size() << endl;
	   cout << "Capacity of y = " << y.capacity() << endl;
	   if (y.empty())
		   cout << "y is empty" << endl;
	   else
		   cout << "y is not empty" << endl;

	   //test copy constrcut
	   arrayList<int> w(y);
	   cout << "w=y is"<<endl;
	   cout << w << endl;

	   try {
		   y.insert(-3, 0);
	   }
	   catch (std::out_of_range &e)
	   {
	      cout << e.what()<< endl;
	   }

	   // a few more inserts, just for fun
	   y.insert(0,4);
	   y.insert(0,5);
	   y.insert(0,6);
	   y.insert(0,7);
	   y.insert(3,9);

	   cout << "y is " << y << endl;

	   arrayList<int> m;
	   m = y;

	   cout << "m is "<< m << endl;



	   //测试迭代器
	   arrayList<int>::iterator  itStart, itEnd;

	   itStart = y.begin();
	   itEnd = y.end();

	   cout << "output y by iterator " << y << endl;

	   //使用迭代器逐一访问arrayList中的元素
	   while(itStart != itEnd){
		   cout << *itStart<<"  ";
		   ++itStart;//看相关的实现代码，++写在前面不用使用临时变量
	   }
	   cout<<endl;

	   //arrayList中有了迭代器，就可以使用标准库中的算法处理arrayList
	   std::reverse(y.begin(), y.end());
	   cout << "The reversed list is " << y << endl;
	   int sum = std::accumulate(y.begin(), y.end(), 0);
	   cout << "The sum of the elements is " << sum << endl;
	   std::sort(y.begin(),y.end());
	   cout << "after sort the elements is " << y << endl;

	   cout << y<<endl;

	   arrayList<int>::iterator p;
	   p = std::find(y.begin(),y.end(),7);
	   if(p != y.end())
		   cout << "found it: "<< *p<<endl;


	   itStart = y.begin();
	   itEnd = y.end();
	   cout << y <<endl;


	   //加入10影响了iterator
	   y.insert(3,10);
	   cout << y <<endl;

	   while(itStart != itEnd){
		   cout << *itStart<<"  ";
		   ++itStart;//看相关的实现代码，++写在前面不用使用临时变量
	   }
	   cout<<endl;

	   //测试逆迭代器
	   arrayList<int>::reverse_iterator  ritStart, ritEnd;

	   ritStart = y.rbegin();
	   ritEnd = y.rend();

	   cout << "output y by reverse iterator: " << endl;

	   //使用迭代器逐一访问arrayList中的元素
	   while(ritStart != ritEnd){
		   cout << *ritStart<<"  ";
		   ++ritStart;//看相关的实现代码，++写在前面不用使用临时变量
	   }
	   cout<<endl;


    //测试arrayList里面放置arrayList
	arrayList<arrayList<int> > xx;

	arrayList<int>yy;
	yy.insert(0,1);
	yy.insert(1,2);
	yy.insert(2,3);
	xx.insert(0,yy);

	yy.insert(0,10);
	xx.insert(1,yy);

	arrayList<arrayList<int> >::iterator tmpiterator;
	tmpiterator = std::find(xx.begin(),xx.end(),yy);
	cout << *tmpiterator<<endl;
	cout << xx;
}
*/

int main(){
//测试chain
	  // test constructor
	   linearList<double> *x = new chain<double>(20);//
	   chain<int> y(2), z;//


	   // test capacity
	   cout << "Capacity of x, y and z = "
	        << ((arrayList<double>*) x)->capacity() << ", "
	        << y.capacity() << ", "
	        << z.capacity() << endl;
	           // test size
	   cout << "Initial size of x, y, and z = "
	        << x->size() << ", "
	        << y.size() << ", "
	        << z.size() << endl;

	   // test empty
	   if (x->empty())
		   cout << "x is empty" << endl;
	   else
		   cout << "x is not empty" << endl;
	   if (y.empty())
		   cout << "y is empty" << endl;
	   else
		   cout << "y is not empty" << endl;

	      // test insert
	   y.insert(0, 2);
	   y.insert(1, 6);
	   y.insert(0, 1);
	   y.insert(2, 4);
	   y.insert(3, 5);
	   y.insert(2, 3);
	   cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	   cout << "Size of y = " << y.size() << endl;
	   cout << "Capacity of y = " << y.capacity() << endl;
	   if (y.empty())
		   cout << "y is empty" << endl;
	   else
		   cout << "y is not empty" << endl;
	   y.output(cout);

	   cout << "Testing overloaded <<" << endl;
	   cout << y << endl;

	      // test indexOf
	   int index = y.indexOf(4);
	   if (index < 0)
		   cout << "4 not found" << endl;
	   else
		   cout << "The index of 4 is " << index << endl;

	   index = y.indexOf(7);
	   if (index < 0)
		   cout << "7 not found" << endl;
	   else
		   cout << "The index of 7 is " << index << endl;

	   // test get
	   cout << "Element with index 0 is " << y.get(0) << endl;
	   cout << "Element with index 3 is " << y.get(3) << endl;


	      // test erase
	   y.erase(1);
	   cout << "Element 1 erased" << endl;
	   cout << "The list is "  << y << endl;
	   y.erase(2);
	   cout << "Element 2 erased" << endl;
	   cout << "The list is "  << y << endl;

	   cout << "Size of y = " << y.size() << endl;
	   cout << "Capacity of y = " << y.capacity() << endl;
	   if (y.empty())
		   cout << "y is empty" << endl;
	   else
		   cout << "y is not empty" << endl;

	   //test copy constrcut
	   chain<int> w(y);
	   cout << "w=y"<<endl;
	   cout << w << endl;

	   try {
		   y.insert(-3, 0);
	   }
	   catch (std::out_of_range &e)
	   {
	      cout << e.what()<< endl;
	   }

	   // a few more inserts, just for fun

	   y.insert(0,4);
	   y.insert(0,5);
	   y.insert(0,6);
	   y.insert(0,7);
	   y.insert(3,9);

	   cout << "y is " << y << endl;



	   std::reverse(y.beginRan(), y.endRan());
	   cout << "The reversed list is " << y << endl;
	   std::sort(y.beginRan(),y.endRan());
	   cout << "after sort the elements is " << y << endl;

	   int sum = std::accumulate(y.beginRan(), y.endRan(), 0);
	   cout << "The sum of the elements is " << sum << endl;
}

