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
// $Id: G4Penelope08GammaConversionModel.hh,v 1.1 2010-03-17 14:19:04 pandola Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// Author: Luciano Pandola
//
// History:
// -----------
// 13 Jan 2010   L. Pandola  First implementation
//
// -------------------------------------------------------------------
//
// Class description:
// Low Energy Electromagnetic Physics, Gamma Conversion 
// with Penelope Model, version 2008
// -------------------------------------------------------------------

#ifndef G4PENELOPE08GAMMACONVERSIONMODEL_HH
#define G4PENELOPE08GAMMACONVERSIONMODEL_HH 1

#include "globals.hh"
#include "G4VEmModel.hh"
#include "G4DataVector.hh"
#include "G4ParticleChangeForGamma.hh"

class G4ParticleDefinition;
class G4DynamicParticle;
class G4MaterialCutsCouple;
class G4Material;
class G4PhysicsFreeVector;

class G4Penelope08GammaConversionModel : public G4VEmModel 
{

public:
  
  G4Penelope08GammaConversionModel(const G4ParticleDefinition* p=0,
			 const G4String& processName ="PenConversion");
  
  virtual ~G4Penelope08GammaConversionModel();

  virtual void Initialise(const G4ParticleDefinition*, const G4DataVector&);

  virtual G4double ComputeCrossSectionPerAtom(
					      const G4ParticleDefinition*,
					      G4double kinEnergy,
					      G4double Z,
					      G4double A=0,
					      G4double cut=0,
					      G4double emax=DBL_MAX);

  virtual void SampleSecondaries(std::vector<G4DynamicParticle*>*,
				 const G4MaterialCutsCouple*,
				 const G4DynamicParticle*,
				 G4double tmin,
				 G4double maxEnergy);

  void SetVerbosityLevel(G4int lev){verboseLevel = lev;};
  G4int GetVerbosityLevel(){return verboseLevel;};

protected:
  G4ParticleChangeForGamma* fParticleChange;

private:
  G4Penelope08GammaConversionModel & operator=(const 
					       G4Penelope08GammaConversionModel &right);
  G4Penelope08GammaConversionModel(const G4Penelope08GammaConversionModel&);


  //Intrinsic energy limits of the model: cannot be extended by the parent process
  G4double fIntrinsicLowEnergyLimit;
  G4double fIntrinsicHighEnergyLimit;

  //Use a quicker sampling algorithm if E < smallEnergy
  G4double fSmallEnergy; 

  std::map<const G4int,G4PhysicsFreeVector*> *logAtomicCrossSection;
  void ReadDataFile(const G4int Z);

  void InitializeScreeningRadii();
  G4double fAtomicScreeningRadius[99];

  void InitializeScreeningFunctions(const G4Material*);
  //Effective (scalar) properties attached to materials:
  // effective charge
  std::map<const G4Material*,G4double> *fEffectiveCharge;
  // 2/Rs (Rs = screening radius), BCB array in Penelope
  std::map<const G4Material*,G4double> *fMaterialInvScreeningRadius;
  // Parameters of screening functions
  std::map<const G4Material*,std::pair<G4double,G4double> > *fScreeningFunction;

  std::pair<G4double,G4double> GetScreeningFunctions(G4double);	


  G4int verboseLevel;
  G4bool isInitialised;
};

#endif
