#include <iostream>
#include <vector>
#include <string>
#include <TH1F.h>
using namespace std;

void plots()
{
    vector<std::string> names_files {"bkg1.root", "bkg2.root", "signal1.root", "signal2.root", "signal3.root", "signal4.root" };

    vector<std::string> names {"t#bar{t} h -> #tau+ #tau-", "t#bar{t}b#bar{b}/h", "t#bar{t}Z' m(Z')= 350 GeV", "t#bar{t}Z' m(Z')= 1000 GeV", "t#bar{t}Z' m(Z')= 1500 GeV", "t#bar{t}Z' m(Z')= 2000 GeV" };
    
    vector<std::string> plots {"N_Merged1", "Efficiencies_e", "StMet_e", "PT_Scalar_leptons_e", "PT_Vector_leptons_e", "Efficiencies_mu", "StMet_mu", "PT_Scalar_leptons_mu", "PT_Vector_leptons_mu", "M_leptons_mu", "M_leptons_e" };

    vector<std::string> plots_names {"Merged categories", "Number of event after cuts for e #nu_{e}", "Total scalar PT of final states for e #nu_{e}", "Scalar PT of #tau+ #tau- for e #nu_{e}", "PT of #tau+ #tau- for e #nu_{e}", "Number of event after cuts for #mu #nu_{#mu}", "Total scalar PT of final states for #mu #nu_{#mu}", "Scalar PT of #tau+ #tau- for #mu #nu_{#mu}", "PT of #tau+ #tau- for #mu #nu_{#mu}", "Recostructed mass of #tau+ #tau- for #mu #nu_{#mu}", "Recostructed mass of #tau+ #tau- for #e #nu_{#e}"};
   

    vector<std::string> x_labels {"Merge Categories", "Cuts", "PT  [GeV]", "|P_{T}| (#tau+ #tau-) [GeV]", "P_{T} (#tau+ #tau-) [GeV]", "Cuts", "PT  [GeV]", "|P_{T}| (#tau+ #tau-) [GeV]", "P_{T} (#tau+ #tau-) [GeV]", "M (#tau+ #tau-) [GeV]", "M (#tau+ #tau-) [GeV]"};
    
    //"(1,2),(3,4)", "(1,3),(2,4)", "(1,4),(2,3)",
    // "(b_{1}j_{1}j_{2}),(b_{2}j_{3}j_{4})", "(b_{2}j_{1}j_{2}),(b_{1}j_{3}j_{4})", "(b_{1}j_{1}j_{3}),(b_{2}j_{2}j_{4})", "(b_{2}j_{1}j_{3}),(b_{1}j_{2}j_{4})", "(b_{1}j_{1}j_{4}),(b_{2}j_{2}j_{3})", "(b_{2}j_{1}j_{4}),(b_{1}j_{2}j_{3})"

    //vector<std::string> plots {"deltaR_b1b2"};


    vector<int> colors {82, 5, 6, 2, 4, 7, 6, 8};

    vector<int> linestyles {1, 1, 10, 10, 10, 10, 10, 10};
      
     
    TList *l = new TList();
    for(int i=0; i<plots.size(); i++)
    {
        THStack *hs = new THStack("hs", " ");
        TCanvas *c2 = new TCanvas(plots[i].c_str(),"Histos",1280,1024);  
        Double_t x_1,x_2;
        Double_t y_1,y_2;

        x_1 = 0.65;
        x_2 = 0.85;

        y_1 = 0.65;
        y_2 = 0.85;
        auto legend = new TLegend(x_1,y_1,x_2,y_2);
    for (int j=0; j<names.size(); j++)
    {    
        TFile f(names_files[j].c_str());
        TH1F *h = (TH1F*)f.Get(plots[i].c_str());
        h->SetDirectory(0);
        h->SetLineColor(colors[j]);
        h->SetLineStyle(linestyles[j]);
        h->SetLineWidth(3);
        h->Scale(1.0/h->Integral());
   	legend->AddEntry(h,names[j].c_str(),"l");
        legend->SetBorderSize(0);
        hs->Add(h); 
    }   
        hs->Draw("NOSTACK HIST");
        hs->GetXaxis()->SetTitle(x_labels[i].c_str());
        hs->GetYaxis()->SetTitle("a.u.");
        legend->Draw();
        l->Add(c2);
        std::string filename = plots[i] + "5cut.png";
        c2->SaveAs(filename.c_str());
    }
    
    TFile* Output = new TFile("joined.root", "RECREATE"); 
    l->Write();
    Output->Close();
    
}
    //PRUEBA *********************************************************
