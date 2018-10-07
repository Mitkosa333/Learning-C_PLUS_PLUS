#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

template<typename T>
class MyVector
{
	//Big 4
public:
	MyVector()
	{
		objects = nullptr;
		max_size = 0;
		cur_objects = 0;
	}

	MyVector(unsigned index)
	{
		while (!((index)&(index - 1)) != 0)
		{
			index++;
		}
		objects = new T[index];
		max_size = index;
		cur_objects = 0;
	}

	MyVector(const MyVector& obj)
	{
		objects = new T[obj.max_size];
		cur_objects = obj.cur_objects;
		max_size = obj.max_size;
		for (unsigned i = 0; i < cur_objects; i++)
		{
			objects[i] = obj.objects[i];
		}
	}

	MyVector& operator= (const MyVector& obj)
	{
		if (this != &obj)
		{
			T* buffer;
			buffer = new T[obj.max_size];
			for (unsigned i = 0; i < obj.cur_objects; i++)
			{
				buffer[i] = obj.objects[i];
			}
			delete[] objects;
			objects = buffer;
			cur_objects = obj.cur_objects;
			max_size = obj.max_size;
		}
		return *this;
	}

	~MyVector()
	{
		delete[] objects;
	}
	
	//Element access
public:
	T & operator[](const unsigned index)
	{
		return objects[index];
	}

	T& operator[] (const unsigned index) const
	{
		return objects[index];
	}

	T & back()
	{
		return objects[cur_objects - 1];
	}

	T & front()
	{
		return objects[0];
	}

	//Capacity
public:
	unsigned get_cur_objects() const
	{
		return cur_objects;
	}

	unsigned get_max_size() const
	{
		return max_size;
	}

	bool is_empty() const
	{
		return (max_size == 0);
	}

	//Modifiers
public:
	void push_back(const T& element)
	{
		expand();
		objects[cur_objects] = element;
		cur_objects++;
	}

	void pop_back()
	{
		cur_objects--;
	}

	void remove_member(const unsigned& index)
	{
		if (index < cur_objects)
		{
			for (unsigned i = index; i < cur_objects - 1; i++)
			{
				objects[i] = objects[i + 1];
			}
			cur_objects--;
		}
	}

	void add_memeber(const unsigned& index,const T& element)
	{
		cur_objects++;
		if (index < cur_objects)
		{
			expand();
			for (int i = cur_objects; i > index; --i)
			{
				objects[i] = objects[i - 1];
			}
			objects[index] = element;
		}
	}


	void swap_members(const unsigned& first, const unsigned& second)
	{
		if (first < cur_objects && second < cur_objects)
		{
			T temp = objects[first];
			objects[first] = objects[second];
			objects[second] = temp;
		}
	}

	void expand()
	{
		if (cur_objects >= max_size)
		{
			if (max_size == 0)
			{
				max_size++;
				objects = new T[max_size];
			}
			else
			{
				T* buffer = new T[max_size * 2];
				for (unsigned i = 0; i < cur_objects; i++)
				{
					buffer[i] = objects[i];
				}
				delete[] objects;
				objects = buffer;

				max_size *= 2;
			}
		}
	}

	void clear()
	{
		MyVector temp;
		*this = temp;
	}

private:
	T * objects;
	unsigned cur_objects;
	unsigned max_size;
};

template<typename T>
void swap(T& first, T& second)
{
	T temp = first;
	first = second;
	second = temp;
}

#endif //VECTOR_HPP
