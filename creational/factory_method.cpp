#include <iostream>
#include <string>

class Product {
public:
    virtual ~Product() {}
    virtual std::string Operation() const = 0;
};

class ConcreteProductA : public Product {
public:
    std::string Operation() const override {
        return "Product A Operate";
    }
};

class ConcreteProductB : public Product {
    std::string Operation() const override {
        return "Product B operate";
    }
};

class Creator {
public:
    virtual ~Creator() {};
    virtual Product* FactoryMethod() const = 0;

    std::string DoOperation() const {
        Product* product = this->FactoryMethod();
        std::string result = "Creator Operation" + product->Operation();

        delete product;
        return result;
    }
};

class ConcreteCreatorA : public Creator {
public:
    Product* FactoryMethod() const {
        return new ConcreteProductA();
    }
};

class ConcreteCreatorB : public Creator {
public:
    Product* FactoryMethod() const {
        return new ConcreteProductB();
    }
};

void ClientCode(const Creator& creator) {
    std::cout << "Not aware of creator class"
        << creator.DoOperation() << std::endl;
}

int main () {
    std::cout << "App: Lanched with ConcreteCreatorA" << std::endl;
    Creator* creatorA = new ConcreteCreatorA();
    ClientCode(*creatorA);
    delete creatorA;

    std::cout << std::endl;

    std::cout << "App: Lanched with ConcreteCreatorB" << std::endl;
    Creator* creatorB = new ConcreteCreatorB();
    ClientCode(*creatorB);
    delete creatorB;
    
    return 0;
};
