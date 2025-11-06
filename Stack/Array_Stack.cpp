#include<iostream>
#include<stdexcept>

template<typename T>
class ArrayStack
{
    private:
    T* data;
    size_t currSize;
    size_t capacity;

    //функции

    void copyFrom(const ArrayStack<T>& other);
    void moveFrom(ArrayStack<T>&& other);
    void free();
    void resize(size_t newCap);

     public:

     //конструи и деструктори
     ArrayStack();
     ArrayStack(const ArrayStack<T>& other);
     ArrayStack(ArrayStack<T>&& other) noexcept;
     ArrayStack<T>& operator=(const ArrayStack<T>& other);
     ArrayStack<T>& operator=(ArrayStack<T>&& other) noexcept;
     ~ArrayStack();

     //основни функции

     void pop();
     void push(const T& newE);
     const T& peek() const;

     //Помощни функции
     void clear();
     bool isEmpty() const;
     size_t size() const;
     size_t getCapacity() const {return capacity; }

     void print() const;
};

template<typename T>
ArrayStack<T>::ArrayStack() : currSize(0), capacity(4)
{
    data = new T[capacity];
}

template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& other)
{
   copyFrom(other);
}

template<typename T>
ArrayStack<T>::ArrayStack(ArrayStack<T>&& other) noexcept
{
    moveFrom(std::move(other));
}


template<typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& other)
{
  if(this != &other)
  {
    free();
    copyFrom(other);
  }

 return *this;
}

template<typename T>
ArrayStack<T>& ArrayStack<T>::operator=(ArrayStack<T>&& other) noexcept
{
    if(this!= &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

template<typename T>
ArrayStack<T>::~ArrayStack()
{
    free();
}

template<typename T>
void ArrayStack<T>::copyFrom(const ArrayStack<T>& other)
{
    data = new T[other.capacity];
    for (size_t i = 0; i < other.currSize; i++)
    {
        data[i] = other.data[i];
    }

    currSize=other.currSize;
    capacity= other.capacity;
    
}

template<typename T>
void ArrayStack<T>::moveFrom(ArrayStack<T>&& other)
{
    data=other.data;
    capacity=other.capacity;
    currSize=other.currSize;

    other.data = nullptr;
    other.capacity = 0;
    other.currSize = 0; 

}

template <typename T>
void ArrayStack<T>::resize(size_t newCap)
{
   T* temp = data;
   data = new T[newCap];

   for (size_t i = 0; i < currSize; i++)
   {
     data[i] = temp[i];
   }

   capacity = newCap;
   delete[] temp;
   
}

template<typename T>
void ArrayStack<T>::free()
{
    delete[] data;
    data = nullptr;
    currSize = 0;
    capacity = 0;
}


template<typename T>
void ArrayStack<T>::push(const T& NewE)
{
    if(capacity <= currSize)
    {
        resize(capacity*2);
    }

    data[currSize++] = NewE;
}


template<typename T>
void ArrayStack<T>::pop()
{
    if(isEmpty())
    {
        throw std::runtime_error("Stack is empty");
    }

    T el = data[--currSize];
    if(currSize*2 <= capacity && capacity > 1)
    {
        resize(capacity/2);
    }
}

template<typename T>
const T& ArrayStack<T>::peek() const
{
    if(isEmpty())
    {
        throw std::runtime_error("Stak is empty");
    }

    return data[currSize -1 ];

}

template<typename T>
void ArrayStack<T>:: print() const
{
    std::cout << "Stack size: " << currSize << std::endl;
    for (size_t i = 0; i < currSize; i++)
    {
        std::cout<< data[i] << " ";
    }

    std::cout << std::endl;
    
}

template<typename T>

bool ArrayStack<T>::isEmpty() const
{
   return size()==0;
}

template<typename T>
size_t ArrayStack<T>::size()const
{
    return currSize;
}

template<typename T>
void ArrayStack<T>::clear() 
{
    currSize=0;
    resize(4);
}

int main()
{
   ArrayStack<int> s;

   s.push(10);
   s.push(20);
   s.push(30);

   s.print();

   std::cout<< "Peek: " << s.peek()<< std::endl;

   s.pop();
    std::cout<< "Peek after pop: " << s.peek()<< std::endl;

    s.pop();
    s.pop();

    std::cout<< "Is is empty before clear? " << (s.isEmpty() ? "Yes" : "No") << std::endl;

    s.clear();

   std::cout<< "Is is empty? " << (s.isEmpty() ? "Yes" : "No");
return 0;
}