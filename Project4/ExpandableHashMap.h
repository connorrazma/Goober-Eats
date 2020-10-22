// ExpandableHashMap.h
#include <vector>
#include<list>
// Skeleton for the ExpandableHashMap class template.  You must implement the first six
// member functions.

template<typename KeyType, typename ValueType>
class ExpandableHashMap
{
public:
	ExpandableHashMap(double maximumLoadFactor = 0.5);
	~ExpandableHashMap();
	void reset();
	int size() const;
	void associate(const KeyType& key, const ValueType& value);

	// for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const;

	// for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const ExpandableHashMap*>(this)->find(key));
	}

	// C++11 syntax for preventing copying and assignment
	ExpandableHashMap(const ExpandableHashMap&) = delete;
	ExpandableHashMap& operator=(const ExpandableHashMap&) = delete;

private:
	struct Node
	{
		Node(KeyType key, ValueType value)
		{
			m_key = key;
			m_value = value;
		}

		KeyType m_key;
		ValueType m_value;
	};

	std::vector<std::list<Node>> m_storage;
	
	int m_size;
	double m_load;
	int m_buckets;

	unsigned int getBucketNumber(const KeyType& key) const;
	void reHash();

};

template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::ExpandableHashMap(double maximumLoadFactor )
{
	m_size = 0;
	m_load = maximumLoadFactor;
	m_storage.resize(8);
	m_buckets = 8;
	
}


template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::~ExpandableHashMap()
{
	m_storage.clear();

}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::reset()
{
	m_storage.clear();
	m_storage.resize(8);
	m_size = 0;
	m_buckets = 8;
}

template<typename KeyType, typename ValueType>
int ExpandableHashMap<KeyType, ValueType>::size() const
{
	return m_size; // Delete this line and implement this function correctly
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
	int num = getBucketNumber(key);
	if (m_storage[num].empty() == false)
	{
		typename std::list<Node>::iterator it;
		it = m_storage[num].begin();
		for  ( ;  it != m_storage[num].end(); it++)
		{
			if (it->m_key == key)
			{
				it->m_value = value;
				return;
			}
		}	
	}

	m_storage[num].push_back(Node(key, value));
	m_size++;

	if (1.0*(m_size / (m_buckets *1.0)) > m_load)
		reHash();


	
}

template<typename KeyType, typename ValueType>
const ValueType* ExpandableHashMap<KeyType, ValueType>::find(const KeyType& key) const
{
	int num = getBucketNumber(key);
	if (m_storage[num].empty() == true)
	{
		return nullptr;
	}

	typename std::list<Node>::const_iterator it;
	it = m_storage[num].begin();
	for (; it != m_storage[num].end(); it++)
	{
		if (it->m_key == key)
		{
			return &(it->m_value);
		}


	}
	return nullptr;
	 // Delete this line and implement this function correctly
}

template<typename KeyType, typename ValueType>
unsigned int ExpandableHashMap<KeyType, ValueType>::getBucketNumber(const KeyType& key) const
{
	
	unsigned int hash(const KeyType & k);
	unsigned int h = hash(key);
	return h % m_buckets;

}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::reHash()
{
	m_buckets = m_buckets * 2;
	std::vector<std::list<Node>> temp;
	temp.resize(m_buckets);
	for (int i = 0; i < m_storage.size(); i++)
	{
		
		
			typename std::list<Node>::iterator it;
			it = m_storage[i].begin();
			while ( it != m_storage[i].end())
			{
				int num = getBucketNumber(it->m_key);
				//m_storage[num].push_back(Node(tempValue, tempKey));
				typename std::list<Node>::iterator tempIt = it;
				it++;
				temp[num].splice(temp[num].begin(), m_storage[i], tempIt);
				
			}
		
	}
	temp.swap(m_storage);
}