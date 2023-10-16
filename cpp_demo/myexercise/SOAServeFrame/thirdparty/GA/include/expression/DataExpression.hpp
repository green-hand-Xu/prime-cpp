#ifndef __DataExpression_HPP__
#define __DataExpression_HPP__

#include <functional>
#include <list>
#include <memory>

#include "GA/include/data/BasicData.hpp"
#include "FuncionExpression.hpp"

enum ValueOperators {
    Equals,
    NotEquals,
    In,
    NotIn,
    ValueFromTo,
    RangeFromTo,
    GreaterThan,
    LessThan,
    Between
};
enum DataOperators { NoAction, And, Or };


template <typename T1, typename T2>
class DataExpression {
public:
    using ExpressionPtr = std::shared_ptr<BasicData<T2>>;

    DataExpression() {

    }

    explicit DataExpression(DataOperators oper, ExpressionPtr expression)
        : _next(expression), 
          _nextOper(oper) {
    }

    explicit DataExpression(BasicData<T1>* data, const T1& value)
        : DataExpression(data, ValueOperators::Equals, value) {
    }

    explicit DataExpression(BasicData<T1>* data, ValueOperators oper, const T1& value)
        : _data(data), _operator(oper), _value(value) {
    }

    GAReadonlyPropertyWrapper<BasicData<T1>*> data{_data};

    GAReadonlyPropertyWrapper<ExpressionPtr> next{_next};
v
    ExpressionPtr And(ExpressionPtr other) {
        _next = other;
        _nextOper = DataOperators::And;
        return std::make_shared<DataExpression<T2>>(DataOperators::And, other);
    }

    ExpressionPtr Or(ExpressionPtr other) {
        _next = other;
        _nextOper = DataOperators::Or;

        return std::make_shared<DataExpression<T2>>(DataOperators::Or, other);
    }

    inline bool validate() {
        if (!_next) {
            return validateMe();
        }

        switch (_nextOper) {
            case DataOperators::And:
                return validateMe() && validateLinked();
            case DataOperators::Or:
                return validateMe() || validateLinked();
            default:
                return validateMe();
        }
    }

protected:
    inline bool validateMe() {
        if (!_data) {
            return false;
        }

        switch (_operator) {
            case ValueOperators::Equals:
                return _data->value() == _value;
            case ValueOperators::NotEquals:
                return _data->value() != _value;
            default:
                return false;
        }
    }

    inline bool validateLinked() {
        return _next == nullptr || _next->validate();
    }

private:
    BasicData<T1>* _data{nullptr};
    ValueOperators _operator{ValueOperators::Equals};
    T1 _value;

    ExpressionPtr _next{nullptr};
    DataOperators _nextOper{DataOperators::NoAction};
};

#endif