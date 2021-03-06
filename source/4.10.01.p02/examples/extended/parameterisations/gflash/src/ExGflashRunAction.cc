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
// $Id: ExGflashRunAction.cc 70923 2013-06-07 13:10:39Z gcosmo $
//
/// \file parameterisations/gflash/src/ExGflashRunAction.cc
/// \brief Implementation of the ExGflashRunAction class
//
#include "ExGflashRunAction.hh"
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"




ExGflashRunAction::ExGflashRunAction(): fRunID(0)
{
}


ExGflashRunAction::~ExGflashRunAction()
{
}


void ExGflashRunAction::BeginOfRunAction(const G4Run* aRun)
{  
   ((G4Run *)(aRun))->SetRunID(fRunID++);
   
   std::cout << "### Run " << aRun->GetRunID() << " start." << std::endl;
   
   if (G4VVisManager::GetConcreteInstance())
     {
       G4UImanager* UI = G4UImanager::GetUIpointer();
       UI->ApplyCommand("/vis/scene/notifyHandlers");
     } 
}


void ExGflashRunAction::EndOfRunAction(const G4Run* aRun)
{ 
  if (G4VVisManager::GetConcreteInstance())
    {
      G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
    }

  G4cout << "number of event = " << aRun->GetNumberOfEvent() << G4endl;

}











