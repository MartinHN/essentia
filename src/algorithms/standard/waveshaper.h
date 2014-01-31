/*
 * Copyright (C) 2006-2013  Music Technology Group - Universitat Pompeu Fabra
 *
 * This file is part of Essentia
 *
 * Essentia is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the Free
 * Software Foundation (FSF), either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the Affero GNU General Public License
 * version 3 along with this program.  If not, see http://www.gnu.org/licenses/
 */

#ifndef ESSENTIA_waveshaper_H
#define ESSENTIA_waveshaper_H

#include "algorithmfactory.h"
#include <complex>

namespace essentia {
namespace standard {

class waveshaper : public Algorithm {

 protected:
  Input<std::vector<Real> > _signal;
  Output<std::vector<Real> > _signalout;
double _p1x;
double  _p2x;
double  _p3x;
double  _p4x;
double  _p1y;
double  _p2y;
double  _p3y;
double  _p4y;
double _c1,_c2,_c3;


 public:
  waveshaper()   {
    declareInput(_signal, "array", "the array to be shaped");
    declareOutput(_signalout, "shaped_signal", "shaped");

  }

  ~waveshaper() {

  }

  void declareParameters() {
	declareParameter("p0x","coordinate","(-inf,inf)",0);
	declareParameter("p0y","coordinate","(-inf,inf)",1);
	declareParameter("p1x","coordinate","(-inf,inf)",2);
	declareParameter("p1y","coordinate","(-inf,inf)",3);
	declareParameter("p2x","coordinate","(-inf,inf)",4);
	declareParameter("p2y","coordinate","(-inf,inf)",5);
	declareParameter("p3x","coordinate","(-inf,inf)",6);
	declareParameter("p3y","coordinate","(-inf,inf)",7);
  }

  void configure();
  void compute();

 protected:
  void createFFTObject(int size);

 public:
  static const char* name;
  static const char* description;

};

} // namespace standard
} // namespace essentia

#include "streamingalgorithmwrapper.h"

namespace essentia {
namespace streaming {

class waveshaper : public StreamingAlgorithmWrapper {

 protected:
  Sink<std::vector<Real> > _signal;
  Source<std::vector<Real> > _signalout;

 public:
  waveshaper() {
    declareAlgorithm("waveshaper");
    declareInput(_signal, TOKEN, "array");
    declareOutput(_signalout, TOKEN, "autoCorrelation");
  }
};

} // namespace streaming
} // namespace essentia

#endif // ESSENTIA_AUTOCORRELATION_H
