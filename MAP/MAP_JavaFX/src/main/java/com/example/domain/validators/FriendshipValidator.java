package com.example.domain.validators;


import com.example.domain.Friendship;
import com.example.domain.Tuple;
import com.example.domain.exceptions.ValidationException;

import java.util.Objects;

public class FriendshipValidator implements Validator<Tuple<Long, Long>, Friendship> {

    @Override
    public void validate(Friendship entity) throws ValidationException {
        if (Objects.equals(entity.getId().getLeft(), entity.getId().getRight()))
            throw new ValidationException("user cannot be his own friend");
    }

}

