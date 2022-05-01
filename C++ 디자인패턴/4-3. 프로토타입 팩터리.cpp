#include<iostream>
#include<memory>
using namespace std;

struct Address{
    string street, city;
    int suite;
    
    Address(const string& street, const string& city, const int suite)
        : street{street}, city{city}, suite{suite}{}
        
    Address(const Address& address)
        : street{address.street}, city{address.city}, suite{address.suite}{}
        
    friend ostream& operator<<(ostream& os, const Address& obj){
        return os << "street: " << obj.street
                  << " city: " << obj.city
                  << " suite: " << obj.suite;
    }
};

struct Contact{
    string name;
    Address* address;  

    Contact() : name(nullptr), address(nullptr){}
    Contact(const string name, Address* address)
        : name{name}, address{address}{
    }
    friend ostream& operator<<(ostream& os, const Contact& obj){
        return os << "name: " << obj.name
                  << " address: " << *obj.address;
    }
    ~Contact(){
        delete address;
    }
};

struct EmployeeFactory{
    static Contact main;
    static Contact aux;

    static Contact* NewMainOfficeEmployee(string name, int suite){
        return NewEmployee(name, suite, main);
    }

    static Contact* NewAuxOfficeEmployee(string name, int suite){
        return NewEmployee(name, suite, aux);
    }

private:
    static Contact* NewEmployee(string name, int suite, Contact& proto){
        auto result = new Contact(proto);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};

Contact EmployeeFactory::main{"", new Address{"123 East Dr", "London", 0}};
Contact EmployeeFactory::aux{"", new Address{"123B East Dr", "London", 0}};

int main(){
    auto john = EmployeeFactory::NewMainOfficeEmployee("John Doe", 123);
    auto jane = EmployeeFactory::NewAuxOfficeEmployee("Jane Doe", 125);

    cout << *john << endl << *jane << endl;

    return 0;
}