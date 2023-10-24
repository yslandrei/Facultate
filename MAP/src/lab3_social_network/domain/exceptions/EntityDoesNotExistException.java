package lab3_social_network.domain.exceptions;

import lab3_social_network.domain.Entity;

public class EntityDoesNotExistException extends RuntimeException {
    public EntityDoesNotExistException(Long id) {
        super("entity with id: " + id + " does not exist");
    }

    public EntityDoesNotExistException(Entity entity) {
        super("entity with id: " + entity.getId() + " does not exist");
    }
}
