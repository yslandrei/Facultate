package lab3_social_network.repository;


import lab3_social_network.domain.Entity;
import lab3_social_network.domain.validators.Validator;

import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {

    private final Validator<E> validator;

    private Map<ID,E> entities;

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        entities = new HashMap<ID,E>();
    }

    @Override
    public E findOne(ID id){
        if (id == null)
            throw new IllegalArgumentException("id must be not null");

        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    public E save(E entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must be not null");

        validator.validate(entity);
        if (entities.get(entity.getId()) != null) {
            return entity;
        }
        else {
            entities.put(entity.getId(), entity);
        }
        return null;
    }

    @Override
    public E delete(ID id) {
        if (id == null)
            throw new IllegalArgumentException("id must not be null");

        if (entities.get(id) == null) {
            return null;
        }
        else {
            return entities.remove(id);
        }
    }

    @Override
    public E update(E entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must be not null!");

        validator.validate(entity);
        entities.put(entity.getId(), entity);
        if (entities.get(entity.getId()) != null) {
            entities.put(entity.getId(), entity);
            return null;
        }
        return entity;
    }
}
