#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <iostream>

void SingleLayerPlot()
{
//=========Macro generated from canvas: c1/First canvas
//=========  (Mon Mar 20 14:45:18 2017) by ROOT version6.08/06
// First define all the hexagons for plotting
   TCanvas *c1 = new TCanvas("c1", "First canvas",0,45,900,900);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH2Poly *SingleLayer = new TH2Poly("SingleLayer", "Pedestal(ADC counts)", 25, -7.14598, 7.14598, 25, -6.1886, 6.1886);
   
   Double_t Graph_fx1[4] = {
   6.171528,
   6.496345,
   7.14598,
   6.496345};
   Double_t Graph_fy1[4] = {
   0.5626,
   1.166027e-08,
   1.282629e-08,
   1.1252};
   TGraph *graph = new TGraph(4,Graph_fx1,Graph_fy1);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx2[4] = {
   6.171528,
   6.496345,
   7.14598,
   6.496345};
   Double_t Graph_fy2[4] = {
   -0.5626,
   -1.1252,
   1.282629e-08,
   1.166027e-08};
   graph = new TGraph(4,Graph_fx2,Graph_fy2);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx3[4] = {
   5.197076,
   5.521893,
   6.171528,
   5.521893};
   Double_t Graph_fy3[4] = {
   2.2504,
   1.6878,
   1.6878,
   2.813};
   graph = new TGraph(4,Graph_fx3,Graph_fy3);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx4[6] = {
   5.197076,
   5.521893,
   6.171528,
   6.496345,
   6.171528,
   5.521893};
   Double_t Graph_fy4[6] = {
   1.1252,
   0.5626,
   0.5626,
   1.1252,
   1.6878,
   1.6878};
   graph = new TGraph(6,Graph_fx4,Graph_fy4);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx5[6] = {
   5.197076,
   5.521893,
   6.171528,
   6.496345,
   6.171528,
   5.521893};
   Double_t Graph_fy5[6] = {
   9.328214e-09,
   -0.5626,
   -0.5626,
   1.166027e-08,
   0.5626,
   0.5626};
   graph = new TGraph(6,Graph_fx5,Graph_fy5);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx6[6] = {
   5.197076,
   5.521893,
   6.171528,
   6.496345,
   6.171528,
   5.521893};
   Double_t Graph_fy6[6] = {
   -1.1252,
   -1.6878,
   -1.6878,
   -1.1252,
   -0.5626,
   -0.5626};
   graph = new TGraph(6,Graph_fx6,Graph_fy6);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx7[4] = {
   5.197076,
   5.521893,
   6.171528,
   5.521893};
   Double_t Graph_fy7[4] = {
   -2.2504,
   -2.813,
   -1.6878,
   -1.6878};
   graph = new TGraph(4,Graph_fx7,Graph_fy7);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx8[4] = {
   4.222624,
   4.547442,
   5.197076,
   4.547442};
   Double_t Graph_fy8[4] = {
   3.9382,
   3.3756,
   3.3756,
   4.5008};
   graph = new TGraph(4,Graph_fx8,Graph_fy8);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx9[6] = {
   4.222624,
   4.547442,
   5.197076,
   5.521893,
   5.197076,
   4.547442};
   Double_t Graph_fy9[6] = {
   2.813,
   2.2504,
   2.2504,
   2.813,
   3.3756,
   3.3756};
   graph = new TGraph(6,Graph_fx9,Graph_fy9);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx10[6] = {
   4.222624,
   4.547442,
   5.197076,
   5.521893,
   5.197076,
   4.547442};
   Double_t Graph_fy10[6] = {
   1.6878,
   1.1252,
   1.1252,
   1.6878,
   2.2504,
   2.2504};
   graph = new TGraph(6,Graph_fx10,Graph_fy10);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx11[6] = {
   4.222624,
   4.547442,
   5.197076,
   5.521893,
   5.197076,
   4.547442};
   Double_t Graph_fy11[6] = {
   0.5626,
   8.162187e-09,
   9.328214e-09,
   0.5626,
   1.1252,
   1.1252};
   graph = new TGraph(6,Graph_fx11,Graph_fy11);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx12[6] = {
   4.222624,
   4.547441,
   5.197076,
   5.521893,
   5.197076,
   4.547442};
   Double_t Graph_fy12[6] = {
   -0.5626,
   -1.1252,
   -1.1252,
   -0.5626,
   9.328214e-09,
   8.162187e-09};
   graph = new TGraph(6,Graph_fx12,Graph_fy12);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx13[6] = {
   4.222624,
   4.547441,
   5.197076,
   5.521893,
   5.197076,
   4.547441};
   Double_t Graph_fy13[6] = {
   -1.6878,
   -2.2504,
   -2.2504,
   -1.6878,
   -1.1252,
   -1.1252};
   graph = new TGraph(6,Graph_fx13,Graph_fy13);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx14[6] = {
   4.222624,
   4.547441,
   5.197076,
   5.521893,
   5.197076,
   4.547441};
   Double_t Graph_fy14[6] = {
   -2.813,
   -3.3756,
   -3.3756,
   -2.813,
   -2.2504,
   -2.2504};
   graph = new TGraph(6,Graph_fx14,Graph_fy14);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx15[4] = {
   4.222624,
   4.547441,
   5.197076,
   4.547441};
   Double_t Graph_fy15[4] = {
   -3.9382,
   -4.5008,
   -3.3756,
   -3.3756};
   graph = new TGraph(4,Graph_fx15,Graph_fy15);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx16[4] = {
   3.248173,
   3.57299,
   4.222624,
   3.57299};
   Double_t Graph_fy16[4] = {
   5.626,
   5.0634,
   5.0634,
   6.1886};
   graph = new TGraph(4,Graph_fx16,Graph_fy16);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx17[6] = {
   3.248173,
   3.57299,
   4.222624,
   4.547442,
   4.222624,
   3.57299};
   Double_t Graph_fy17[6] = {
   4.5008,
   3.9382,
   3.9382,
   4.5008,
   5.0634,
   5.0634};
   graph = new TGraph(6,Graph_fx17,Graph_fy17);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx18[6] = {
   3.248173,
   3.57299,
   4.222624,
   4.547442,
   4.222624,
   3.57299};
   Double_t Graph_fy18[6] = {
   3.3756,
   2.813,
   2.813,
   3.3756,
   3.9382,
   3.9382};
   graph = new TGraph(6,Graph_fx18,Graph_fy18);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx19[6] = {
   3.248173,
   3.57299,
   4.222624,
   4.547442,
   4.222624,
   3.57299};
   Double_t Graph_fy19[6] = {
   2.2504,
   1.6878,
   1.6878,
   2.2504,
   2.813,
   2.813};
   graph = new TGraph(6,Graph_fx19,Graph_fy19);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx20[6] = {
   3.248173,
   3.57299,
   4.222624,
   4.547442,
   4.222624,
   3.57299};
   Double_t Graph_fy20[6] = {
   1.1252,
   0.5626,
   0.5626,
   1.1252,
   1.6878,
   1.6878};
   graph = new TGraph(6,Graph_fx20,Graph_fy20);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx21[6] = {
   3.248173,
   3.57299,
   4.222624,
   4.547442,
   4.222624,
   3.57299};
   Double_t Graph_fy21[6] = {
   5.830134e-09,
   -0.5626,
   -0.5626,
   8.162187e-09,
   0.5626,
   0.5626};
   graph = new TGraph(6,Graph_fx21,Graph_fy21);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx22[6] = {
   3.248172,
   3.57299,
   4.222624,
   4.547441,
   4.222624,
   3.57299};
   Double_t Graph_fy22[6] = {
   -1.1252,
   -1.6878,
   -1.6878,
   -1.1252,
   -0.5626,
   -0.5626};
   graph = new TGraph(6,Graph_fx22,Graph_fy22);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx23[6] = {
   3.248172,
   3.57299,
   4.222624,
   4.547441,
   4.222624,
   3.57299};
   Double_t Graph_fy23[6] = {
   -2.2504,
   -2.813,
   -2.813,
   -2.2504,
   -1.6878,
   -1.6878};
   graph = new TGraph(6,Graph_fx23,Graph_fy23);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx24[6] = {
   3.248172,
   3.57299,
   4.222624,
   4.547441,
   4.222624,
   3.57299};
   Double_t Graph_fy24[6] = {
   -3.3756,
   -3.9382,
   -3.9382,
   -3.3756,
   -2.813,
   -2.813};
   graph = new TGraph(6,Graph_fx24,Graph_fy24);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx25[6] = {
   3.248172,
   3.57299,
   4.222624,
   4.547441,
   4.222624,
   3.57299};
   Double_t Graph_fy25[6] = {
   -4.5008,
   -5.0634,
   -5.0634,
   -4.5008,
   -3.9382,
   -3.9382};
   graph = new TGraph(6,Graph_fx25,Graph_fy25);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx26[4] = {
   3.248172,
   3.57299,
   4.222624,
   3.57299};
   Double_t Graph_fy26[4] = {
   -5.626,
   -6.1886,
   -5.0634,
   -5.0634};
   graph = new TGraph(4,Graph_fx26,Graph_fy26);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx27[4] = {
   2.273721,
   2.598538,
   3.248173,
   3.57299};
   Double_t Graph_fy27[4] = {
   6.1886,
   5.626,
   5.626,
   6.1886};
   graph = new TGraph(4,Graph_fx27,Graph_fy27);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx28[6] = {
   2.273721,
   2.598538,
   3.248173,
   3.57299,
   3.248173,
   2.598538};
   Double_t Graph_fy28[6] = {
   5.0634,
   4.5008,
   4.5008,
   5.0634,
   5.626,
   5.626};
   graph = new TGraph(6,Graph_fx28,Graph_fy28);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx29[6] = {
   2.273721,
   2.598538,
   3.248173,
   3.57299,
   3.248173,
   2.598538};
   Double_t Graph_fy29[6] = {
   3.9382,
   3.3756,
   3.3756,
   3.9382,
   4.5008,
   4.5008};
   graph = new TGraph(6,Graph_fx29,Graph_fy29);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx30[6] = {
   2.273721,
   2.598538,
   3.248173,
   3.57299,
   3.248173,
   2.598538};
   Double_t Graph_fy30[6] = {
   2.813,
   2.2504,
   2.2504,
   2.813,
   3.3756,
   3.3756};
   graph = new TGraph(6,Graph_fx30,Graph_fy30);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx31[6] = {
   2.273721,
   2.598538,
   3.248173,
   3.57299,
   3.248173,
   2.598538};
   Double_t Graph_fy31[6] = {
   1.6878,
   1.1252,
   1.1252,
   1.6878,
   2.2504,
   2.2504};
   graph = new TGraph(6,Graph_fx31,Graph_fy31);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx32[6] = {
   2.273721,
   2.598538,
   3.248173,
   3.57299,
   3.248173,
   2.598538};
   Double_t Graph_fy32[6] = {
   0.5626,
   4.664107e-09,
   5.830134e-09,
   0.5626,
   1.1252,
   1.1252};
   graph = new TGraph(6,Graph_fx32,Graph_fy32);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx33[6] = {
   2.273721,
   2.598538,
   3.248172,
   3.57299,
   3.248173,
   2.598538};
   Double_t Graph_fy33[6] = {
   -0.5626,
   -1.1252,
   -1.1252,
   -0.5626,
   5.830134e-09,
   4.664107e-09};
   graph = new TGraph(6,Graph_fx33,Graph_fy33);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx34[6] = {
   2.273721,
   2.598538,
   3.248172,
   3.57299,
   3.248172,
   2.598538};
   Double_t Graph_fy34[6] = {
   -1.6878,
   -2.2504,
   -2.2504,
   -1.6878,
   -1.1252,
   -1.1252};
   graph = new TGraph(6,Graph_fx34,Graph_fy34);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx35[6] = {
   2.273721,
   2.598538,
   3.248172,
   3.57299,
   3.248172,
   2.598538};
   Double_t Graph_fy35[6] = {
   -2.813,
   -3.3756,
   -3.3756,
   -2.813,
   -2.2504,
   -2.2504};
   graph = new TGraph(6,Graph_fx35,Graph_fy35);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx36[6] = {
   2.273721,
   2.598538,
   3.248172,
   3.57299,
   3.248172,
   2.598538};
   Double_t Graph_fy36[6] = {
   -3.9382,
   -4.5008,
   -4.5008,
   -3.9382,
   -3.3756,
   -3.3756};
   graph = new TGraph(6,Graph_fx36,Graph_fy36);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx37[6] = {
   2.273721,
   2.598538,
   3.248172,
   3.57299,
   3.248172,
   2.598538};
   Double_t Graph_fy37[6] = {
   -5.0634,
   -5.626,
   -5.626,
   -5.0634,
   -4.5008,
   -4.5008};
   graph = new TGraph(6,Graph_fx37,Graph_fy37);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx38[4] = {
   2.273721,
   3.57299,
   3.248172,
   2.598538};
   Double_t Graph_fy38[4] = {
   -6.1886,
   -6.1886,
   -5.626,
   -5.626};
   graph = new TGraph(4,Graph_fx38,Graph_fy38);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx39[6] = {
   1.299269,
   1.624086,
   2.273721,
   2.598538,
   2.273721,
   1.624086};
   Double_t Graph_fy39[6] = {
   5.626,
   5.0634,
   5.0634,
   5.626,
   6.1886,
   6.1886};
   graph = new TGraph(6,Graph_fx39,Graph_fy39);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx40[6] = {
   1.299269,
   1.624086,
   2.273721,
   2.598538,
   2.273721,
   1.624086};
   Double_t Graph_fy40[6] = {
   4.5008,
   3.9382,
   3.9382,
   4.5008,
   5.0634,
   5.0634};
   graph = new TGraph(6,Graph_fx40,Graph_fy40);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx41[6] = {
   1.299269,
   1.624086,
   2.273721,
   2.598538,
   2.273721,
   1.624086};
   Double_t Graph_fy41[6] = {
   3.3756,
   2.813,
   2.813,
   3.3756,
   3.9382,
   3.9382};
   graph = new TGraph(6,Graph_fx41,Graph_fy41);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx42[6] = {
   1.299269,
   1.624086,
   2.273721,
   2.598538,
   2.273721,
   1.624086};
   Double_t Graph_fy42[6] = {
   2.2504,
   1.6878,
   1.6878,
   2.2504,
   2.813,
   2.813};
   graph = new TGraph(6,Graph_fx42,Graph_fy42);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx43[6] = {
   1.299269,
   1.624086,
   2.273721,
   2.598538,
   2.273721,
   1.624086};
   Double_t Graph_fy43[6] = {
   1.1252,
   0.5626,
   0.5626,
   1.1252,
   1.6878,
   1.6878};
   graph = new TGraph(6,Graph_fx43,Graph_fy43);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx44[6] = {
   1.299269,
   1.624086,
   2.273721,
   2.598538,
   2.273721,
   1.624086};
   Double_t Graph_fy44[6] = {
   2.332053e-09,
   -0.5626,
   -0.5626,
   4.664107e-09,
   0.5626,
   0.5626};
   graph = new TGraph(6,Graph_fx44,Graph_fy44);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx45[6] = {
   1.299269,
   1.624086,
   2.273721,
   2.598538,
   2.273721,
   1.624086};
   Double_t Graph_fy45[6] = {
   -1.1252,
   -1.6878,
   -1.6878,
   -1.1252,
   -0.5626,
   -0.5626};
   graph = new TGraph(6,Graph_fx45,Graph_fy45);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx46[6] = {
   1.299269,
   1.624086,
   2.273721,
   2.598538,
   2.273721,
   1.624086};
   Double_t Graph_fy46[6] = {
   -2.2504,
   -2.813,
   -2.813,
   -2.2504,
   -1.6878,
   -1.6878};
   graph = new TGraph(6,Graph_fx46,Graph_fy46);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx47[6] = {
   1.299269,
   1.624086,
   2.273721,
   2.598538,
   2.273721,
   1.624086};
   Double_t Graph_fy47[6] = {
   -3.3756,
   -3.9382,
   -3.9382,
   -3.3756,
   -2.813,
   -2.813};
   graph = new TGraph(6,Graph_fx47,Graph_fy47);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx48[6] = {
   1.299269,
   1.624086,
   2.273721,
   2.598538,
   2.273721,
   1.624086};
   Double_t Graph_fy48[6] = {
   -4.5008,
   -5.0634,
   -5.0634,
   -4.5008,
   -3.9382,
   -3.9382};
   graph = new TGraph(6,Graph_fx48,Graph_fy48);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx49[6] = {
   1.299269,
   1.624086,
   2.273721,
   2.598538,
   2.273721,
   1.624086};
   Double_t Graph_fy49[6] = {
   -5.626,
   -6.1886,
   -6.1886,
   -5.626,
   -5.0634,
   -5.0634};
   graph = new TGraph(6,Graph_fx49,Graph_fy49);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx50[4] = {
   0.3248173,
   0.6496345,
   1.299269,
   1.624086};
   Double_t Graph_fy50[4] = {
   6.1886,
   5.626,
   5.626,
   6.1886};
   graph = new TGraph(4,Graph_fx50,Graph_fy50);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx51[6] = {
   0.3248173,
   0.6496345,
   1.299269,
   1.624086,
   1.299269,
   0.6496345};
   Double_t Graph_fy51[6] = {
   5.0634,
   4.5008,
   4.5008,
   5.0634,
   5.626,
   5.626};
   graph = new TGraph(6,Graph_fx51,Graph_fy51);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx52[6] = {
   0.3248173,
   0.6496345,
   1.299269,
   1.624086,
   1.299269,
   0.6496345};
   Double_t Graph_fy52[6] = {
   3.9382,
   3.3756,
   3.3756,
   3.9382,
   4.5008,
   4.5008};
   graph = new TGraph(6,Graph_fx52,Graph_fy52);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx53[6] = {
   0.3248173,
   0.6496345,
   1.299269,
   1.624086,
   1.299269,
   0.6496345};
   Double_t Graph_fy53[6] = {
   2.813,
   2.2504,
   2.2504,
   2.813,
   3.3756,
   3.3756};
   graph = new TGraph(6,Graph_fx53,Graph_fy53);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx54[6] = {
   0.3248173,
   0.6496345,
   1.299269,
   1.624086,
   1.299269,
   0.6496345};
   Double_t Graph_fy54[6] = {
   1.6878,
   1.1252,
   1.1252,
   1.6878,
   2.2504,
   2.2504};
   graph = new TGraph(6,Graph_fx54,Graph_fy54);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx55[6] = {
   0.3248173,
   0.6496345,
   1.299269,
   1.624086,
   1.299269,
   0.6496345};
   Double_t Graph_fy55[6] = {
   0.5626,
   1.166027e-09,
   2.332053e-09,
   0.5626,
   1.1252,
   1.1252};
   graph = new TGraph(6,Graph_fx55,Graph_fy55);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx56[6] = {
   0.3248172,
   0.6496345,
   1.299269,
   1.624086,
   1.299269,
   0.6496345};
   Double_t Graph_fy56[6] = {
   -0.5626,
   -1.1252,
   -1.1252,
   -0.5626,
   2.332053e-09,
   1.166027e-09};
   graph = new TGraph(6,Graph_fx56,Graph_fy56);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx57[6] = {
   0.3248172,
   0.6496345,
   1.299269,
   1.624086,
   1.299269,
   0.6496345};
   Double_t Graph_fy57[6] = {
   -1.6878,
   -2.2504,
   -2.2504,
   -1.6878,
   -1.1252,
   -1.1252};
   graph = new TGraph(6,Graph_fx57,Graph_fy57);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx58[6] = {
   0.3248172,
   0.6496345,
   1.299269,
   1.624086,
   1.299269,
   0.6496345};
   Double_t Graph_fy58[6] = {
   -2.813,
   -3.3756,
   -3.3756,
   -2.813,
   -2.2504,
   -2.2504};
   graph = new TGraph(6,Graph_fx58,Graph_fy58);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx59[6] = {
   0.3248172,
   0.6496345,
   1.299269,
   1.624086,
   1.299269,
   0.6496345};
   Double_t Graph_fy59[6] = {
   -3.9382,
   -4.5008,
   -4.5008,
   -3.9382,
   -3.3756,
   -3.3756};
   graph = new TGraph(6,Graph_fx59,Graph_fy59);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx60[6] = {
   0.3248172,
   0.6496345,
   1.299269,
   1.624086,
   1.299269,
   0.6496345};
   Double_t Graph_fy60[6] = {
   -5.0634,
   -5.626,
   -5.626,
   -5.0634,
   -4.5008,
   -4.5008};
   graph = new TGraph(6,Graph_fx60,Graph_fy60);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx61[4] = {
   0.3248172,
   1.624086,
   1.299269,
   0.6496345};
   Double_t Graph_fy61[4] = {
   -6.1886,
   -6.1886,
   -5.626,
   -5.626};
   graph = new TGraph(4,Graph_fx61,Graph_fy61);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx62[6] = {
   -0.6496345,
   -0.3248172,
   0.3248173,
   0.6496345,
   0.3248173,
   -0.3248172};
   Double_t Graph_fy62[6] = {
   5.626,
   5.0634,
   5.0634,
   5.626,
   6.1886,
   6.1886};
   graph = new TGraph(6,Graph_fx62,Graph_fy62);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx63[6] = {
   -0.6496345,
   -0.3248172,
   0.3248173,
   0.6496345,
   0.3248173,
   -0.3248172};
   Double_t Graph_fy63[6] = {
   4.5008,
   3.9382,
   3.9382,
   4.5008,
   5.0634,
   5.0634};
   graph = new TGraph(6,Graph_fx63,Graph_fy63);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx64[6] = {
   -0.6496345,
   -0.3248172,
   0.3248173,
   0.6496345,
   0.3248173,
   -0.3248172};
   Double_t Graph_fy64[6] = {
   3.3756,
   2.813,
   2.813,
   3.3756,
   3.9382,
   3.9382};
   graph = new TGraph(6,Graph_fx64,Graph_fy64);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx65[6] = {
   -0.6496345,
   -0.3248172,
   0.3248173,
   0.6496345,
   0.3248173,
   -0.3248172};
   Double_t Graph_fy65[6] = {
   2.2504,
   1.6878,
   1.6878,
   2.2504,
   2.813,
   2.813};
   graph = new TGraph(6,Graph_fx65,Graph_fy65);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx66[6] = {
   -0.6496345,
   -0.3248172,
   0.3248173,
   0.6496345,
   0.3248173,
   -0.3248172};
   Double_t Graph_fy66[6] = {
   1.1252,
   0.5626,
   0.5626,
   1.1252,
   1.6878,
   1.6878};
   graph = new TGraph(6,Graph_fx66,Graph_fy66);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx67[6] = {
   -0.6496345,
   -0.3248173,
   0.3248172,
   0.6496345,
   0.3248173,
   -0.3248172};
   Double_t Graph_fy67[6] = {
   -1.166027e-09,
   -0.5626,
   -0.5626,
   1.166027e-09,
   0.5626,
   0.5626};
   graph = new TGraph(6,Graph_fx67,Graph_fy67);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx68[6] = {
   -0.6496345,
   -0.3248173,
   0.3248172,
   0.6496345,
   0.3248172,
   -0.3248173};
   Double_t Graph_fy68[6] = {
   -1.1252,
   -1.6878,
   -1.6878,
   -1.1252,
   -0.5626,
   -0.5626};
   graph = new TGraph(6,Graph_fx68,Graph_fy68);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx69[6] = {
   -0.6496345,
   -0.3248173,
   0.3248172,
   0.6496345,
   0.3248172,
   -0.3248173};
   Double_t Graph_fy69[6] = {
   -2.2504,
   -2.813,
   -2.813,
   -2.2504,
   -1.6878,
   -1.6878};
   graph = new TGraph(6,Graph_fx69,Graph_fy69);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx70[6] = {
   -0.6496345,
   -0.3248173,
   0.3248172,
   0.6496345,
   0.3248172,
   -0.3248173};
   Double_t Graph_fy70[6] = {
   -3.3756,
   -3.9382,
   -3.9382,
   -3.3756,
   -2.813,
   -2.813};
   graph = new TGraph(6,Graph_fx70,Graph_fy70);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx71[6] = {
   -0.6496345,
   -0.3248173,
   0.3248172,
   0.6496345,
   0.3248172,
   -0.3248173};
   Double_t Graph_fy71[6] = {
   -4.5008,
   -5.0634,
   -5.0634,
   -4.5008,
   -3.9382,
   -3.9382};
   graph = new TGraph(6,Graph_fx71,Graph_fy71);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx72[6] = {
   -0.6496345,
   -0.3248173,
   0.3248172,
   0.6496345,
   0.3248172,
   -0.3248173};
   Double_t Graph_fy72[6] = {
   -5.626,
   -6.1886,
   -6.1886,
   -5.626,
   -5.0634,
   -5.0634};
   graph = new TGraph(6,Graph_fx72,Graph_fy72);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx73[4] = {
   -1.624086,
   -1.299269,
   -0.6496345,
   -0.3248172};
   Double_t Graph_fy73[4] = {
   6.1886,
   5.626,
   5.626,
   6.1886};
   graph = new TGraph(4,Graph_fx73,Graph_fy73);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx74[6] = {
   -1.624086,
   -1.299269,
   -0.6496345,
   -0.3248172,
   -0.6496345,
   -1.299269};
   Double_t Graph_fy74[6] = {
   5.0634,
   4.5008,
   4.5008,
   5.0634,
   5.626,
   5.626};
   graph = new TGraph(6,Graph_fx74,Graph_fy74);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx75[6] = {
   -1.624086,
   -1.299269,
   -0.6496345,
   -0.3248172,
   -0.6496345,
   -1.299269};
   Double_t Graph_fy75[6] = {
   3.9382,
   3.3756,
   3.3756,
   3.9382,
   4.5008,
   4.5008};
   graph = new TGraph(6,Graph_fx75,Graph_fy75);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx76[6] = {
   -1.624086,
   -1.299269,
   -0.6496345,
   -0.3248172,
   -0.6496345,
   -1.299269};
   Double_t Graph_fy76[6] = {
   2.813,
   2.2504,
   2.2504,
   2.813,
   3.3756,
   3.3756};
   graph = new TGraph(6,Graph_fx76,Graph_fy76);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx77[6] = {
   -1.624086,
   -1.299269,
   -0.6496345,
   -0.3248172,
   -0.6496345,
   -1.299269};
   Double_t Graph_fy77[6] = {
   1.6878,
   1.1252,
   1.1252,
   1.6878,
   2.2504,
   2.2504};
   graph = new TGraph(6,Graph_fx77,Graph_fy77);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx78[6] = {
   -1.624086,
   -1.299269,
   -0.6496345,
   -0.3248172,
   -0.6496345,
   -1.299269};
   Double_t Graph_fy78[6] = {
   0.5626,
   -2.332053e-09,
   -1.166027e-09,
   0.5626,
   1.1252,
   1.1252};
   graph = new TGraph(6,Graph_fx78,Graph_fy78);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx79[6] = {
   -1.624086,
   -1.299269,
   -0.6496345,
   -0.3248173,
   -0.6496345,
   -1.299269};
   Double_t Graph_fy79[6] = {
   -0.5626,
   -1.1252,
   -1.1252,
   -0.5626,
   -1.166027e-09,
   -2.332053e-09};
   graph = new TGraph(6,Graph_fx79,Graph_fy79);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx80[6] = {
   -1.624086,
   -1.299269,
   -0.6496345,
   -0.3248173,
   -0.6496345,
   -1.299269};
   Double_t Graph_fy80[6] = {
   -1.6878,
   -2.2504,
   -2.2504,
   -1.6878,
   -1.1252,
   -1.1252};
   graph = new TGraph(6,Graph_fx80,Graph_fy80);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx81[6] = {
   -1.624086,
   -1.299269,
   -0.6496345,
   -0.3248173,
   -0.6496345,
   -1.299269};
   Double_t Graph_fy81[6] = {
   -2.813,
   -3.3756,
   -3.3756,
   -2.813,
   -2.2504,
   -2.2504};
   graph = new TGraph(6,Graph_fx81,Graph_fy81);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx82[6] = {
   -1.624086,
   -1.299269,
   -0.6496345,
   -0.3248173,
   -0.6496345,
   -1.299269};
   Double_t Graph_fy82[6] = {
   -3.9382,
   -4.5008,
   -4.5008,
   -3.9382,
   -3.3756,
   -3.3756};
   graph = new TGraph(6,Graph_fx82,Graph_fy82);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx83[6] = {
   -1.624086,
   -1.299269,
   -0.6496345,
   -0.3248173,
   -0.6496345,
   -1.299269};
   Double_t Graph_fy83[6] = {
   -5.0634,
   -5.626,
   -5.626,
   -5.0634,
   -4.5008,
   -4.5008};
   graph = new TGraph(6,Graph_fx83,Graph_fy83);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx84[4] = {
   -1.624086,
   -0.3248173,
   -0.6496345,
   -1.299269};
   Double_t Graph_fy84[4] = {
   -6.1886,
   -6.1886,
   -5.626,
   -5.626};
   graph = new TGraph(4,Graph_fx84,Graph_fy84);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx85[6] = {
   -2.598538,
   -2.273721,
   -1.624086,
   -1.299269,
   -1.624086,
   -2.273721};
   Double_t Graph_fy85[6] = {
   5.626,
   5.0634,
   5.0634,
   5.626,
   6.1886,
   6.1886};
   graph = new TGraph(6,Graph_fx85,Graph_fy85);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx86[6] = {
   -2.598538,
   -2.273721,
   -1.624086,
   -1.299269,
   -1.624086,
   -2.273721};
   Double_t Graph_fy86[6] = {
   4.5008,
   3.9382,
   3.9382,
   4.5008,
   5.0634,
   5.0634};
   graph = new TGraph(6,Graph_fx86,Graph_fy86);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx87[6] = {
   -2.598538,
   -2.273721,
   -1.624086,
   -1.299269,
   -1.624086,
   -2.273721};
   Double_t Graph_fy87[6] = {
   3.3756,
   2.813,
   2.813,
   3.3756,
   3.9382,
   3.9382};
   graph = new TGraph(6,Graph_fx87,Graph_fy87);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx88[6] = {
   -2.598538,
   -2.273721,
   -1.624086,
   -1.299269,
   -1.624086,
   -2.273721};
   Double_t Graph_fy88[6] = {
   2.2504,
   1.6878,
   1.6878,
   2.2504,
   2.813,
   2.813};
   graph = new TGraph(6,Graph_fx88,Graph_fy88);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx89[6] = {
   -2.598538,
   -2.273721,
   -1.624086,
   -1.299269,
   -1.624086,
   -2.273721};
   Double_t Graph_fy89[6] = {
   1.1252,
   0.5626,
   0.5626,
   1.1252,
   1.6878,
   1.6878};
   graph = new TGraph(6,Graph_fx89,Graph_fy89);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx90[6] = {
   -2.598538,
   -2.273721,
   -1.624086,
   -1.299269,
   -1.624086,
   -2.273721};
   Double_t Graph_fy90[6] = {
   -4.664107e-09,
   -0.5626,
   -0.5626,
   -2.332053e-09,
   0.5626,
   0.5626};
   graph = new TGraph(6,Graph_fx90,Graph_fy90);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx91[6] = {
   -2.598538,
   -2.273721,
   -1.624086,
   -1.299269,
   -1.624086,
   -2.273721};
   Double_t Graph_fy91[6] = {
   -1.1252,
   -1.6878,
   -1.6878,
   -1.1252,
   -0.5626,
   -0.5626};
   graph = new TGraph(6,Graph_fx91,Graph_fy91);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx92[6] = {
   -2.598538,
   -2.273721,
   -1.624086,
   -1.299269,
   -1.624086,
   -2.273721};
   Double_t Graph_fy92[6] = {
   -2.2504,
   -2.813,
   -2.813,
   -2.2504,
   -1.6878,
   -1.6878};
   graph = new TGraph(6,Graph_fx92,Graph_fy92);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx93[6] = {
   -2.598538,
   -2.273721,
   -1.624086,
   -1.299269,
   -1.624086,
   -2.273721};
   Double_t Graph_fy93[6] = {
   -3.3756,
   -3.9382,
   -3.9382,
   -3.3756,
   -2.813,
   -2.813};
   graph = new TGraph(6,Graph_fx93,Graph_fy93);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx94[6] = {
   -2.598538,
   -2.273721,
   -1.624086,
   -1.299269,
   -1.624086,
   -2.273721};
   Double_t Graph_fy94[6] = {
   -4.5008,
   -5.0634,
   -5.0634,
   -4.5008,
   -3.9382,
   -3.9382};
   graph = new TGraph(6,Graph_fx94,Graph_fy94);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx95[6] = {
   -2.598538,
   -2.273721,
   -1.624086,
   -1.299269,
   -1.624086,
   -2.273721};
   Double_t Graph_fy95[6] = {
   -5.626,
   -6.1886,
   -6.1886,
   -5.626,
   -5.0634,
   -5.0634};
   graph = new TGraph(6,Graph_fx95,Graph_fy95);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx96[4] = {
   -3.57299,
   -3.248172,
   -2.598538,
   -2.273721};
   Double_t Graph_fy96[4] = {
   6.1886,
   5.626,
   5.626,
   6.1886};
   graph = new TGraph(4,Graph_fx96,Graph_fy96);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx97[6] = {
   -3.57299,
   -3.248172,
   -2.598538,
   -2.273721,
   -2.598538,
   -3.248172};
   Double_t Graph_fy97[6] = {
   5.0634,
   4.5008,
   4.5008,
   5.0634,
   5.626,
   5.626};
   graph = new TGraph(6,Graph_fx97,Graph_fy97);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx98[6] = {
   -3.57299,
   -3.248172,
   -2.598538,
   -2.273721,
   -2.598538,
   -3.248172};
   Double_t Graph_fy98[6] = {
   3.9382,
   3.3756,
   3.3756,
   3.9382,
   4.5008,
   4.5008};
   graph = new TGraph(6,Graph_fx98,Graph_fy98);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx99[6] = {
   -3.57299,
   -3.248172,
   -2.598538,
   -2.273721,
   -2.598538,
   -3.248172};
   Double_t Graph_fy99[6] = {
   2.813,
   2.2504,
   2.2504,
   2.813,
   3.3756,
   3.3756};
   graph = new TGraph(6,Graph_fx99,Graph_fy99);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx100[6] = {
   -3.57299,
   -3.248172,
   -2.598538,
   -2.273721,
   -2.598538,
   -3.248172};
   Double_t Graph_fy100[6] = {
   1.6878,
   1.1252,
   1.1252,
   1.6878,
   2.2504,
   2.2504};
   graph = new TGraph(6,Graph_fx100,Graph_fy100);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx101[6] = {
   -3.57299,
   -3.248173,
   -2.598538,
   -2.273721,
   -2.598538,
   -3.248172};
   Double_t Graph_fy101[6] = {
   0.5626,
   -5.830134e-09,
   -4.664107e-09,
   0.5626,
   1.1252,
   1.1252};
   graph = new TGraph(6,Graph_fx101,Graph_fy101);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx102[6] = {
   -3.57299,
   -3.248173,
   -2.598538,
   -2.273721,
   -2.598538,
   -3.248173};
   Double_t Graph_fy102[6] = {
   -0.5626,
   -1.1252,
   -1.1252,
   -0.5626,
   -4.664107e-09,
   -5.830134e-09};
   graph = new TGraph(6,Graph_fx102,Graph_fy102);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx103[6] = {
   -3.57299,
   -3.248173,
   -2.598538,
   -2.273721,
   -2.598538,
   -3.248173};
   Double_t Graph_fy103[6] = {
   -1.6878,
   -2.2504,
   -2.2504,
   -1.6878,
   -1.1252,
   -1.1252};
   graph = new TGraph(6,Graph_fx103,Graph_fy103);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx104[6] = {
   -3.57299,
   -3.248173,
   -2.598538,
   -2.273721,
   -2.598538,
   -3.248173};
   Double_t Graph_fy104[6] = {
   -2.813,
   -3.3756,
   -3.3756,
   -2.813,
   -2.2504,
   -2.2504};
   graph = new TGraph(6,Graph_fx104,Graph_fy104);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx105[6] = {
   -3.57299,
   -3.248173,
   -2.598538,
   -2.273721,
   -2.598538,
   -3.248173};
   Double_t Graph_fy105[6] = {
   -3.9382,
   -4.5008,
   -4.5008,
   -3.9382,
   -3.3756,
   -3.3756};
   graph = new TGraph(6,Graph_fx105,Graph_fy105);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx106[6] = {
   -3.57299,
   -3.248173,
   -2.598538,
   -2.273721,
   -2.598538,
   -3.248173};
   Double_t Graph_fy106[6] = {
   -5.0634,
   -5.626,
   -5.626,
   -5.0634,
   -4.5008,
   -4.5008};
   graph = new TGraph(6,Graph_fx106,Graph_fy106);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx107[4] = {
   -3.57299,
   -2.273721,
   -2.598538,
   -3.248173};
   Double_t Graph_fy107[4] = {
   -6.1886,
   -6.1886,
   -5.626,
   -5.626};
   graph = new TGraph(4,Graph_fx107,Graph_fy107);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx108[4] = {
   -4.222624,
   -3.57299,
   -3.248172,
   -3.57299};
   Double_t Graph_fy108[4] = {
   5.0634,
   5.0634,
   5.626,
   6.1886};
   graph = new TGraph(4,Graph_fx108,Graph_fy108);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx109[6] = {
   -4.547441,
   -4.222624,
   -3.57299,
   -3.248172,
   -3.57299,
   -4.222624};
   Double_t Graph_fy109[6] = {
   4.5008,
   3.9382,
   3.9382,
   4.5008,
   5.0634,
   5.0634};
   graph = new TGraph(6,Graph_fx109,Graph_fy109);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx110[6] = {
   -4.547441,
   -4.222624,
   -3.57299,
   -3.248172,
   -3.57299,
   -4.222624};
   Double_t Graph_fy110[6] = {
   3.3756,
   2.813,
   2.813,
   3.3756,
   3.9382,
   3.9382};
   graph = new TGraph(6,Graph_fx110,Graph_fy110);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx111[6] = {
   -4.547441,
   -4.222624,
   -3.57299,
   -3.248172,
   -3.57299,
   -4.222624};
   Double_t Graph_fy111[6] = {
   2.2504,
   1.6878,
   1.6878,
   2.2504,
   2.813,
   2.813};
   graph = new TGraph(6,Graph_fx111,Graph_fy111);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx112[6] = {
   -4.547441,
   -4.222624,
   -3.57299,
   -3.248172,
   -3.57299,
   -4.222624};
   Double_t Graph_fy112[6] = {
   1.1252,
   0.5626,
   0.5626,
   1.1252,
   1.6878,
   1.6878};
   graph = new TGraph(6,Graph_fx112,Graph_fy112);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx113[6] = {
   -4.547442,
   -4.222624,
   -3.57299,
   -3.248173,
   -3.57299,
   -4.222624};
   Double_t Graph_fy113[6] = {
   -8.162187e-09,
   -0.5626,
   -0.5626,
   -5.830134e-09,
   0.5626,
   0.5626};
   graph = new TGraph(6,Graph_fx113,Graph_fy113);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx114[6] = {
   -4.547442,
   -4.222624,
   -3.57299,
   -3.248173,
   -3.57299,
   -4.222624};
   Double_t Graph_fy114[6] = {
   -1.1252,
   -1.6878,
   -1.6878,
   -1.1252,
   -0.5626,
   -0.5626};
   graph = new TGraph(6,Graph_fx114,Graph_fy114);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx115[6] = {
   -4.547442,
   -4.222624,
   -3.57299,
   -3.248173,
   -3.57299,
   -4.222624};
   Double_t Graph_fy115[6] = {
   -2.2504,
   -2.813,
   -2.813,
   -2.2504,
   -1.6878,
   -1.6878};
   graph = new TGraph(6,Graph_fx115,Graph_fy115);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx116[6] = {
   -4.547442,
   -4.222624,
   -3.57299,
   -3.248173,
   -3.57299,
   -4.222624};
   Double_t Graph_fy116[6] = {
   -3.3756,
   -3.9382,
   -3.9382,
   -3.3756,
   -2.813,
   -2.813};
   graph = new TGraph(6,Graph_fx116,Graph_fy116);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx117[6] = {
   -4.547442,
   -4.222624,
   -3.57299,
   -3.248173,
   -3.57299,
   -4.222624};
   Double_t Graph_fy117[6] = {
   -4.5008,
   -5.0634,
   -5.0634,
   -4.5008,
   -3.9382,
   -3.9382};
   graph = new TGraph(6,Graph_fx117,Graph_fy117);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx118[4] = {
   -3.57299,
   -3.248173,
   -3.57299,
   -4.222624};
   Double_t Graph_fy118[4] = {
   -6.1886,
   -5.626,
   -5.0634,
   -5.0634};
   graph = new TGraph(4,Graph_fx118,Graph_fy118);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx119[4] = {
   -5.197076,
   -4.547441,
   -4.222624,
   -4.547441};
   Double_t Graph_fy119[4] = {
   3.3756,
   3.3756,
   3.9382,
   4.5008};
   graph = new TGraph(4,Graph_fx119,Graph_fy119);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx120[6] = {
   -5.521893,
   -5.197076,
   -4.547441,
   -4.222624,
   -4.547441,
   -5.197076};
   Double_t Graph_fy120[6] = {
   2.813,
   2.2504,
   2.2504,
   2.813,
   3.3756,
   3.3756};
   graph = new TGraph(6,Graph_fx120,Graph_fy120);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx121[6] = {
   -5.521893,
   -5.197076,
   -4.547441,
   -4.222624,
   -4.547441,
   -5.197076};
   Double_t Graph_fy121[6] = {
   1.6878,
   1.1252,
   1.1252,
   1.6878,
   2.2504,
   2.2504};
   graph = new TGraph(6,Graph_fx121,Graph_fy121);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx122[6] = {
   -5.521893,
   -5.197076,
   -4.547442,
   -4.222624,
   -4.547441,
   -5.197076};
   Double_t Graph_fy122[6] = {
   0.5626,
   -9.328214e-09,
   -8.162187e-09,
   0.5626,
   1.1252,
   1.1252};
   graph = new TGraph(6,Graph_fx122,Graph_fy122);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx123[6] = {
   -5.521893,
   -5.197076,
   -4.547442,
   -4.222624,
   -4.547442,
   -5.197076};
   Double_t Graph_fy123[6] = {
   -0.5626,
   -1.1252,
   -1.1252,
   -0.5626,
   -8.162187e-09,
   -9.328214e-09};
   graph = new TGraph(6,Graph_fx123,Graph_fy123);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx124[6] = {
   -5.521893,
   -5.197076,
   -4.547442,
   -4.222624,
   -4.547442,
   -5.197076};
   Double_t Graph_fy124[6] = {
   -1.6878,
   -2.2504,
   -2.2504,
   -1.6878,
   -1.1252,
   -1.1252};
   graph = new TGraph(6,Graph_fx124,Graph_fy124);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx125[6] = {
   -5.521893,
   -5.197076,
   -4.547442,
   -4.222624,
   -4.547442,
   -5.197076};
   Double_t Graph_fy125[6] = {
   -2.813,
   -3.3756,
   -3.3756,
   -2.813,
   -2.2504,
   -2.2504};
   graph = new TGraph(6,Graph_fx125,Graph_fy125);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx126[4] = {
   -4.547442,
   -4.222624,
   -4.547442,
   -5.197076};
   Double_t Graph_fy126[4] = {
   -4.5008,
   -3.9382,
   -3.3756,
   -3.3756};
   graph = new TGraph(4,Graph_fx126,Graph_fy126);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx127[4] = {
   -6.171528,
   -5.521893,
   -5.197076,
   -5.521893};
   Double_t Graph_fy127[4] = {
   1.6878,
   1.6878,
   2.2504,
   2.813};
   graph = new TGraph(4,Graph_fx127,Graph_fy127);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx128[6] = {
   -6.496345,
   -6.171528,
   -5.521893,
   -5.197076,
   -5.521893,
   -6.171528};
   Double_t Graph_fy128[6] = {
   1.1252,
   0.5626,
   0.5626,
   1.1252,
   1.6878,
   1.6878};
   graph = new TGraph(6,Graph_fx128,Graph_fy128);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx129[6] = {
   -6.496345,
   -6.171528,
   -5.521893,
   -5.197076,
   -5.521893,
   -6.171528};
   Double_t Graph_fy129[6] = {
   -1.166027e-08,
   -0.5626,
   -0.5626,
   -9.328214e-09,
   0.5626,
   0.5626};
   graph = new TGraph(6,Graph_fx129,Graph_fy129);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx130[6] = {
   -6.496345,
   -6.171528,
   -5.521893,
   -5.197076,
   -5.521893,
   -6.171528};
   Double_t Graph_fy130[6] = {
   -1.1252,
   -1.6878,
   -1.6878,
   -1.1252,
   -0.5626,
   -0.5626};
   graph = new TGraph(6,Graph_fx130,Graph_fy130);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx131[4] = {
   -5.521893,
   -5.197076,
   -5.521893,
   -6.171528};
   Double_t Graph_fy131[4] = {
   -2.813,
   -2.2504,
   -1.6878,
   -1.6878};
   graph = new TGraph(4,Graph_fx131,Graph_fy131);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx132[4] = {
   -7.14598,
   -6.496345,
   -6.171528,
   -6.496345};
   Double_t Graph_fy132[4] = {
   -1.282629e-08,
   -1.166027e-08,
   0.5626,
   1.1252};
   graph = new TGraph(4,Graph_fx132,Graph_fy132);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);
   
   Double_t Graph_fx133[4] = {
   -6.496345,
   -6.171528,
   -6.496345,
   -7.14598};
   Double_t Graph_fy133[4] = {
   -1.1252,
   -0.5626,
   -1.166027e-08,
   -1.282629e-08};
   graph = new TGraph(4,Graph_fx133,Graph_fy133);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   SingleLayer->AddBin(graph);

