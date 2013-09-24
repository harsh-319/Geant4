//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
#ifndef G4ElectroNuclearBuilder_h
#define G4ElectroNuclearBuilder_h 1

#include "globals.hh"
#include "G4ios.hh"

#include "G4TheoFSGenerator.hh"
#include "G4GeneratorPrecompoundInterface.hh"
#include "G4QGSModel.hh"
#include "G4GammaParticipants.hh"
#include "G4QGSMFragmentation.hh"
#include "G4ExcitedStringDecay.hh"

#include "G4GammaNuclearReaction.hh"
#include "G4ElectroNuclearReaction.hh"
#include "G4PhotoNuclearProcess.hh"
#include "G4ElectronNuclearProcess.hh"
#include "G4PositronNuclearProcess.hh"

class G4ElectroNuclearBuilder 
{
  public: 
    G4ElectroNuclearBuilder();
    virtual ~G4ElectroNuclearBuilder();

  public: 
    virtual void Build();

  protected:
    G4PhotoNuclearProcess * thePhotoNuclearProcess;
    G4ElectronNuclearProcess * theElectronNuclearProcess;
    G4PositronNuclearProcess * thePositronNuclearProcess;
    G4ElectroNuclearReaction * theElectroReaction;
    G4GammaNuclearReaction * theGammaReaction;  
    
    G4TheoFSGenerator * theModel;
    G4GeneratorPrecompoundInterface * theCascade;
    G4QGSModel< G4GammaParticipants > * theStringModel;
    G4QGSMFragmentation * theFragmentation;
    G4ExcitedStringDecay * theStringDecay;
    G4bool wasActivated;
};

// 2002 by J.P. Wellisch

#endif

