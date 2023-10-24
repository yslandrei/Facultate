package lab3_social_network.view;

import lab3_social_network.domain.User;
import lab3_social_network.service.UserService;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class UserInterface {

    private UserService userService;

    private BufferedReader reader;

    public UserInterface(UserService userService) {
        this.userService = userService;
        this.reader = new BufferedReader(
                new InputStreamReader(System.in));;
    }

    private void printAllUsersWithFriends() {
        System.out.println("Users:");
        userService.getAllUsers().forEach(user -> {
            System.out.print(user);
            System.out.println(" is friends with:");
            userService.getFriendsOfUser(user).forEach(friend -> {
                System.out.println("    -" + friend);
            });
            System.out.println();
        });
    }

    private void printCommands() {
        System.out.println("Add User                            - addUsr [id],[fName],[lName],[user],[pass]");
        System.out.println("Remove User                         - popUsr [id]");
        System.out.println("Add Friendship                      - addFrd [id1],[id2]");
        System.out.println("Remove Friendship                   - popFrd [id1],[id2]");
        System.out.println("Print All Users and Friends         - wrtUsr");
        System.out.println("Number of Communities               - nofCom");
        System.out.println("Largest Communities                 - larCom");
    }

    public void run() {
        while (true) {
            printCommands();
            System.out.println();

            String inputLine = "";
            try {
                inputLine =  reader.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            String inputCommand = inputLine.indexOf(' ') != -1 ? inputLine.substring(0, inputLine.indexOf(' '))
                    : inputLine;
            List<String> inputArgs = inputLine.indexOf(' ') != -1 ? Arrays.asList(inputLine.substring(inputLine.indexOf(' ') + 1).split(","))
                    : new ArrayList<>();

            try {
                switch (inputCommand) {
                    case "addUsr" -> {
                        User newUser = userService.extractUser(inputArgs);
                        userService.addUser(newUser);
                    }
                    case "addusr" -> {
                        userService.removeUser(Long.parseLong(inputArgs.get(0)));
                    }
                    case "addFrd" -> {
                        userService.addFriendToUser(Long.parseLong(inputArgs.get(0)),
                                Long.parseLong(inputArgs.get(1)));
                    }
                    case "popFrd" -> {
                        userService.removeFriendFromUser(Long.parseLong(inputArgs.get(0)),
                                Long.parseLong(inputArgs.get(1)));
                    }
                    case "nofCom" -> {
                        System.out.println("There are " + userService.getNumberOfCommunities() + " communities\n");
                    }
                    case "larCom" -> {
                        System.out.println("The largest community is comprised of the users: ");
                        userService.getLargestCommunity().forEach(System.out::println);
                        System.out.println();
                    }
                    case "wrtUsr" -> {
                        printAllUsersWithFriends();
                    }
                }

            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage() + "!\n");
            }
        }
    }

}
