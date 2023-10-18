package lab1;

import lab1.factory.ExpressionFactory;
import lab1.model.Complex;
import lab1.parser.ExpressionParser;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        ExpressionFactory expressionFactory;

        Scanner scanner = new Scanner(System. in);
        String input = scanner.nextLine();
        // ex:
        // + +4+2i -3+1i -4-5i
        ExpressionParser expressionParser = new ExpressionParser(input);
        try {
            Complex result = expressionParser.getResult();
            System.out.println(result.toString());
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}