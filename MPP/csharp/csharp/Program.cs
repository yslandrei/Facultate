// See https://aka.ms/new-console-template for more information

// Host=localhost;Port=5432;Database=festival;Username=postgres;Password=root;

using System.Diagnostics;

using csharp.repository;
using Microsoft.Extensions.Configuration;
using Serilog;

Log.Logger = new LoggerConfiguration()
    .WriteTo.Console()
    .CreateLogger();

IConfiguration configuration = new ConfigurationBuilder()
    .AddJsonFile("config.json", optional: true, reloadOnChange: true)
    .Build();

IUserRepository userDatabaseRepository = new UserDatabaseRepositoryImpl(configuration["url"]);
Console.WriteLine(userDatabaseRepository.FindOne(1L).Email);

IConcertRepository concertDatabaseRepository = new ConcertDatabaseRepositoryImpl(configuration["url"]);
Console.WriteLine(concertDatabaseRepository.FindOne(1L).Date);

ITicketRepository ticketDatabaseRepository = new TicketDatabaseRepositoryImpl(configuration["url"]);
Console.WriteLine(ticketDatabaseRepository.FindOne(1L).Concert.Id);