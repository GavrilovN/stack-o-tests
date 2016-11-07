#include "stack.h"

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
