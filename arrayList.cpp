/*
 * arrayList.cpp
 *
 *  Created on: 2017年3月19日
 *      Author: lsn
 */

#include "arrayList.h"
#include <sstream>//定义了ostringstream类



template<class T>
arrayList<T>::arrayList(int initialCapacity) {
	//因为是构造函数，arrayList对象还不存在，构造一个新arrayList对象
	arrayLength = initialCapacity ;
	//T必须有缺省构造函数
//	/注意：按照new操作的含义 已经生成了arrayLength个 T 的对象！！！
	element = new T[arrayLength];
	listSize = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList& theList) {
	//因为是构造函数，对象还不存在，这个函数的目的是根据theList对象，构造一个新对象
	arrayLength  = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const{
	if(theIndex < 0 || theIndex >=listSize){
		std::ostringstream s;
		s << "index = "<<theIndex <<" size = " <<listSize;
		throw std::out_of_range(s.str());
		//throw std::out_of_range(std::to_string(theIndex)); //C++11标准引入的
	}
}


template<class T>
T& arrayList<T>::get(int theIndex) const{
	checkIndex(theIndex);//0<=theIndex<listSize
	return element[theIndex];
}

template<class T>
const T * arrayList<T>::find( const T* start, const T* end, const T &theElement) const{
	while(start != end && *start != theElement) start++;//利用了求&&的特点，左边不满足就不在对计算右边
	return start;//如果没有找到start == end
}

template<class T>
void arrayList<T>::copy_backward(const T * start, const T* end, T* target) const{
	while(start != end)	*--target = *--end;//end和target都往右多1位
}

template<class T>
void arrayList<T>::copy(const T* start,const T* end, T* target) const{
	while(start != end) *target++ = *start++;
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement){

	if(theIndex != listSize)//插入最后1个元素的后面是允许的。
		checkIndex(theIndex);

	if(listSize == arrayLength)
	{
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	element[theIndex] = theElement;//因为theElement是const，所以要求opertor=(const

	listSize++;
}

template<class T>
void arrayList<T>::erase(int theIndex){
	checkIndex(theIndex);
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);
	//element[--listSize].~T();//这里有问题，需要好好安排
	--listSize;

}


template<class T>
void arrayList<T>::changeLength1D(T * &a, int oldLength, int newLength){
	if(newLength < 0)
		throw std::invalid_argument("new length must be >= 0");
	T * temp = new T[newLength];
	int number = std::min(oldLength,newLength);
	std::copy(a, a + number, temp);
	delete [] a;
	a= temp;
}

template<class T>
int arrayList<T>::indexOf(const T &theElement ) const{
	int theIndex = (int)(std::find(element,element + listSize, theElement) - element);
	//theElement 是const，要求find函数的theElement也是const
	if(theIndex == listSize)
		return -1;
	else
		return theIndex;

}


template<class T>
arrayList<T>& arrayList<T>::operator=(const arrayList& rhs){
	//this这个对象已经存在
	if(this == &rhs) return *this;
	listSize = rhs.listSize;
	if(arrayLength < rhs.arrayLength){
		arrayLength = rhs.arrayLength;
		delete [] element;
		element = new T[arrayLength];
	};
	std::copy(rhs.element, rhs.element + listSize, element);
	return *this;
}


template<class T>
void arrayList<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	std::copy(element, element + listSize, std::ostream_iterator<T>(out, "  "));
	//for(T * p = element;  p < element + arrayLength; p++) out << *p << " ";
	//out << std::endl;
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x){
	x.output(out);
	return out;
}

