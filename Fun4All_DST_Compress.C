// $Id: $

/*!
 * \file Fun4All_DST_Compress.C
 * \brief 
 * \author Jin Huang <jhuang@bnl.gov>
 * \version $Revision:   $
 * \date $Date: $
 */

#include <fun4all/Fun4AllDstInputManager.h>
#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/SubsysReco.h>

#include <g4eval/PHG4DstCompressReco.h>
#include <g4eval/SvtxTruthRecoTableEval.h>

#include <TSystem.h>

R__LOAD_LIBRARY(libg4detectors.so)
R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libg4eval.so)

//TOP (PHCompositeNode)/
//   DST (PHCompositeNode)/
//      Sync (IO,SyncObjectv1)
//      EventHeader (IO,EventHeaderv1)
//      HCALIN (PHCompositeNode)/
//         TOWER_SIM_HCALIN (IO,RawTowerContainer)
//         TOWER_RAW_HCALIN (IO,RawTowerContainer)
//         TOWER_CALIB_HCALIN (IO,RawTowerContainer)
//         CLUSTER_HCALIN (IO,RawClusterContainer)
//         G4HIT_HCALIN (IO,PHG4HitContainer)
//      HCALOUT (PHCompositeNode)/
//         TOWER_SIM_HCALOUT (IO,RawTowerContainer)
//         TOWER_RAW_HCALOUT (IO,RawTowerContainer)
//         TOWER_CALIB_HCALOUT (IO,RawTowerContainer)
//         CLUSTER_HCALOUT (IO,RawClusterContainer)
//         G4HIT_HCALOUT (IO,PHG4HitContainer)
//      GLOBAL (PHCompositeNode)/
//         GlobalVertexMap (IO,GlobalVertexMapv1)
//      CEMC (PHCompositeNode)/
//         TOWER_SIM_CEMC (IO,RawTowerContainer)
//         TOWER_RAW_CEMC (IO,RawTowerContainer)
//         TOWER_CALIB_CEMC (IO,RawTowerContainer)
//         CLUSTER_CEMC (IO,RawClusterContainer)
//         CLUSTER_POS_COR_CEMC (IO,RawClusterContainer)
//      BBC (PHCompositeNode)/
//         G4HIT_BBC (IO,PHG4HitContainer)
//      EPD (PHCompositeNode)/
//         G4HIT_EPD (IO,PHG4HitContainer)
//      G4HIT_CEMC (IO,PHG4HitContainer)
//      MVTX (PHCompositeNode)/
//         G4HIT_MVTX (IO,PHG4HitContainer)
//      INTT (PHCompositeNode)/
//         G4HIT_INTT (IO,PHG4HitContainer)
//      TPC (PHCompositeNode)/
//         G4HIT_TPC (IO,PHG4HitContainer)
//      MICROMEGAS (PHCompositeNode)/
//         G4HIT_MICROMEGAS (IO,PHG4HitContainer)
//      PHHepMCGenEventMap (IO,PHHepMCGenEventMap)
//      G4HIT_BH_1 (IO,PHG4HitContainer)
//      G4TruthInfo (IO,PHG4TruthInfoContainer)
//      TRKR (PHCompositeNode)/
//         TRKR_CLUSTER (IO,TrkrClusterContainerv3)
//         TRKR_CLUSTERHITASSOC (IO,TrkrClusterHitAssocv3)
//         TRKR_HITSET (IO,TrkrHitSetContainerv1)
//         TRKR_HITTRUTHASSOC (IO,TrkrHitTruthAssocv1)
//      SVTX (PHCompositeNode)/
//         SvtxSiliconTrackMap (IO,SvtxTrackMap_v1)
//         SvtxTrackMap (IO,SvtxTrackMap_v1)
//         AssocInfoContainer (IO,AssocInfoContainerv1)
//         TpcSeedTrackMap (IO,TpcSeedTrackMapv1)
//         SvtxVertexMap (IO,SvtxVertexMap_v1)
//         SvtxVertexMapRave (IO,SvtxVertexMap_v1)

