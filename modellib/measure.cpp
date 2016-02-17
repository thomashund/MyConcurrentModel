//################################################
// This code file
// defines Measure class used to track properties
// (e.g. peak, min, duration) of specified state variable.
//
// Copyright (C) 2015 Thomas J. Hund.
// Updated 07/2015
// Email thomas.hund@osumc.edu
//#################################################

#include "measure.h"

//#############################################################
// Measure class constructor and destructor
//#############################################################


Measure::Measure()
{
    peak=-100.0;
    min=100.0;
    vartakeoff=-100.0;
    repol = -25.0;
    amp = 70.0;
    maxderiv=0.0;
    maxderiv2nd=0.0;
    cl=0.0;
    told = -10000.0;
    mint = 0.0;
    maxt = 0.0;
    varold = 100.0;
    derivold = 0.0;
    minflag = 0;
    maxflag = 0;
    ampflag = 0;
    ddrflag = 0;
    derivt2 = 0.0;
    derivt1 = 0.0;
    derivt = 0.0;
    deriv2ndt = 0.0;
    durflag = 0;
    percrepol = 50.0;
    returnflag = 0;
    
    varmap["cl"]=&cl;
    varmap["peak"]=&peak;
    varmap["min"]=&min;
    varmap["amp"]=&amp;
    varmap["ddr"]=&ddr;
    varmap["maxderiv"]=&maxderiv;
    varmap["dur"]=&dur;
    varmap["durtime1"]=&durtime1;
    varmap["vartakeoff"]=&vartakeoff;
    varmap["mint"]=&mint;
    varmap["derivt"]=&derivt;
    varmap["deriv2ndt"]=&deriv2ndt;
    
    datamap["peak"]=&peak;
    datamap["min"]=&min;
    datamap["maxderiv"]=&maxderiv;
    datamap["dur"]=&dur;
};

Measure::Measure(const Measure& toCopy) {
    this->copy(toCopy);
};

Measure::Measure( Measure&& toCopy) {
    this->copy(toCopy); 
};

Measure& Measure::operator=(const Measure& toCopy) {
    this->copy(toCopy);
    return *this;
};

Measure::~Measure()
{
};

void Measure::copy(const Measure& toCopy) {
    std::map<string, double*>::iterator it;

    peak= toCopy.peak;
    min= toCopy.min;
    vartakeoff= toCopy.vartakeoff;
    repol = toCopy.repol;
    amp = toCopy.amp;
    maxderiv= toCopy.maxderiv;
    maxderiv2nd= toCopy.maxderiv2nd;
    cl= toCopy.cl;
    told = toCopy.told;
    mint = toCopy.mint;
    maxt = toCopy.maxt;
    varold = toCopy.varold;
    derivold = toCopy.derivold;
    minflag = toCopy.minflag;
    maxflag = toCopy.maxflag;
    ampflag = toCopy.ampflag;
    ddrflag = toCopy.ddrflag;
    derivt2 = toCopy.derivt2;
    derivt1 = toCopy.derivt1;
    derivt = toCopy.derivt;
    deriv2ndt = toCopy.deriv2ndt;
    durflag = toCopy.durflag;
    percrepol = toCopy.percrepol;
    returnflag = toCopy.returnflag;
    dur = toCopy.dur;
    varname = toCopy.varname;    

    varmap["cl"]=&cl;
    varmap["peak"]=&peak;
    varmap["min"]=&min;
    varmap["amp"]=&amp;
    varmap["ddr"]=&ddr;
    varmap["maxderiv"]=&maxderiv;
    varmap["dur"]=&dur;
    varmap["durtime1"]=&durtime1;
    varmap["vartakeoff"]=&vartakeoff;
    varmap["mint"]=&mint;
    varmap["derivt"]=&derivt;
    varmap["deriv2ndt"]=&deriv2ndt;

    datamap = toCopy.datamap;   
    for(it = datamap.begin(); it != datamap.end() ; it++) {
        datamap[it->first] = varmap[it->first];
    } 
};

//################################################################
// Function to track properties (e.g. peak, min, duration) of
// specified state variable and return status flag to calling fxn.
//################################################################
int Measure::measure(double time, double var)
{
    double deriv,deriv2nd;
    
    returnflag = 0;  //default for return...set to 1 when props ready for output
    
    deriv=(var-varold)/(time-told);
    deriv2nd=(deriv-derivold)/(time-told);
    
    if(deriv>maxderiv){             // Track value and time of max 1st deriv
        maxderiv=deriv;
        derivt=time;
    }
    
    if(deriv2nd>.02&&var>(0.01*abs(min)+min)&&ddrflag==0){   // Track 2nd deriv for SAN ddr
        vartakeoff=var;
        deriv2ndt=time;
        ddr=(vartakeoff-min)/(time-mint);
        ddrflag=1;
    }
    
    if(minflag==1&&var>peak){          // Track value and time of peak
        peak=var;
        maxt=time;
    }
    else if((peak-min)>0.3*abs(min))    // Assumes true max is more than 30% greater than the min.
        maxflag=1;
    
    if(var<min){                        // Track value and time of min
        min=var;
        mint=time;
    }
    else
        minflag=1;
    
    if(var>repol&&durflag==0){          // t1 for dur calculation = first time var crosses repol.
        durtime1=time;            // will depend on percrepol - default is 50 but can be changed.
        durflag=1;
    }
    
    if(maxflag==1&&minflag==1&&ampflag==0){
        amp=peak-min;
        ampflag = 1;
        cl=derivt-derivt1;
        derivt2=derivt1;
        derivt1=derivt;
        repol = (1-percrepol*0.01)*amp+min;
    }
    
    if(durflag==1&&var<repol){
        dur=time-durtime1;
        durflag=0;
        returnflag = 1;  // lets calling fxn know that it is time to output and reset.
    }
    
    told=time;
    varold=var;
    derivold=deriv;
    
    return (returnflag);
};


void Measure::reset()
{
    peak=-100.0;
    min=100.0;
    maxderiv=0.0;
    maxderiv2nd=0.0;
    told = 0.0;
    minflag = 0;
    maxflag = 0;
    ampflag = 0;
    ddrflag = 0;
};

