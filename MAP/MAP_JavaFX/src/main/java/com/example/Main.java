package com.example;

import com.example.domain.validators.FriendshipValidator;
import com.example.domain.validators.UserValidator;
import com.example.repository.database.FriendshipDatabaseRepository;
import com.example.repository.database.UserDatabaseRepository;
import com.example.service.UserService;
import com.example.view.ConsoleUserInterface;

public class Main {

    public static void main(String[] args) {
        UserDatabaseRepository userDatabaseRepository = new UserDatabaseRepository(
                "jdbc:postgresql://localhost:5432/socialnetwork",
                "postgres",
                "root",
                new UserValidator());

        FriendshipDatabaseRepository friendshipDatabaseRepository = new FriendshipDatabaseRepository(
                "jdbc:postgresql://localhost:5432/socialnetwork",
                "postgres",
                "root",
                new FriendshipValidator());

        UserService userService = new UserService(userDatabaseRepository, friendshipDatabaseRepository);

        ConsoleUserInterface userInterface = new ConsoleUserInterface(userService);
        userInterface.run();
    }
}
