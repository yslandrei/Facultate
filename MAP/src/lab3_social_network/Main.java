package lab3_social_network;

import lab3_social_network.domain.validators.FriendshipValidator;
import lab3_social_network.domain.validators.UserValidator;
import lab3_social_network.repository.FriendshipFileRepository;
import lab3_social_network.repository.UserFileRepository;
import lab3_social_network.service.UserService;
import lab3_social_network.view.UserInterface;

public class Main {

    public static void main(String[] args) {
        UserFileRepository userFileRepository = new UserFileRepository("users.csv", new UserValidator());
        FriendshipFileRepository friendshipFileRepository = new FriendshipFileRepository("friendships.csv", new FriendshipValidator() {
        });

        UserService userService = new UserService(userFileRepository, friendshipFileRepository);

        UserInterface userInterface = new UserInterface(userService);
        userInterface.run();
    }
}
