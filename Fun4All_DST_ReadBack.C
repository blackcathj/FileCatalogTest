// $Id: $

/*!
 * \file Fun4All_DST_ReadBack.C
 * \brief 
 * \author Jin Huang <jhuang@bnl.gov>
 * \version $Revision:   $
 * \date $Date: $
 */

#include <G4_Intt.C>
#include <G4_Micromegas.C>
#include <G4_Mvtx.C>
#include <G4_TPC.C>
#include <QA.C>

#include <fun4all/Fun4AllDstInputManager.h>
#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/SubsysReco.h>

#include <g4eval/SvtxEvaluator.h>

#include <TSystem.h>

R__LOAD_LIBRARY(libg4detectors.so)
R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libg4eval.so)

void Fun4All_DST_ReadBack(const int nevnt = 0)
{
  gSystem->Load("libg4dst");
  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(1);

  {
    Fun4AllInputManager *in = new Fun4AllDstInputManager("DST_TRUTH_ANALYSIS");
    in->fileopen("DST_TRUTH_ANALYSIS-0000000004-00000.root");
    se->registerInputManager(in);
  }

  //----------------
  // Tracking evaluation
  //----------------
  SvtxEvaluator *eval;
  eval = new SvtxEvaluator("SVTXEVALUATOR", "DST_TRUTH_ANALYSIS_tracking_eval.root", "SvtxTrackMap",
                           G4MVTX::n_maps_layer,
                           G4INTT::n_intt_layer,
                           G4TPC::n_gas_layer,
                           G4MICROMEGAS::n_micromegas_layer);
  eval->do_info_eval(false);
  eval->do_vertex_eval(true);
  eval->do_gpoint_eval(true);
  eval->do_g4hit_eval(false);
  eval->do_hit_eval(false);
  eval->do_cluster_eval(false);
  eval->do_g4cluster_eval(false);
  eval->do_gtrack_eval(true);
  eval->do_track_eval(true);
  eval->do_gseed_eval(false);
  eval->do_track_match(false);
  eval->do_eval_light(true);
  eval->do_vtx_eval_light(true);
  eval->scan_for_embedded(true);
  eval->scan_for_primaries(false);
  //  eval->Verbosity(1);
  se->registerSubsystem(eval);

  se->run(nevnt);
  se->End();
  delete se;
  gSystem->Exit(0);
}
