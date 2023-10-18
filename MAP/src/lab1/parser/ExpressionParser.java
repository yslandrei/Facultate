package lab1.parser;


import lab1.factory.ExpressionFactory;
import lab1.model.Complex;
import lab1.model.expression.ComplexExpression;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ExpressionParser {

    private String input;

    private final ExpressionFactory expressionFactory = ExpressionFactory.getInstance();

    public ExpressionParser(String input) {
        this.input = input;
    }

    public boolean isValid() {
        ArrayList<String> signs = new ArrayList<>();
        String[] inputs = input.split(" ");

        for (int i = 1; i < inputs.length; i += 2) {
            if (i > 1 && ! inputs[i - 2].equals(inputs[i]))
                return false;
        }

        return true;
    }

    public Complex getResult() throws Exception {
        if (! isValid())
            throw new Exception("Expression not Valid");

        ArrayList<Complex> args = new ArrayList<>();

        Arrays.stream(input.split(" ")).forEach(i -> {
            if (! i.equals("+")) {
                args.add(Complex.fromString(i));
            }
        });

        ComplexExpression complexExpression = expressionFactory
                .createExpression("+", args);

        return complexExpression.execute();
    }

}
