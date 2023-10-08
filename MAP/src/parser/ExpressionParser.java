package parser;

import factory.ExpressionFactory;
import model.Complex;
import model.Operation;
import model.expression.ComplexExpression;

import java.util.ArrayList;
import java.util.StringTokenizer;

public class ExpressionParser {

    private String input;

    private final ExpressionFactory expressionFactory = ExpressionFactory.getInstance();

    public ExpressionParser(String input) {
        this.input = input;
    }

    public boolean isValid() {
        return true;
    }

    public Complex getResult() throws Exception {
        if (! isValid())
            throw new Exception("Expression not Valid");

        StringTokenizer numbers = new StringTokenizer(input, " \n");
        String op = numbers.nextToken();

        ArrayList<Complex> args = new ArrayList<>();
        while(numbers.hasMoreTokens()) {
            String number = numbers.nextToken();
            Float re = 0F, im = 0F;

            if (number.charAt(0) == '+')
                re = Float.parseFloat(number.substring(1, 2));
            else if (number.charAt(0) == '-')
                re = - Float.parseFloat(number.substring(1, 2));

            if (number.charAt(2) == '+')
                im = Float.parseFloat(number.substring(3, 4));
            else if (number.charAt(2) == '-')
                im = - Float.parseFloat(number.substring(3, 4));

            args.add(new Complex(re, im));
        }

        ComplexExpression complexExpression = expressionFactory
                .createExpression(op, args);

        return complexExpression.execute();
    }

}
