#include <string>
#include <iostream>

class Target {
public:
    virtual ~Target() = default;

    virtual std::string Request() const 
    {
        return "Target: the default behavior";
    }
};

class Special {
public:
    std::string SpecificRequest() const 
    {
        return "special adaptee request";
    }
};

class Adaptor : public Target {
public:
    Adaptor(Special* adaptee) : m_adaptee(adaptee) {}

    std::string Request() const override
    {
        return "TRNSLATED, " + m_adaptee->SpecificRequest();
    }

private:
    Special* m_adaptee;
};

void ClientCode(const Target* target) {
    std::cout << target->Request();
}

int main()
{
    Special* adaptee = new Special;
    Adaptor* adaptor = new Adaptor(adaptee);

    ClientCode(adaptor);

    delete adaptee;
    delete adaptor;

    return 0;
}