package lab1.model.expression;


import lab1.model.Complex;
import lab1.model.Operation;

import java.util.ArrayList;

public class ComplexExpressionAddition extends ComplexExpression {

    public ComplexExpressionAddition(Operation op, ArrayList<Complex> args) {
        super(op, args);
    }

    @Override
    public Complex executeOneOperation(Complex a, Complex b) {
        return a.add(b);
    }
}
