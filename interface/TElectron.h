#ifndef TElectron_h
#define TElectron_h

#include "TLepton.h"

class TElectron : public TLepton{
public:
  //constructor
  TElectron(double ptTemp,double etatemp,double phitemp, double energytemp, int chargetemp, int gsfCharget, int ctfCharget, int scpixCharget, double dEtatemp, double dPhitemp, double dZtemp, double siptemp, double d0temp,double hOverEtemp, double mHitstemp, double ooEmooPtemp, double sigmaIetaIetatemp, double chIsotemp,double puIsotemp, double neuIsotemp, double photIsotemp,double rhoIsotemp,double AEfftemp, int passConv,int chargeconsitencytemp, double mvatemp, double mva80xtemp, double miniIsotemp, double susyisotemp);
  //varibles for charge
  int gsfCharge;
  int ctfCharge;
  int scpixCharge;
  //variables for tracking cuts
  double dEta; 
  double dPhi;
  //variables for primary vtx cuts
  double dZ;
  double SIP3d;
  double d0;
  // Hadronic energy divided by the Electromagnetic
  double hOverE;
  //Minimum hits
  double mHits;
  double ooEmooP;
  //shower shape
  double sigmaIetaIeta;
  //Isolation
  double chIso;
  double puIso;
  double neutIso;
  double photIso;
  double rhoIso;
  double AEff;
  double relIsoDB;
  double relIsoEA;
  //passed conversion cuts
  int passConversion;
  //charge consistency
  int    chargeConsistency;

  // mvaID value and ID flags
  double mvaValue;
  double mvaValue80X;
  double miniIso;
  double susyIso;

  bool mvaTight();
  bool mva80XTight();
  bool mvaLoose();
  bool mva80XLoose();
  bool mvaTightIso();
  bool mva80XTightIso();
  bool mvaTightMedIso();
  bool mvaLooseIso();
  bool mva80XLooseIso();

  bool mvaTightNew();
  bool mvaLooseNew();
  bool mvaTightNewRC();
  bool mvaLooseNewRC();


  bool mvaTightRC();
  bool mva80XTightRC();
  bool mvaLooseRC();
  bool mva80XLooseRC();
  bool mvaTightCC();
  bool mvaLooseCC();
  bool mvaTightCCIso();
  bool mvaLooseCCIso();
  bool mvaTightRCIso();
  bool mva80XTightRCIso();
  bool mvaTightRCMedIso();
  bool mvaTightLCIso();
  bool mvaLooseRCIso();
  bool mva80XLooseRCIso();
  bool mvaLooseLCIso();

  //susy ids
  bool susyTight();
  bool susyLoose();
  bool susyTightRC();
  bool susyLooseRC();

  bool cutBasedTight50ns();
  bool cutBasedLoose50ns();
  bool cutBasedTight25nsSpring15MC();
  bool cutBasedLoose25nsSpring15MC();
  bool cutBasedTight25nsSpring15MCRC();
  bool cutBasedLoose25nsSpring15MCRC();
  bool cutBasedTightMay2015();
  bool cutBasedLooseMay2015();
  bool cutBasedTightApr2015();
  bool cutBasedLooseApr2015();
  bool CMSDASTight();
  bool CMSDASLoose();

  void init(){
    pt   = -100;
    eta  = -100;
    phi  = -100;
    
    dEta = -100;
    dPhi = -100;

    dZ   = -100;
    SIP3d= -100;
    d0   = -100;
    
    hOverE  = -100;
    
    mHits   =  100;
    ooEmooP = -100;
    
    relIsoEA = 100;
    sigmaIetaIeta = -100;
    
    chargeConsistency = 0;

  }

};

#endif
