
using System;

namespace WindowsFormsApp1.domain;

public class Concert(long id, string artist, DateTime date, string location, int availableTickets)
    : Entity<long>(id)
{
    public Concert(string artist, DateTime date, string location, int availableTickets) : this(0, artist, date,
        location, availableTickets)
    {
    }

    public string Artist { get; set; } = artist;

    public DateTime Date { get; set; } = date;
    
    public string Location { get; set; } = location;

    public int AvailableTickets { get; set; } = availableTickets;

    public override bool Equals(object? obj)
    {
        if (this == obj)
            return true;

        if (obj == null || GetType() != obj.GetType())
            return false;

        var concert = (Concert)obj;
        return AvailableTickets == concert.AvailableTickets && Artist == concert.Artist && Date == concert.Date && Location == concert.Location;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Artist, Date, Location, AvailableTickets);
    }
}