using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using Serilog;
using WindowsFormsApp1.domain;
using WindowsFormsApp1.repository;
using Form1 = WindowsFormsApp1.Form1;


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
            IUserRepository userDatabaseRepository = new UserDatabaseRepository(connectionString);
            IConcertRepository concertDatabaseRepository = new ConcertDatabaseRepository(connectionString);
            ITicketRepository ticketDatabaseRepository = new TicketDatabaseRepository(connectionString, concertDatabaseRepository, userDatabaseRepository);
            
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}