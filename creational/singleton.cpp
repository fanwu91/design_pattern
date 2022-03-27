#include <thread>
#include <iostream>
#include <string>

class Singleton {
public:
    static Singleton* GetInstance(const std::string& value)
    {
        if (!m_singleton) {
            m_singleton = new Singleton(value);
        }
        
        return m_singleton;
    }

    Singleton(const Singleton& other) = delete;
    void operator=(const Singleton& rhs) = delete;

    const std::string& GetValue() 
    {
        return m_value;
    }
private:
    Singleton(std::string value) : m_value(value) {}
    
    static Singleton* m_singleton;
    std::string m_value;
};

Singleton* Singleton::m_singleton = nullptr;

void Runnable1() {
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    Singleton* singleton = Singleton::GetInstance("Foo");
    std::cout << singleton->GetValue() << std::endl;
}

void Runnable2() {
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    Singleton* singleton = Singleton::GetInstance("Bar");
    std::cout << singleton->GetValue() << std::endl;
}

int main() {
    std::thread t1(Runnable1);
    std::thread t2(Runnable2);

    t1.join();
    t2.join();

    return 0;
}