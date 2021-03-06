#include <Riostream.h>
#include <TFile.h>
#include <AliRDHFCutsLctopKpi.h>
#include <AliAODPidHF.h>
#include <TClonesArray.h>
#include <TParameter.h>
#include <TF1.h>
#include <TCanvas.h>


//Use:
//Set hard coded commentet with //set this!!
// root[] .L makeInput...C++
// root[] makeInputAliAnalysisTaskSE...()
//similar macros for the other D mesons

//Author: Rosa Romita, r.romita@gsi.de


//macro to make a .root file which contains an AliRDHFCutsLctopKpi for AliAnalysisTaskSELambdac task

void SetupCombinedPID(AliRDHFCutsLctopKpi *cutsObj,Double_t threshold,TString priorFileName="noferini-priors.root") {

  cutsObj->GetPidHF()->SetUseCombined(kTRUE);
  cutsObj->GetPidHF()->SetPriorsHistos(priorFileName);
  cutsObj->GetPidHF()->SetCombDetectors(AliAODPidHF::kTPCTOF);
  for (Int_t ispecies=0;ispecies<AliPID::kSPECIES;++ispecies)
    cutsObj->SetPIDThreshold(static_cast<AliPID::EParticleType>(ispecies),threshold);
}



void makeInputAliAnalysisTaskSELctopKpi(){

  AliRDHFCutsLctopKpi* RDHFLctopKpiProd=new AliRDHFCutsLctopKpi();
  RDHFLctopKpiProd->SetName("LctopKpiProdCuts");
  RDHFLctopKpiProd->SetTitle("Production cuts for Lc analysis");

  AliRDHFCutsLctopKpi* RDHFLctopKpiAn=new AliRDHFCutsLctopKpi();
  RDHFLctopKpiAn->SetName("LctopKpiAnalysisCuts");
  RDHFLctopKpiAn->SetTitle("Analysis cuts for Lc analysis");

  AliESDtrackCuts* esdTrackCuts=new AliESDtrackCuts();
  esdTrackCuts->SetRequireSigmaToVertex(kFALSE);
  //default
  esdTrackCuts->SetRequireTPCRefit(kTRUE);
  esdTrackCuts->SetRequireITSRefit(kTRUE);
  esdTrackCuts->SetMinNClustersITS(4); // default is 5
  esdTrackCuts->SetMinNClustersTPC(70);
  esdTrackCuts->SetClusterRequirementITS(AliESDtrackCuts::kSPD,
					 AliESDtrackCuts::kAny); 
 // default is kBoth, otherwise kAny
  esdTrackCuts->SetMinDCAToVertexXY(0.);
  esdTrackCuts->SetPtRange(0.3,1.e10);


  RDHFLctopKpiProd->AddTrackCuts(esdTrackCuts);
  RDHFLctopKpiAn->AddTrackCuts(esdTrackCuts);

  const Int_t nvars=13;

  const Int_t nptbins=4;
  Float_t* ptbins;
  ptbins=new Float_t[nptbins+1];
  ptbins[0]=0.;
  ptbins[1]=2.;
  ptbins[2]=3.;
  ptbins[3]=4.;
  ptbins[4]=12.;
  

  Float_t** prodcutsval;
  prodcutsval=new Float_t*[nvars];
  for(Int_t iv=0;iv<nvars;iv++){
    prodcutsval[iv]=new Float_t[nptbins];
  }

  //  inv. mass [GeV]
  // pTK [GeV/c]
  // pTPi [GeV/c]
  // d0K [cm]   lower limit!
  // d0Pi [cm]  lower limit!
  // dist12 (cm)
  // sigmavert (cm)
  // dist prim-sec (cm)
  // pM=Max{pT1,pT2,pT3} (GeV/c)
  // cosThetaPoint
  // Sum d0^2 (cm^2)
  // dca cut (cm)
  for(Int_t ipt=0;ipt<nptbins;ipt++){
    prodcutsval[0][ipt]=0.18;
    prodcutsval[1][ipt]=0.4;
    prodcutsval[2][ipt]=0.5;
    prodcutsval[3][ipt]=0.;
    prodcutsval[4][ipt]=0.;
    prodcutsval[5][ipt]=0.01;
    prodcutsval[6][ipt]=0.06;
    prodcutsval[7][ipt]=0.005;
    prodcutsval[8][ipt]=0.7;
    prodcutsval[9][ipt]=0.;
    prodcutsval[10][ipt]=0.;
    prodcutsval[11][ipt]=0.05;
    prodcutsval[12][ipt]=0.4;
  }

  RDHFLctopKpiProd->SetPtBins(nptbins+1,ptbins);
  RDHFLctopKpiProd->SetCuts(nvars,nptbins,prodcutsval);

  Float_t** anacutsval;
  anacutsval=new Float_t*[nvars];
  for(Int_t ic=0;ic<nvars;ic++){anacutsval[ic]=new Float_t[nptbins];}
  for(Int_t ipt2=0;ipt2<nptbins;ipt2++){
   anacutsval[0][ipt2]=0.18;
   anacutsval[1][ipt2]=0.4;
   anacutsval[2][ipt2]=0.5;
   anacutsval[3][ipt2]=0.;
   anacutsval[4][ipt2]=0.;
   anacutsval[5][ipt2]=0.01;
   anacutsval[6][ipt2]=0.06;
   anacutsval[7][ipt2]=0.005;
   anacutsval[8][ipt2]=0.7;
   anacutsval[9][ipt2]=0.;
   anacutsval[10][ipt2]=0.;
   anacutsval[11][ipt2]=0.05;
   anacutsval[12][ipt2]=0.4;
  }

  // pt kaon
  anacutsval[1][0]=0.5;
  anacutsval[1][1]=0.85;
  anacutsval[1][2]=0.9;
  anacutsval[1][3]=0.4;
  //pt proton
  anacutsval[2][0]=0.5;
  anacutsval[2][1]=0.6;
  anacutsval[2][2]=0.9;
  anacutsval[2][3]=0.9;

  //pt pion
  anacutsval[12][0]=0.475;
  anacutsval[12][1]=0.75;
  anacutsval[12][2]=0.75;
  anacutsval[12][3]=0.7;

  anacutsval[5][0]=0.02;
  anacutsval[5][1]=0.025;
  anacutsval[5][2]=0.02;
  anacutsval[5][3]=0.01;

  anacutsval[7][0]=0.00625;
  anacutsval[7][1]=0.0125;
  anacutsval[7][2]=0.005;
  anacutsval[7][3]=0.007;

  anacutsval[9][0]=0.5;
  anacutsval[9][1]=0.2;
  anacutsval[9][2]=0.6;
  anacutsval[9][3]=0.;

  anacutsval[10][0]=0.00125;

  RDHFLctopKpiAn->SetPtBins(nptbins+1,ptbins);
  RDHFLctopKpiAn->SetCuts(nvars,nptbins,anacutsval);

 //  RDHFLc->SetRecoKF(); //set this if you want to recompute the secondary vertex with the KF package
    //pid settings
    //1. kaon: default one
  AliAODPidHF* pidObjK=new AliAODPidHF();
  Double_t sigmasK[5]={3.,1.,1.,3.,2.};
  pidObjK->SetSigma(sigmasK);
  pidObjK->SetAsym(kTRUE);
  pidObjK->SetMatch(1);
  pidObjK->SetTPC(kTRUE);
  pidObjK->SetTOF(kTRUE);
  Double_t plimK[2]={0.5,0.8};
  pidObjK->SetPLimit(plimK,2);
  pidObjK->SetTOFdecide(kTRUE);
  
  RDHFLctopKpiProd->SetPidHF(pidObjK);
  RDHFLctopKpiAn->SetPidHF(pidObjK);

    //2. pion 
  AliAODPidHF* pidObjpi=new AliAODPidHF();
  pidObjpi->SetTPC(kTRUE);
  Double_t sigmaspi[5]={3.,0.,0.,0.,0.};
  pidObjpi->SetSigma(sigmaspi);
//  pidObjpi->SetTOFdecide(kTRUE);

  RDHFLctopKpiProd->SetPidpion(pidObjpi);
  RDHFLctopKpiAn->SetPidpion(pidObjpi);

  // 3. proton
  AliAODPidHF* pidObjp=new AliAODPidHF();
  Double_t sigmasp[5]={3.,1.,1.,3.,2.};
  pidObjp->SetSigma(sigmasp);
  pidObjp->SetAsym(kTRUE);
  pidObjp->SetMatch(1);
  pidObjp->SetTPC(kTRUE);
  pidObjp->SetTOF(kTRUE);
  Double_t plimp[2]={1.,2.};
  pidObjp->SetPLimit(plimp,2);
  pidObjp->SetTOFdecide(kTRUE);

  RDHFLctopKpiProd->SetPidprot(pidObjp);
  RDHFLctopKpiAn->SetPidprot(pidObjp);

  // uncomment these lines for Baysian PID:
   Double_t threshold=0.3;
   SetupCombinedPID(RDHFLctopKpiAn  ,threshold);
   SetupCombinedPID(RDHFLctopKpiProd,threshold);
   RDHFLctopKpiAn  ->SetPIDStrategy(AliRDHFCutsLctopKpi::kCombined);
   RDHFLctopKpiProd->SetPIDStrategy(AliRDHFCutsLctopKpi::kCombined);


   AliPIDCombined *pid=RDHFLctopKpiAn->GetPidHF()->GetPidCombined();
   TH1* hplot=pid->GetPriorDistribution(static_cast<AliPID::EParticleType>(3));
   TCanvas *c1=new TCanvas();
   hplot->Draw();
  //


  //uncomment these lines to apply cuts with the KF package
  //RDHFLctopKpiAn  ->SetCutsStrategy(AliRDHFCutsLctopKpi::kKF);
  //RDHFLctopKpiProd->SetCutsStrategy(AliRDHFCutsLctopKpi::kKF);
  //for(Int_t ipt2=0;ipt2<nptbins;ipt2++){
  //   anacutsval[0][ipt2]=1.;  //if <0., no topological constraint
  //   anacutsval[1][ipt2]=2.;  //cut on the Chi2/Ndf
  //   prodcutsval[0][ipt2]=1.;  //if <0., no topological constraint
  //   prodcutsval[1][ipt2]=2.;  //cut on the Chi2/Ndf
  // }

  Bool_t pidflag=kTRUE;
  RDHFLctopKpiAn->SetUsePID(pidflag);
  RDHFLctopKpiProd->SetUsePID(pidflag);
  if(pidflag) cout<<"PID is used"<<endl;
  else cout<<"PID is not used"<<endl;

  cout<<"This is the object I'm going to save:"<<endl;
  RDHFLctopKpiProd->PrintAll();
  RDHFLctopKpiAn->PrintAll();
  TFile* fout=new TFile("prova.root","RECREATE"); 
  fout->cd();
  RDHFLctopKpiProd->Write();
  RDHFLctopKpiAn->Write();
  fout->Close();
  delete fout;
  delete pidObjp;
  delete pidObjpi;
  delete pidObjK;
  delete RDHFLctopKpiProd;
  delete RDHFLctopKpiAn;

}


