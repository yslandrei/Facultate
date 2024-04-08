using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Windows.Forms.Design;
using Serilog;
using WindowsFormsApp1.domain;
using WindowsFormsApp1.repository;
using WindowsFormsApp1.service;


namespace WindowsFormsApp1
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Log.Logger = new LoggerConfiguration()
                .WriteTo.Console()
                .CreateLogger();
            
            string connectionString = ConfigurationManager.ConnectionStrings["db"].ConnectionString;
            IUserRepository userRepository = new UserDatabaseRepository(connectionString);
            IConcertRepository concertRepository = new ConcertDatabaseRepository(connectionString);
            ITicketRepository ticketRepository = new TicketDatabaseRepository(connectionString, concertRepository, userRepository);
            
            IUserService userService = new UserService(userRepository);
            IConcertService concertService = new ConcertService(concertRepository);
            ITicketService ticketService = new TicketService(concertRepository, ticketRepository);
            
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false); 
            Application.Run(new LogInSignUpForm(userService, concertService, ticketService));
            
        }
    }
}