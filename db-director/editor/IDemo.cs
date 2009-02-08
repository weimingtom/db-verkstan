using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace db_director
{
    public interface IProgressCallback
    {
        void ProgressUpdated(float progress);
    }

    public class Tweakable
    {
        public string Name { get; set; }
        public object Value { get; set; }

        public Tweakable(string name, object value)
        {
            Name = name;
            Value = value;
        }
    }

    public interface IDemo
    {
        int Ticks { get; set; }
        int Length { get; }

        void Init(IntPtr hwnd);
        void Load(IProgressCallback progress);
        void Stop();
        void Start();

        IList<Tweakable> GetTweakables();
    }

    public class TestDemo : IDemo
    {
        public int Ticks { get; set; }
        public int Length { get; set; }

        public void Init(IntPtr hwnd) { }
        public void Load(IProgressCallback progress)
        {
            for (int i = 0; i < 50; i++)
            {
                System.Threading.Thread.Sleep(10);
                progress.ProgressUpdated(i / 50.0f);
            }
        }
        public void Stop() { }
        public void Start() { }
        public void ShutDown() { }

        public IList<Tweakable> GetTweakables() { return new List<Tweakable>(); }

    }
}
