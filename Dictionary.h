#ifndef PFZCOLLECTIONSDICTIONARYH
#define PFZCOLLECTIONSDICTIONARYH


#include "ObjectPool.h"

#include <assert.h>

template<typename T>
class IEnumerator
{
public:
	virtual ~IEnumerator(){}
	virtual const T *GetNext() = 0;
};

template<typename T>
class ICountAwareEnumerator:
	public IEnumerator<T>
{
public:
	virtual size_t GetCount() const = 0;
};

template<typename TKey, typename TValue>
class Pair
{
public:
	TKey key;
	TValue value;
	
	Pair(const TKey &key, const TValue &value):
		key(key),
		value(value)
	{
	}

	const TKey &GetKey() const
	{
		return key;
	}
	const TValue &GetValue() const
	{
		return value;
	}
};

template<typename TKey, typename TValue, class TMemoryAllocator=DefaultMemoryAllocator>
class Dictionary
{
public:
	struct Node
	{
		Node *nextNode;
		size_t hashCode;
		Pair<TKey, TValue> pair;

		Node(Node *nextNode, size_t hashCode, const TKey &key, const TValue &value):
			nextNode(nextNode),
			hashCode(hashCode),
			pair(key, value)
		{
		}
	};

#define GetEmptyPointer() (Node *)(((char *)0)-1)
#define IsEmpty(n) (n->nextNode==(Node *)(((char *)0)-1))

	// We try to use only prime numbers as the capacities (number of buckets).
	// Yet, for performance reasons, we don't really look for a real prime, only
	// a number that's not divisible from the primes up to 31.
	static size_t AdaptSize(size_t size)
	{
		if (size <= 31)
			return 31;

		if (size % 2 == 0)
			size --;
		else
			size -= 2;

		while(true)
		{
			size += 2;

			if (size % 3 == 0) continue;
			if (size % 5 == 0) continue;
			if (size % 7 == 0) continue;
			if (size % 11 == 0) continue;
			if (size % 13 == 0) continue;
			if (size % 17 == 0) continue;
			if (size % 19 == 0) continue;
			if (size % 23 == 0) continue;
			if (size % 29 == 0) continue;
			if (size % 31 == 0) continue;

			return size;
		}
	}

	Node *buckets;
	size_t count;
	size_t capacity;
	ObjectPool<Node, TMemoryAllocator> *pool;

	ObjectPool<Node, TMemoryAllocator> *GetPool()
	{
		if (pool == NULL)
			pool = new ObjectPool<Node, TMemoryAllocator>();

		return pool;
	}
	void Resize()
	{
		size_t newCapacity = AdaptSize(capacity * 2);
		if (newCapacity < capacity)
			throw ("The new required capacity is not supported in this environment.");

		ResizeAlreadyAdaptedSize(newCapacity);
	}

	void ResizeAlreadyAdaptedSize(size_t newCapacity)
	{
		ObjectPool<Node, TMemoryAllocator> *newPool = NULL;
		Node *newBuckets = (Node *)TMemoryAllocator::Allocate(newCapacity * sizeof(Node));
		if (newBuckets == NULL)
			throw std::bad_alloc();

		for(size_t i=0; i<newCapacity; i++)
			newBuckets[i].nextNode = GetEmptyPointer();

		if (count > 0)
		{
			try
			{
				size_t newCount = 0;

				for(size_t i=0; i<capacity; i++)
				{
					Node *oldNode = &buckets[i];
					if (IsEmpty(oldNode))
						continue;

					do
					{
						size_t hashCode = oldNode->hashCode;
						size_t newBucketIndex = hashCode % newCapacity;
						Node *newFirstNode = &newBuckets[newBucketIndex];

						if (IsEmpty(newFirstNode))
						{
							new (newFirstNode) Node(NULL, hashCode, oldNode->pair.GetKey(), oldNode->pair.GetValue());
						}
						else
						{
							if (newPool == NULL)
								newPool = new ObjectPool<Node, TMemoryAllocator>();

							Node *newNode = newPool->GetNextWithoutInitializing();
							new (newNode) Node(newFirstNode->nextNode, hashCode, oldNode->pair.GetKey(), oldNode->pair.GetValue());
							newFirstNode->nextNode = newNode;
						}

						oldNode = oldNode->nextNode;

						newCount++;

#ifndef DEBUG
						if (newCount == count)
							goto exitWhileAndFor;
#endif

					} while (oldNode);
				}

				assert(newCount == count);

#ifndef DEBUG
				exitWhileAndFor:
				{
					// block needed to avoid compilation errors.
				}
#endif
			}
			catch(...)
			{
				// if there's an exception we clean up
				// our new allocated objects, without touching
				// the previous ones. As long as the possible
				// assignment operators don't touch the
				// old values, the dictionary should not get
				// corrupted and no leaks should happen.
				// If the copy constructors did move content from one
				// place to another, then the dictionary will be corrupted,
				// without memory leaks. So, the caller will be responsible
				// for dealing with the corrupted data or killing the dictionary.
				for(size_t i=0; i<newCapacity; i++)
				{
					Node *node = &newBuckets[i];

					if (!IsEmpty(node))
					{
						do
						{
							node->~Node();
							node = node->nextNode;
						} while(node);
					}
				}

				delete newPool;

				throw;
			}
		}

		Node *oldBuckets = buckets;
		ObjectPool<Node, TMemoryAllocator> *oldPool = pool;
		size_t oldCapacity = capacity;

		capacity = newCapacity;
		buckets = newBuckets;
		pool = newPool;

		// destroy all inner nodes and then the oldbuckets and pool.
		for(size_t i=0; i<oldCapacity; i++)
		{
			Node *node = &oldBuckets[i];

			if (!IsEmpty(node))
			{
				do
				{
					node->~Node();
					node = node->nextNode;
				} while(node);
			}
		}

		TMemoryAllocator::Deallocate(oldBuckets, oldCapacity * sizeof(Node));
		delete oldPool;
	}

