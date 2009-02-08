using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace db_director
{
    public class Plugin
    {
        public static T GetPlugin<T>(string file)
        {
            Assembly assembly = Assembly.LoadFile(file);
            foreach (Type t in assembly.GetTypes())
            {
                if (t.IsInterface || t.IsNotPublic) { continue; }

                if (typeof(T).IsAssignableFrom(t))
                {
                    return (T)Activator.CreateInstance(t);
                }
            }
            return default(T);
        }
    }
}
