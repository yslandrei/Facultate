package org.example.domain;

import java.time.LocalDateTime;
import java.util.Objects;

public class Concert extends Entity<Long> {

    private String artist;

    private LocalDateTime date;

    private String location;

    private int availableTickets;

    public Concert(Long id, String artist, LocalDateTime date, String location, int availableTickets) {
        super(id);
        this.artist = artist;
        this.date = date;
        this.location = location;
        this.availableTickets = availableTickets;
    }

    public Concert(String artist, LocalDateTime date, String location, int availableTickets) {
        super(null);
        this.artist = artist;
        this.date = date;
        this.location = location;
        this.availableTickets = availableTickets;
    }

    public String getArtist() {
        return artist;
    }

    public void setArtist(String artist) {
        this.artist = artist;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public int getAvailableTickets() {
        return availableTickets;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Concert concert = (Concert) o;
        return availableTickets == concert.availableTickets && Objects.equals(artist, concert.artist) && Objects.equals(date, concert.date) && Objects.equals(location, concert.location);
    }

    @Override
    public String toString() {
        return "Concert{" +
                "id=" + getId() + '\'' +
                "artist='" + artist + '\'' +
                ", date=" + date +
                ", location='" + location + '\'' +
                ", availableTickets=" + availableTickets +
                '}';
    }

    @Override
    public int hashCode() {
        return Objects.hash(artist, date, location, availableTickets);
    }

    public void setAvailableTickets(int availableTickets) {
        this.availableTickets = availableTickets;
    }
}