	Dictionary(const Dictionary<TKey, TValue, TMemoryAllocator> &source);
	void operator = (const Dictionary<TKey, TValue, TMemoryAllocator> &source);

public:
	explicit Dictionary(size_t capacity=31):
		buckets(NULL),
		count(0),
		capacity(AdaptSize(capacity)),
		pool(NULL)
	{
		buckets = (Node *)TMemoryAllocator::Allocate(capacity * sizeof(Node));
		if (buckets == NULL)
			throw std::bad_alloc();

		for(size_t i=0; i<capacity; i++)
			buckets[i].nextNode = GetEmptyPointer();
	}
	~Dictionary()
	{
		if (count == 0)
		{
			TMemoryAllocator::Deallocate(buckets, capacity * sizeof(Node));
			delete pool;
			return;
		}

		int clearCount = 0;
		for(size_t i=0; i<capacity; i++)
		{
			Node *node = &buckets[i];

			if (!IsEmpty(node))
			{
				do
				{
					node->~Node();
					node = node->nextNode;

					clearCount ++;

					if (clearCount == count)
					{
						assert(node == NULL);
						goto deallocate;
					}
				} while(node);
			}
		}

		assert(clearCount == count);
		
		deallocate:
		TMemoryAllocator::Deallocate(buckets, capacity * sizeof(Node));
		delete pool;
	}
/*
	// Gets the number of associations done by this dictionary.
	size_t GetCount() const
	{
		return count;
	}

	// Gets the number of association slots already allocated, independently
	// on how many associations are currently in use.
	size_t GetCapacity() const
	{
		return capacity;
	}
*/
	// Tries to set the capacity (number of "association slots") allocated to the given
	// value. If such value is less than Count an exception is thrown. This function returns
	// false if the capacity is the same as the actual one (or if it becomes the same by the
	// prime search logic). It returns true if the capacity was correctly changed. Note
	// that the final capacity may be bigger than the one you asked for.
	bool SetCapacity(size_t newCapacity)
	{
		if (newCapacity < count)
			throw ("newCapacity must at least equals count.");

		size_t originalParameter = newCapacity;
		newCapacity = AdaptSize(newCapacity);
		if (newCapacity < originalParameter)
			throw ("The new capacity is not supported in this environment.");

		if (newCapacity == capacity)
			return false;

		ResizeAlreadyAdaptedSize(newCapacity);
		return true;
	}

	// Tries to reduce the capacity to the same size as the number of items in
	// this dictionary.
	bool TrimExcess()
	{
		return SetCapacity(count);
	}

	// Returns a value indicating if the given key exists in this dictionary.
	bool ContainsKey(const TKey &key) const
	{
		return TryGetValue(key) != NULL;
	}

