package com.example.domain.exceptions;

import com.example.domain.Entity;

public class EntityAlreadyExistsException extends RuntimeException {
    public EntityAlreadyExistsException(Long id) {
        super("entity with id: " + id + " already exists");
    }

    public EntityAlreadyExistsException(Entity entity) {
        super("entity with id: " + entity.getId() + " already exists");
    }
}
