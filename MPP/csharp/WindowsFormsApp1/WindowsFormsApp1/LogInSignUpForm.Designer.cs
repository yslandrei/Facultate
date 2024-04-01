namespace WindowsFormsApp1
{
    partial class LogInSignUpForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

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
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxLogInEmail = new System.Windows.Forms.TextBox();
            this.textBoxLogInPassword = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxSignUpPassword = new System.Windows.Forms.TextBox();
            this.textBoxSignUpEmail = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.textBoxSignUpName = new System.Windows.Forms.TextBox();
            this.buttonLogIn = new System.Windows.Forms.Button();
            this.buttonSignUp = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 40F, System.Drawing.FontStyle.Bold);
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(538, 63);
            this.label1.TabIndex = 0;
            this.label1.Text = "Festival Tickets";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // textBoxLogInEmail
            // 
            this.textBoxLogInEmail.Location = new System.Drawing.Point(103, 163);
            this.textBoxLogInEmail.Name = "textBoxLogInEmail";
            this.textBoxLogInEmail.Size = new System.Drawing.Size(119, 20);
            this.textBoxLogInEmail.TabIndex = 1;
            // 
            // textBoxLogInPassword
            // 
            this.textBoxLogInPassword.Location = new System.Drawing.Point(103, 198);
            this.textBoxLogInPassword.Name = "textBoxLogInPassword";
            this.textBoxLogInPassword.PasswordChar = '*';
            this.textBoxLogInPassword.Size = new System.Drawing.Size(119, 20);
            this.textBoxLogInPassword.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(44, 163);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 19);
            this.label2.TabIndex = 3;
            this.label2.Text = "Email";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(44, 199);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 19);
            this.label3.TabIndex = 4;
            this.label3.Text = "Password";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(300, 215);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 19);
            this.label4.TabIndex = 8;
            this.label4.Text = "Password";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(300, 179);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 19);
            this.label5.TabIndex = 7;
            this.label5.Text = "Email";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // textBoxSignUpPassword
            // 
            this.textBoxSignUpPassword.Location = new System.Drawing.Point(359, 214);
            this.textBoxSignUpPassword.Name = "textBoxSignUpPassword";
            this.textBoxSignUpPassword.PasswordChar = '*';
            this.textBoxSignUpPassword.Size = new System.Drawing.Size(119, 20);
            this.textBoxSignUpPassword.TabIndex = 6;
            // 
            // textBoxSignUpEmail
            // 
            this.textBoxSignUpEmail.Location = new System.Drawing.Point(359, 179);
            this.textBoxSignUpEmail.Name = "textBoxSignUpEmail";
            this.textBoxSignUpEmail.Size = new System.Drawing.Size(119, 20);
            this.textBoxSignUpEmail.TabIndex = 5;
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(300, 144);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(59, 19);
            this.label6.TabIndex = 10;
            this.label6.Text = "Name";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // textBoxSignUpName
            // 
            this.textBoxSignUpName.Location = new System.Drawing.Point(359, 144);
            this.textBoxSignUpName.Name = "textBoxSignUpName";
            this.textBoxSignUpName.Size = new System.Drawing.Size(119, 20);
            this.textBoxSignUpName.TabIndex = 9;
            // 
            // buttonLogIn
            // 
            this.buttonLogIn.Location = new System.Drawing.Point(115, 252);
            this.buttonLogIn.Name = "buttonLogIn";
            this.buttonLogIn.Size = new System.Drawing.Size(90, 24);
            this.buttonLogIn.TabIndex = 11;
            this.buttonLogIn.Text = "Log In";
            this.buttonLogIn.UseVisualStyleBackColor = true;
            this.buttonLogIn.Click += new System.EventHandler(this.buttonLogIn_Click);
            // 
            // buttonSignUp
            // 
            this.buttonSignUp.Location = new System.Drawing.Point(374, 252);
            this.buttonSignUp.Name = "buttonSignUp";
            this.buttonSignUp.Size = new System.Drawing.Size(90, 24);
            this.buttonSignUp.TabIndex = 12;
            this.buttonSignUp.Text = "Sign Up";
            this.buttonSignUp.UseVisualStyleBackColor = true;
            this.buttonSignUp.Click += new System.EventHandler(this.buttonSignUp_Click);
            // 
            // LogInSignUpForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(562, 364);
            this.Controls.Add(this.buttonSignUp);
            this.Controls.Add(this.buttonLogIn);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.textBoxSignUpName);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBoxSignUpPassword);
            this.Controls.Add(this.textBoxSignUpEmail);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBoxLogInPassword);
            this.Controls.Add(this.textBoxLogInEmail);
            this.Controls.Add(this.label1);
            this.Location = new System.Drawing.Point(15, 15);
            this.Name = "LogInSignUpForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        private System.Windows.Forms.Button buttonLogIn;
        private System.Windows.Forms.Button buttonSignUp;

        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBoxSignUpName;

        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxSignUpPassword;
        private System.Windows.Forms.TextBox textBoxSignUpEmail;

        private System.Windows.Forms.Label label3;

        private System.Windows.Forms.Label label2;

        private System.Windows.Forms.TextBox textBoxLogInPassword;

        private System.Windows.Forms.TextBox textBoxLogInEmail;

        private System.Windows.Forms.Label label1;

        #endregion
    }
}