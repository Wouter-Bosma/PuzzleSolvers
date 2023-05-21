using PuzzleGui.Connectivity;

namespace PuzzleGui.Puzzles
{
    internal class WordPathSolver : IPuzzleSolver
    {
        private TextBox startTextBox;
        private TextBox endTextBox;
        private TextBox resultTextBox;
        private TextBox debugTextBox;
        private SolverConnectivity solverConnectivity;
        private bool isDepth;
        public WordPathSolver(SolverConnectivity solverConnectivity, TextBox startTextBox, TextBox endTextBox, TextBox resultTextBox, TextBox debugTextBox, bool isDepth)
        {
            this.startTextBox = startTextBox;
            this.endTextBox = endTextBox;
            this.resultTextBox = resultTextBox;
            this.debugTextBox = debugTextBox;
            this.isDepth = isDepth;
            this.solverConnectivity = solverConnectivity;
        }

        public string Serialize()
        {
            return $"WORDPATH;{(isDepth ? "DEPTH" : "SHORT")};{startTextBox.Text};{endTextBox.Text}";
        }

        public void Deserialize(string input)
        {
            if (string.IsNullOrEmpty(input))
            {
                debugTextBox.AppendText($"Empty string received from solver.{Environment.NewLine}");
                return;
            }

            var tokens = input.Split(';');
            if (tokens.Length < 3)
            {
                debugTextBox.AppendText($"Can't decode the received response {input}.{Environment.NewLine}");
                return;
            }

            if (tokens[0] != "WORDPATH")
            {
                debugTextBox.AppendText($"Incorrect puzzle received in response {input}.{Environment.NewLine}");
                return;
            }

            for (int i = 2; i < tokens.Length; i++)
            {
                resultTextBox.AppendText($"{tokens[i]}{Environment.NewLine}");
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

        public void GridValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            throw new NotImplementedException();
        }
    }
}
