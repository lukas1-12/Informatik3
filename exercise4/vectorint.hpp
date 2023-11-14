#ifndef MY_INTEGER_VECTOR_HPP
#define MY_INTEGER_VECTOR_HPP

class VectorInt {
public:
    VectorInt(int size);
    ~VectorInt();
    void push_back(int data);
    int size();
    int max_size();
    void resize(int new_size);
    void clear(int pos);
    int at(int pos);
    void copy_dyn_data(int * src , int size_);
    void print();
    int get_mp_Data();

private:
    int m_size;
    int capacity;
    int* mp_Data;
};

#endif