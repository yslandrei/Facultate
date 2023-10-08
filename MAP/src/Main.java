import factory.ExpressionFactory;
import parser.ExpressionParser;
import model.Complex;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        ExpressionFactory expressionFactory;

        Scanner scanner = new Scanner(System. in);
        String input = scanner.nextLine();

        ExpressionParser expressionParser = new ExpressionParser(input);
        try {
            Complex result = expressionParser.getResult();
            System.out.println(result.toString());
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}