using System.Data;
using System.Data.SqlClient;
using System.Diagnostics;
using System.Reflection.Emit;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;
using System.Configuration;
using Label = System.Windows.Forms.Label;

namespace lab1
    {
    public partial class Form1 : Form
    {
        SqlConnection cs = new SqlConnection(ConfigurationManager.ConnectionStrings["cn"].ConnectionString);
        SqlDataAdapter da = new SqlDataAdapter();

        DataSet ds = new DataSet();
        BindingSource bs = new BindingSource();

        DataSet dsChild = new DataSet();
        BindingSource bsChild = new BindingSource();

        string parentTable = ConfigurationManager.AppSettings["ParentTable"];
        string[] columnNamesParent = ConfigurationManager.AppSettings["ColumnNamesParent"].Split(';');

        string childTable = ConfigurationManager.AppSettings["ChildTable"];
        string[] columnNamesChild = ConfigurationManager.AppSettings["ColumnNamesChild"].Split(';');

        string selectParentCommand;
        string selectChildCommand;
        string insertChildCommand;
        string updateChildCommand;
        string deleteChildCommand;

        Dictionary<string, TextBox> textBoxes = new Dictionary<string, TextBox>();

        public Form1()
        {
            InitializeComponent();
        }

        private void InitializeCommands()
        {
            selectParentCommand = "select id, ";
            for (int i = 0; i < columnNamesParent.Length; i++)
            {
                selectParentCommand += columnNamesParent[i];
                selectParentCommand += i < columnNamesParent.Length - 1 ? ", " : " ";
            }
            selectParentCommand = selectParentCommand + "from " + parentTable;

            selectChildCommand = "select id, ";
            insertChildCommand = $"insert into {childTable} (";
            updateChildCommand = $"update {childTable} set ";
            deleteChildCommand = $"delete from {childTable} where id = @id";
            for (int i = 0; i < columnNamesChild.Length; i++)
            {
                selectChildCommand += columnNamesChild[i] + (i < columnNamesChild.Length - 1 ? ", " : $" from {childTable} where {parentTable}_id = {{0}}");
                insertChildCommand += columnNamesChild[i] + (i < columnNamesChild.Length - 1 ? ", " : $", {parentTable}_id) values (");
                updateChildCommand += columnNamesChild[i] + " = @" + columnNamesChild[i] + (i < columnNamesChild.Length - 1 ? ", " : " where id = @id");
            }
            for (int i = 0; i < columnNamesChild.Length; i++)
            {
                insertChildCommand += "@" + columnNamesChild[i] + (i < columnNamesChild.Length - 1 ? ", " : ", @f_id)");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            InitializeCommands();

            da.SelectCommand = new SqlCommand(selectParentCommand, cs);
            ds.Clear();
            da.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0];
            bs.DataSource = ds.Tables[0];
            
            int f_id = int.Parse(dataGridView1.Rows[0].Cells[0].Value.ToString());
            da.SelectCommand = new SqlCommand(string.Format(selectChildCommand, f_id), cs);
            dsChild.Clear();
            da.Fill(dsChild);
            dataGridChildView.DataSource = dsChild.Tables[0];
            bsChild.DataSource = dsChild.Tables[0];

            int k = 1;
            foreach (string column in columnNamesChild)
            {
                Label label = new Label();
                label.Text = column;
                label.Location = new Point(0, (k - 1) * 30);
                label.Size = new Size(70, 30);
                labelRecord.Text = column;
                textBoxes.Add(column, new TextBox());
                if (dataGridChildView.Rows.Count > 1)
                    textBoxes[column].Text = dataGridChildView.Rows[0].Cells[k].Value.ToString();
                else
                    textBoxes[column].Text = "";
                textBoxes[column].Location = new Point(70, (k - 1) * 30);
                k++;
                panel1.Controls.Add(label);
                panel1.Controls.Add(textBoxes[column]);
            }

            labelRecord.Text = "Record " + (bs.Position + 1) + " of " + bs.Count;
        }

        private void records()
        {
            labelRecord.Text = "Record " + (bs.Position + 1) + " of " + bs.Count;
        }

        private void dataGridView1Update()
        {
            dataGridView1.ClearSelection();
            dataGridView1.Rows[bs.Position].Selected = true;
            records();
            dataGridChildViewUpdate();
        }

        private void dataGridChildViewUpdate()
        {
            int f_id = int.Parse(dataGridView1.SelectedRows[0].Cells[0].Value.ToString());
            da.SelectCommand = new SqlCommand(string.Format(selectChildCommand, f_id), cs);
            dsChild.Clear();
            da.Fill(dsChild);
            dataGridChildView.DataSource = dsChild.Tables[0];
            bsChild.DataSource = dsChild.Tables[0];

            int k = 1;
            foreach (string column in textBoxes.Keys)
            {
                if (dataGridChildView.Rows.Count > 1)
                    textBoxes[column].Text = dataGridChildView.Rows[0].Cells[k].Value.ToString();
                else
                    textBoxes[column].Text = "";
                k++;
            }
        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0 && e.RowIndex < bs.Count)
            {
                dataGridView1.ClearSelection();
                bs.Position = e.RowIndex;
                dataGridView1.Rows[e.RowIndex].Selected = true;
                dataGridChildViewUpdate();
                records();
            }
            
        }

        private void dataGridChildView_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            bsChild.Position = e.RowIndex;
            dataGridChildView.ClearSelection();
            dataGridChildView.Rows[e.RowIndex].Selected = true;

            int k = 1;
            foreach (string column in textBoxes.Keys)
            {
                textBoxes[column].Text = dataGridChildView.Rows[e.RowIndex].Cells[k].Value.ToString();
                k++;
            }
        }


        private void buttonFirst_Click(object sender, EventArgs e)
        {
            bs.MoveFirst();
            dataGridView1Update();
            dataGridChildViewUpdate();
            records();
        }

        private void buttonPrev_Click(object sender, EventArgs e)
        {
            bs.MovePrevious();
            dataGridView1Update();
            dataGridChildViewUpdate();
            records();
        }

        private void buttonNext_Click(object sender, EventArgs e)
        {
            bs.MoveNext();
            dataGridView1Update();
            dataGridChildViewUpdate();
            records();
        }

        private void buttonLast_Click(object sender, EventArgs e)
        {
            bs.MoveLast();
            dataGridView1Update();
            dataGridChildViewUpdate();
            records();
        }

        private bool validateTextBoxes()
        {
            return true;
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            if (validateTextBoxes())
            {
                da.InsertCommand = new SqlCommand(insertChildCommand, cs);

                for (int i = 0; i < columnNamesChild.Length; i ++)
                {
                    da.InsertCommand.Parameters.Add("@" + columnNamesChild[i], SqlDbType.VarChar).Value = textBoxes[columnNamesChild[i]].Text;
                }

                da.InsertCommand.Parameters.Add("@f_id", SqlDbType.VarChar).Value = ds.Tables[0].Rows[bs.Position][0];
                cs.Open();
                da.InsertCommand.ExecuteNonQuery();
                cs.Close();
                dsChild.Clear();
                da.Fill(dsChild);
            }
        }

        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            if (validateTextBoxes())
            {
                da.UpdateCommand = new SqlCommand(updateChildCommand, cs);
                
                for (int i = 0; i < columnNamesChild.Length; i++)
                {
                    da.UpdateCommand.Parameters.Add("@" + columnNamesChild[i], SqlDbType.VarChar).Value = textBoxes[columnNamesChild[i]].Text;
                }

                da.UpdateCommand.Parameters.Add("@id", SqlDbType.VarChar).Value = dsChild.Tables[0].Rows[bsChild.Position][0];
                cs.Open();
                da.UpdateCommand.ExecuteNonQuery();
                cs.Close();
                dsChild.Clear();
                da.Fill(dsChild);
            }
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            da.DeleteCommand = new SqlCommand(deleteChildCommand, cs);
            da.DeleteCommand.Parameters.Add("@id", SqlDbType.Int).Value = dsChild.Tables[0].Rows[bsChild.Position][0];
            cs.Open();
            da.DeleteCommand.ExecuteNonQuery();
            cs.Close();
            dsChild.Clear();
            da.Fill(dsChild);
        }
    }
}
