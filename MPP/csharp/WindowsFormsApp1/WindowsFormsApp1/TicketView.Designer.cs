using System.ComponentModel;

namespace WindowsFormsApp1;

partial class TicketView
{
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }

        base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        this.dataGridView1 = new System.Windows.Forms.DataGridView();
        this.id = new System.Windows.Forms.DataGridViewTextBoxColumn();
        this.artist = new System.Windows.Forms.DataGridViewTextBoxColumn();
        this.date = new System.Windows.Forms.DataGridViewTextBoxColumn();
        this.location = new System.Windows.Forms.DataGridViewTextBoxColumn();
        this.availableTickets = new System.Windows.Forms.DataGridViewTextBoxColumn();
        this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
        this.textBoxBuyer = new System.Windows.Forms.TextBox();
        this.textBoxSeats = new System.Windows.Forms.TextBox();
        this.buttonBuy = new System.Windows.Forms.Button();
        this.label1 = new System.Windows.Forms.Label();
        this.label2 = new System.Windows.Forms.Label();
        ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
        this.SuspendLayout();
        // 
        // dataGridView1
        // 
        this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] { this.id, this.artist, this.date, this.location, this.availableTickets });
        this.dataGridView1.Location = new System.Drawing.Point(135, 99);
        this.dataGridView1.Name = "dataGridView1";
        this.dataGridView1.Size = new System.Drawing.Size(542, 272);
        this.dataGridView1.TabIndex = 1;
        this.dataGridView1.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellClick);
        // 
        // id
        // 
        this.id.HeaderText = "id";
        this.id.Name = "id";
        // 
        // artist
        // 
        this.artist.HeaderText = "artist";
        this.artist.Name = "artist";
        // 
        // date
        // 
        this.date.HeaderText = "date";
        this.date.Name = "date";
        // 
        // location
        // 
        this.location.HeaderText = "location";
        this.location.Name = "location";
        // 
        // availableTickets
        // 
        this.availableTickets.HeaderText = "availableTickets";
        this.availableTickets.Name = "availableTickets";
        // 
        // dateTimePicker1
        // 
        this.dateTimePicker1.Location = new System.Drawing.Point(241, 43);
        this.dateTimePicker1.Name = "dateTimePicker1";
        this.dateTimePicker1.Size = new System.Drawing.Size(302, 20);
        this.dateTimePicker1.TabIndex = 2;
        this.dateTimePicker1.CloseUp += new System.EventHandler(this.dateTimePicker1_CloseUp);
        // 
        // textBoxBuyer
        // 
        this.textBoxBuyer.Location = new System.Drawing.Point(135, 402);
        this.textBoxBuyer.Name = "textBoxBuyer";
        this.textBoxBuyer.Size = new System.Drawing.Size(114, 20);
        this.textBoxBuyer.TabIndex = 3;
        // 
        // textBoxSeats
        // 
        this.textBoxSeats.Location = new System.Drawing.Point(349, 403);
        this.textBoxSeats.Name = "textBoxSeats";
        this.textBoxSeats.Size = new System.Drawing.Size(110, 20);
        this.textBoxSeats.TabIndex = 4;
        // 
        // buttonBuy
        // 
        this.buttonBuy.Location = new System.Drawing.Point(541, 400);
        this.buttonBuy.Name = "buttonBuy";
        this.buttonBuy.Size = new System.Drawing.Size(98, 21);
        this.buttonBuy.TabIndex = 5;
        this.buttonBuy.Text = "Buy";
        this.buttonBuy.UseVisualStyleBackColor = true;
        this.buttonBuy.Click += new System.EventHandler(this.button1_Click);
        // 
        // label1
        // 
        this.label1.Location = new System.Drawing.Point(79, 404);
        this.label1.Name = "label1";
        this.label1.Size = new System.Drawing.Size(50, 19);
        this.label1.TabIndex = 6;
        this.label1.Text = "Buyer";
        // 
        // label2
        // 
        this.label2.Location = new System.Drawing.Point(302, 408);
        this.label2.Name = "label2";
        this.label2.Size = new System.Drawing.Size(41, 13);
        this.label2.TabIndex = 7;
        this.label2.Text = "Seats";
        // 
        // TicketView
        // 
        this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
        this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        this.ClientSize = new System.Drawing.Size(800, 450);
        this.Controls.Add(this.label2);
        this.Controls.Add(this.label1);
        this.Controls.Add(this.buttonBuy);
        this.Controls.Add(this.textBoxSeats);
        this.Controls.Add(this.textBoxBuyer);
        this.Controls.Add(this.dateTimePicker1);
        this.Controls.Add(this.dataGridView1);
        this.Name = "TicketView";
        this.Text = "Form1";
        this.Load += new System.EventHandler(this.TicketView_Load);
        ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
        this.ResumeLayout(false);
        this.PerformLayout();
    }

    private System.Windows.Forms.TextBox textBoxBuyer;
    private System.Windows.Forms.TextBox textBoxSeats;
    private System.Windows.Forms.Button buttonBuy;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label2;

    private System.Windows.Forms.DateTimePicker dateTimePicker1;

    private System.Windows.Forms.DataGridViewTextBoxColumn id;
    private System.Windows.Forms.DataGridViewTextBoxColumn artist;
    private System.Windows.Forms.DataGridViewTextBoxColumn date;
    private System.Windows.Forms.DataGridViewTextBoxColumn location;
    private System.Windows.Forms.DataGridViewTextBoxColumn availableTickets;

    private System.Windows.Forms.DataGridView dataGridView1;

    #endregion
}