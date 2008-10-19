﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using DB.Darkfile;

using Vorlon2;

using Midi;

namespace VorlonSeq.Seq
{
    public class Clip : IChunkReader
    {
        public class Event
        {
            public Event(DarkInStream s)
            {
                s.Read(out Time);
                Message = new MidiMessage(s.ReadUInt());
            }

            public Event(MidiMessage message, int time)
            {
                Message = message;
                Time = time;
            }

            public MidiMessage Message;
            public int Time;
        }

        public class NoteEvent
        {
            public byte Note;
            public byte Velocity;
            public int StartTime;
            public int Length;

            public NoteEvent(DarkInStream s)
            {
                s.Read(out StartTime);
                s.Read(out Note);
                s.Read(out Velocity);
                s.Read(out Length);
            }

            public NoteEvent(byte note, byte velocity, int startTime, int length)
            {
                StartTime = startTime;
                Note = note;
                Velocity = velocity;                
                Length = length;
            }

            public int EndTime { get { return StartTime + Length; } set { Length = value - StartTime; } }

            public Event ToEvent(MidiMessage.Commands command)
            {
                if (command == MidiMessage.Commands.NoteOn)
                {
                    return new Event(new MidiMessage(0, MidiMessage.Commands.NoteOn, (uint)Note, (uint)Velocity), StartTime);
                }
                else if (command == MidiMessage.Commands.NoteOff)
                {
                    return new Event(new MidiMessage(0, MidiMessage.Commands.NoteOff, (uint)Note, 0), StartTime + Length); 
                }

                throw new Exception("Command must be NoteOn or NoteOff");
            }
        }

        public Channel Channel;
        public readonly List<Event> ControllerEvents = new List<Event>();
        public readonly List<NoteEvent> NoteEvents = new List<NoteEvent>();
        public int StartTime = 0;
        public int Length = 64;
        public int EndTime { get { return StartTime + Length; } set { Length = value - StartTime; } }

        public List<MidiMessage> GetAllEventsBetween(int start, int end)
        {
            List<MidiMessage> result = new List<MidiMessage>();
            
            foreach (Event e in ControllerEvents)
            {
                if (e.Time >= start && e.Time < end)
                {
                    result.Add(e.Message);
                }
            }

            foreach (NoteEvent e in NoteEvents)
            {
                if (e.StartTime >= start && e.StartTime < end)
                {
                    result.Add(e.ToEvent(MidiMessage.Commands.NoteOn).Message);
                }

                if (e.EndTime >= start && e.EndTime < end)
                {
                    result.Add(e.ToEvent(MidiMessage.Commands.NoteOff).Message);
                }
            }

            return result;
        }

        public void Write(DarkOutStream s)
        {
            s.Write(StartTime);
            s.Write(Length);

            s.OpenChunk("NOTE");
            s.Write(NoteEvents.Count);            
            foreach (NoteEvent e in NoteEvents)
            {
                s.Write(e.StartTime);
                s.Write(e.Note);
                s.Write(e.Velocity);
                s.Write(e.Length);
            }
            s.CloseChunk();

            s.OpenChunk("CTRL");
            s.Write(ControllerEvents.Count);
            foreach (Event e in ControllerEvents)
            {
                s.Write(e.Time);
                s.Write(e.Message.GetAsUInt());
            }
            s.CloseChunk();
        }

        public void Read(DarkInStream s)
        {
            s.Read(out StartTime);
            s.Read(out Length);
            s.ReadAllChunks(this);
        }

        public void ReadChunk(string id, long length, DarkInStream s)
        {
            if (id.Equals("NOTE"))
            {
                int numNoteEvents = s.ReadInt();
                for (int i = 0; i < numNoteEvents; i++)
                {
                    NoteEvents.Add(new NoteEvent(s));
                }
            }

            if (id.Equals("CTRL"))
            {
                int numControllerEvents = s.ReadInt();
                for (int i = 0; i < numControllerEvents; i++)
                {
                    ControllerEvents.Add(new Event(s));
                }
            }
        }
    }

    public class Channel : IChunkReader
    {
        public readonly int Number;
        public string Name;
        public readonly List<Clip> clips = new List<Clip>();

        public IList<Clip> Clips { get { return clips.AsReadOnly(); } }

        public void AddClip(Clip c)
        {
            clips.Add(c);
            c.Channel = this;
        }

        public void RemoveClip(Clip c)
        {
            if (clips.Remove(c))
            {
                c.Channel = null;
            }
        }

        public Channel(int number)
        {
            Number = number;
            Name = "Channel #" + number;
        }

