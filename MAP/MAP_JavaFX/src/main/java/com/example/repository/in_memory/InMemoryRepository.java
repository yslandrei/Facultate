package com.example.repository.in_memory;


import com.example.domain.Entity;
import com.example.domain.validators.Validator;
import com.example.repository.Repository;
import com.example.repository.paging.Page;
import com.example.repository.paging.Pageable;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {

    private final Validator<ID, E> validator;

    private final Map<ID, E> entities;

    public InMemoryRepository(Validator<ID, E> validator) {
        this.validator = validator;
        entities = new HashMap<ID, E>();
    }

    @Override
    public Optional<E> findOne(ID id){
        if (id == null)
            throw new IllegalArgumentException("id must be not null");

        return Optional.ofNullable(entities.get(id));
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    public Page<E> findAll(Pageable pageable) {
        return null;
    }

    @Override
    public Optional<E> save(E entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must be not null");

        validator.validate(entity);
        if (entities.get(entity.getId()) != null) {
            return Optional.of(entity);
        }
        entities.put(entity.getId(), entity);
        return Optional.empty();
    }

    @Override
    public Optional<E> delete(ID id) {
        if (id == null)
            throw new IllegalArgumentException("id must not be null");

        if (entities.get(id) == null) {
            return Optional.empty();
        }
        return Optional.ofNullable(entities.remove(id));
    }

    @Override
    public Optional<E> update(E entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must be not null!");

        validator.validate(entity);
        entities.put(entity.getId(), entity);
        if (entities.get(entity.getId()) != null) {
            entities.put(entity.getId(), entity);
            return Optional.empty();
        }
        return Optional.of(entity);
    }
}
