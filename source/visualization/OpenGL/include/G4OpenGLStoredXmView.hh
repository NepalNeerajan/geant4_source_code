// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4OpenGLStoredXmView.hh,v 2.1 1998/11/06 13:42:22 allison Exp $
// GEANT4 tag $Name: geant4-00 $
//
// 
// Andrew Walkden  10th February 1997
// Class G4OpenGLStoredXmView : a class derived from G4OpenGLXmView 
//                              and G4OpenGLStoredView.

#ifdef G4VIS_BUILD_OPENGLXM_DRIVER

#ifndef G4OpenGLSTOREDXMVIEW_HH
#define G4OpenGLSTOREDXMVIEW_HH

#include "G4VView.hh"
#include "G4OpenGLStoredView.hh"
#include "G4OpenGLXmView.hh"

class G4OpenGLStoredScene;

class G4OpenGLStoredXmView:
public G4OpenGLXmView, public G4OpenGLStoredView{
  
public:
  G4OpenGLStoredXmView (G4OpenGLStoredScene& scene, const G4String& name = "");
  void DrawView ();

};

#endif

#endif