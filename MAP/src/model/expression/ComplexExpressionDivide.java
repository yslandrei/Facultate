package model.expression;

import model.Complex;
import model.Operation;

import java.util.ArrayList;

public class ComplexExpressionDivide extends ComplexExpression {

    public ComplexExpressionDivide(Operation op, ArrayList<Complex> args) {
        super(op, args);
    }

    @Override
    public Complex executeOneOperation(Complex a, Complex b) {
        return a.divide(b);
    }
}
