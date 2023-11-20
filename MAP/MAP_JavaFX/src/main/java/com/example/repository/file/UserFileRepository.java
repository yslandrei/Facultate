package com.example.repository.file;


import com.example.domain.User;
import com.example.domain.validators.Validator;
import com.example.repository.file.AbstractFileRepository;

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
