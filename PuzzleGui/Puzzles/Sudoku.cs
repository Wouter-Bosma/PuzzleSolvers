using System.Text;
using PuzzleGui.Connectivity;

namespace PuzzleGui.Puzzles
{
    internal class Sudoku : IPuzzleSolver
    {
        private DataGridView sudokuGrid;
        private TextBox resultTextBox;
        private SolverConnectivity solverConnectivity;
        public Sudoku(SolverConnectivity solverConnectivity, DataGridView sudokuGrid, TextBox resultTextBox)
        {
            this.sudokuGrid = sudokuGrid;
            this.resultTextBox = resultTextBox;
            this.solverConnectivity = solverConnectivity;
        }
        
        public string Serialize()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("SUDOKU;9");
            for (int row = 0; row < 9; ++row)

            {
                sb.Append(";9");
                for (int column = 0; column < 9; ++column)
                {
                    var value = sudokuGrid.Rows[row].Cells[column].Value;
                    int.TryParse(value?.ToString() ?? string.Empty, out int myVal);
                    sb.Append($";{myVal}");
                }
            }
            return sb.ToString();
        }

        public void ClearGrid()
        {
            for (int row = 0; row < 9; ++row)
            {
                for (int column = 0; column < 9; column++)
                {
                    sudokuGrid.Rows[row].Cells[column].Value = string.Empty;
                }
            }
        }

        private void PlotSudoku(string[] tokens, int counter, int numRows)
        {
            for (int row = 0; row < numRows; ++row)
            {
                if (!int.TryParse(tokens[counter++], out int numColumns) || numColumns != 9)
                {
                    throw new ArgumentException("Not supported number of columns");
                }

                for (int column = 0; column < numColumns; column++)
                {
                    if (!int.TryParse(tokens[counter++], out int value) || value < 0 || value > 9)
                    {
                        throw new ArgumentException("Not supported value in grid");
                    }

                    bool newValue = string.IsNullOrEmpty(sudokuGrid.Rows[row].Cells[column].Value?.ToString());
                    sudokuGrid.Rows[row].Cells[column].Value = value == 0 ? string.Empty : value.ToString();
                    if (newValue)
                    {
                        sudokuGrid.Rows[row].Cells[column].Style.ForeColor = Color.LimeGreen;
                    }
                }
            }
        }

        private void DeserializeString(string[] tokens)
        {
            int counter = 0;
            if (tokens[counter++] != "SUDOKU")
            {
                throw new ArgumentException("Wrong type of string to decode");
            }

            if (tokens[counter++] != "SUCCESS")
            {
                foreach (var token in tokens)
                {
                    resultTextBox.AppendText($"{token};");
                }
                resultTextBox.AppendText($"{Environment.NewLine};");
                return;
            }

            if (!int.TryParse(tokens[counter++], out int numRows) || numRows != 9)
            {
                throw new ArgumentException("Not supported number of rows");
            }
            PlotSudoku(tokens, counter, numRows);
        }

        public void Deserialize(string sudoku)
        {
            if (string.IsNullOrEmpty(sudoku))
            {
                resultTextBox.Text = $@"Received an empty string.{Environment.NewLine}";
                return;
            }
            var tokens = sudoku.Split(';');
            if (tokens.Length != 9 * 10 + 1 + 1 + 1) //92
            {
                resultTextBox.Text = $@"Can't process return {sudoku}{Environment.NewLine}";
                return;
            }

            try
            {
                DeserializeString(tokens);
            }
            catch (Exception e)
            {
                resultTextBox.AppendText(e.ToString());
                ClearGrid();
            }
        }
        
        public void Solve()
        {
            if (!solverConnectivity.Connected)
            {
                resultTextBox.Text = $@"Can't solve sudoku, not connected to the solver.{Environment.NewLine}";
                return;
            }
            var serializedSudoku = Serialize();
            var result = solverConnectivity.SendRequest(serializedSudoku);
            Deserialize(result);
        }

        public bool Validate()
        {
            if (!solverConnectivity.Connected)
            {
                resultTextBox.AppendText($"Can't solve sudoku, not connected to the solver.{Environment.NewLine}");
                return false;
            }

            var serializedSudoku = Serialize();
            var result = solverConnectivity.SendRequest(serializedSudoku);
            if (result.Contains("SUCCESS"))
            {
                resultTextBox.AppendText($"Sudoku is valid{Environment.NewLine}");
                return true;
            }

            resultTextBox.AppendText($"Sudoku is not valid{Environment.NewLine}");
            return false;
        }

        public void GridValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (!(sender is DataGridView myView))
            {
                return;
            }
            int row = (int)e.RowIndex;
            int column = e.ColumnIndex;
            if (!int.TryParse(myView.Rows[row].Cells[column].Value.ToString(), out var myInt) || myInt < 0 || myInt > 9)
            {
                myView.Rows[row].Cells[column].Value = "";
            }

            sudokuGrid.Rows[row].Cells[column].Style.ForeColor = Color.Black;
        }
    }
}
