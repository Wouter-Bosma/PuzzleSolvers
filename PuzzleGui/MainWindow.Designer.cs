namespace PuzzleGui
{
    partial class MainWindow
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

        private int SquareNum(int row, int column)
        {
            return (column / 3) * 3 + row / 3;
        }

        private void SetCellStyles()
        {
            sudokuDataGridView.Rows.Add(9);
            for (int column = 0; column < 9; ++column)
            {
                for (int row = 0; row < 9; ++row)
                {
                    sudokuDataGridView.Rows[row].Cells[column].Style.BackColor = SquareNum(row, column) % 2 == 0 ? Color.White : Color.Gray;
                }
            }
        }

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            mainWindowControl = new TabControl();
            tabPage1 = new TabPage();
            startSolverButton = new Button();
            button2 = new Button();
            sudokuPage = new TabPage();
            clearButton = new Button();
            checkButton = new Button();
            solveSudokuButton = new Button();
            sudokuDataGridView = new DataGridView();
            Column1 = new DataGridViewTextBoxColumn();
            Column2 = new DataGridViewTextBoxColumn();
            Column3 = new DataGridViewTextBoxColumn();
            Column4 = new DataGridViewTextBoxColumn();
            Column5 = new DataGridViewTextBoxColumn();
            Column6 = new DataGridViewTextBoxColumn();
            Column7 = new DataGridViewTextBoxColumn();
            Column8 = new DataGridViewTextBoxColumn();
            Column9 = new DataGridViewTextBoxColumn();
            resultTextBox = new TextBox();
            label1 = new Label();
            label2 = new Label();
            textBox1 = new TextBox();
            mainWindowControl.SuspendLayout();
            tabPage1.SuspendLayout();
            sudokuPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)sudokuDataGridView).BeginInit();
            SuspendLayout();
            // 
            // mainWindowControl
            // 
            mainWindowControl.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            mainWindowControl.Controls.Add(tabPage1);
            mainWindowControl.Controls.Add(sudokuPage);
            mainWindowControl.Location = new Point(0, 0);
            mainWindowControl.Margin = new Padding(3, 2, 3, 2);
            mainWindowControl.Name = "mainWindowControl";
            mainWindowControl.SelectedIndex = 0;
            mainWindowControl.Size = new Size(700, 323);
            mainWindowControl.TabIndex = 0;
            // 
            // tabPage1
            // 
            tabPage1.Controls.Add(label2);
            tabPage1.Controls.Add(label1);
            tabPage1.Controls.Add(startSolverButton);
            tabPage1.Controls.Add(button2);
            tabPage1.Location = new Point(4, 24);
            tabPage1.Margin = new Padding(3, 2, 3, 2);
            tabPage1.Name = "tabPage1";
            tabPage1.Padding = new Padding(3, 2, 3, 2);
            tabPage1.Size = new Size(692, 295);
            tabPage1.TabIndex = 0;
            tabPage1.Text = "Connectivity";
            tabPage1.UseVisualStyleBackColor = true;
            // 
            // startSolverButton
            // 
            startSolverButton.BackColor = Color.LightGray;
            startSolverButton.Location = new Point(3, 0);
            startSolverButton.Margin = new Padding(3, 2, 3, 2);
            startSolverButton.Name = "startSolverButton";
            startSolverButton.Size = new Size(82, 26);
            startSolverButton.TabIndex = 1;
            startSolverButton.Text = "Start";
            startSolverButton.UseVisualStyleBackColor = false;
            startSolverButton.Click += startSolverButton_Click;
            // 
            // button2
            // 
            button2.BackColor = Color.Red;
            button2.Location = new Point(3, 69);
            button2.Margin = new Padding(3, 2, 3, 2);
            button2.Name = "button2";
            button2.Size = new Size(82, 26);
            button2.TabIndex = 0;
            button2.Text = "Connect";
            button2.UseVisualStyleBackColor = false;
            button2.Click += button2_Click;
            // 
            // sudokuPage
            // 
            sudokuPage.Controls.Add(textBox1);
            sudokuPage.Controls.Add(clearButton);
            sudokuPage.Controls.Add(checkButton);
            sudokuPage.Controls.Add(solveSudokuButton);
            sudokuPage.Controls.Add(sudokuDataGridView);
            sudokuPage.Location = new Point(4, 24);
            sudokuPage.Margin = new Padding(3, 2, 3, 2);
            sudokuPage.Name = "sudokuPage";
            sudokuPage.Padding = new Padding(3, 2, 3, 2);
            sudokuPage.Size = new Size(692, 295);
            sudokuPage.TabIndex = 1;
            sudokuPage.Text = "Sudoku";
            sudokuPage.UseVisualStyleBackColor = true;
            // 
            // clearButton
            // 
            clearButton.Location = new Point(237, 60);
            clearButton.Margin = new Padding(3, 2, 3, 2);
            clearButton.Name = "clearButton";
            clearButton.Size = new Size(82, 22);
            clearButton.TabIndex = 3;
            clearButton.Text = "Clear";
            clearButton.UseVisualStyleBackColor = true;
            clearButton.Click += clearButton_Click;
            // 
            // checkButton
            // 
            checkButton.Location = new Point(237, 34);
            checkButton.Margin = new Padding(3, 2, 3, 2);
            checkButton.Name = "checkButton";
            checkButton.Size = new Size(82, 22);
            checkButton.TabIndex = 2;
            checkButton.Text = "Check";
            checkButton.UseVisualStyleBackColor = true;
            checkButton.Click += checkButton_Click;
            // 
            // solveSudokuButton
            // 
            solveSudokuButton.Location = new Point(237, 8);
            solveSudokuButton.Margin = new Padding(3, 2, 3, 2);
            solveSudokuButton.Name = "solveSudokuButton";
            solveSudokuButton.Size = new Size(82, 22);
            solveSudokuButton.TabIndex = 1;
            solveSudokuButton.Text = "Solve";
            solveSudokuButton.UseVisualStyleBackColor = true;
            solveSudokuButton.Click += solveSudokuButton_Click;
            // 
            // sudokuDataGridView
            // 
            sudokuDataGridView.AllowUserToAddRows = false;
            sudokuDataGridView.AllowUserToDeleteRows = false;
            sudokuDataGridView.ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle.None;
            sudokuDataGridView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            sudokuDataGridView.ColumnHeadersVisible = false;
            sudokuDataGridView.Columns.AddRange(new DataGridViewColumn[] { Column1, Column2, Column3, Column4, Column5, Column6, Column7, Column8, Column9 });
            sudokuDataGridView.Location = new Point(3, 2);
            sudokuDataGridView.Margin = new Padding(3, 2, 3, 2);
            sudokuDataGridView.Name = "sudokuDataGridView";
            sudokuDataGridView.RowHeadersVisible = false;
            sudokuDataGridView.RowHeadersWidth = 51;
            sudokuDataGridView.RowTemplate.Height = 29;
            sudokuDataGridView.ScrollBars = ScrollBars.None;
            sudokuDataGridView.Size = new Size(228, 264);
            sudokuDataGridView.TabIndex = 0;
            sudokuDataGridView.CellValueChanged += sudokuDataGridView_CellValueChanged;
            // 
            // Column1
            // 
            Column1.HeaderText = "Column1";
            Column1.MinimumWidth = 6;
            Column1.Name = "Column1";
            Column1.Width = 25;
            // 
            // Column2
            // 
            Column2.HeaderText = "Column2";
            Column2.MinimumWidth = 6;
            Column2.Name = "Column2";
            Column2.Width = 25;
            // 
            // Column3
            // 
            Column3.HeaderText = "Column3";
            Column3.MinimumWidth = 6;
            Column3.Name = "Column3";
            Column3.Width = 25;
            // 
            // Column4
            // 
            Column4.HeaderText = "Column4";
            Column4.MinimumWidth = 6;
            Column4.Name = "Column4";
            Column4.Width = 25;
            // 
            // Column5
            // 
            Column5.HeaderText = "Column5";
            Column5.MinimumWidth = 6;
            Column5.Name = "Column5";
            Column5.Width = 25;
            // 
            // Column6
            // 
            Column6.HeaderText = "Column6";
            Column6.MinimumWidth = 6;
            Column6.Name = "Column6";
            Column6.Width = 25;
            // 
            // Column7
            // 
            Column7.HeaderText = "Column7";
            Column7.MinimumWidth = 6;
            Column7.Name = "Column7";
            Column7.Width = 25;
            // 
            // Column8
            // 
            Column8.HeaderText = "Column8";
            Column8.MinimumWidth = 6;
            Column8.Name = "Column8";
            Column8.Width = 25;
            // 
            // Column9
            // 
            Column9.HeaderText = "Column9";
            Column9.MinimumWidth = 6;
            Column9.Name = "Column9";
            Column9.Width = 25;
            // 
            // resultTextBox
            // 
            resultTextBox.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            resultTextBox.Location = new Point(4, 323);
            resultTextBox.Margin = new Padding(3, 2, 3, 2);
            resultTextBox.Multiline = true;
            resultTextBox.Name = "resultTextBox";
            resultTextBox.ReadOnly = true;
            resultTextBox.Size = new Size(692, 57);
            resultTextBox.TabIndex = 2;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(91, 7);
            label1.Name = "label1";
            label1.Size = new Size(444, 15);
            label1.TabIndex = 2;
            label1.Text = "Button to automatically start the c++ executable with the solvers and connect to it.";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(91, 75);
            label2.Name = "label2";
            label2.Size = new Size(421, 15);
            label2.TabIndex = 3;
            label2.Text = "When the solver is manually launched this button can be used to connect to it.";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(325, 8);
            textBox1.Multiline = true;
            textBox1.Name = "textBox1";
            textBox1.ReadOnly = true;
            textBox1.Size = new Size(361, 189);
            textBox1.TabIndex = 4;
            textBox1.Text = resources.GetString("textBox1.Text");
            // 
            // MainWindow
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(700, 391);
            Controls.Add(resultTextBox);
            Controls.Add(mainWindowControl);
            Margin = new Padding(3, 2, 3, 2);
            Name = "MainWindow";
            Text = "Form1";
            FormClosed += MainWindow_FormClosed;
            mainWindowControl.ResumeLayout(false);
            tabPage1.ResumeLayout(false);
            tabPage1.PerformLayout();
            sudokuPage.ResumeLayout(false);
            sudokuPage.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)sudokuDataGridView).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TabControl mainWindowControl;
        private TabPage tabPage1;
        private TabPage sudokuPage;
        private DataGridView sudokuDataGridView;
        private DataGridViewTextBoxColumn Column1;
        private DataGridViewTextBoxColumn Column2;
        private DataGridViewTextBoxColumn Column3;
        private DataGridViewTextBoxColumn Column4;
        private DataGridViewTextBoxColumn Column5;
        private DataGridViewTextBoxColumn Column6;
        private DataGridViewTextBoxColumn Column7;
        private DataGridViewTextBoxColumn Column8;
        private DataGridViewTextBoxColumn Column9;
        private Button solveSudokuButton;
        private Button button2;
        private TextBox resultTextBox;
        private Button startSolverButton;
        private Button clearButton;
        private Button checkButton;
        private Label label2;
        private Label label1;
        private TextBox textBox1;
    }
}