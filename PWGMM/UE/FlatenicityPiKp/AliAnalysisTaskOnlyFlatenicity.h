/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. */
/* See cxx source for full Copyright notice */
/* Add a description of your MPI analysis */

#ifndef AliAnalysisTaskOnlyFlatenicity_H
#define AliAnalysisTaskOnlyFlatenicity_H

class AliESDtrackCuts;
class AliESDEvent;
class TList;
class TH1D;
class TH2D;
class TH3D;
class TH3F;
class TH1I;
class TF1;
class TProfile;
class THnSparse;

#include "AliAnalysisTaskSE.h"

#include "AliGenEventHeader.h"
#include "AliMCEvent.h"
#include "AliMCEventHandler.h"
#include "AliMCParticle.h"
#include "AliStack.h"
#include "TParticle.h"

#include <iostream>
#include <string>
#include <map>


class AliAnalysisTaskOnlyFlatenicity : public AliAnalysisTaskSE {
	public:
		AliAnalysisTaskOnlyFlatenicity();
		AliAnalysisTaskOnlyFlatenicity(const char *name);
		virtual ~AliAnalysisTaskOnlyFlatenicity();

		virtual void UserCreateOutputObjects();
		virtual void UserExec(Option_t *option);
		virtual void Terminate(Option_t *option);
		double GetFlatenicityV0();
		double GetMidRapidityMultiplicity();
		double GetFlatenicityTPC();
		double GetFlatenicityMC();
		double EtaCalibration(const double&);
		double EtaCalibrationEl(const double&);
		void MakeMCanalysis();
		void MakeDataanalysis();
		void MakePIDanalysis();
		void AnalyzeV0s();
		void SetPtMin(Double_t val) { fPtMin = val; } // Set pT cut for associated particles
		void SetNcl(UShort_t ncl) { fNcl = ncl; } // Set pT cut for associated particles
		void SetUseMC(Bool_t flat_flag = kFALSE) { fUseMC = flat_flag; } // use to analyse MC data
		void IsdEdxCalibrated(Bool_t dEdxCal = kTRUE) { fdEdxCalibrated = dEdxCal; }
		void SetDetectorForFlatenicity(TString det = "V0") { fDetFlat = det; }
		void SetDataPeriod(std::string period = "16l") { fPeriod = period;}
		void SetMCclosureTest(Bool_t flat_flag = kFALSE) { fIsMCclosure = flat_flag; }
		void SetDeltaV0(Bool_t deltav0 = kFALSE) { fDeltaV0 = deltav0; }
		void SetRemoveTrivialScaling(Bool_t flat_flag = kFALSE) { fRemoveTrivialScaling = flat_flag; }
		bool PhiCut(Double_t , Double_t , Double_t , Float_t , TF1* , TF1* );
		bool HasRecVertex();
		bool TOFPID(AliESDtrack*);
		int GetPidCode(Int_t);


	protected:
	private:
		AliESDEvent *fESD; //! input ESD event
		AliEventCuts fEventCuts;
		AliStack *fMCStack; //! MC stack
		AliMCEvent *fMC;    //! MC Event
		Bool_t fUseMC;      // analyze MC events
		Float_t fV0MMultiplicity;
		TString fDetFlat;
		Bool_t fIsMCclosure;
		Bool_t fDeltaV0;
		Bool_t fRemoveTrivialScaling;
		Int_t fnGen;
		AliPIDResponse* fPIDResponse;
		AliAnalysisFilter* fTrackFilter;
		AliAnalysisFilter* fTrackFilterPID;
		TList *fOutputList; //! output list in the root file
		Double_t fEtaCut;
		Double_t fPtMin;
		Double_t fNcl;
		Bool_t fdEdxCalibrated;
		TF1* fEtaCalibrationPos;
		TF1* fEtaCalibrationNeg;
		TF1* felededxfitPos;
		TF1* felededxfitNeg;
		TF1* fcutLow;
		TF1* fcutHigh;
		TF1* fcutDCAxy;
		std::string fPeriod;
		Double_t ftrackmult08;
		Double_t fv0mpercentile;
		Double_t fFlat;
		Double_t fFlatTPC;
		Float_t fFlatMC;
		AliMultSelection *fMultSelection;
		TH1F *hFlat;
		TH2F *hFlatVsMult; 
		TH2F *hFlatenicityMC;
		TH2F *hFlatenicityMCRec;
		TH2F *hFlatResponse;
		TH2F *hFlatVsPtMC;
		TProfile *hActivityV0McSect;
		TH2F *hFlatVsNchMC;
		TH3F *hNsigmaPiPos[4];
		TH3F *hNsigmaKPos[4];
		TH3F *hNsigmaPPos[4];
		TH2F *hPtTPCEtaPos[4];
		TH3F *hNsigmaPiNeg[4];
		TH3F *hNsigmaKNeg[4];
		TH3F *hNsigmaPNeg[4];
		TH2F *hPtTPCEtaNeg[4];
		TH3F* hBetaPos[4];
		TH3F* hBetaNeg[4];
		TH2F* hMomentumTOFEtaPos[4];
		TH2F* hMomentumTOFEtaNeg[4];
		TH2F* hPtTOFEtaPos[4];
		TH2F* hPtTOFEtaNeg[4];
		TH3F* hdEdx[4];
		TH2F* hPtrTPC[4];
		TH2F* hPtVsP[4];

		TProfile* pMIPVsEta;
		TProfile* pPlateauVsEta;

		//! Histograms for V0s
		TProfile* pMIPVsEtaV0s;
		TH2F* histPiV0[4];
		TH2F* histPV0[4];
		TH2F* histEV0[4];
		TH2F* histPiTof[4];
		TH2F* histPiTof2[4];


		AliAnalysisTaskOnlyFlatenicity(
				const AliAnalysisTaskOnlyFlatenicity &); // not implemented
		AliAnalysisTaskOnlyFlatenicity &
			operator=(const AliAnalysisTaskOnlyFlatenicity &); // not implemented

		ClassDef(AliAnalysisTaskOnlyFlatenicity, 3);
};

#endif

