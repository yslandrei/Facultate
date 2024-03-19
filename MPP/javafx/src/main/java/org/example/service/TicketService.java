package org.example.service;

public interface TicketService {
    void buyTicket(String email, Long concertId, int seats);
}
