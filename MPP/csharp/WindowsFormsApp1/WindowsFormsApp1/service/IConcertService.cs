using System;
using System.Collections.Generic;
using WindowsFormsApp1.domain;

namespace WindowsFormsApp1.service;

public interface IConcertService
{
    List<Concert> GetConcertsFromDay(DateTime dateTime);
    
    List<Concert> GetAllConcerts();
}