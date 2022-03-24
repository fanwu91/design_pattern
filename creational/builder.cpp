#include <iostream>
#include <string>
#include <vector>

class Product {
public:
    std::vector<std::string> m_parts;

    void ListParts() const {
        std::cout << "Product parts: " << std::endl;

        for (size_t i = 0; i < m_parts.size(); ++i) {
            if (m_parts[i] == m_parts.back()) {
                std::cout << m_parts.back();
            } else {
                std::cout << m_parts[i] << ",";
            }
        }
        
        std::cout << std::endl;
    }
};

class Builder {
public:
    virtual ~Builder() {}
    virtual void SetPartA() const = 0;
    virtual void SetPartB() const = 0;
    virtual void SetPartC() const = 0;
};

class ConcreteBuilder : public Builder {
public:
    ConcreteBuilder() : m_product(nullptr) {
        this->Reset();
    }

    ~ConcreteBuilder() {
        delete m_product;
    }

    void SetPartA() const override {
        this->m_product->m_parts.push_back("Part A");
    }

    void SetPartB() const override {
        this->m_product->m_parts.push_back("Part B");
    }

    void SetPartC() const override {
        this->m_product->m_parts.push_back("Part C");
    }

    Product* GetProduct() {
        Product* result = this->m_product;
        this->Reset();

        return result;
    }

    void Reset() {
        this->m_product = new Product();
    }

private:
    Product* m_product;
};

class Director {
public:
    void SetBuilder(Builder* builder) {
        this->m_builder = builder;
    }

    void BuildMVP() const {
        this->m_builder->SetPartA();
    }

    void BuildFullProduct() const {
        this->m_builder->SetPartA();
        this->m_builder->SetPartB();
        this->m_builder->SetPartC();
    }
private:    
    Builder* m_builder;
};

void ClientCode(Director& director) {
    ConcreteBuilder* builder = new ConcreteBuilder();
    director.SetBuilder(builder);

    std::cout << "MVP: " << std::endl;
    director.BuildMVP();
    Product* mvp = builder->GetProduct();
    mvp->ListParts();
    delete mvp;

    std::cout << "Full product: " << std::endl;
    director.BuildFullProduct();
    Product* fullProduct = builder->GetProduct();
    fullProduct->ListParts();
    delete fullProduct;

    delete builder;
}

int main() {
    Director* director = new Director();
    ClientCode(*director);
    delete director;

    return 0;
}
