#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

template <typename T>
class SingletonHolder
{
    SingletonHolder() = default;
public:
    SingletonHolder(const SingletonHolder&) = delete;
    SingletonHolder& operator=(const SingletonHolder&) = delete;

    static T& instance()
    {
        static T unique_instance; // lazy initialization, thread-safe in C++11 and later

        return unique_instance;
    }
};

#endif /*SINGLETON_HPP_*/
