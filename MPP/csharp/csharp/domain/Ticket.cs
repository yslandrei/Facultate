namespace csharp.domain;


    public class Ticket(long id, Concert concert, string buyer, int seats)
        : Entity<long>(id)
    {
        public Concert Concert { get; set; } = concert;

        public string Buyer { get; set; } = buyer;

        public int Seats { get; set; } = seats;

        public override bool Equals(object? obj)
        {
            if (this == obj)
                return true;

            if (obj == null || GetType() != obj.GetType())
                return false;

            Ticket ticket = (Ticket)obj;
            return Seats == ticket.Seats && Concert == ticket.Concert && Buyer == ticket.Buyer;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Concert, Buyer, Seats);
        }
    }
