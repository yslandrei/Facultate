package lab3_social_network.domain.validators;

import lab3_social_network.domain.User;
import lab3_social_network.domain.exceptions.ValidationException;

public interface Validator<ID, T> {

    void validate(T entity) throws ValidationException;

    void validateId(ID id) throws ValidationException;

}