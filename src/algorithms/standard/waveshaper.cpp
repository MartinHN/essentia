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

#include "waveshaper.h"
#include "essentiamath.h"

using namespace std;
using namespace essentia;
using namespace standard;


namespace essentia {
namespace standard {


const char* waveshaper::name = "waveshaper";
const char* waveshaper::description = DOC(
"shapes the signal to a waveshaping model made of 3 continuous linear part\n"
"(p1,p2),(p2,p3),(p3,p4) "
"\n"
"\n"
"References:\n"
" \n");


void waveshaper::configure() {


  _p1x =  parameter("p1x").toReal();
  _p2x =  parameter("p2x").toReal();
  _p3x =  parameter("p3x").toReal();
  _p4x =  parameter("p4x").toReal();
  _p1y =  parameter("p1y").toReal();
  _p2y =  parameter("p2y").toReal();
  _p3y =  parameter("p3y").toReal();
  _p4y =  parameter("p4y").toReal();
if(_p1x>=_p2x||_p2x>=_p3x||_p3x>=_p4x) throw EssentiaException("wrong Params or badly sorted p1x<p2x<p3x<p4x") ;
  _c1 = (_p2y-_p1y)/(_p2x-_p1x);
  _c2 = (_p3y-_p2y)/(_p3x-_p2x);
  _c3 = (_p4y-_p3y)/(_p4x-_p3x);
  

}

void waveshaper::compute() {

  const std::vector<Real>& signal = _signal.get();
  vector<Real>& signalout = _signalout.get();

  if (signal.size() == 0) {
    signalout.resize(0);
    return;
  }
  else{
  int size = int(signal.size());
  
  for(int i = 0 ; i< size;i++){
  
	if(signal[i]>_p1x&&signal[i]<=_p2x)  
		signalout[i] = _p1y+(signal[i]-_p1x)*_c1;
	else if(signal[i]>_p2x&&signal[i]<=_p3x) 
		signalout[i] = _p2y+(signal[i]-_p2x)*_c2;
	else if(signal[i]>_p3x&&signal[i]<=_p4x) 
		signalout[i] = _p3y+(signal[i]-_p3x)*_c3;
	else if(signal[i]<_p1x) 
		signalout[i] = _p1y;
	else 
		signalout[i] = _p4y;
    
  }
  
  }



  

}

}
}