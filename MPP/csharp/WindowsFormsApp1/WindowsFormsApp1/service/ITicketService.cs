using System;
using WindowsFormsApp1.domain;

namespace WindowsFormsApp1.service;

public interface ITicketService
{
    void BuyTicket(Concert concert, User user, String buyer, int seats);
}