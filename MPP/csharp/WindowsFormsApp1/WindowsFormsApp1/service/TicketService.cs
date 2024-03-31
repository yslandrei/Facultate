using System;
using System.Collections.Generic;
using WindowsFormsApp1.domain;
using WindowsFormsApp1.repository;
using WindowsFormsApp1.utils;

namespace WindowsFormsApp1.service;

public class TicketService(IConcertRepository concertRepository, ITicketRepository ticketRepository)
    : ITicketService, IObservable
{
    private IConcertRepository _concertRepository = concertRepository;

    private ITicketRepository _ticketRepository = ticketRepository;

    private List<IObserver> observers = new List<IObserver>();
    
    public void BuyTicket(Concert concert, User user, string buyer, int seats)
    {
        if (concert.AvailableTickets < seats)
        {
            throw new Exception("Not enough seats");
        }

        concert.AvailableTickets = concert.AvailableTickets - seats;
        _concertRepository.Update(concert);
        _ticketRepository.Save(new Ticket(concert, buyer, seats, user));
        NotifyObservers();
    }

    public void AddObserver(IObserver observer)
    {
        observers.Add(observer);
    }

    public void RemoveObserver(IObserver observer)
    {
        observers.Remove(observer);
    }

    public void NotifyObservers()
    {
        foreach (IObserver observer in observers)
        {
            observer.Update();
        }
    }
}