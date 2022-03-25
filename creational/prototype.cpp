#include <iostream>
#include <string>
#include <unordered_map>

enum Type {
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

class Prototype {
public:
    Prototype() {}
    Prototype(std::string prototypeName)
        : m_prototypeName(prototypeName),
          m_prototypeField(0.0f) {}
    virtual ~Prototype() {}
    virtual Prototype* Clone() const = 0;
    virtual void Method(float field)
    {
        this->m_prototypeField = field;
        std::cout << "Call method from " << m_prototypeName <<
            "with field : " << m_prototypeField << std::endl;
    }

protected:
    std::string m_prototypeName;
    float m_prototypeField;
};

class ConcretePrototypeA : public Prototype {
public:
    ConcretePrototypeA(std::string protoTypeName, float concretePrototypeField)
        : Prototype(protoTypeName), 
          m_concretePrototypeFieldA(concretePrototypeField) {}
    
    Prototype* Clone() const
    {
        return new ConcretePrototypeA(*this);
    }
private:
    float m_concretePrototypeFieldA;
};

class ConcretePrototypeB : public Prototype {
public:
    ConcretePrototypeB(std::string protoTypeName, float concretePrototypeField)
        : Prototype(protoTypeName), 
          m_concretePrototypeFieldB(concretePrototypeField) {}
    
    Prototype* Clone() const
    {
        return new ConcretePrototypeB(*this);
    }
private:
    float m_concretePrototypeFieldB;
};

class PrototypeFactory {
public:
    PrototypeFactory()
    {
        m_prototypes[Type::PROTOTYPE_1] = new ConcretePrototypeA("Prototype A", 50.f);
        m_prototypes[Type::PROTOTYPE_2] = new ConcretePrototypeB("Prototype A", 60.f);
    }

    ~PrototypeFactory()
    {
        delete m_prototypes[Type::PROTOTYPE_1];
        delete m_prototypes[Type::PROTOTYPE_2];
    }

    Prototype* CreatePrototype(Type type)
    {
        return m_prototypes[type]->Clone();
    }

private:
    std::unordered_map<Type, Prototype*, std::hash<int>> m_prototypes;
};

void Client(PrototypeFactory& factory)
{
    std::cout << "Let's create a Prototype A" << std::endl;
    Prototype* prototype = factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90);
    delete prototype;
}

int main()
{
    PrototypeFactory* factory = new PrototypeFactory();
    Client(*factory);
    delete factory;

    return 0;
}
