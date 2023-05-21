using System.Diagnostics;
using PuzzleGui.Connectivity;
using PuzzleGui.Puzzles;

namespace PuzzleGui
{
    public partial class MainWindow : Form
    {
        private SolverConnectivity connection;
        private bool initialized = false;
        private IPuzzleSolver sudokuSolver;
        private IPuzzleSolver wordPathDepth;
        private IPuzzleSolver wordPathShort;
        private Process? mySolver = null;

        public MainWindow()
        {
            InitializeComponent();
            SetCellStyles();
            initialized = true;
            connection = new SolverConnectivity();
            sudokuSolver = new Sudoku(connection, sudokuDataGridView, resultTextBox);
            wordPathDepth = new WordPathSolver(connection, wordPathStartTextBox, wordPathEndTextBox, wordPathResultTextBox, resultTextBox, true);
            wordPathShort = new WordPathSolver(connection, wordPathStartTextBox, wordPathEndTextBox, wordPathResultTextBox, resultTextBox, false);
        }

        private void Connect()
        {
            if (connection.Connected)
            {
                connection.Disconnect();
            }
            else
            {
                connection.ConnectToServer();
            }

            button2.BackColor = connection.Connected ? Color.Green : Color.Red;
            button2.Text = connection.Connected ? "Disconnect" : "Connect";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Connect();
        }

        private void solveSudokuButton_Click(object sender, EventArgs e)
        {
            sudokuSolver.Solve();
        }

        private void sudokuDataGridView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (!initialized)
            {
                return;
            }
            sudokuSolver.GridValueChanged(sender, e);
        }

        private string resolveFilePath()
        {
            int runCount = 0;
            while (runCount < 2)
            {
                string filePath = Path.GetDirectoryName(Application.ExecutablePath);
                bool isx86 = false;
                bool isDebug = false;
#if X86
            isx86 = true;
#endif
#if DEBUG
                isDebug = true;
#endif
                filePath = Path.Combine(filePath, runCount == 0 ? @"..\..\..\..\" : @"..\..\..\..\..\");
                if (!isx86)
                {
                    filePath = Path.Combine(filePath, @"x64\");
                }

                filePath = Path.Combine(filePath, isDebug ? @"Debug\CppSolvers.exe" : @"Release\CppSolvers.exe");

                if (File.Exists(filePath))
                {
                    return filePath;
                }
                ++runCount;
            }

            return string.Empty;
        }

        private void startSolverButton_Click(object sender, EventArgs e)
        {
            string filePath = resolveFilePath();

            if (!File.Exists(filePath))
            {
                resultTextBox.AppendText($"File not found {filePath}{Environment.NewLine}");
                return;
            }

            mySolver = new Process();
            mySolver.StartInfo.FileName = filePath;
            mySolver.StartInfo.WorkingDirectory = Path.GetDirectoryName(filePath);
            if (mySolver.Start())
            {
                resultTextBox.AppendText($"Solver is started from {filePath}.{Environment.NewLine}");
                Connect();
            }
            else
            {
                resultTextBox.AppendText($"Solver failed to start from {filePath}.");
                mySolver = null;
            }
        }

        private void checkButton_Click(object sender, EventArgs e)
        {
            ((Sudoku)sudokuSolver).Validate();
        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            ((Sudoku)sudokuSolver).ClearGrid();
        }

        private void MainWindow_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (mySolver != null)
            {
                mySolver.Kill();
            }
        }

        private void wordPathDepthButton_Click(object sender, EventArgs e)
        {
            wordPathDepth.Solve();
        }

        private void wordPathShortestButton_Click(object sender, EventArgs e)
        {
            wordPathShort.Solve();
        }
    }
}