package com.example.utils.observer;

import com.example.utils.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}