	// Tries to get the value for a given key.
	// Teh return is either the address of the Value or NULL.
	TValue *TryGetValue(const TKey &key) const
	{
		size_t hashCode = (size_t)key;
		size_t bucketIndex = hashCode % capacity;
		Node *firstNode = &buckets[bucketIndex];

		if (IsEmpty(firstNode))
			return NULL;

		Node *node = firstNode;
		do
		{
			if (hashCode == node->hashCode)
				if (key == node->pair.GetKey())
					return const_cast<TValue *>(&node->pair.GetValue());

			node = node->nextNode;
		} while (node);

		return NULL;
	}

	// Gets the value for a given key.
	// Throws an exception if there's no value for such a key.
	TValue &GetValue(const TKey &key) const
	{
		TValue *result = TryGetValue(key);

		if (result == NULL)
			throw ("There's no value for the given key.");

		return *result;
	}

	TValue & operator[](const TKey &key)
	{
		return GetOrCreateDefaultValue(key);
	}

	// Gets the value associated with the given key.
	// If there's no value associated with the given key, the default TValue()
	// is returned.
	TValue GetValueOrDefault(const TKey &key) const
	{
		TValue *result = TryGetValue(key);

		if (result == NULL)
			return TValue();

		return *result;
	}

	// Gets the value associated with the given key.
	// If there's no value associated with the given key, the provided
	// defaultValue is returned.
	TValue GetValueOrDefault(const TKey &key, const TValue &defaultValue) const
	{
		TValue *result = TryGetValue(key);

		if (result == NULL)
			return defaultValue;

		return *result;
	}

	// Adds a key/value pair to this dictionary.
	void Add(const TKey &key, const TValue &value)
	{
		TryAdd(key, value);
		//if (!TryAdd(key, value))
		//	throw ("There's already a value for the given key.");
	}

	// Tries to add a key/value pair to this dictionary.
	// If the pair is added, the return is true.
	// If there's an already existing association, nothing is changed
	// and the function returns false.
	bool TryAdd(const TKey &key, const TValue &value)
	{
		size_t hashCode = (size_t)key;
		size_t bucketIndex = hashCode % capacity;
		Node *firstNode = &buckets[bucketIndex];

		if (IsEmpty(firstNode))
		{
			new (firstNode) Node(NULL, hashCode, key, value);
			count++;
			return true;
		}

		Node *node = firstNode;
		do
		{
			if (hashCode == node->hashCode)
				if (key == node->pair.GetKey())
					return false;

			node = node->nextNode;
		} while (node);

		if (count >= capacity)
		{
			Resize();
			bucketIndex = hashCode % capacity;
			firstNode = &buckets[bucketIndex];

			if (IsEmpty(firstNode))
			{
				new (firstNode) Node(NULL, hashCode, key, value);
				count++;
				return true;
			}
		}

		node = GetPool()->GetNextWithoutInitializing();
		new (node) Node(firstNode->nextNode, hashCode, key, value);
		firstNode->nextNode = node;
		count++;
		return true;
	}

	// Sets a value for the given key, replacing a previous association
	// or adding a new one if necessary.
	void Set(const TKey &key, const TValue &value)
	{
		size_t hashCode = (size_t)key;
		size_t bucketIndex = hashCode % capacity;
		Node *firstNode = &buckets[bucketIndex];

		if (IsEmpty(firstNode))
		{
			new (firstNode) Node(NULL, hashCode, key, value);
			count++;
			return;
		}

		Node *node = firstNode;
		do
		{
			if (hashCode == node->hashCode)
			{
				if (key == node->pair.GetKey())
				{
					const_cast<TValue &>(node->pair.GetValue()) = value;
					return;
				}
			}

			node = node->nextNode;
		} while (node);

		if (count >= capacity)
		{
			Resize();
			bucketIndex = hashCode % capacity;
			firstNode = &buckets[bucketIndex];

			if (IsEmpty(firstNode))
			{
				new (firstNode) Node(NULL, hashCode, key, value);
				count++;
				return;
			}
		}

		node = GetPool()->GetNextWithoutInitializing();
		new (node) Node(firstNode->nextNode, hashCode, key, value);
		firstNode->nextNode = node;
		count++;
	}

	
	TValue &GetOrCreateDefaultValue(const TKey &key)
	{
		size_t hashCode = (size_t)key;
		size_t bucketIndex = hashCode % capacity;
		Node *firstNode = &buckets[bucketIndex];
		
		if (IsEmpty(firstNode))
		{
			TValue value;
			new (firstNode) Node(NULL, hashCode, key, value);
			count++;
			return const_cast<TValue &>(firstNode->pair.GetValue());
		}

		Node *node = firstNode;
		do
		{
			if (hashCode == node->hashCode)
				if (key == node->pair.GetKey())
					return const_cast<TValue &>(node->pair.GetValue());

			node = node->nextNode;
		} while (node);

		if (count >= capacity)
		{
			Resize();
			bucketIndex = hashCode % capacity;
			firstNode = &buckets[bucketIndex];

			if (IsEmpty(firstNode))
			{
				TValue value;
				new (firstNode) Node(NULL, hashCode, key, value);
				count++;
				return const_cast<TValue &>(firstNode->pair.GetValue());
			}
		}

		node = GetPool()->GetNextWithoutInitializing();
		TValue value;
		new (node) Node(firstNode->nextNode, hashCode, key, value);
		firstNode->nextNode = node;
		count++;
		return const_cast<TValue &>(node->pair.GetValue());
	}

