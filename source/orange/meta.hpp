/*
    This file is part of Orange.

    Orange is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Orange is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Orange; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Authors: Janez Demsar, Blaz Zupan, 1996--2002
    Contact: janez.demsar@fri.uni-lj.si
*/


#ifndef __META_HPP
#define __META_HPP

#include <string>
#include <vector>
#include "garbage.hpp"
#include "values.hpp"
using namespace std;

extern long metaID;

long getMetaID();

WRAPPER(Variable)

// A vector of meta values with id's
class TMetaValues : public vector<pair<long, TValue> > {
public:
  TValue &operator[](long id);
  const TValue &operator[](long id) const;
  bool exists(long id) const;
  void setValue(const long &id, const TValue &val);
  void removeValue(const long &id);
  void removeValueIfExists(const long &id);
};


class TMetaDescriptor {
public:
  long   id;
  PVariable variable;

  TMetaDescriptor();
  TMetaDescriptor(const long &ai, const PVariable &avar);
  TMetaDescriptor(const TMetaDescriptor &);
};


class TMetaVector : public vector<TMetaDescriptor> {
public:
  TMetaDescriptor *operator[](PVariable);
  TMetaDescriptor const *operator[](PVariable) const;
  TMetaDescriptor *operator[](const string &sna);
  TMetaDescriptor const *operator[](const string &sna) const;
  TMetaDescriptor *operator[](const long &ai);
  TMetaDescriptor const *operator[](const long &ai) const;
};

extern const char *_getweightwho, *_unknownweightexception, *_noncontinuousweightexception;

inline float _getweight(const TValue &val)
{ if (val.valueType)
    raiseErrorWho(_getweightwho, _unknownweightexception);
  if (val.varType!=TValue::FLOATVAR)
    raiseErrorWho(_getweightwho, _noncontinuousweightexception);
  return val.floatV;
}

// A macro to return a weight of an example or 1 if the weightID == 0
#define WEIGHT(ex) (weightID<0 ? _getweight((ex)[weightID]) : float(1.0))
#define WEIGHT2(ex,w) (w<0 ? _getweight((ex)[w]) : float(1.0))

#endif

