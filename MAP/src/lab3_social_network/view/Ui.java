package lab3_social_network.view;

import lab3_social_network.domain.User;
import lab3_social_network.service.UserService;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;

public class Ui {

    private UserService userService;

    private BufferedReader reader;

    public Ui(UserService userService) {
        this.userService = userService;
        this.reader = new BufferedReader(
                new InputStreamReader(System.in));;
    }

    private void printAllUsers() {
        userService.getAllUsers().forEach(System.out::println);
    }

    private void printCommands() {
        System.out.println("Add User          - usrAdd [id], [fName], [lName], [user], [pass]");
        System.out.println("Remove User       - usrPop [id]");
        System.out.println("Add Friendship    - frdAdd [id1], [id2]");
        System.out.println("Remove Friendship - frdPop [id]");
    }

    public void run() {
        while (true) {
            printAllUsers();
            System.out.println();
            printCommands();
            System.out.println();

            String inputLine = "";
            try {
                inputLine =  reader.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            String inputCommand = inputLine.substring(0, inputLine.indexOf(' '));
            List<String> inputArgs = Arrays.asList(inputLine.substring(inputLine.indexOf(' ') + 1).split(","));
//
//            if (inputCommand.equals("addUsr")) {
//                User newUser = new User(Long.parseLong(inputArgs.get(0)),
//                        inputArgs)
//            }
        }
    }

}
