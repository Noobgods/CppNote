#include<iostream>
using namespace std;

// 인터프리터 패턴

class Expression {
public:
	virtual ~Expression(){}
	virtual double evaluate()=0;
};

class NumberExpression:public Expression{
public:
	NumberExpression(double value) : value_(value){}
	virtual double evaluate() {return value_;}

private:
	double value_;
};
class AdditionExpression:public Expression{
public:
	AdditionExpression(Expression* left, Expression* right)
	: left_(left), right_(right){}

	virtual double evaluate(){
		double left = left_->evaluate();
		double right = right_->evaluate();

		return left+right;
	}
	
private:
	Expression* left_;
	Expression* right_;
};

int main(){
	NumberExpression a = 5, b = 2;
	AdditionExpression s(&a, &b);
	cout << s.evaluate() << endl;

	return 0;
}