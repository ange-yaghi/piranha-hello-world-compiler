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


    }

protected:
    piranha::pNodeInput m_integerInput;
};
