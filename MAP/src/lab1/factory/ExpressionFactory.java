package lab1.factory;

import model.Complex;
import model.Operation;
import model.expression.*;

import java.util.ArrayList;

public class ExpressionFactory {

    private ExpressionFactory() {

    }

    private static final ExpressionFactory instance = new ExpressionFactory();

    public static ExpressionFactory getInstance(){
        return instance;
    }

    public ComplexExpression createExpression(String op, ArrayList<Complex> args) {
        if (op.equals("+"))
            return new ComplexExpressionAddition(Operation.ADDITION, args);

        if (op.equals("-"))
            return new ComplexExpressionSubtract(Operation.SUBTRACTION, args);

        if (op.equals("*"))
            return new ComplexExpressionMultiply(Operation.MULTIPLICATION, args);

        if (op.equals("/"))
            return new ComplexExpressionDivide(Operation.DIVISION, args);

        return null;
    }

}
