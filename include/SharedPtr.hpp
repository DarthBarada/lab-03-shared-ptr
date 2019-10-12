#pragma once

#include <atomic>
#include <cstddef>

template <typename T>
class SharedPtr
{
T* data = nullptr;
std::atomic_uint* count;

public:
    SharedPtr()
        {
            data  = nullptr;
            count = nullptr;
        }

    SharedPtr(T* ptr)
        {
            data  = ptr;
            count = new std::atomic_uint{1};
        }

    SharedPtr(const SharedPtr& r)
        {
            *this = r;
        }

    SharedPtr(SharedPtr&& r)
        {
           *this = std::move(r);
        }

    ~SharedPtr()
        {
             if (data == nullptr) 
                 {
                    return;
                 }
            else
                {
                    *(count) = *(count) - 1;
                    if (*(count) == 0)
                        {
                            delete data;
                            delete count;
                        }
                    else if (*(count) > 0)
                        {
                            data = nullptr;
                            count = nullptr;
                        }
                }
        }

    SharedPtr& operator=(const SharedPtr& r)
        {
            if (&r == this)
                {
                    return *this;
                }

            this->~SharedPtr();

            data  = r.data;
            count = r.count;
            (*count)++;

            return *this;
        }

    SharedPtr& operator=(SharedPtr&& r) noexcept
        {
            if (&r == this)
                {
                    return *this;
                }

            this->~SharedPtr();

            data  = r.data;
            count = r.count;

            r.data = nullptr;
            r.count = nullptr;

            return *this;
        }

    // Проверяет, указывает ли указатель на объект
    operator bool() const
        {
            return data != nullptr;
        }

     T &operator*() const
        {
            return *data;
        }

    T *operator->() const
        {
            return data;
        }

    T* get()
        {
            return data;
        }
    void reset()
        {
            *this = SharedPtr();
        }

    void reset(T *ptr)
        {
            *this = SharedPtr(ptr);
        }

    void swap(SharedPtr& r)
        {
            if (&r == this)
                {
                    return;
                }

            std::swap(data, r.data);
            std::swap(count, r.count);
        }

    // Возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    unsigned int use_count() const
        {
            if (data!=nullptr)
              {
                return *count;
              }
            else
              {
                return 0;
              }
        }
};