void Fun4All_DST_Compress(const int nevnt = 10)
{
  gSystem->Load("libg4dst");
  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(1);

  {
    Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_CALO_CLUSTER_pythia8_Charm_3MHz");
    in->fileopen("DST_CALO_CLUSTER_pythia8_Charm_3MHz-0000000004-00000.root");
    se->registerInputManager(in);
  }

  {
    Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_BBC_G4HIT_pythia8_Charm_3MHz");
    in->fileopen("DST_BBC_G4HIT_pythia8_Charm_3MHz-0000000004-00000.root");
    se->registerInputManager(in);
  }

  {
    Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_CALO_G4HIT_pythia8_Charm_3MHz");
    in->fileopen("DST_CALO_G4HIT_pythia8_Charm_3MHz-0000000004-00000.root");
    se->registerInputManager(in);
  }

  {
    Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_TRKR_G4HIT_pythia8_Charm_3MHz");
    in->fileopen("DST_TRKR_G4HIT_pythia8_Charm_3MHz-0000000004-00000.root");
    se->registerInputManager(in);
  }

  {
    Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_TRUTH_G4HIT_pythia8_Charm_3MHz");
    in->fileopen("DST_TRUTH_G4HIT_pythia8_Charm_3MHz-0000000004-00000.root");
    se->registerInputManager(in);
  }

  {
    Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_VERTEX_pythia8_Charm_3MHz");
    in->fileopen("DST_VERTEX_pythia8_Charm_3MHz-0000000004-00000.root");
    se->registerInputManager(in);
  }

  {
    Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_TRACKS_pythia8_Charm_3MHz");
    in->fileopen("DST_TRACKS_pythia8_Charm_3MHz-0000000004-00000.root");
    se->registerInputManager(in);
  }

  {
    Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_TRKR_HIT_pythia8_Charm_3MHz");
    in->fileopen("DST_TRKR_HIT_pythia8_Charm_3MHz-0000000004-00000.root");
    se->registerInputManager(in);
  }

  {
    Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_TRUTH_pythia8_Charm_3MHz");
    in->fileopen("DST_TRUTH_pythia8_Charm_3MHz-0000000004-00000.root");
    se->registerInputManager(in);
  }

  // build high level tracker association table
  SvtxTruthRecoTableEval *tables = new SvtxTruthRecoTableEval();
  //  tables->Verbosity(verbosity);
  se->registerSubsystem(tables);

  // this drop hits and particles, which should run after tracker compress
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
  // tracker
  compress->KeepRecoTrackMatchedParticles();
  compress->AddHitContainer("G4HIT_MVTX");
  compress->AddHitContainer("G4HIT_INTT");
  compress->AddHitContainer("G4HIT_TPC");
  compress->AddHitContainer("G4HIT_MICROMEGAS");
  se->registerSubsystem(compress);

  Fun4AllDstOutputManager *out = new Fun4AllDstOutputManager("DSTOUT", "DST_TRUTH_ANALYSIS-0000000004-00000.root");
  out->AddNode("EventHeader");
  out->AddNode("TOWER_CALIB_HCALIN");
  out->AddNode("CLUSTER_HCALIN");
  out->AddNode("TOWER_CALIB_HCALOUT");
  out->AddNode("CLUSTER_HCALOUT");
  out->AddNode("GlobalVertexMap");
  out->AddNode("TOWER_CALIB_CEMC");
  out->AddNode("CLUSTER_CEMC");
  out->AddNode("CLUSTER_POS_COR_CEMC");
  //  out->AddNode("G4HIT_BBC");
  //  out->AddNode("G4HIT_EPD");
  out->AddNode("PHHepMCGenEventMap");
  out->AddNode("G4HIT_BH_1");
  out->AddNode("G4TruthInfo");
  out->AddNode("SvtxTrackMap");
  out->AddNode("SvtxVertexMap");
  out->AddNode("SvtxTrackMap");
  out->AddNode("PHG4ParticleSvtxMap");
  out->AddNode("SvtxPHG4ParticleMap");
  se->registerOutputManager(out);

  se->run(nevnt);
  se->End();
  delete se;
  gSystem->Exit(0);
}
