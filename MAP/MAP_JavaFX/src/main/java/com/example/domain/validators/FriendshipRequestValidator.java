package com.example.domain.validators;


import com.example.domain.FriendshipRequest;
import com.example.domain.Tuple;
import com.example.domain.exceptions.ValidationException;

import java.util.Objects;

public class FriendshipRequestValidator implements Validator<Tuple<Long, Long>, FriendshipRequest> {

    @Override
    public void validate(FriendshipRequest entity) throws ValidationException {
        if (Objects.equals(entity.getId().getLeft(), entity.getId().getRight()))
            throw new ValidationException("user cannot send himself a friend request");
    }

}

