package lab1.model.expression;


import lab1.model.Complex;
import lab1.model.Operation;

import java.util.ArrayList;

public abstract class ComplexExpression {

    Operation op;

    ArrayList<Complex> args;

    public ComplexExpression(Operation op, ArrayList<Complex> args) {
        this.op = op;
        this.args = args;
    }

    public Complex execute() {
        Complex result = args.get(0);
        for (Complex arg : args.subList(1, args.size())) {
            result = executeOneOperation(result, arg);
        }
        return result;
    }

    public abstract Complex executeOneOperation(Complex a, Complex b);
}
