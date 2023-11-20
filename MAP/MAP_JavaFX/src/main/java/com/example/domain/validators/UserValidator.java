package com.example.domain.validators;


import com.example.domain.User;
import com.example.domain.exceptions.ValidationException;

public class UserValidator implements Validator<Long, User> {

    @Override
    public void validate(User entity) throws ValidationException {
        if (entity.getId() < 0)
            throw new ValidationException("id must be positive");

        if (entity.getFirstName().length() == 0)
            throw new ValidationException("first name cannot be empty");
        if (entity.getLastName().length() == 0)
            throw new ValidationException("last name cannot be empty");
        if (entity.getUsername().length() == 0)
            throw new ValidationException("user name cannot be empty");
        if (entity.getPassword().length() == 0)
            throw new ValidationException("password name cannot be empty");

        if (!entity.getFirstName().matches("^[a-zA-Z ]+$"))
            throw new ValidationException("first name must contain only letters and spaces");
        if (!entity.getLastName().matches("^[a-zA-Z ]+$"))
            throw new ValidationException("last name must contain only letters and spaces");
    }

    @Override
    public void validateId(Long id) throws ValidationException {
        if (id < 0)
            throw new ValidationException("id must be positive");
    }

}

