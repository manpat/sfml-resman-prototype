#include "resourceptr.h"
#include "baseresource.h"

resource_ptr::resource_ptr(){
	raw = nullptr;
	dat = nullptr;
}
resource_ptr::resource_ptr(BaseResource* _raw){ // new
	raw = _raw;
	dat = new PtrData;
	dat->count = 1;
}
resource_ptr::resource_ptr(const resource_ptr& o){ // copy
	raw = o.raw;
	dat = o.dat;
	_inc();
}
resource_ptr::resource_ptr(resource_ptr&& o){ // move
	raw = o.raw;
	dat = o.dat;
	o.raw = nullptr;	
	o.dat = nullptr;	
}
resource_ptr::~resource_ptr(){
	_dec();
	raw = nullptr;
	dat = nullptr;
}

void resource_ptr::_inc(){
	if(dat) dat->count++;
}
void resource_ptr::_dec(){
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

resource_ptr& resource_ptr::operator= (BaseResource* o){
	_dec();
	raw = o;
	dat = new PtrData;
	dat->count = 1;
}
resource_ptr& resource_ptr::operator= (resource_ptr& o){
	_dec();
	raw = o.raw;
	dat = o.dat;
	_inc();
}
resource_ptr& resource_ptr::operator= (resource_ptr&& o){
	raw = o.raw;
	dat = o.dat;
	o.raw = nullptr;	
	o.dat = nullptr;
}
BaseResource& resource_ptr::operator*(){
	return *raw;
}
BaseResource* resource_ptr::operator->(){
	return raw;
}

BaseResource* resource_ptr::getRaw(){
	return raw;
}
size_t resource_ptr::getRefCount(){
	if(dat) return dat->count;
	return 0;
}