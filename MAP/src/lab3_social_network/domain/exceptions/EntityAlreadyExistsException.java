package lab3_social_network.domain.exceptions;

import lab3_social_network.domain.Entity;

public class EntityAlreadyExistsException extends RuntimeException {
    public EntityAlreadyExistsException(Long id) {
        super("entity with id: " + id + " already exists");
    }

    public EntityAlreadyExistsException(Entity entity) {
        super("entity with id: " + entity.getId() + " already exists");
    }
}
