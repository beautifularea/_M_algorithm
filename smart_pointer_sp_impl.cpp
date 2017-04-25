//source : https://www.codeproject.com/Articles/15351/Implementing-a-simple-smart-pointer-in-c

class Person {
public:
    Person() : age(0), pname(nullptr){}
    Person(int age, char *name) : age(age), pname(name) {}
    ~Person() {
    }
    void display() {
        std::cout << "Let's display it : " << pname << " " << age << "\n";
    }
    void shout() {
        std::cout << "shooooooooooooooooooooout!" << "\n";
    }
private:
    int age;
    char *pname;
};

/*
 We will maintain a pointer to class RC in our SP class and 
 this pointer will be shared for all instances of 
 the smart pointer which refers to the same pointer.
 */
class RC {
public:
    void addRef() {
        count++;
    }
    int Release() {
        return --count;
    }
    
public:
    int count;
};

// Implementing a reference counting
// We should not delete the Person class pointer unless no body is using it
template<typename T>
class SP {
public:
    SP() : pData(0), reference(0) {
        reference = new RC();
        reference->addRef();
    }
    SP(T *pvalue) : pData(pvalue) {
        reference = new RC();
        reference->addRef();
    }
    ~SP() {
        if(reference->Release() == 0) {
            delete pData;
            delete reference;
        }
    }
    
    //the smart pointer should behave like a pointer,
    //it should support the same interface as pointers do.
    Person& operator*() { return *pData; }
    Person* operator->() { return pData; }
    
    //we need to have an assignment operator and copy constructor
    SP(const SP<T>& sp) : pData(sp.pData), reference(sp.reference) {
        pData = sp.pData;
        reference = sp.reference;
        
        reference->addRef();
    }
    
    //Assignment operator
    SP<T>& operator=(const SP<T>& sp) {
        if(this != &sp) {
            if(reference->Release() == 0) {
                delete pData;
                delete reference;
            }
            
            pData = sp.pData;
            reference = sp.reference;
            
            reference->addRef();
        }
        
        return *this;
    }
    
private:
    T *pData;
    RC *reference;
};

//test case
int main(int argc, char **argv) {
        SP<Person> p(new Person( 25, "Scott"));
        p->display();
        {
            SP<Person> q = p;
            q->display();
            // Destructor of q will be called here..
            
            
            SP<Person> r;
            r = p;
            r->display();
            // Destructor of r will be called here..
            
        }
        p->display();
        
        return 0;
}