	// Gets the value for a given key or creates one using the given
	// value creator.
/*	
	template<class TValueCreator>
	TValue &GetOrCreateValue(const TKey &key, const TValueCreator &valueCreator)
	{
		size_t hashCode = (size_t)key;
		size_t bucketIndex = hashCode % capacity;
		Node *firstNode = &buckets[bucketIndex];

		if (IsEmpty(firstNode))
		{
			new (firstNode) Node(NULL, hashCode, key, valueCreator(key));
			count++;
			return const_cast<TValue &>(firstNode->pair.GetValue());
		}

		Node *node = firstNode;
		do
		{
			if (hashCode == node->hashCode)
				if (key == node->pair.GetKey())
					return const_cast<TValue &>(node->pair.GetValue());

			node = node->nextNode;
		} while (node);

		if (count >= capacity)
		{
			Resize();
			bucketIndex = hashCode % capacity;
			firstNode = &buckets[bucketIndex];

			if (IsEmpty(firstNode))
			{
				new (firstNode) Node(NULL, hashCode, key, valueCreator(key));
				count++;
				return const_cast<TValue &>(firstNode->pair.GetValue());
			}
		}

		node = GetPool()->GetNextWithoutInitializing();
		new (node) Node(firstNode->nextNode, hashCode, key, valueCreator(key));
		firstNode->nextNode = node;
		count++;
		return const_cast<TValue &>(node->pair.GetValue());
	}

	// Gets the value for a given key or creates one using the given
	// value creator.
	template<typename TContextData>
	TValue &GetOrCreateValue(const TKey &key, TValue (*valueCreator)(const TKey &key, TContextData *contextData), TContextData *contextData)
	{
		size_t hashCode = (size_t)key;
		size_t bucketIndex = hashCode % capacity;
		Node *firstNode = &buckets[bucketIndex];

		if (IsEmpty(firstNode))
		{
			new (firstNode) Node(NULL, hashCode, key, valueCreator(key, contextData));
			count++;
			return const_cast<TValue &>(firstNode->pair.GetValue());
		}

		Node *node = firstNode;
		do
		{
			if (hashCode == node->hashCode)
				if (key == node->pair.GetKey())
					return const_cast<TValue &>(node->pair.GetValue());

			node = node->nextNode;
		} while (node);

		if (count >= capacity)
		{
			Resize();
			bucketIndex = hashCode % capacity;
			firstNode = &buckets[bucketIndex];

			if (IsEmpty(firstNode))
			{
				new (firstNode) Node(NULL, hashCode, key, valueCreator(key, contextData));
				count++;
				return const_cast<TValue &>(firstNode->pair.GetValue());
			}
		}

		node = GetPool()->GetNextWithoutInitializing();
		new (node) Node(firstNode->nextNode, hashCode, key, valueCreator(key, contextData));
		firstNode->nextNode = node;
		count++;
		return const_cast<TValue &>(node->pair.GetValue());
	}
*/
	// Removes all items in this dictionary.
	// Note that the Capacity is not reset by this action, so if you really want
	// to reduce the memory utilisation, do a TrimExcess or SetCapacity after this call.
	void Clear()
	{
		if (count == 0)
			return;

		int clearCount = 0;
		for(size_t i=0; i<capacity; i++)
		{
			Node *node = &buckets[i];

			if (!IsEmpty(node))
			{
				bool isFirst = true;
				do
				{
					Node *nextNode = node->nextNode;
					node->~Node();

					if (isFirst)
					{
						node->nextNode = GetEmptyPointer();
						isFirst = false;
					}
					else
					{
						assert(pool);
						pool->DeleteWithoutDestroying(node);
					}

					clearCount ++;

					if (clearCount == count)
					{
						assert(nextNode == NULL);

						count = 0;
						return;
					}

					node = nextNode;
				} while(node);
			}
		}

		assert(clearCount == count);
		count = 0;
	}

