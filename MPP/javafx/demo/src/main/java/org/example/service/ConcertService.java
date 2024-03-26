package org.example.service;

import org.example.domain.Concert;

import java.time.LocalDateTime;
import java.util.List;

public interface ConcertService {
    List<Concert> getConcertsFromDay(LocalDateTime date);

    List<Concert> getAllConcerts();
}
