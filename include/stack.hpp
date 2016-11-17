#include <iostream>
#include <stdexcept>


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
	stack(size_t size = 0);/*noexcept*/
	stack(stack const &); /*strong*/
	auto count() const noexcept->size_t;/*noexcept*/
	auto push(T const &)->void;/*strong*/
	auto pop()->void;/*strong*/
	auto top() const->T const&;/*strong*/
	~stack(); 	/*noexcept*/
	auto operator=(const stack&tmp)->stack&;/*strong*/
	auto empty()->bool;/*noexcept*/

};
template<typename T> 
auto stack<T>::empty() const noexcept->bool {
	return (allocator<T>::count_ == 0);
}

template <typename T>
stack<T>::~stack() {
destroy(allocator<T>::array_, allocator<T>::array_ + allocator<T>::count_);};

template <typename T>
stack<T>::stack(size_t size): allocator<T>(size) {};

template <typename T>
auto stack<T>::push(T const &val)->void {
	if (allocator<T>::count_ == allocator<T>::size_) {
		size_t array_size = allocator<T>::size_ * 2 + (allocator<T>::size_ == 0);
		stack<T> temp(array_size);
		while (temp.count() < allocator<T>::count_) temp.push(allocator<T>::array_[temp.count()]); 
		this->swap(temp);
	}
	construct(allocator<T>::array_+allocator<T>::count_,val);
	++allocator<T>::count_;
}


template <typename T>
stack<T>::stack(stack const &tmp): allocator<T>(tmp.size_){
	
	for (size_t i = 0; i < tmp.count_; i++) construct(allocator<T>::array_ + i, tmp.array_[i]);
	allocator<T>::count_ = tmp.count_;
	
};

template <typename T>
auto stack<T>::operator=(const stack &tmp)->stack& {
	if (this != &tmp) {
		(stack(tmp)).swap(*this);
	}
	return *this;
}


template <typename T>
auto stack<T>::count() const noexcept->size_t {
	return allocator<T>::count_;
}

template <typename T>
auto stack<T>::pop()->void {
	if (allocator<T>::count_ == 0) throw std::logic_error("Empty!");
	destroy(allocator<T>::array_+allocator<T>::count_);
	--allocator<T>::count_;
}

template <typename T>
auto stack<T>::top() const->T const& {
	if (allocator<T>::count_ == 0) throw std::logic_error("Empty!");
	return allocator<T>::array_[allocator<T>::count_-1];

}

template <typename T>
auto stack<T>::top()->T& {
	if (allocator<T>::count_ == 0) throw std::logic_error("Empty!");
	return allocator<T>::array_[allocator<T>::count_-1];

}

