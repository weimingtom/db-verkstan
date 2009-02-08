#pragma once

#include <db-util.hpp>

using namespace System;

#ifndef DB_USE_DIRECTOR
#error You should define DB_USE_DIRECTOR to 0 or 1
#endif

#if DB_USE_DIRECTOR
#define getTweakFloat(name)  (director.getTweakableByName(#name, Tweakable::TypeFloat).getFloat())
#define getTweakInt(name)    (director.getTweakableByName(#name, Tweakable::TypeInt).getInt())
#define getTweakVector(name) (director.getTweakableByName(#name, Tweakable::TypeVector).getVector())
#define getTweakSpline(name) (director.getTweakableByName(#name, Tweakable::TypeSpline).getSpline())
#else
#include "tweakconstants.hpp"
#define getTweakFloat(name)  (name)
#define getTweakInt(name)    (name)
#define getTweakVector(name) (name)
#define getTweakSpline(name) (name)
#endif

namespace Verkstan
{
	public ref class Tweakable
	{
	public:
		enum Type
		{
			TypeInt,
			TypeFloat,
			TypeVector,
			TypeSpline
		};

		Tweakable(string _name, Type type) :
		  name(_name),
		  type(_type),
		  floatVal(0.0f),
		  intVal(0),
		  vecVal(0.0f, 0.0f, 0.0f),
		  splineVal()
		{}

		float getFloat();
		void setFloat(float v);

		int getInt();
		void setInt(int v);

		Vec3 getVector();
		void setVector(Vec3 v);

		Spline getSpline();
		void setSpline(Spline v);

		string getName();
		
	private:
		Type type;
		string name;
		Vec3 vecVal;
		float floatVal;
		int intVal;
		Spline splineVal;
	};

    public interface IDirectorInterface
    {
    public:
        int getTick();
		int getLength();
		void setTick(int tick);
		void run();
		void stop();
		
		int getNumTweakables();
		Tweakable getTweakableByIndex(int index);
		Tweakable getTweakableByName(string name, Type type);
    };
}