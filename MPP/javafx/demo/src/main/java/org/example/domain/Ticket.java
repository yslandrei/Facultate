package org.example.domain;

import java.util.Objects;

public class Ticket extends Entity<Long> {

    private Concert concert;

    private User user;

    private String buyer;

    private int seats;

    public Concert getConcert() {
        return concert;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public void setConcert(Concert concert) {
        this.concert = concert;
    }

    public String getBuyer() {
        return buyer;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Ticket ticket = (Ticket) o;
        return seats == ticket.seats && Objects.equals(concert, ticket.concert) && Objects.equals(user, ticket.user) && Objects.equals(buyer, ticket.buyer);
    }

    @Override
    public int hashCode() {
        return Objects.hash(concert, user, buyer, seats);
    }

    public void setBuyer(String buyer) {
        this.buyer = buyer;
    }

    public int getSeats() {
        return seats;
    }

    public void setSeats(int seats) {
        this.seats = seats;
    }

    public Ticket(Long id, Concert concert, User user, String buyer, int seats) {
        super(id);
        this.concert = concert;
        this.user = user;
        this.buyer = buyer;
        this.seats = seats;
    }

    public Ticket(Concert concert, User user, String buyer, int seats) {
        super(null);
        this.concert = concert;
        this.user = user;
        this.buyer = buyer;
        this.seats = seats;
    }

}
