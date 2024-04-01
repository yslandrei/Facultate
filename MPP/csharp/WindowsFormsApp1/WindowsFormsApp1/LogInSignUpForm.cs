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

namespace WindowsFormsApp1
{
    public partial class LogInSignUpForm : Form
    {
        private IUserService _userService;

        private IConcertService _concertService;
        
        private ITicketService _ticketService;
        
        public LogInSignUpForm(IUserService userService, IConcertService concertService, ITicketService ticketService)
        {
            _userService = userService;
            _concertService = concertService;
            _ticketService = ticketService;
            InitializeComponent();
        }

        private void buttonLogIn_Click(object sender, EventArgs e)
        {
            if (textBoxLogInEmail.Text.Length == 0)
            {
                MessageBox.Show("Email text box can't be empty", "Error", MessageBoxButtons.OK);
                return;
            }
            if (textBoxLogInPassword.Text.Length == 0)
            {
                MessageBox.Show("Password text box can't be empty", "Error", MessageBoxButtons.OK);
                return;
            }

            User user = _userService.LogInUser(textBoxLogInEmail.Text, textBoxLogInPassword.Text);
            TicketView ticketView = new TicketView(_userService, _concertService, _ticketService, user);
            ticketView.Show();
        }

        private void buttonSignUp_Click(object sender, EventArgs e)
        {
            if (textBoxSignUpName.Text.Length == 0)
            {
                MessageBox.Show("Name text box can't be empty", "Error", MessageBoxButtons.OK);
                return;
            }
            if (textBoxSignUpEmail.Text.Length == 0)
            {
                MessageBox.Show("Email text box can't be empty", "Error", MessageBoxButtons.OK);
                return;
            }
            if (textBoxSignUpPassword.Text.Length == 0)
            {
                MessageBox.Show("Password text box can't be empty", "Error", MessageBoxButtons.OK);
                return;
            }
            User user = _userService.RegisterUser(new User(textBoxSignUpName.Text, textBoxSignUpEmail.Text, textBoxSignUpPassword.Text));
            TicketView ticketView = new TicketView(_userService, _concertService, _ticketService, user);
            ticketView.Show();
        }
    }
}