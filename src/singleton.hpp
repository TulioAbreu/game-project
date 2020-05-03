#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <typename T>
class Singleton {
protected:
    static T* mInstance;
    Singleton() {}

public:
    virtual ~Singleton() {

    }

    static T* getInstance() {
        if (!mInstance) {
            mInstance = new T();
        }
        return mInstance;
    }
};

template <typename T>
T* Singleton<T>::mInstance = nullptr;

#endif