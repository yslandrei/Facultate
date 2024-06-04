using System.Data;
using System.Data.SqlClient;
using System.Diagnostics;
using System.Reflection.Emit;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;

namespace lab1
    {
    public partial class Form1 : Form
    {
        SqlConnection cs = new SqlConnection("Data Source=YSLANDREI\\SQLEXPRESS; Initial Catalog = ebay_db_manual; Integrated Security = True");
        SqlDataAdapter da = new SqlDataAdapter();

        DataSet ds = new DataSet();
        BindingSource bs = new BindingSource();

        DataSet dsChild = new DataSet();
        BindingSource bsChild = new BindingSource();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            da.SelectCommand = new SqlCommand("SELECT id, name, email FROM seller", cs);
            ds.Clear();
            da.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0];
            bs.DataSource = ds.Tables[0];

            int seller_id = int.Parse(dataGridView1.Rows[0].Cells[0].Value.ToString());
            da.SelectCommand = new SqlCommand($"SELECT id, name, price FROM product WHERE product.seller_id = {seller_id}", cs);
            dsChild.Clear();
            da.Fill(dsChild);
            dataGridChildView.DataSource = dsChild.Tables[0];
            bsChild.DataSource = dsChild.Tables[0];
            textBoxName.Text = dataGridChildView.Rows[0].Cells[1].Value.ToString();
            textBoxPrice.Text = dataGridChildView.Rows[0].Cells[2].Value.ToString();

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
            int seller_id = int.Parse(dataGridView1.SelectedRows[0].Cells[0].Value.ToString());
            da.SelectCommand = new SqlCommand($"SELECT id, name, price FROM product WHERE product.seller_id = {seller_id}", cs);
            dsChild.Clear();
            da.Fill(dsChild);
            dataGridChildView.DataSource = dsChild.Tables[0];
            bsChild.DataSource = dsChild.Tables[0];
            textBoxName.Text = dataGridChildView.Rows[0].Cells[1].Value.ToString();
            textBoxPrice.Text = dataGridChildView.Rows[0].Cells[2].Value.ToString();
        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex != bs.Count)
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
            dataGridChildView.ClearSelection();
            bsChild.Position = e.RowIndex;
            dataGridChildView.Rows[e.RowIndex].Selected = true;
            textBoxName.Text = dataGridChildView.Rows[e.RowIndex].Cells[1].Value.ToString();
            textBoxPrice.Text = dataGridChildView.Rows[e.RowIndex].Cells[2].Value.ToString();
            //recordsChild();
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
            if (textBoxName.Text.Length == 0)
            {
                MessageBox.Show("Name text box can't be empty", "Error", MessageBoxButtons.OK);
                return false;
            }
            if (textBoxPrice.Text.Length == 0)
            {
                MessageBox.Show("Price text box can't be empty", "Error", MessageBoxButtons.OK);
                return false;
            }
            try
            {
                int.Parse(textBoxPrice.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Price text box needs to be a number", "Error", MessageBoxButtons.OK);
                return false;
            }

            return true;

        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            if (validateTextBoxes())
            {
                da.InsertCommand = new SqlCommand("insert into product (name, created_date, seller_id, category_id, price) values (@n, @c, @sid, @cid, @p)", cs);
                da.InsertCommand.Parameters.Add("@n", SqlDbType.VarChar).Value = textBoxName.Text;
                da.InsertCommand.Parameters.Add("@c", SqlDbType.DateTime).Value = DateTime.Now;
                da.InsertCommand.Parameters.Add("@sid", SqlDbType.BigInt).Value = int.Parse(ds.Tables[0].Rows[bs.Position][0].ToString());
                da.InsertCommand.Parameters.Add("@cid", SqlDbType.BigInt).Value = 1;
                da.InsertCommand.Parameters.Add("@p", SqlDbType.BigInt).Value = textBoxPrice.Text;
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
                da.UpdateCommand = new SqlCommand("update product set name = @n, price = @p where id = @id", cs);
                da.UpdateCommand.Parameters.Add("@n", SqlDbType.VarChar).Value = textBoxName.Text;
                da.UpdateCommand.Parameters.Add("@p", SqlDbType.BigInt).Value = textBoxPrice.Text;
                da.UpdateCommand.Parameters.Add("@id", SqlDbType.BigInt).Value = dsChild.Tables[0].Rows[bsChild.Position][0];
                cs.Open();
                da.UpdateCommand.ExecuteNonQuery();
                cs.Close();
                dsChild.Clear();
                da.Fill(dsChild);
            }
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            da.DeleteCommand = new SqlCommand("delete from product where ID = @id", cs);
            da.DeleteCommand.Parameters.Add("@id", SqlDbType.Int).Value = dsChild.Tables[0].Rows[bsChild.Position][0];
            cs.Open();
            da.DeleteCommand.ExecuteNonQuery();
            cs.Close();
            dsChild.Clear();
            da.Fill(dsChild);
        }

        private void textBoxName_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
