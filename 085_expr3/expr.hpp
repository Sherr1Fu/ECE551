#include <iostream>
#include <sstream>
class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression(){};
};
class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long value) : number(value){};
  std::string toString() const {
    std::stringstream s;
    s << number;
    return s.str();
  }
  long evaluate() const { return number; }
};
class OpExpression : public Expression {
 protected:
  Expression * left;
  Expression * right;

 public:
  OpExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs){};
  ~OpExpression() {
    delete left;
    delete right;
  }
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
};
class PlusExpression : public OpExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs){};
  std::string toString() const {
    std::stringstream s;
    s << "(" << left->toString() << " + " << right->toString() << ")";
    return s.str();
  }
  long evaluate() const { return left->evaluate() + right->evaluate(); }
};
class MinusExpression : public OpExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs){};
  std::string toString() const {
    std::stringstream s;
    s << "(" << left->toString() << " - " << right->toString() << ")";
    return s.str();
  }
  long evaluate() const { return left->evaluate() - right->evaluate(); }
};
class TimesExpression : public OpExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs){};
  std::string toString() const {
    std::stringstream s;
    s << "(" << left->toString() << " * " << right->toString() << ")";
    return s.str();
  }
  long evaluate() const { return left->evaluate() * right->evaluate(); }
};
class DivExpression : public OpExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs){};
  std::string toString() const {
    std::stringstream s;
    s << "(" << left->toString() << " / " << right->toString() << ")";
    return s.str();
  }
  long evaluate() const { return left->evaluate() / right->evaluate(); }
};
