package org.example.service;

import org.example.domain.Concert;
import org.example.domain.Ticket;
import org.example.domain.User;
import org.example.repository.ConcertRepository;
import org.example.repository.TicketRepository;
import org.example.repository.UserRepository;

public class TicketServiceImpl implements TicketService {

    private final UserRepository userRepository;

    private final ConcertRepository concertRepository;

    private final TicketRepository ticketRepository;

    public TicketServiceImpl(UserRepository userRepository, ConcertRepository concertRepository, TicketRepository ticketRepository) {
        this.userRepository = userRepository;
        this.concertRepository = concertRepository;
        this.ticketRepository = ticketRepository;
    }

    @Override
    public void buyTicket(String email, Long concertId, int seats) {
        User user = userRepository.findByEmail(email)
                .orElseThrow(() -> new RuntimeException("User not found"));
        Concert concert = concertRepository.findOne(concertId)
                .orElseThrow(() -> new RuntimeException("Concert not found"));
        if (concert.getAvailableTickets() < seats) {
            throw new RuntimeException("Not enough seats");
        }
        concert.setAvailableTickets(concert.getAvailableTickets() - seats);
        concertRepository.update(concert);
        ticketRepository.save(new Ticket(concert, user, email, seats));
    }
}
