/*
 * Array.h
 *
 *  Created on: 2017年4月9日
 *      Author: aaaa
 */

#ifndef BASE_ARRAY_H_
#define BASE_ARRAY_H_




#pragma once


#include <stdlib.h>
#include <assert.h>
typedef int INT;
typedef int BOOL;
//动态数组
template< class T > struct Array
{
public:

	Array()
	 :	m_iArrayNum(0)
	 ,	m_iArrayMax(0)
	 ,	m_pData(NULL)
	{}

	Array( INT iNum )
	 :	m_iArrayNum( 0 )
	 ,	m_iArrayMax( iNum )
	 ,	m_pData( NULL )
	{
		_Realloc();
	}

	Array( const Array& other )
	 :	m_iArrayNum( other.m_iArrayNum )
	 ,	m_iArrayMax( other.m_iArrayNum )
	 ,	m_pData( NULL )
	{
		_Realloc();

		if( sizeof(T) != 1 )
		{
			for( INT i = 0; i < m_iArrayNum; ++i )
				(*this)[i] = other[i];
		}
		else
		{
			memcpy( &(*this)[0], &other[0], m_iArrayNum * sizeof(T) );
		}
	}

	~Array()
	{
		if(m_iArrayNum >= 0 && m_iArrayMax >= m_iArrayNum)
		{
		    Remove( 0, m_iArrayNum );
		    if( m_pData )
			    free( m_pData );
		}
	}


	T*	GetData( void ) const{ return m_iArrayNum > 0 ? m_pData : NULL; }
	INT Num( void ) const{ return m_iArrayNum; }
	BOOL IsEmpty( void ) const{ return 0 == m_iArrayNum; }
	BOOL IsNotEmpty( void ) const{ return 0 != m_iArrayNum; }
    T& Item( INT i )
	{
		assert( i >= 0 && i < m_iArrayNum );
		return m_pData[i];
	}
	const T& Item( INT i ) const
	{
		assert( i >= 0 && i < m_iArrayNum );
		return m_pData[i];
	}
	T& Last( INT i = 0 )
	{
		assert( i >= 0 && i < m_iArrayNum );
		return m_pData[m_iArrayNum - i - 1];
	}
	const T& Last( INT i = 0 ) const
	{
		assert( i >= 0 && i < m_iArrayNum );
		return m_pData[m_iArrayNum - i - 1];
	}

	INT FindItem( const T& Item ) const
	{
		for( INT Index = 0; Index < m_iArrayNum; ++Index )
			if( m_pData[Index] == Item ) return Index;
		return -1;
	}

	// Add, Insert, Remove, Empty
	INT Add( INT n = 1 )
	{
		assert( n > 0 );
		INT iIndex = _AddInternal( n );
		return iIndex;
	}
	void Insert( INT iIndex, INT iCount = 1 )
	{
		assert( iIndex >= 0 && iIndex <= m_iArrayNum );
		assert( iCount > 0 );
		_InsertInternal( iIndex, iCount );
	}

	void InsertItem( INT iIndex, const T& Item )
	{
		assert( iIndex >= 0 && iIndex <= m_iArrayNum );
		Insert( iIndex );
		m_pData[iIndex] = Item;
	}
	void Remove( INT iIndex, INT iCount = 1 )
	{
		assert( iIndex >= 0 && iIndex <= m_iArrayNum );
		assert( iCount >= 0 );
		assert( iIndex + iCount <= m_iArrayNum );
		if( iCount )
		{
			memmove(m_pData + iIndex, m_pData + iIndex + iCount, (m_iArrayNum - iIndex - iCount ) * sizeof(T));
			m_iArrayNum -= iCount;
			if(    (3*m_iArrayNum < 2*m_iArrayMax  || (m_iArrayMax - m_iArrayNum) * sizeof(T) >= 16384)
			        && (m_iArrayMax - m_iArrayNum > 64 || m_iArrayNum == 0) )
			{
				m_iArrayMax = m_iArrayNum;
				_Realloc();
			}
		}
	}
	void Empty( INT iNewMax = 0 )
	{
		assert( iNewMax >= 0 );
		m_iArrayNum = 0;
		m_iArrayMax = iNewMax;
		_Realloc();
	}
	void SetSize( INT iNewNum )
	{
		assert( iNewNum >= 0 );
		INT iOldNum = m_iArrayNum;

		if( iNewNum == 0 )
		{
			m_iArrayNum = 0;
		}
		else
		{
			if( m_iArrayMax >= iNewNum )
				m_iArrayNum = iNewNum;
			else
			{
				m_iArrayMax = m_iArrayNum = iNewNum;
				_Realloc();
			}
		}
	}

	//算符
    T& operator[]( INT i )
	{
		assert( i >=0 && i < m_iArrayNum );
		return m_pData[i];
	}
	const T& operator[]( INT i ) const
	{
		assert( i >=0 && i < m_iArrayNum );
		return m_pData[i];
	}


	void operator+=( const Array& other )
	{
		if( this != &other )
		{
			_AddInternal( other.m_iArrayNum );
			for( INT i = 0; i < other.m_iArrayNum; ++i )
			{
				m_pData[m_iArrayNum-other.m_iArrayNum+i] = other[i];
			}
		}
	}
	void operator=( const Array& other )
	{
		if( this != &other )
		{
			Empty( other.m_iArrayMax );
			for( INT i = 0; i < other.m_iArrayNum; ++i )
			{
				m_pData[i] = other[i];
				++ m_iArrayNum;
			}
		}
	}
	INT AddItem( const T& Item )
	{
		INT iIndex = Add();
		m_pData[iIndex] = Item;
		return iIndex;
	}
	INT AddZeroed( INT n = 1 )
	{
		INT iIndex = Add( n  );
		memset( m_pData+iIndex, 0, n*sizeof(T) );
		return iIndex;
	}
	INT AddUniqueItem( const T& Item )
	{
		for( INT iIndex = 0; iIndex < m_iArrayNum; ++iIndex )
			if( m_pData[iIndex] == Item )
				return iIndex;
		return AddItem( Item );
	}
	INT RemoveItem( const T& Item )
	{
		INT OriginalNum = m_iArrayNum;
		for( INT iIndex = 0; iIndex < m_iArrayNum; ++iIndex )
			if( m_pData[iIndex] == Item )
				Remove( iIndex-- );
		return OriginalNum - m_iArrayNum;
	}


protected:

	T *			m_pData;
	INT			m_iArrayNum;
	INT			m_iArrayMax;


	void _Realloc( void )
	{
		if( m_pData && m_iArrayMax > 0 )
			m_pData = (T*)realloc( m_pData, m_iArrayMax*sizeof(T) );
		else if( m_iArrayMax > 0 )
			m_pData = (T*)malloc( m_iArrayMax*sizeof(T) );
		else if( m_pData )
		{
			free( m_pData );
			m_pData = NULL;
		}
	}

	INT _AddInternal( INT n = 1 )
	{
		INT iOldNum = m_iArrayNum;
		if( (m_iArrayNum += n) > m_iArrayMax )
		{
			m_iArrayMax = m_iArrayNum + 3*m_iArrayNum/8 + 32;
			_Realloc();
		}

		return iOldNum;
	}

	void _InsertInternal( INT iIndex, INT iCount = 1 )
	{
		INT iOldNum = m_iArrayNum;
		if( (m_iArrayNum += iCount) > m_iArrayMax )
		{
			m_iArrayMax = m_iArrayNum + 3*m_iArrayNum/8 + 32;
			_Realloc();
		}
		memmove( m_pData + iIndex + iCount, m_pData + iIndex, ( iOldNum - iIndex )*sizeof(T) );
	}
};

#endif /* BASE_ARRAY_H_ */
