using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    public abstract class Clip: IDisposable
    {
        #region Properties
        public abstract void Dispose();
        public abstract int Id { get; }
        #endregion
    }
}
