#include<iostream>
#include<memory>
#include<sstream>

#include<boost/serialization/access.hpp>
#include<boost/serialization/string.hpp>
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
using namespace std;
using namespace boost;

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
private:
    friend class boost::serialization::access;
    template<class Ar>
    void serialize(Ar& ar, const unsigned int version){
        ar& street;
        ar& city;
        ar& suite;
    }
};

struct Contact{
    string name;
    Address* address;  

    Contact() : name(nullptr), address(nullptr){}
    Contact(const Contact& other)
        : name{name}{
        address = new Address(*other.address);
    }
    Contact& operator=(const Contact& other){
        if(this == &other)
            return *this;
        name = other.name;
        address = other.address;
        return *this;
    }
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
private:
    friend class boost::serialization::access;
    template<class Ar>
    void serialize(Ar& ar, const unsigned int version){
        ar& name;
        ar& address;
    }
};
int main(){
    Contact worker{"", new Address("123 East Dr", "London", 0)};
    Contact john{worker}; // or Contact john = worker;
    john.name = "John Doe";
    john.address->suite = 10;

    auto clone = [](const Contact& c){
        ostringstream oss;
        boost::archive::text_oarchive oa(oss);
        oa << c;
        string s = oss.str();

        istringstream iss(oss.str());
        boost::archive::text_iarchive ia(iss);
        Contact result;
        ia >> result;
        return result;
    };

    Contact jane = clone(john);
    jane.name = "Jane Doe";
	jane.address->street = "123B West Dr";
	jane.address->suite = 300;

    cout << john << endl << jane << endl;

    return 0;
}