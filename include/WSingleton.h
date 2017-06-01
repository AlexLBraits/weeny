#ifndef SINGLETON_H
#define SINGLETON_H

///
/// http://ideone.com/Wh9cX9
///

#include <functional>

template<typename T> // Singleton policy class
class WSingleton
{
protected:
    WSingleton() = default;
    WSingleton(const WSingleton&) = delete;
    WSingleton& operator=(const WSingleton&) = delete;
    virtual ~WSingleton() = default;
public:
    template<typename... Args>
    static T& getInstance(Args... args) // Singleton
    {
    	// we pack our arguments in a T&() function...
			// the bind is there to avoid some gcc bug
    	static auto onceFunction = 	std::bind( createInstanceInternal<Args...>, args... ); 
    	// and we apply it once...
    	return apply( onceFunction );
    }
    
private:
	
	// single instance so the static reference should be initialized only once 
	// so the function passed in is called only the first time
	static T& apply( const std::function<T&()>& function  )
	{
		static T& instanceRef = function();
		return instanceRef;
	}
	
	template<typename... Args>
    static T& createInstanceInternal(Args... args)
    {
		static T instance{ std::forward<Args>(args)... };
		return instance;
    }
};

#endif // SINGLETON_H
