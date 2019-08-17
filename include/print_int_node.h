#include <piranha.h>

#include <iostream>

class PrintIntNode : public piranha::Node {
public:
    PrintIntNode() {}
    ~PrintIntNode() {}

protected:
    virtual void _evaluate() {
        // Retrieve data from the integer input
        int data;
        static_cast<piranha::IntValueOutput *>(m_integerInput)->fullCompute((void *)&data);

        std::cout << "Integer value: " << data << std::endl;
    }

    virtual void registerInputs() {
        registerInput(&m_integerInput, "value");
    }

protected:
    piranha::pNodeInput m_integerInput;
};
