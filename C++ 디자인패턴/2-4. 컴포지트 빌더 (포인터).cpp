#include<iostream>
#include<sstream>
#include<string>
using namespace std;

class PersonAddressBuilder;
class PersonJobBuilder;
class PersonBuilder;
class PersonBuilderBase;

class Person{
    // 주소
    string street_address, post_code, city;

    // 직업
    string company_name, position;
    int annual_income = 0;

    Person(){}

public:
    ~Person(){}
    
    static PersonBuilder create();
    // 생성자
    Person(Person&& other)
        : street_address{other.street_address},
        post_code{other.post_code},
        city{other.city},
        company_name{other.company_name},
        position{other.position},
        annual_income{other.annual_income}{}

    // 복사 생성자 (이동시멘틱)
    Person& operator=(Person&& other){
        if(this == &other)
            return *this;
        street_address = move(other.street_address);
        post_code = move(other.post_code);
        city = move(other.city);
        company_name = move(other.company_name);
        position = move(other.position);
        annual_income = move(other.annual_income);
        return *this;
    }
    
    // 출력
    friend ostream& operator<<(ostream& os, const Person& obj){
        os << "street_address: " << obj.street_address
			<< " post_code: " << obj.post_code
			<< " city: " << obj.city
			<< " company_name: " << obj.company_name
			<< " position: " << obj.position
			<< " annual_income: " << obj.annual_income;
        return os;
    }
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
    friend class PersonBuilder;
};
class PersonBuilderBase{
protected:
    Person* person;
    explicit PersonBuilderBase(Person* person)
        : person{person}{}

public:
    operator Person() const{
        return move(*person);
    }

    //builder facets
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};

//* Person Builder
class PersonBuilder : public PersonBuilderBase{
public:
    PersonBuilder(Person* p) : PersonBuilderBase{p} {}
};

class PersonAddressBuilder : public PersonBuilderBase{
    typedef PersonAddressBuilder Self;
public:
    explicit PersonAddressBuilder(Person* Person)
    : PersonBuilderBase{person}{}

    Self& at(string street_adress){
        person->street_address = street_adress;
        return *this;
    }
    Self& with_postcode(string post_code){
        person->post_code = post_code;
        return *this;
    }
    Self& in(string city){
        person->city = city;
        return *this;
    }
};

class PersonJobBuilder : public PersonBuilderBase{
	typedef PersonJobBuilder Self;
public:
	explicit PersonJobBuilder(Person* person)
		: PersonBuilderBase{ person }{}

	Self& at(std::string company_name){
		person->company_name = company_name;
		return *this;
	}

	Self& as_a(std::string position){
		person->position = position;
		return *this;
	}

	Self& earning(int annual_income){
		person->annual_income = annual_income;
		return *this;
	}
};

PersonBuilder Person::create(){
    return PersonBuilder(new Person);
}

PersonAddressBuilder PersonBuilderBase::lives() const{
    return PersonAddressBuilder{person};
}

PersonJobBuilder PersonBuilderBase::works() const{
    return PersonJobBuilder{person};
}

int main(){
    Person p = Person::create()
		.lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
		.works().at("PragmaSoft").as_a("Consultant").earning(10e6);

	cout << p << endl;
	getchar();
    return 0;
}