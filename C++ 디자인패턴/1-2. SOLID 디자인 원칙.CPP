#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<boost/lexical_cast.hpp>
using namespace std;

// SOLID 디자인 원칙
// - 단일 책임 원칙 (Single Responsibility Principle, SRP)
// - 열림-닫힘 원칙 (Open-Closed Principle, OCP)
// - 리스코프 치환 원칙 (Liskov Substitution Principle, LSP)
// - 인터페이스 분리 원칙 (Interface Segregatopm Principle, ISP)
// - 의존성 역전 원칙 (Dependency Inversion Principle, DIP)

// 1. 단일 책임 원칙 (Single Responsibility Principle, SRP)
struct Journal {
	string title;
	vector<string> entries;

	explicit Journal(const string& title) : title{ title } {}
public:
	void add(const string& entry);
	//void save(const string& filename);
};

void Journal::add(const string& entry) {
	static int count = 1;
	entries.push_back(boost::lexical_cast<string>(count++) + ": " + entry); 
}

// 메모장은 메모 기입/관리 기능을 수행하는 것이지 데이터를 쓰는 것이 아니다.
/* 데이터 저장 방식이 바뀔때 수정을 여러클래스에 걸쳐서 해야하는 징조(코드스멜)가 나타난다.
void Journal::save(const string& filename) {
	ofstream ofs(filename);
	for (auto& s : entries)
		ofs << s << endl;
}
*/

// 각 클래스는 단 한가지의 책임을 부여받아 수정할 이유가 단 한가지어야 한다.
// 저장 방식을 바꾸기 위해선 PersistenceManager객체만 수정해야 한다.
struct PersistenceManager {
	static void save(const Journal& j, const string& filename) {
		ofstream ofs(filename);
		for (auto& s : j.entries) {
			ofs << s << endl;
		}
	}
};
// 2. 열림-닫힘 원칙(Open-Closed Principle, OCP)
// 고정된 것과 유기적인 것을 구분하여 열고 닫는다.
// 부모클래스는 닫히게 하고 자식클래스는 열어놓는다.
enum class Color{Red, Green, Blue};
enum class Size{Small, Medium, Large};

struct Product {
	string name;
	Color color;
	Size size;
};
struct ProductFilter {
	typedef vector<Product*> Items;

	//Items by_color(Items items, Color color);
	//Items by_size(Items items, Size size);
	//Items by_color_and_size(Items items, Size size, Color color);
};

/* 색상을 기준으로 제품 구분
ProductFilter::Items ProductFilter::by_color(Items items, Color color) {
	Items result;
	for (auto& i : items)
		if (i->color == color)
			result.push_back(i);
	return result;
}*/

/* 사이즈를 기준으로 제품 구분. 위의 코드와 같은 작업을 반복한다.
ProductFilter::Items ProductFilter::by_size(Items items, Size size) {
	Items result;
	for (auto& i : items)
		if (i->size == size)
			result.push_back(i);
	return result;
}*/

/* 색상과 사이즈를 기준으로 제품 구분. 위의 작업을 또 반복한다.
ProductFilter::Items ProductFilter::by_color_and_size(Items items, Size size, Color color) {
	Items result;
	for (auto& i : items)
		if (i->size == size && i->color == color)
			result.push_back(i);
	return result;
}*/

// 이러한 경우에 필요한 것이 열림-닫힘 원칙이다. 기존 코드의 수정없이 필터링을 확장할 수 있는 방법이 필요.
// 먼저, SRP원칙을 적용해 "필터"와 "명세"로 구분

template<typename T> struct Specification {
	virtual bool is_satisfied(T* item) = 0;
	
	/*
	AndSpecification<T> operator&& (Specification&& other) {
		return AndSpecification<T>(*this, other);
	}*/
};

// 색상 명세
struct ColorSpecification : Specification<Product> {
	Color color;

	explicit ColorSpecification(const Color color) : color{color}{}
	
	bool is_satisfied(Product* item) override {
		return item->color == color;
	}
};

// 크기 명세
struct SizeSpecification : Specification<Product> {
	Size size;

	explicit SizeSpecification(const Size size) : size{ size } {}

	bool is_satisfied(Product* item) override {
		return item->size == size;
	}
};