	// Removes an association of a key/value pair. The search is done by the key only
	// and the return is true if such key was found (and removed) or false if it was
	// not found (so, nothing changed in the dictionary).
	bool Remove(const TKey &key)
	{
		size_t hashCode = (size_t)key;
		size_t bucketIndex = hashCode % capacity;
		Node *firstNode = &buckets[bucketIndex];

		if (IsEmpty(firstNode))
			return false;

		Node *previousNode = NULL;
		Node *node = firstNode;
		do
		{
			if (hashCode == node->hashCode)
			{
				if (key == node->pair.GetKey())
				{
					if (node == firstNode)
					{
						assert(previousNode == NULL);
						Node *nextNode = node->nextNode;
						node->~Node();

						if (nextNode == NULL)
							node->nextNode = GetEmptyPointer();
						else
						{
							assert(pool);
							new (node) Node(nextNode->nextNode, nextNode->hashCode, nextNode->pair.GetKey(), nextNode->pair.GetValue());
							pool->Delete(nextNode);
						}
					}
					else
					{
						assert(previousNode != NULL);
						assert(pool);

						previousNode->nextNode = node->nextNode;
						pool->Delete(node);
					}

					count--;
					return true;
				}
			}

			previousNode = node;
			node = node->nextNode;
		} while (node);

		return false;
	}

	class DictionaryEnumerator:
		public ICountAwareEnumerator<Pair<TKey, TValue> >
	{
		Dictionary<TKey, TValue, TMemoryAllocator> *dictionary;
		size_t bucketIndex;
		Node *node;

	public:
		DictionaryEnumerator(Dictionary<TKey, TValue, TMemoryAllocator> *dictionary):
			dictionary(dictionary),
			bucketIndex(0),
			node(NULL)
		{
			assert(dictionary);
		}

		inline size_t GetCount() const
		{
			return dictionary->count;
		}

		const Pair<TKey, TValue> *GetCurrent()
		{
			if (node)
				return &node->pair;
			return NULL;
		}

		const Pair<TKey, TValue> *GetNext()
		{
			if (node)
			{
				node = node->nextNode;

				if (node)
					return &node->pair;

				bucketIndex++;
			}

			while(true)
			{
				if (bucketIndex >= dictionary->capacity)
				{
					node = NULL;
					return NULL;
				}

				node = &dictionary->buckets[bucketIndex];
				if (!IsEmpty(node))
					return &node->pair;

				bucketIndex++;
			}
		}
	};

	// Creates an object that's capable of enumerating all key/value pairs
	// that exist in this dictionary. It's up to you to delete the created
	// object.
	DictionaryEnumerator CreateEnumerator()
	{
		return DictionaryEnumerator(this);
	}

	class KeysEnumerator:
		public ICountAwareEnumerator<TKey>
	{
	private:
		DictionaryEnumerator enumerator;

	public:
		KeysEnumerator(Dictionary<TKey, TValue, /*TEqualityComparer,*/ TMemoryAllocator> *dictionary):
			enumerator(dictionary)
		{
		}

		size_t GetCount() const
		{
			return enumerator.GetCount();
		}

		const TKey *GetNext()
		{
			const Pair<TKey, TValue> *pair = enumerator.GetNext();
			if (pair)
				return pair.key;

			return 0;
		}
	};

	// Creates an object that's capable of enumerating all keys
	// that exist in this dictionary. It's up to you to delete the created
	// object.
	KeysEnumerator CreateKeysEnumerator()
	{
		return KeysEnumerator(this);
	}

	class ValuesEnumerator:
		public ICountAwareEnumerator<TValue>
	{
	private:
		DictionaryEnumerator enumerator;

	public:
		ValuesEnumerator(Dictionary<TKey, TValue, /*TEqualityComparer,*/ TMemoryAllocator> *dictionary):
			enumerator(dictionary)
		{
		}

		size_t GetCount() const 
		{
			return enumerator.GetCount();
		}

		const TValue *GetNext()
		{
			const Pair<TKey, TValue> *pair = enumerator.GetNext();
			if (pair)
				return pair.value;

			return 0;
		}
	};

	// Creates an object that's capable of enumerating all values
	// that exist in this dictionary. It's up to you to delete the created
	// object.
	ValuesEnumerator CreateValuesEnumerator()
	{
		return ValuesEnumerator(this);
	}
};

#endif
