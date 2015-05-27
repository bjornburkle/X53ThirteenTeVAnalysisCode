#ifndef TMuon_h
#define TMuon_h

#include "TLepton.h"

class TMuon : public TLepton{
public:

  //constructor
  TMuon(double ptTemp,double etatemp,double phitemp, double energytemp, int chargetemp, int isLtemp, int isTtemp, bool globaltemp,bool pftemp,bool trackertemp,double chi2temp, int nMuHtemp, int nMatchStattemp, double dxytemp, double dztemp, int ValPixtemp,int nTracktemp, double relIsotemp);

  //built-in ID flags
  int isLoose;
  int isTight;
  bool Global;
  bool PFMuon;
  bool Tracker;

  //int    global;
  double chi2;
  int    nValMuHits;
  int    nMatchedStations;
  double dxy;
  double dz;
  int    nValPixelHits;
  int    nTrackerLayers;
  double relIso;

  bool cutBasedLoose();
  bool cutBasedTight();

  void init();
};

#endif
