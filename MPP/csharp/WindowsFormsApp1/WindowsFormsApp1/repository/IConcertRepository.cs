using System;
using System.Collections.Generic;
using WindowsFormsApp1.domain;

namespace WindowsFormsApp1.repository;

public interface IConcertRepository : IRepository<long, Concert>
{
    List<Concert> FindAllByDate(DateTime dateTime);
    
}