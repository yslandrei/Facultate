package com.example.domain.validators;

import com.example.domain.User;
import com.example.domain.exceptions.ValidationException;

public interface Validator<ID, T> {

    void validate(T entity) throws ValidationException;

}