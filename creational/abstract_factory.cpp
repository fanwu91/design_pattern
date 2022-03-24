#include <iostream>
#include <string>

class AbstractProductA {
public:
    virtual ~AbstractProductA() {}
    virtual std::string UsefulFunctionA() const = 0;
};

class AbstractProductB {
public:
    virtual ~AbstractProductB() {}
    virtual std::string UsefulFunctionB() const = 0;
    virtual std::string AnotherUsefulFunctionB(
        const AbstractProductA& collaborator) const = 0;
};

class ConcreteProductA1 : public AbstractProductA {
public:
    std::string UsefulFunctionA() const override {
        return "Useful A1";
    };
};

class ConcreteProductA2 : public AbstractProductA {
public:
    std::string UsefulFunctionA() const override {
        return "Useful A2";
    }
};

class ConcreteProductB1 : public AbstractProductB {
public:
    std::string UsefulFunctionB() const override {
        return "Useful B1";
    }

    std::string AnotherUsefulFunctionB(
        const AbstractProductA& collaborator) const override {
        return "B1 & " + collaborator.UsefulFunctionA();
    }
};

class ConcreteProductB2 : public AbstractProductB {
public:
    std::string UsefulFunctionB() const override {
        return "Useful B2";
    }

    std::string AnotherUsefulFunctionB(
        const AbstractProductA& collaborator) const override {
        return "B2 & " + collaborator.UsefulFunctionA();
    }
};

class AbstractFactory {
public:
    virtual AbstractProductA* CreateProductA() const = 0;
    virtual AbstractProductB* CreateProductB() const = 0;    
};

class ConcreteFactory1 : public AbstractFactory {
public:
    virtual AbstractProductA* CreateProductA() const override {
        return new ConcreteProductA1();
    }

    virtual AbstractProductB* CreateProductB() const override {
        return new ConcreteProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory {
public:
    virtual AbstractProductA* CreateProductA() const override {
        return new ConcreteProductA2();
    }

    virtual AbstractProductB* CreateProductB() const override {
        return new ConcreteProductB2();
    }
};

void ClientCode(const AbstractFactory& factory) {
    const AbstractProductA* productA = factory.CreateProductA();
    const AbstractProductB* productB = factory.CreateProductB();

    std::cout << productB->UsefulFunctionB() << std::endl;
    std::cout << productB->AnotherUsefulFunctionB(*productA) << std::endl;

    delete productA;
    delete productB;
};

int main() {
    std::cout << "First concrete factory" << std::endl;
    ConcreteFactory1* f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;

    std::cout << "Second concrete factory" << std::endl;
    ConcreteFactory2* f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
    return 0;
}
