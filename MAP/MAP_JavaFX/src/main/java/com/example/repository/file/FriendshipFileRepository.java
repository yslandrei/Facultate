package com.example.repository.file;


import com.example.domain.Friendship;
import com.example.domain.Tuple;
import com.example.domain.validators.Validator;
import com.example.repository.file.AbstractFileRepository;

import java.util.List;

public class FriendshipFileRepository extends AbstractFileRepository<Tuple<Long, Long>, Friendship> {

    public FriendshipFileRepository(String fileName, Validator<Tuple<Long, Long>, Friendship> validator) {
        super(fileName, validator);
    }

    @Override
    public Friendship extractEntity(List<String> args) {
        return new Friendship(new Tuple<>(
                Long.parseLong(args.get(0)),
                Long.parseLong(args.get(1))));
    }

    @Override
    protected String createEntityAsString(Friendship entity) {
        return entity.getId().getLeft() + "," +
                entity.getId().getRight();
    }
}