// 동시에 필터링 하는 조건 명세
template<typename T> struct AndSpecification : Specification<T> {
	Specification<T>& first;
	Specification<T>& second;

	AndSpecification(Specification<T>& first,
		Specification<T>& second)
		: first{first}, second{second} {}

	bool is_satisfied(T* item) override {
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};

template<typename T> struct Filter {
	virtual vector<T*> filter(
		vector<T*> items,
		Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
	vector<Product*> filter(
		vector<Product*> items,
		Specification<Product>& spec) override
	{
		vector<Product*> result;
		for (auto& p : items)
			if (spec.is_satisfied(p))
				result.push_back(p);
		return result;
	}
};

// 3. 리스코프 치환 원칙
// 어떤 자식 객체에 접근할 때 부모 객체의 인터페이스로 접근하더라도 문제가 없어야한다.
class Rectangle {
protected:
	int width, height;
public:
	Rectangle(const int width, const int height)
		: width{ width }, height{ height }{}

	int get_width() const { return width; }
	virtual void set_width(const int width) { this->width = width; }
	int get_height() const { return height; }
	virtual void set_height(const int height) { this->height = height; }


	bool is_square() const;
	int area() const { return width * height; }
};

/* 
직사각형의 특별한 경우인 정사각형을 만든다고 하면

class Square : public Rectangle {
public:
	Square(int size) : Rectangle(size,size){}
	void set_width(const int width) override {
		this->width = height = width;
	}
	void set_height(const int height) override {
		this->height = width = height;
	}
};

Square 객체를 인자로 하여 Rectangle 객체로 접근하면 문제가 발생한다.

void process(Rectangle& r) {
	int w = r.get_width();
	r.set_height(10);

	cout << "expected area = " << (w * 10)<< ", got " << r.area() << endl;
} 
*/
// 생성하는 함수를 가지고 있는 클래스를 두어 따로따로 생성한다.

struct RectangleFactory {
	static Rectangle create_rectangle(int w, int h);
	static Rectangle create_square(int size);
};

bool Rectangle::is_square() const {
	return width == height;
}

Rectangle RectangleFactory::create_rectangle(int w, int h){
	Rectangle R(w,h);
	return R;
}
Rectangle RectangleFactory::create_square(int size){
	Rectangle S(size,size);
	return S;
}

// 4. 인터페이스 분리 원칙
// 필요에 따라 구현할 대상을 선별할 수 있도록 인터페이스를 별개로 두어야 한다.
struct Document{};

struct IPrinter{
	virtual void print(vector<Document*> docs) = 0;
};
struct IScanner{
	virtual void scan(vector<Document*> docs) = 0;
};

struct Printer : IPrinter{
	void print(vector<Document*> docs) override;
};
struct Scanner : IScanner{
	void scan(vector<Document*> docs) override;
};

// 복합기 전체를 나타내는 인터페이스
struct IMachine: IPrinter , IScanner {
};

struct Machine : IMachine{
	IPrinter& printer;
	IScanner& scanner;

	Machine (IPrinter& printer, IScanner& scanner)
	: printer{printer}, scanner{scanner}{}

	void print(vector<Document*> docs) override{
		printer.print(docs);
	}
	void scan(vector<Document*> docs) override{
		scanner.scan(docs);
	}
};

// 5. 의존성 역전 원칙
// - 상위 모듈이 하위모듈에 종속성을 가져서는 안된다. 양쪽 모두 추상화(인터페이스)에 의존해야 한다.
// - 추상화가 세부 사항에 의존해서는 안 된다. 세부 사항이 추상화에 의존해야 한다.

// -> 종속성이 실 구현 타입이 아니라 인터페이스 또는 부모 클래스에 있어야 한다는것
// 이 원칙이 지켜지면 구성에 대한 설정이 편리해지고 모듈을 테스트 하는 것도 쉬워진다.

/* Reporting이 ILogger에 의존해야 하는 코드는 아래와 같이 나타낼 수 있다.
class Reporting {
	ILogger& logger;
public:
	Reporting(const ILogger& logger) : logger{logger}{}
	void prepare_report(){
		logger.log_info("Preparing the report");
		...
	}
};*/
// 이 클래스를 인스턴스화 하려면 구현 클래스를 호출 해야하는 문제가 있다.
// (Reporting{ConsoleLogger{}} 등의 방법으로)
// 만약 ConsoleLogger 가 자체적으로 다른 종속성을 가지고 있거나 
// Reporting 클래스가 서로 다른 인터페이스를 사용해야한다면 아주 많은 코드를 작성해야 한다.

// 오늘날 의존성 역전 원칙을 구현하는 방법은 종속성 주입 테크닉을 활용하는 것이다.

// 예로 자동차를 생각해보면 엔진과 로그 기능을 필요로 한다고 한다.
// 자동차는 이 두기능에 의존성을 가지고 있다.
struct Engine{
	float volume = 5;
	int horse_power = 400;

	friend ostream& operator<<(ostream& os, const Engine& obj){
		return os << "Volume: " << obj.volume << "horse_power: " << obj.horse_power;
	}
};
// 이제 자동차에 엔진을 제공할때 IEngine 인터페이스를 따로 추출할지 말지 선택할 수 있다.
// 만약 엔진들이 어떤 계층을 이루거나, 테스트를 위한 NullEngine이 필요하다면 엔진을 추상화하여 
// IEngine 인터페이스를 따로 추출해야 한다.
// Logging의 경우에도 여러가지 방법으로 할 수 있으므로 ILogger 인터페이스를 두는 것이 좋을 것이다.
struct ILogger{
	virtual ~ILogger(){}
	virtual void Log(const string& s) = 0;
};

// 위 인터페이스의 구현클래스
struct ConsoleLogger : ILogger{
	ConsoleLogger(){}

	void Log(const string& s) override{
		cout << "LOG: " << s.c_str()<< endl;
	}
};
// 우리가 정의할 자동차는 엔진과 로깅 두 컴포넌트에 모두 의존하므로 두 컴포넌트를 내부에서 접근할 수 있어야 한다.
struct Car{
	unique_ptr<Engine> engine;
	shared_ptr<ILogger> logger;

	Car(unique_ptr<Engine> engine, const shared_ptr<ILogger>& logger)
	: engine{move(engine)}, logger{logger}{
		logger->Log("making a car");
	}

	friend ostream& operator<<(ostream& os, const Car& obj){
		return os<<"car with engine: " << *obj.engine;
	}
};

// Dependency Injection을 간단히 설명하자면 프레임워크 등에 의해 의존성이 주입되 는 것이다.
// 외부(프레임워크 등)에서 객체가 생성되고 생성된 객체가 컴포넌트에 주입된다.
// 책에서는 make_unique/make_shared의 호출없이 boost.DI(github의 boost-experimental에 속해있다.)을 이용하여 종속성을 주입한다.
/*
	auto injector = di::make_inject(di::bind<ILogger>().to<ConsoleLogger>());

	auto car = injector.create<shared_ptr<Car>>();
*/
// 이러한 접근방법의 장점은 사용할 ILogger 인스턴스의 타입을 바꿀때 단 한 곳, 
// 즉, bind가 수행되는 부분만 수정하면 자동으로 ILoggerf를 사용하는 모든 곳에 적용된다는 점이다.
// 이러한 방식은 단위 테스트도 쉽게 할 수 있게 해준다.
int main() {
	// 1. SRP
	Journal j{ "Dear Diary" };
	j.add("I cried today");
	j.add("I ate a bug");
	PersistenceManager pm;
	pm.save(j, "srp.txt");

	// 2. OCP
	Product apple{ "Apple", Color::Green, Size::Small };
	Product tree{ " Tree", Color::Green, Size::Large };
	Product house{ "House", Color::Blue, Size::Large };

	vector<Product*> all{ &apple, &tree, &house };

	BetterFilter bf;
	ColorSpecification green(Color::Green);

	auto green_things = bf.filter(all, green);
	for (auto& x : green_things)
		cout << x->name << " is green" << endl;

	SizeSpecification large(Size::Large);
	ColorSpecification green2(Color::Green);
	AndSpecification<Product> green_and_large{ large, green2 };

	auto big_green_things = bf.filter(all, green_and_large);
	for (auto& x : big_green_things)
		cout << x->name << " is large and green" << endl;

	/* 
	// 두개의 필터 명세를 하는데 많은 코드를 작성해야 되므로 연산자 오버로딩을 이용하여 단순화 한다.
	// 책에는 되지만 직접 작성하고보니 작동하지 않는다. 아마 부모클래스에서 자식클래스를 반환하기 때문이고,
	// 그리고 Specification을 수정하게되어 OCP 위반이므로 그냥 객체를 두개 사용하는 것이 옳은 것 같다.
	auto green_and_large = ColorSpecification(Color::Green) && SizeSpecification(Size::Large);
	auto big_green_things = bf.filter(all, green_and_large);
	for (auto& x : big_green_things)
		cout << x->name << "is large and green" << endl;
	*/

	// 3. LSP
	Rectangle R = RectangleFactory::create_rectangle(10, 20);
	Rectangle S = RectangleFactory::create_square(10);

	if(S.is_square()) cout << "is square!" << endl;
	
	return 0;
}