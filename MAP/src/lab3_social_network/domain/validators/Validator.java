package lab3_social_network.domain.validators;

import lab3_social_network.domain.exceptions.ValidationException;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}