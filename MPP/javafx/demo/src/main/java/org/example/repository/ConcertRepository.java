package org.example.repository;

import org.example.domain.Concert;

import java.time.LocalDateTime;
import java.util.List;

public interface ConcertRepository extends Repository<Long, Concert> {

    List<Concert> findAllByDate(LocalDateTime date);

}
