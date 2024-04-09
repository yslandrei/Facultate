namespace lab1
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            dataGridView1 = new DataGridView();
            buttonFirst = new Button();
            buttonPrev = new Button();
            buttonNext = new Button();
            buttonLast = new Button();
            labelRecord = new Label();
            dataGridChildView = new DataGridView();
            buttonAdd = new Button();
            buttonDelete = new Button();
            buttonUpdate = new Button();
            panel1 = new Panel();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridChildView).BeginInit();
            SuspendLayout();
            // 
            // dataGridView1
            // 
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Location = new Point(23, 25);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.Size = new Size(389, 342);
            dataGridView1.TabIndex = 0;
            dataGridView1.CellClick += dataGridView1_CellClick;
            // 
            // buttonFirst
            // 
            buttonFirst.Location = new Point(48, 373);
            buttonFirst.Name = "buttonFirst";
            buttonFirst.Size = new Size(75, 23);
            buttonFirst.TabIndex = 1;
            buttonFirst.Text = "First";
            buttonFirst.UseVisualStyleBackColor = true;
            buttonFirst.Click += buttonFirst_Click;
            // 
            // buttonPrev
            // 
            buttonPrev.Location = new Point(129, 373);
            buttonPrev.Name = "buttonPrev";
            buttonPrev.Size = new Size(75, 23);
            buttonPrev.TabIndex = 2;
            buttonPrev.Text = "Previous";
            buttonPrev.UseVisualStyleBackColor = true;
            buttonPrev.Click += buttonPrev_Click;
            // 
            // buttonNext
            // 
            buttonNext.Location = new Point(210, 373);
            buttonNext.Name = "buttonNext";
            buttonNext.Size = new Size(75, 23);
            buttonNext.TabIndex = 3;
            buttonNext.Text = "Next";
            buttonNext.UseVisualStyleBackColor = true;
            buttonNext.Click += buttonNext_Click;
            // 
            // buttonLast
            // 
            buttonLast.Location = new Point(291, 373);
            buttonLast.Name = "buttonLast";
            buttonLast.Size = new Size(75, 23);
            buttonLast.TabIndex = 4;
            buttonLast.Text = "Last";
            buttonLast.UseVisualStyleBackColor = true;
            buttonLast.Click += buttonLast_Click;
            // 
            // labelRecord
            // 
            labelRecord.AutoSize = true;
            labelRecord.Location = new Point(23, 7);
            labelRecord.Name = "labelRecord";
            labelRecord.Size = new Size(44, 15);
            labelRecord.TabIndex = 5;
            labelRecord.Text = "Record";
            // 
            // dataGridChildView
            // 
            dataGridChildView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridChildView.Location = new Point(435, 25);
            dataGridChildView.Name = "dataGridChildView";
            dataGridChildView.Size = new Size(343, 181);
            dataGridChildView.TabIndex = 6;
            dataGridChildView.CellClick += dataGridChildView_CellClick;
            // 
            // buttonAdd
            // 
            buttonAdd.Location = new Point(448, 221);
            buttonAdd.Name = "buttonAdd";
            buttonAdd.Size = new Size(75, 23);
            buttonAdd.TabIndex = 11;
            buttonAdd.Text = "Add";
            buttonAdd.UseVisualStyleBackColor = true;
            buttonAdd.Click += buttonAdd_Click;
            // 
            // buttonDelete
            // 
            buttonDelete.Location = new Point(679, 221);
            buttonDelete.Name = "buttonDelete";
            buttonDelete.Size = new Size(75, 23);
            buttonDelete.TabIndex = 12;
            buttonDelete.Text = "Delete";
            buttonDelete.UseVisualStyleBackColor = true;
            buttonDelete.Click += buttonDelete_Click;
            // 
            // buttonUpdate
            // 
            buttonUpdate.Location = new Point(564, 221);
            buttonUpdate.Name = "buttonUpdate";
            buttonUpdate.Size = new Size(75, 23);
            buttonUpdate.TabIndex = 13;
            buttonUpdate.Text = "Update";
            buttonUpdate.UseVisualStyleBackColor = true;
            buttonUpdate.Click += buttonUpdate_Click;
            // 
            // panel1
            // 
            panel1.Location = new Point(448, 262);
            panel1.Name = "panel1";
            panel1.Size = new Size(306, 134);
            panel1.TabIndex = 14;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(panel1);
            Controls.Add(buttonUpdate);
            Controls.Add(buttonDelete);
            Controls.Add(buttonAdd);
            Controls.Add(dataGridChildView);
            Controls.Add(labelRecord);
            Controls.Add(buttonLast);
            Controls.Add(buttonNext);
            Controls.Add(buttonPrev);
            Controls.Add(buttonFirst);
            Controls.Add(dataGridView1);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridChildView).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private DataGridView dataGridView1;
        private Button buttonFirst;
        private Button buttonPrev;
        private Button buttonNext;
        private Button buttonLast;
        private Label labelRecord;
        private DataGridView dataGridChildView;
        private Button buttonAdd;
        private Button buttonDelete;
        private Button buttonUpdate;
        private Panel panel1;
    }
}
