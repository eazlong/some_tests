#pragma once

template< class T >
class mininum_heap
{
public:
	mininum_heap( unsigned int size )
		:m_heap( new T[size] ), m_used(0), m_size(size)
	{
	}
	~mininum_heap(void)
	{
		delete [] m_heap;
	}
	
	bool push( T data )
	{
		if ( m_size == m_used )
		{
			return false;
		}

		if ( m_used == 0 )
		{
			m_heap[m_used] = data;
			m_used++;
			return true;
		}

		shiftup( data );
		m_used++;
		return true;
	}

	bool pop( T& data )
	{
		if ( m_used == 0 )
			return false;

		data = m_heap[0];
		
		shiftdown();
		m_used--;
		return true;
	}

	T& front()
	{
		return m_heap[0];
	}

protected:
	void shiftup( T& data )
	{
		int pos = m_used;
		int parent = (pos-1)/2;
		while ( pos > 0 )
		{
			if ( m_heap[parent] > data )
			{
				m_heap[pos] = m_heap[parent];
				pos = parent;
				parent = (pos-1)/2;
			}
			else
			{
				break;
			}
		}
		m_heap[pos] = data;
	}

	void shiftdown()
	{
		T data = m_heap[m_used-1];
		int parent = 0;
		while( parent <= (m_used-1)/2 )
		{
			int child = 2*parent+1;
			int right = child+1;
			if ( right < m_used && m_heap[child] > m_heap[right] )
				child = right;

			if ( data > m_heap[child] )
			{
				m_heap[parent] = m_heap[child];
				parent = child;
			}
			else 
			{
				break;
			}
		}
		m_heap[parent] = data;
	}

private:
	T*  m_heap;
	int m_used;
	int m_size;
};
