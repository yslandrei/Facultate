using System.Windows.Forms;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WindowsFormsApp1.domain;
using WindowsFormsApp1.service;

namespace WindowsFormsApp1;

public partial class TicketView : Form
{
    private IUserService _userService;

    private IConcertService _concertService;
        
    private ITicketService _ticketService;

    private User _user;
    
    private List<Concert> _shownConcerts;
    
    public TicketView(IUserService userService, IConcertService concertService, ITicketService ticketService, User user)
    {   
        _userService = userService;
        _concertService = concertService;
        _ticketService = ticketService;
        _user = user;
        InitializeComponent();
    }

    private void dateTimePicker1_CloseUp(object sender, EventArgs e)
    {
        DateTime selectedDate = dateTimePicker1.Value;
        _shownConcerts = _concertService.GetConcertsFromDay(selectedDate);
        dataGridView1.Rows.Clear();
        foreach (var concert in _shownConcerts)
        {
            dataGridView1.Rows.Add(concert.Id, concert.Artist, concert.Date, concert.Location,
                concert.AvailableTickets);
            
        }
    }

    private void button1_Click(object sender, EventArgs e)
    {   
        if (textBoxBuyer.Text.Length == 0)
        {
            MessageBox.Show("Buyer text box can't be empty", "Error", MessageBoxButtons.OK);
            return;
        }
        if (textBoxSeats.Text.Length == 0)
        {
            MessageBox.Show("Seats text box can't be empty", "Error", MessageBoxButtons.OK);
            return;
        }
        
        try
        {
            Int32.Parse(textBoxSeats.Text);
        }
        catch (Exception exception)
        {
            MessageBox.Show("Seats text box must be a number", "Error", MessageBoxButtons.OK);
        }

        _ticketService.BuyTicket(_shownConcerts[dataGridView1.SelectedRows[0].Index], _user, textBoxBuyer.Text, Int32.Parse(textBoxSeats.Text));
        DateTime selectedDate = dateTimePicker1.Value;
        _shownConcerts = _concertService.GetConcertsFromDay(selectedDate);
        dataGridView1.Rows.Clear();
        foreach (var concert in _shownConcerts)
        {
            dataGridView1.Rows.Add(concert.Id, concert.Artist, concert.Date, concert.Location,
                concert.AvailableTickets);
            
        }
    }

    private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
    {
        dataGridView1.Rows[dataGridView1.SelectedCells[0].RowIndex].Selected = true;
    }

    private void TicketView_Load(object sender, EventArgs e)
    {
        _shownConcerts = _concertService.GetAllConcerts();
        dataGridView1.Rows.Clear();
        foreach (var concert in _shownConcerts)
        {
            dataGridView1.Rows.Add(concert.Id, concert.Artist, concert.Date, concert.Location,
                concert.AvailableTickets);
        }
    }
}