#include<iostream>
#include<vector>

using namespace std;

/*
DSL (Domain Specific Languege) : 도메인 특화 언어
    관련 특정 분야에 최적화된 프로그래밍 언어. (*Groovy, Kotlin에서 생성 지원)
    해당 분야 또는 도메인의 개념과 규칙을 사용
*/

/*
struct Tag{
    string name;
    string text;
    vector<Tag> children;
    vector<pair<string, string>> attribute;

    friend ostream& operator<<(ostream& os, const Tag& tag){
        // 구현 생략
    }
};
*/
/*
몇개의 protected 생성자를 만들어 보자.
앞선 경우에 따라서 다음의 두 경우를 고려해야 한다.
- 태그가 이름과 텍스트로 초기화 되는 경우
- 태그가 이름과 자식의 집합으로 초기화 되는 경우
*/
struct Tag{
    string name;
    string text;
    vector<Tag> children;
    vector<pair<string, string>> attributes;

    friend ostream& operator<<(ostream& os, const Tag& tag){
        os << "<" << tag.name;

        for (const auto& att : tag.attributes)
            os << " " << att.first << "=\"" << att.second << "\"";

        if (tag.children.size() == 0 && tag.text.length() == 0){
            os << "/>" << endl;
        } 
        else{
            os << ">" << endl;

            if (tag.text.length())
                os << tag.text << endl;

            for (const auto& child : tag.children)
                os << child;

            os << "</" << tag.name << ">" << endl;
        }

        return os;
    }
protected:
    Tag(const string& name, const string& text)
    : name{name}, text{text}{}

    Tag(const string& name, const vector<Tag>& children)
    : name{name}, children{children}{}
};

// 이제 이 Tag 클래스를 상속 받을 수 있다. 단 유효한 HTML 태그여야만 한다. 
// 두개의 태그를 정의해 보자. 하나는 문단을 나타내고, 다른 하나는 이미지를 나타낸다.

struct P: Tag{
    explicit P(const string& text)
    : Tag{"p", text} {}

    P(initializer_list<Tag> children)
    : Tag{"p", children}{}
};

struct IMG : Tag{
    explicit IMG(const string& url)
    : Tag{"img", ""}{
        attributes.emplace_back(make_pair("src", url));
    }
};
int main(){
    cout << P{
        IMG {"http://pokemon.com/pikachu.png"}
    }
    << endl;

    return 0;
}