//Now prepare the contents of the plot
//First the mapping between rootplot and sensor cell
   Int_t Mapping[133] = {104,104,81,92,103,113,121,
			 58,69,80,91,102,112,120,126,
			 25,46,57,68,79,90,101,111,119,125,127,
			 25,35,45,56,67,78,89,100,110,118,124,127,
			 24,34,44,55,66,77,88,99,109,117,123,
			 14,23,33,43,54,65,76,87,98,108,116,122,
			 13,22,32,42,53,64,75,86,97,107,115,
			 6,12,21,31,41,52,63,74,85,96,106,114,
			 5,11,20,30,40,51,62,73,84,95,105,
			 1,4,10,19,29,39,50,61,72,83,94,93,
			 1,3,9,18,28,38,49,60,71,82,93,
			 2,8,17,27,37,48,59,70,
			 7,16,26,36,47,15,15};
     
//Now read the data file
   float lgped[127];
   float lgstdev[127];
   float hgped[127];
   float hgstdev[127];
   FILE *file;
   char *line = new char[20];
   size_t count;
   int i=0, j=0;

   vector<float> numbers;
   ifstream in("AVG_ANA_RUN_170317_0912.txt", ios::in);
   printf("opened data file ok\n");

   float number;
   int num=0;
   while (in >> number) {
     numbers.push_back(number);
     //     printf("number=%f, num=%d\n",number, num);
     num++;
   }
   in.close();

   printf("read in the data ok, num = %d\n",num);
   

   for (i=0 ; i<127 ; i++) {
     lgped[i] = numbers[i*2];
     lgstdev[i] = numbers[i*2+1];
     hgped[i] = numbers[i*2+254];
     hgstdev[i] = numbers[i*2+254+1];
   }

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   SingleLayer->SetLineColor(ci);
   SingleLayer->GetXaxis()->SetTitle("X[cm]");
   SingleLayer->GetXaxis()->CenterTitle(true);
   SingleLayer->GetXaxis()->SetLabelFont(42);
   SingleLayer->GetXaxis()->SetLabelSize(0.035);
   SingleLayer->GetXaxis()->SetTitleSize(0.035);
   SingleLayer->GetXaxis()->SetTitleFont(42);
   SingleLayer->GetYaxis()->SetTitle("Y[cm]");
   SingleLayer->GetYaxis()->CenterTitle(true);
   SingleLayer->GetYaxis()->SetLabelFont(42);
   SingleLayer->GetYaxis()->SetLabelSize(0.035);
   SingleLayer->GetYaxis()->SetTitleSize(0.035);
   SingleLayer->GetYaxis()->SetTitleFont(42);
   SingleLayer->GetZaxis()->SetLabelFont(42);
   SingleLayer->GetZaxis()->SetLabelSize(0.035);
   SingleLayer->GetZaxis()->SetTitleSize(0.035);
   SingleLayer->GetZaxis()->SetTitleFont(42);

   /*
   // Low gain pedestals   
   for (int icell = 0; icell < 133 ; icell++)
     {
       SingleLayer->SetBinContent(icell+1,int(hgped[Mapping[icell]-1]));
       //Following line shows the mapping
       //SingleLayer->SetBinContent(icell+1,Mapping[icell]);
     }
   
   // For Pedestals
   SingleLayer->SetMinimum(150);
   SingleLayer->SetMaximum(250);
   SingleLayer->SetEntries(133);
   SingleLayer->Draw("colz,text");
   TLatex *   tex = new TLatex(0.2,0.94,"Hexaboard High Gain Pedestals");
   tex->SetNDC();
   tex->SetTextAlign(1);
   tex->SetTextFont(42);
   tex->SetLineWidth(2);
   tex->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
   */
   
   // Low gain stdev   
   for (int icell = 0; icell < 133 ; icell++)
     {
       SingleLayer->SetBinContent(icell+1,(hgstdev[Mapping[icell]-1]));
       //Following line shows the mapping
       //SingleLayer->SetBinContent(icell+1,Mapping[icell]);
     }
   
   // For stdev
   SingleLayer->SetMinimum(1.5);
   SingleLayer->SetMaximum(2.5);
   SingleLayer->SetEntries(133);
   SingleLayer->Draw("colz,text");
   TLatex *   tex2 = new TLatex(0.2,0.94,"Hexaboard High Gain STDEV");
   tex2->SetNDC();
   tex2->SetTextAlign(1);
   tex2->SetTextFont(42);
   tex2->SetLineWidth(2);
   tex2->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
   
}
