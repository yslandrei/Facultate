using System;
using System.Collections.Generic;
using WindowsFormsApp1.domain;
using WindowsFormsApp1.repository;

namespace WindowsFormsApp1.service;

public class ConcertService(IConcertRepository concertRepository) : IConcertService
{
    private IConcertRepository _concertRepository = concertRepository;

    public List<Concert> GetConcertsFromDay(DateTime dateTime)
    {
        return _concertRepository.FindAllByDate(dateTime);
    }

    public List<Concert> GetAllConcerts()
    {
        return _concertRepository.FindAll();
    }
}