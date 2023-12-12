package com.example.domain.validators;


import com.example.domain.Message;
import com.example.domain.User;
import com.example.domain.exceptions.ValidationException;

public class MessageValidator implements Validator<Long, Message> {

    @Override
    public void validate(Message entity) throws ValidationException {
        if (entity.getMessage().length() == 0)
            throw new ValidationException("message cannot be empty");
    }

}

