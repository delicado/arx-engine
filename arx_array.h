#ifndef ARX_ARRAY_H
#define ARX_ARRAY_H

#include <stdlib.h>
#include <new>
#include <stdexcept>

namespace arx {
	

template <typename T>
class Array {
	T* d;
	int dsize;
	int msize;
protected:
	int AlignedSize( int sz){
		int ret = 1;
		while( ret < sz ){
			ret *= 2;
		}
		return ret;
	}
	
	void BufferCheck( int sz ){
		int szq = sizeof(T) * sz; 
		if( d ){
			if( szq > msize){
				szq = this->AlignedSize( szq );
				T* t = static_cast< T*>( malloc( szq ));
				for( T* i=d, *j=t, *e=d+dsize; i<e; i++,j++){
					new ((void*)j) T(*i);
					i->~T();
				}
				free( d );
				d = t;
				msize = szq;
			}
		} else {
			msize = this->AlignedSize( szq );
			d = static_cast<T*>( malloc( msize ) );
		}
	}
	
	void Construct( T* a, T* b ){
		while( a < b ){
			new ((void*)a) T();
			a++;
		}
	}
	
	void Construct( T* a, T* b, const T& t ){
		while( a < b ){
			new ((void*)a) T(t);
			a++;
		}
	}
	
	void Destruct( T* a, T* b ){
		while( a < b ){
			a->~T();
			a++;
		}
	}
	
	void Move( T* src, T* dst, int size ){
	}
public:

    typedef  T* iterator;
    typedef const T* const_iterator;
    
	Array(){
		d = 0;
		dsize = msize = 0;
	}
	
	~Array(){
		if( d ) {
			this->Destruct( d, d + dsize );
			free( d);
			d = 0;
			dsize = msize = 0;
		}
	}
	
	void push_back( const T& dt ){
		this->BufferCheck( dsize + 1 );
		new ( (void*)(d + dsize) ) T( dt);
		dsize++;
	}
	
	T& back() const {
		return d[ dsize - 1];
	}
	
	T& operator[]( int i ) const {
		return d[ i];
	}
	
	T& at( int i ) const {
		if( i > dsize ) throw std::out_of_range("index out of range.");
		return d[ i];
	}
	bool empty() const {
		return dsize - 1;
	}
	
	void clear(){
		T* i = d, *e = d + dsize;
		while( i < e ) {
			i->~T();
			i++;
		}
		dsize = 0;
	}
	
	int size() const {
		return dsize;
	}
	
	iterator begin() const {
		return d;
	}
	
	iterator end() const {
		return d + dsize;
	}
	
	int capacity() const {
		return msize / sizeof(T);
	}
	
	void resize( const T& a, int size ){
		if( size > dsize ){
			this->BufferCheck( size );
			this->Construct( d + dsize, d + size, a);
			dsize = size;
		} else if( size > 0 && size != dsize ){
			this->Destruct( d + size, d + dsize );
			dsize = size;
		}
	}
};

}

#endif