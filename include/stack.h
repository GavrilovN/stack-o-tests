#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class allocator
{
protected:
	allocator(size_t size = 0);
	~allocator();
	auto swap(allocator& other)->void;
	allocator(allocator const&) = delete;
	auto operator=(allocator const&)->allocator& = delete;
	T * array_;
	size_t size_;
	size_t count_;
};

//__________________________________________________________________________________________________________________
//__________________________________________________________________________________________________________________


template <typename T1, typename T2>
auto construct(T1 * array_, T2 const & value)->void {
	new(array_) T1(value);
}

template <typename T>
void destroy(T * array_) noexcept
{
	array_->~T();
}

template <typename FwdIter>
void destroy(FwdIter first, FwdIter last) noexcept
{
	for (; first != last; ++first) {
		destroy(&*first);
	}
}

template <typename T>
allocator<T>::allocator(size_t size) : ptr_(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))), size_(size), count_(0) {
};

template <typename T>
allocator<T>::~allocator() {
{
	destroy(array_, array_ + array_size_);
	operator delete(array_);
}

template <typename T>
auto allocator<T>::swap(allocator& other)->void {
	std::swap(array_, other.array_);
	std::swap(size_, other.size_);
	std::swap(count_, other.count_);
};

//__________________________________________________________________________________________________________________
//__________________________________________________________________________________________________________________
 
template <typename T>
class stack : private allocator<T>
{
public:
	stack();/*noexcept*/
	stack(stack const &); /*strong*/
	auto count() const noexcept->size_t;/*noexcept*/
	auto push(T const &)->void;/*strong*/
	auto pop()->void;/*strong*/
	auto top() const->T const&;/*strong*/
	~stack(); 	/*noexcept*/
	auto operator=(const stack&tmp)->stack&;/*strong*/
	auto empty()->bool;/*noexcept*/

};