//macro to make a .root file (for significance maximization) which contains an AliRDHFCutsLctopKpi with loose set of cuts  and TParameter with the tighest value of these cuts

void makeInputAliAnalysisTaskSESignificanceMaximization(){

  AliRDHFCutsLctopKpi* RDHFLctopKpi=new AliRDHFCutsLctopKpi();
  RDHFLctopKpi->SetName("loosercuts");
  RDHFLctopKpi->SetTitle("Cuts for significance maximization");

  AliESDtrackCuts* esdTrackCuts=new AliESDtrackCuts();
  esdTrackCuts->SetRequireSigmaToVertex(kFALSE);
  //default
  esdTrackCuts->SetRequireTPCRefit(kTRUE);
  esdTrackCuts->SetMinNClustersTPC(70);
  esdTrackCuts->SetRequireITSRefit(kTRUE);
  esdTrackCuts->SetMinNClustersITS(4);

  esdTrackCuts->SetClusterRequirementITS(AliESDtrackCuts::kSPD,AliESDtrackCuts::kAny);
  esdTrackCuts->SetMinDCAToVertexXY(0.);
  esdTrackCuts->SetEtaRange(-0.8,0.8);
  esdTrackCuts->SetPtRange(0.3,1.e10);
  
  RDHFLctopKpi->AddTrackCuts(esdTrackCuts);

  const Int_t nvars=13;

  const Int_t nptbins=4; //change this when adding pt bins!
  Float_t ptbins[nptbins+1];
  ptbins[0]=0.;
  ptbins[1]=2.;
  ptbins[2]=3.;
  ptbins[3]=4.;
  ptbins[4]=12.;

  RDHFLctopKpi->SetPtBins(nptbins+1,ptbins);

  Float_t** rdcutsvalmine;
  rdcutsvalmine=new Float_t*[nvars];
  for(Int_t iv=0;iv<nvars;iv++){
    rdcutsvalmine[iv]=new Float_t[nptbins];
  }

  //setting my cut values
  //  inv. mass [GeV]
  // pTK [GeV/c]
  // pTP [GeV/c]
  // d0K [cm]   lower limit!
  // d0Pi [cm]  lower limit!
  // dist12 (cm)
  // sigmavert (cm)
  // dist prim-sec (cm)
  // pM=Max{pT1,pT2,pT3} (GeV/c)
  // cosThetaPoint
  // Sum d0^2 (cm^2)
  // dca cut (cm)
  // pt pion
  Float_t cutsMatrixLctopKpiStand[nptbins][nvars]=
  {{0.18,0.4,0.5,0.,0.,0.01,0.06,0.005,0.7,0.,0.,0.05,0.4},
   {0.18,0.4,0.5,0.,0.,0.01,0.06,0.005,0.7,0.,0.,0.05,0.4},
   {0.18,0.4,0.5,0.,0.,0.01,0.06,0.005,0.7,0.,0.,0.05,0.4},
   {0.18,0.4,0.5,0.,0.,0.01,0.06,0.005,0.7,0.,0.,0.05,0.4}};

  //CREATE TRANSPOSE MATRIX...REVERSE INDICES as required by AliRDHFCuts
  Float_t **cutsMatrixTransposeStand=new Float_t*[nvars];
  for(Int_t iv=0;iv<nvars;iv++)cutsMatrixTransposeStand[iv]=new Float_t[nptbins];
  for (Int_t ibin=0;ibin<nptbins;ibin++){
    for (Int_t ivar = 0; ivar<nvars; ivar++){
      cutsMatrixTransposeStand[ivar][ibin]=cutsMatrixLctopKpiStand[ibin][ivar];
    }
  }
  RDHFLctopKpi->SetCuts(nvars,nptbins,cutsMatrixTransposeStand);


  Int_t nvarsforopt=RDHFLctopKpi->GetNVarsForOpt();
  Int_t dim=4; //set this!!
  Bool_t *boolforopt;
  boolforopt=new Bool_t[nvars];
  if(dim>nvarsforopt){
    cout<<"Number of variables for optimization has probably changed, check and edit accordingly"<<endl;
    return;
  } else {
    if(dim==nvarsforopt){
      boolforopt=RDHFLctopKpi->GetVarsForOpt();
    }else{
      TString *names;
      names=new TString[nvars];
      TString answer="";
      Int_t checktrue=0;
      names=RDHFLctopKpi->GetVarNames();
      for(Int_t i=0;i<nvars;i++){
	cout<<names[i]<<" for opt? (y/n)"<<endl;
	cin>>answer;
	if(answer=="y") {
	  boolforopt[i]=kTRUE;
	  checktrue++;
	}
	else boolforopt[i]=kFALSE;
      }
      if (checktrue!=dim) {
	cout<<"Error! You set "<<checktrue<<" kTRUE instead of "<<dim<<endl;
	return;
      }
      RDHFLctopKpi->SetVarsForOpt(dim,boolforopt);
    }
  }


  Float_t tighterval[dim][nptbins];
  // 5 dist12 (cm)        <---
  // 7 dist prim-sec (cm) <---
  // 9 cosThetaPoint      <---
  // 10 Sum d0^2 (cm^2)   <---
  // 11 dca cut (cm)      
  // {0.18,0.4,0.5,0.,0.,0.01 <--- ,0.06,0.005 <--- ,0.7,0. <--- ,0. <--- ,0.05 }

  //number of steps for each variable is set in the AddTask arguments (default=8)
  //set this!!
  for(Int_t ipt=0;ipt<nptbins;ipt++){
    tighterval[0][ipt]=0.03;
    tighterval[1][ipt]=0.02;
    tighterval[2][ipt]=1.;
    tighterval[3][ipt]=0.01;
  }



  TString name=""; 
  Int_t arrdim=dim*nptbins;
  cout<<"Will save "<<arrdim<<" TParameter<float>"<<endl;
  TClonesArray max("TParameter<float>",arrdim);
  for(Int_t ival=0;ival<dim;ival++){
    for(Int_t jpt=0;jpt<nptbins;jpt++){
      name=Form("par%dptbin%d",ival,jpt);
      cout<<"Setting "<<name.Data()<<" to "<<tighterval[ival][jpt]<<endl;
      new(max[jpt*dim+ival])TParameter<float>(name.Data(),tighterval[ival][jpt]);
    }
  }

  Bool_t flagPID=kFALSE;
  RDHFLctopKpi->SetUsePID(flagPID);

  RDHFLctopKpi->PrintAll();
  printf("Use PID? %s\n",flagPID ? "yes" : "no");

    //pid settings
    //1. kaon: default one
  AliAODPidHF* pidObjK=new AliAODPidHF();
  Double_t sigmasK[5]={3.,1.,1.,3.,2.};
  pidObjK->SetSigma(sigmasK);
  pidObjK->SetAsym(kTRUE);
  pidObjK->SetMatch(1);
  pidObjK->SetTPC(kTRUE);
  pidObjK->SetTOF(kTRUE);
  pidObjK->SetITS(kTRUE);
  Double_t plimK[2]={0.5,0.8};
  pidObjK->SetPLimit(plimK,2);
  pidObjK->SetTOFdecide(kTRUE);
  
  RDHFLctopKpi->SetPidHF(pidObjK);

    //2. pion 
  AliAODPidHF* pidObjpi=new AliAODPidHF();
  pidObjpi->SetTPC(kTRUE);
  Double_t sigmaspi[5]={3.,0.,0.,0.,0.};
  pidObjpi->SetSigma(sigmaspi);
  pidObjpi->SetTOFdecide(kTRUE);

  RDHFLctopKpi->SetPidpion(pidObjpi);

  // 3. proton
  AliAODPidHF* pidObjp=new AliAODPidHF();
  Double_t sigmasp[5]={3.,1.,1.,3.,2.};
  pidObjp->SetSigma(sigmasp);
  pidObjp->SetAsym(kTRUE);
  pidObjp->SetMatch(1);
  pidObjp->SetTPC(kTRUE);
  pidObjp->SetTOF(kTRUE);
  pidObjp->SetITS(kTRUE);
  Double_t plimp[2]={1.,2.};
  pidObjp->SetPLimit(plimp,2);
  pidObjp->SetTOFdecide(kTRUE);

  RDHFLctopKpi->SetPidprot(pidObjp);

  //activate pileup rejection (for pp)
  //RDHFLctopKpi->SetOptPileup(AliRDHFCuts::kRejectPileupEvent);

  //Do not recalculate the vertex
  RDHFLctopKpi->SetRemoveDaughtersFromPrim(kFALSE); //activate for pp

  TString cent="";
  //centrality selection (Pb-Pb)
  Float_t minc=20,maxc=80;
  RDHFLctopKpi->SetMinCentrality(minc);
  RDHFLctopKpi->SetMaxCentrality(maxc);
  cent=Form("%.0f%.0f",minc,maxc);
  //  RDHFLctopKpi->SetUseCentrality(AliRDHFCuts::kCentV0M); //kCentOff,kCentV0M,kCentTRK,kCentTKL,kCentCL1,kCentInvalid
  RDHFLctopKpi->SetUseCentrality(AliRDHFCuts::kCentOff); //kCentOff,kCentV0M,kCentTRK,kCentTKL,kCentCL1,kCentInvalid

  //temporary
  //  RDHFLctopKpi->SetFixRefs();

  TFile* fout=new TFile(Form("cuts4SignifMaxim%s%s%sRecVtx%sPileupRej.root", RDHFLctopKpi->GetUseCentrality()==0 ? "pp" : "PbPb",cent.Data(),RDHFLctopKpi->GetIsPrimaryWithoutDaughters() ? "" : "No",RDHFLctopKpi->GetOptPileUp() ? "" : "No"),"recreate");   //set this!! 

  fout->cd();
  RDHFLctopKpi->Write();
  max.Write();
  fout->Close();
 
}

