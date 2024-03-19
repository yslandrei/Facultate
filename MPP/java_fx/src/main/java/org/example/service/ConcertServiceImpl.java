package org.example.service;

import org.example.domain.Concert;
import org.example.repository.ConcertRepository;

import java.time.LocalDateTime;
import java.util.List;

public class ConcertServiceImpl implements ConcertService {

    private final ConcertRepository concertRepository;

    public ConcertServiceImpl(ConcertRepository concertRepository) {
        this.concertRepository = concertRepository;
    }

    @Override
    public List<Concert> getConcertsFromDay(LocalDateTime date) {
        return concertRepository.findAllByDate(date);
    }
}
