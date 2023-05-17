namespace PuzzleGui.Puzzles
{
    internal interface IPuzzleSolver
    {
        string Serialize();
        void Deserialize(string input);
        void Solve();
        void GridValueChanged(object sender, DataGridViewCellEventArgs e);
    }
}
