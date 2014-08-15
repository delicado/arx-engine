#ifndef ARX_CSTRING_H
#define ARX_CSTRING_H

namespace arx {

template <typename CT>
class CString {
	const CT* _str;
	int _size;
public:
	CString( const CT* s );
	CString( const CT* s, int size );
	int Size() const;
	bool operator== ( const CString& s ) const;
	bool operator!= ( const CString& s ) const;
	bool operator> ( const CString& s ) const;
 	bool operator< ( const CString& s ) const;
 	bool operator>= ( const CString& s ) const;
	bool operator<= ( const CString& s ) const;
	CT operator[] ( int i ) const;
	const CT* Data() const { return _str; }
};
template <typename CT>
CString<CT>::CString( const CT* s ) {
	_str = s;
	_size = 0;
	while( s[ _size ] != 0 ) _size++;
}

template <typename CT>
CString<CT>::CString( const CT* s, int sz ){
	_str = s;
	_size = sz;
}

template <typename CT>
int CString<CT>::Size() const {
	return _size;
}

 template <typename CT> 
CT CString<CT>::operator[] ( int i ) const {
	return _str[ i ];
} 

template <typename CT>
bool CString<CT>::operator== ( const CString& s ) const {
	int ret = 0;
	if( s.Size() == this->Size()){
		while( ret < this->Size() && s[ ret ] == (*this)[ ret ]){
			ret++;
		}
	}
	return ret == this->Size();
} 

template <typename CT> 
bool CString<CT>::operator!= ( const CString& s ) const {
	return !((*this)==s);
}

template <typename CT> 
bool CString<CT>::operator< ( const CString& s ) const {
	int i= 0, sz = this->Size() > s.Size() ? s.Size() : this->Size();
	bool neq = false;
	while( i < sz && (*this)[i] <= s[i]) {
		if( (*this)[i] < s[i] ) neq = 1;
		i++;
	}
	if( i == sz ){
		if( !neq ){
			if( this->Size() < s.Size())
				neq= 1;
		}else neq= 1;
	} else neq= 0;
	return neq;
} 

template <typename CT> 
bool CString<CT>::operator> ( const CString& s ) const {
	int i= 0, sz = this->Size() > s.Size() ? s.Size() : this->Size();
	bool neq = false;
	while( i < sz && (*this)[i] >= s[i]) {
		if( (*this)[i] > s[i] ) neq = 1;
		i++;
	}
	if( i == sz ){
		if( !neq ){
			if( this->Size() > s.Size())
				neq= 1;
		}else neq= 1;
	} else neq= 0;
	return neq;
}
 
template <typename CT> 
bool CString<CT>::operator>= ( const CString& s ) const {
	int i= 0, sz = this->Size() > s.Size() ? s.Size() : this->Size();
	bool neq = false;
	while( i < sz && (*this)[i] >= s[i]) {
		if( (*this)[i] > s[i] ) neq = 1;
		i++;
	}
	if( i == sz ){
		if( !neq ){
			if( this->Size() >= s.Size())
				neq= 1;
		}else neq= 1;
	} else neq= 0;
	return neq;
} 

 template <typename CT> 
bool CString<CT>::operator<= ( const CString& s ) const {
	int i= 0, sz = this->Size() > s.Size() ? s.Size() : this->Size();
	bool neq = false;
	while( i < sz && (*this)[i] <= s[i]) {
		if( (*this)[i] < s[i] ) neq = 1;
		i++;
	}
	if( i == sz ){
		if( !neq ){
			if( this->Size() <= s.Size())
				neq= 1;
		}else neq= 1;
	} else neq= 0;
	return neq;
} 

}

#endif