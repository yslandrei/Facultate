package lab3_social_network;

import lab3_social_network.domain.User;
import lab3_social_network.domain.validators.UserValidator;
import lab3_social_network.repository.EntityFileRepository;
import lab3_social_network.repository.InMemoryRepository;

public class Main {

    public static void main(String[] args) {
        EntityFileRepository<Long, User> userFileRepository = new EntityFileRepository<>("aici.csv", new UserValidator());


    }
}
