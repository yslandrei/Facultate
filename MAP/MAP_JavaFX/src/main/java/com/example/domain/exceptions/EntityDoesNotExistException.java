package com.example.domain.exceptions;

import com.example.domain.Entity;

public class EntityDoesNotExistException extends RuntimeException {
    public EntityDoesNotExistException(Long id) {
        super("entity with id: " + id + " does not exist");
    }

    public EntityDoesNotExistException(Entity entity) {
        super("entity with id: " + entity.getId() + " does not exist");
    }
}
