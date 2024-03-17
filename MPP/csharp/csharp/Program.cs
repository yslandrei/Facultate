// See https://aka.ms/new-console-template for more information

// Host=localhost;Port=5432;Database=festival;Username=postgres;Password=root;

using System.Diagnostics;
using csharp.domain;
using csharp.repository;

string con_string = "Host=localhost;Port=5432;Database=festival;Username=postgres;Password=root;";

UserDatabaseRepository userDatabaseRepository = new UserDatabaseRepository(con_string);
Console.WriteLine(userDatabaseRepository.FindOne(1L).Email);

ConcertDatabaseRepository concertDatabaseRepository = new ConcertDatabaseRepository(con_string);
Console.WriteLine(concertDatabaseRepository.FindOne(1L).Date);

TicketDatabaseRepository ticketDatabaseRepository = new TicketDatabaseRepository(con_string);
Console.WriteLine(ticketDatabaseRepository.FindOne(1L).Concert.Id);