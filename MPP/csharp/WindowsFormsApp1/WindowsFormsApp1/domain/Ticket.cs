using System;

namespace WindowsFormsApp1.domain;


public class Ticket(long id, Concert concert, string buyer, int seats, User user)
    : Entity<long>(id)
{
    public Concert Concert { get; set; } = concert;

    public Ticket(Concert concert, string buyer, int seats, User user) : this(0, concert, buyer, seats, user)
    {
    }

    public string Buyer { get; set; } = buyer;

    public int Seats { get; set; } = seats;

    public User User { get; set; } = user;

    public override bool Equals(object? obj)
    {
        if (this == obj)
            return true;

        if (obj == null || GetType() != obj.GetType())
            return false;

        Ticket ticket = (Ticket)obj;
        return Seats == ticket.Seats && Concert == ticket.Concert && Buyer == ticket.Buyer && User == ticket.User;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Concert, Buyer, Seats, User);
    }
}
