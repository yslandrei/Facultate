// See https://aka.ms/new-console-template for more information

// Host=localhost;Port=5432;Database=festival;Username=postgres;Password=root;

using System.Diagnostics;
using csharp.domain;
using csharp.repository;
using System.Configuration;
using Serilog;

Log.Logger = new LoggerConfiguration()
    .WriteTo.Console()
    .CreateLogger();

string connectionString = ConfigurationManager.ConnectionStrings["db"].ConnectionString;

IUserRepository userDatabaseRepository = new UserDatabaseRepositoryImpl(connectionString);
Console.WriteLine(userDatabaseRepository.FindOne(7L).Email);

IConcertRepository concertDatabaseRepository = new ConcertDatabaseRepositoryImpl(connectionString);
Console.WriteLine(concertDatabaseRepository.FindOne(1L).Date);

ITicketRepository ticketDatabaseRepository = new TicketDatabaseRepositoryImpl(connectionString);
Console.WriteLine(ticketDatabaseRepository.FindOne(1L).Buyer);