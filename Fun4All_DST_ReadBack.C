// $Id: $

/*!
 * \file Fun4All_DST_ReadBack.C
 * \brief 
 * \author Jin Huang <jhuang@bnl.gov>
 * \version $Revision:   $
 * \date $Date: $
 */

#include <fun4all/Fun4AllDstInputManager.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/SubsysReco.h>
#include <g4eval/PHG4DstCompressReco.h>
#include <fun4all/Fun4AllDstOutputManager.h>

#include <TSystem.h>



R__LOAD_LIBRARY(libfun4all.so)


void ShowerCompress(int verbosity = 0)
{
  Fun4AllServer *se = Fun4AllServer::instance();

  PHG4DstCompressReco *compress = new PHG4DstCompressReco("PHG4DstCompressReco");
  compress->AddHitContainer("G4HIT_PIPE");
  compress->AddHitContainer("G4HIT_SVTXSUPPORT");
  compress->AddHitContainer("G4HIT_CEMC_ELECTRONICS");
  compress->AddHitContainer("G4HIT_CEMC");
  compress->AddHitContainer("G4HIT_ABSORBER_CEMC");
  compress->AddHitContainer("G4HIT_CEMC_SPT");
  compress->AddHitContainer("G4HIT_ABSORBER_HCALIN");
  compress->AddHitContainer("G4HIT_HCALIN");
  compress->AddHitContainer("G4HIT_HCALIN_SPT");
  compress->AddHitContainer("G4HIT_MAGNET");
  compress->AddHitContainer("G4HIT_ABSORBER_HCALOUT");
  compress->AddHitContainer("G4HIT_HCALOUT");
  compress->AddHitContainer("G4HIT_BH_1");
  compress->AddHitContainer("G4HIT_BH_FORWARD_PLUS");
  compress->AddHitContainer("G4HIT_BH_FORWARD_NEG");
  compress->AddHitContainer("G4HIT_BBC");
  compress->AddCellContainer("G4CELL_CEMC");
  compress->AddCellContainer("G4CELL_HCALIN");
  compress->AddCellContainer("G4CELL_HCALOUT");
  compress->AddTowerContainer("TOWER_SIM_CEMC");
  compress->AddTowerContainer("TOWER_RAW_CEMC");
  compress->AddTowerContainer("TOWER_CALIB_CEMC");
  compress->AddTowerContainer("TOWER_SIM_HCALIN");
  compress->AddTowerContainer("TOWER_RAW_HCALIN");
  compress->AddTowerContainer("TOWER_CALIB_HCALIN");
  compress->AddTowerContainer("TOWER_SIM_HCALOUT");
  compress->AddTowerContainer("TOWER_RAW_HCALOUT");
  compress->AddTowerContainer("TOWER_CALIB_HCALOUT");
  se->registerSubsystem(compress);

  return;
}

  
  
void Fun4All_DST_ReadBack(const int nevnt = 10)
{
  gSystem->Load("libg4dst");
  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(1);

  {
  Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_TRUTH_pythia8_Charm_3MHz");
  in->fileopen("DST_TRUTH_pythia8_Charm_3MHz-0000000004-00000.root");
  se->registerInputManager(in);
  }
  {
  Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_BBC_G4HIT_pythia8_Charm_3MHz");
  in->fileopen("DST_BBC_G4HIT_pythia8_Charm_3MHz-0000000004-00000.root");
  se->registerInputManager(in);
  }
  {
  Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_TRKR_G4HIT_pythia8_Charm_3MHz");
  in->fileopen("DST_TRKR_G4HIT_pythia8_Charm_3MHz-0000000004-00000.root");
  se->registerInputManager(in);
  }
  
  
  
    Fun4AllDstOutputManager *out = new Fun4AllDstOutputManager("DSTOUT", "DST_TRUTH_COMPRESSED-0000000004-00000.root"); 
      ShowerCompress();
    out->AddNode("EventHeader");
    out->AddNode("PHHepMCGenEventMap");
    out->AddNode("G4HIT_BH_1");
    out->AddNode("EventHeader");
    out->AddNode("G4TruthInfo");
    se->registerOutputManager(out);
  
  
  se->run(nevnt);
  se->End();
  delete se;
  gSystem->Exit(0);
}

