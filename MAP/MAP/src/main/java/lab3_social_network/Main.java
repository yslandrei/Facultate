package lab3_social_network;

import lab3_social_network.domain.validators.FriendshipValidator;
import lab3_social_network.domain.validators.UserValidator;
import lab3_social_network.repository.database.FriendshipDatabaseRepository;
import lab3_social_network.repository.database.UserDatabaseRepository;
import lab3_social_network.service.UserService;
import lab3_social_network.view.ConsoleUserInterface;

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
