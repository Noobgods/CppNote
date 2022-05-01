#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<memory>
using namespace std;

struct HtmlBuilder;

// 빌더 패턴은 생성이 까다로운 객체를 쉽게 처리하기 위한 패턴이다.
// 즉, 생성자 호출 코드 단 한 줄로 생성할 수 없는 객체를 다룬다.

/* 시나리오
    웹 페이지를 그리기위한 컴포넌트들을 생성해야 한다고 할때 
    각각의 HtmlElement를 생성하는 과정을 간소화 한다.
*/
/*
struct HtmlElement{
    string name;
    string text;
    vector<HtmlElement> elements;

    string str(int indent = 0) const{
        // 컨텐츠를 양식에 맞추어 출력
    }
   
    HtmlElement(){}
    HtmlElement(const string& name, const string& text) 
        : name(name), text(text){}

};
*/
// - 단순한 빌더
// 빌더 패턴은 단순하게 개별 객체의 생성을 별도의 다른 클래스에 위임한다.
/*
struct HtmlBuilder{
    HtmlElement root;

    HtmlBuilder(string root_name) {root.name = root_name;}

    *//*
    void add_child(string child_name, string child_text){
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
    }
    *//*
    HtmlBuilder& add_child(string child_name, string child_text){
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);

        return *this;
    }
    
    string str() {return root.str();}
};
*/
// HtmlBuilder는 HTML 구성요소의 생성만을 전담하는 클래스이다.
// add_child()는 현재 요소에 자식요소를 추가하는 목적으로 사용된다.
// 이 클래스는 출력부분 아래와 같이 사용된다.
// <1><main code>
// add_child()의 리턴값은 사용되는곳이 없는데 리턴값을 활용해 편리한 흐름식 인터페이스 스타일을 만들 수 있다.

// - 흐름식 빌더
// 다음과 같이 빌더 자기 자신을 리턴하도록 수정한다.
// <HtmlBuilder Code>
// 빌더 자기자신이 리턴되기 때문에 다음과 같이 메서드들이 꼬리를 무는 호출이 가능해진다.
// 이러한 형태로 호출하는 것을 흐름식 인터페이스라고 부른다.
// <2><main code>
// 리턴을 포인터로 할지 참조로 할지는 개발자의 마음대로다.

// - 의도 알려주기
// 사용자가 빌더 클래스를 사용해야 한다는 것을 알게하기 위해서 빌더를 사용하지 않으면 객체성성을 불가능하게 한다.
class HtmlElement{
public:
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    string str(int indent = 0) const{
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (text.size() > 0)
            oss << string(indent_size*(indent + 1), ' ') << text << endl;

        for (const auto& e : elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }

    static unique_ptr<HtmlBuilder> build(const string& root_name){
        return make_unique<HtmlBuilder>(root_name);
    }
    friend HtmlBuilder;
protected:
    HtmlElement(){}
    HtmlElement(const string& name, const string& text) 
        : name(name), text(text){}
    int num = 10;

};

class HtmlBuilder{
public:
    HtmlBuilder(string root_name){
        root.name = root_name;
    }
    
    HtmlBuilder* add_child(string child_name, string child_text){
        HtmlElement e{child_name, child_text};
        
        root.elements.emplace_back(e);

        return this;
    }
    string str() { return root.str();}
    
    operator HtmlElement() const {return root;}
    HtmlElement root;
    
};

int main(){
    /* 각각 HtmlElement를 생성하고 출력하는 부분 빌더 패턴은 이 생성을 별도의 다른 클래스에 위임한다.
    string words[] = {"hello", "world"};
    HtmlElement list{"ul", ""};
    for(auto w : words)
        list.elements.emplace_back(HtmlElement{"li", w});
    printf(list.str().c_str());
    
    <1>
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello");
    builder.add_child("li", "world");
    cout << builder.str() << endl;
    
    <2>
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    cout << builder.str() << endl;
    */

    auto builder = HtmlElement::build("ul")
    ->add_child("li","Hello")->add_child("li","World");
    cout << builder->str() << endl;

    return 0;
}