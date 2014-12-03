
template<class T>
resource_ptr<T>::resource_ptr(){
	raw = nullptr;
	dat = nullptr;
}

template<class T>
resource_ptr<T>::resource_ptr(T* _raw){ // new
	raw = _raw;
	dat = new PtrData;
	dat->count = 1;
}

template<class T>
resource_ptr<T>::resource_ptr(const resource_ptr& o){ // copy
	raw = o.raw;
	dat = o.dat;
	_inc();
}

template<class T>
resource_ptr<T>::resource_ptr(resource_ptr&& o){ // move
	raw = o.raw;
	dat = o.dat;
	o.raw = nullptr;	
	o.dat = nullptr;	
}

template<class T>
resource_ptr<T>::~resource_ptr(){
	_dec();
	raw = nullptr;
	dat = nullptr;
}


template<class T>
void resource_ptr<T>::_inc(){
	if(dat) dat->count++;
}

template<class T>
void resource_ptr<T>::_dec(){
	if(dat){
		dat->count--;
		if(dat->count == 0){
			delete raw;
			delete dat;

			raw = nullptr;
			dat = nullptr;
		}
	}
}


template<class T>
auto resource_ptr<T>::operator= (T* o) -> rp_t&{
	_dec();
	raw = o;
	dat = new PtrData;
	dat->count = 1;
}

template<class T>
auto resource_ptr<T>::operator= (rp_t& o) -> rp_t&{
	_dec();
	raw = o.raw;
	dat = o.dat;
	_inc();
}

template<class T>
auto resource_ptr<T>::operator= (rp_t&& o) -> rp_t&{
	raw = o.raw;
	dat = o.dat;
	o.raw = nullptr;	
	o.dat = nullptr;
}

template<class T>
T& resource_ptr<T>::operator*(){
	return *raw;
}

template<class T>
T* resource_ptr<T>::operator->(){
	return raw;
}

template<class T>
template<class D>
resource_ptr<D> resource_ptr<T>::cast(){
	resource_ptr<D> r;
	r.raw = static_cast<D*>(raw);
	r.dat = dat;
	_inc();
	return r;
}

template<class T>
resource_ptr<T>::operator bool(){
	return !!raw;
}

template<class T>
T* resource_ptr<T>::getRaw(){
	return raw;
}

template<class T>
size_t resource_ptr<T>::getRefCount(){
	if(dat) return dat->count;
	return 0;
}