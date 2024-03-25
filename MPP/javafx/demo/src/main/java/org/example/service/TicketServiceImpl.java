package org.example.service;

import org.example.domain.Concert;
import org.example.domain.Ticket;
import org.example.domain.User;
import org.example.repository.ConcertRepository;
import org.example.repository.TicketRepository;
import org.example.repository.UserRepository;
import org.example.utils.observer.Observer;

import java.util.ArrayList;
import java.util.List;

public class TicketServiceImpl implements TicketService {

    private final UserRepository userRepository;

    private final ConcertRepository concertRepository;

    private final TicketRepository ticketRepository;

    private List<Observer> observers = new ArrayList<>();

    public TicketServiceImpl(UserRepository userRepository, ConcertRepository concertRepository, TicketRepository ticketRepository) {
        this.userRepository = userRepository;
        this.concertRepository = concertRepository;
        this.ticketRepository = ticketRepository;
    }

    @Override
    public void buyTicket(Concert concert, User user, String buyer, int seats) {
        if (concert.getAvailableTickets() < seats) {
            throw new RuntimeException("Not enough seats");
        }
        concert.setAvailableTickets(concert.getAvailableTickets() - seats);
        concertRepository.update(concert);
        ticketRepository.save(new Ticket(concert, user, buyer, seats));
        notifyObservers();
    }

    @Override
    public void addObserver(Observer e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers() {
        observers.forEach(Observer::update);
    }

}
