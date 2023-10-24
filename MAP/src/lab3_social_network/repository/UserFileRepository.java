package lab3_social_network.repository;


import lab3_social_network.domain.Friendship;
import lab3_social_network.domain.Tuple;
import lab3_social_network.domain.User;
import lab3_social_network.domain.validators.Validator;

import java.util.List;

public class UserFileRepository extends AbstractFileRepository<Long, User> {

    public UserFileRepository(String fileName, Validator<Long, User> validator) {
        super(fileName, validator);
    }

    @Override
    public User extractEntity(List<String> args) {
        return new User(Long.parseLong(args.get(0)),
                args.get(1),
                args.get(2),
                args.get(3),
                args.get(4));
    }

    @Override
    protected String createEntityAsString(User entity) {
        return entity.getId() + "," +
                entity.getFirstName() + "," +
                entity.getLastName() + "," +
                entity.getUsername() + "," +
                entity.getPassword();
    }
}
