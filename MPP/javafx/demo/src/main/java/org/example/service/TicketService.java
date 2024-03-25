package org.example.service;

import org.example.domain.Concert;
import org.example.domain.User;
import org.example.utils.observer.Observable;

public interface TicketService extends Observable {
    void buyTicket(Concert concert, User user, String buyer, int seats);
}