        public List<MidiMessage> GetAllEventsBetween(int start, int end)
        {
            List<MidiMessage> result = new List<MidiMessage>();
            foreach (Clip c in Clips)
            {
                if (end <= c.StartTime || start > c.EndTime)
                {
                    continue;
                }

                result.AddRange(c.GetAllEventsBetween(start - c.StartTime, end - c.StartTime));
            }

            for (int i = 0; i < result.Count; i++)
            {
                MidiMessage m = result[i];
                m.Channel = (uint)Number;
                result[i] = m;
            }

            return result;
        }

        public Clip GetClipAt(int time)
        {
            foreach (Clip c in Clips)
            {
                if (c.StartTime <= time && c.EndTime > time)
                {
                    return c;
                }
            }

            return null;
        }

        public void Write(DarkOutStream s)
        {
            foreach (Clip c in Clips)
            {
                s.OpenChunk("CLIP");
                c.Write(s);
                s.CloseChunk();
            }         
        }

        public void ReadChunk(string id, long length, DarkInStream s)
        {
            if (id.Equals("CLIP"))
            {
                Clip c = new Clip();
                c.Read(s);
                AddClip(c);
            }
        }
    }

    public class Song : IChunkReader
    {
        public const int NumChannels = 16;

        public Channel[] Channels = new Channel[NumChannels];

        public Song()
        {
            for (int i = 0; i < Channels.Length; i++)
            {
                Channels[i] = new Channel(i);
            }
        }

        public void Write(DarkOutStream s)
        {            
            for (int i = 0; i < Channels.Length; i++)
            {
                s.OpenChunk("CHAN");
                s.Write(i);
                Channels[i].Write(s);
                s.CloseChunk();
            }                
        }

        public void ReadChunk(string id, long length, DarkInStream s)
        {
            if (id.Equals("CHAN"))
            {
                int index;
                s.Read(out index);
                s.ReadAllChunks(Channels[index]);
            }
        }
    }

    public class Sequencer
    {
        public static Song Song = new Song();
        static public int FramesPerTick = 21;
        public static VorlonSynth Synth = new VorlonSynth();

        private static List<MidiMessage> toBePlayed = new List<MidiMessage>();
        private static bool running = false;

        public static bool IsPlaying = false;
        public static int PlayPosition = 0;
        private static int frameCounter = 0;

        public static int BPM 
        { 
            get 
            {
                double samplesPerBeat = FramesPerTick * Synth.FrameSize * 4;
                double beatsPerSecond = Synth.SampleRate / samplesPerBeat;
                return (int)(beatsPerSecond * 60.0f);                
            } 
        }

        public static void Load(string path)
        {
            DarkInStream dis = new DarkInStream(File.OpenRead(path));
            Song = new Song();            
            dis.ReadChunk(delegate(string id, long length, DarkInStream s)
            {
                if (id.Equals("VSEQ"))
                {
                    s.Read(out FramesPerTick);

                    s.ReadChunk(delegate(string id2, long length2, DarkInStream s2)
                    {
                        if (id2.Equals("SONG"))
                        {
                            s2.ReadAllChunks(Song);
                        }
                    });
                }
            });
            dis.Close();
        }

        public static void Reset()
        {
            FramesPerTick = 21;
            Song = new Song();
        }

        public static void Save(string path)
        {
            DarkOutStream dos = new DarkOutStream(File.Create(path));
            dos.OpenChunk("VSEQ");
            dos.Write(FramesPerTick);
            dos.OpenChunk("SONG");
            Song.Write(dos);
            dos.CloseChunk();
            dos.CloseChunk();
            dos.Close();
        }

        public static void PlayMidiEvent(MidiMessage midiMessage)
        {
            lock (toBePlayed)
            {
                toBePlayed.Add(midiMessage);
            }
        }

        private static void SendPendingMidiToVorlon()
        {
            lock (toBePlayed)
            {
                foreach (MidiMessage m in toBePlayed)
                {
                    Synth.MidiInput(m.GetAsUInt());
                }
                toBePlayed.Clear();
            }
        }

        public static void StartVorlon()
        {
            if (running)
            {
                return;
            }

            running = true;
            new System.Threading.Thread(VorlonLoop).Start();
        }

        public static void StopVorlon()
        {
            running = false;
        }

        private static void StepSequencer()
        {
            if (!IsPlaying)
            {
                return;
            }

            frameCounter++;

            if (frameCounter >= FramesPerTick)
            {
                frameCounter = 0;
                for (int i = 0; i < Song.NumChannels; i++)
                {
                    Channel channel = Song.Channels[i];
                    IList<MidiMessage> events = channel.GetAllEventsBetween(PlayPosition, PlayPosition + 1);
                    foreach (MidiMessage m in events)
                    {
                        PlayMidiEvent(m);
                    }
                }
                PlayPosition++;
            }
        }

        private static void VorlonLoop()
        {
            while (running)
            {
                StepSequencer();
                SendPendingMidiToVorlon();
                Synth.PlayFrame();
            }
        }
    }
}
