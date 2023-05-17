using NetMQ.Sockets;
using NetMQ;

namespace PuzzleGui.Connectivity
{
    internal class SolverConnectivity
    {
        private object lockingObject = new object();
        public bool Connected { get; private set; }
        public RequestSocket? Requester { get; private set; } = null;
        public void ConnectToServer()
        {
            lock (lockingObject)
            {
                try
                {

                    Requester = new RequestSocket();
                    Requester.Connect("tcp://localhost:5555");
                    Connected = true;
                }
                catch (Exception e)
                {
                    //Report something to the GUI.
                    Console.WriteLine(e);
                    Connected = false;
                }
            }
        }

        public void Disconnect()
        {
            lock (lockingObject)
            {
                if (!Connected)
                {
                    return;
                }

                Requester?.Disconnect("tcp://localhost:5555");
                Requester?.Dispose();
                Connected = false;
            }
        }
        public string SendRequest(string request)
        {
            if (!Connected)
            {
                //Report not connected
                return string.Empty;
            }

            Requester?.SendFrame(request);
            return Requester?.ReceiveFrameString() ?? string.Empty;

            //bool finished = false;
            //var result = new StringBuilder();
            //while (!finished)
            //{
            //var reply = await Requester.ReceiveFrameStringAsync();
            //result.Append(reply.Item1);
            //finished = !reply.Item2;
            //}
            //return result.ToString();
        }
    }
}
