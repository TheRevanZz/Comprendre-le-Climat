/*!
 * \file "prog.cpp"
 * Programme principal.
 * 
 * Copyright (c) 2015 by Benjamin ALBOUY-KISSI
 */
#include <Windows.h>
#include <tchar.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <LibGraph2.h>
//#include "CGraphique.h"
#include "LireDoc.h"
#include "Dessin.h"
#include "CBouton.h"

#include <iostream>
using namespace std;
using namespace LibGraph2;


int APIENTRY _tWinMain(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPTSTR lpCmdLine,
  int nCmdShow)
{
  UNREFERENCED_PARAMETER(hInstance);
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  UNREFERENCED_PARAMETER(nCmdShow);

  //Récupération de l'objet principal de LibGraph 2
  ILibGraph2* libgraph = GetLibGraph2();

  //Affiche un message d'aide succint
  //libgraph->guiMessageBox("Aide", "Appuyez sur la barre d'espace pour faire un pas dans l'algorithme de résolution", msgbtn_types::MsgBtnOK, msgicon_types::MsgIcnInformation);
  //Affiche la fenêtre graphique avec une taille par défaut
  libgraph->show(CSize{ 1920, 1080 });

  evt e;  //Evénement LibGraph 2
  //Boucle principale d'événements
  
  CGraphique graph;
  size_t typeAff = 0;
  CGraphique focus;


  LireDoc(graph); //lecture du cvs est insertion dans l'objet graph
  graph.SetNbAnneeAff(graph.GetAnnees().size());
  graph.SetHauteur(630);
  graph.SetLargeur(1140);
  graph.SetAnneeStart(graph.GetAnnees()[0]);



  auto yearsByDec = graph.ConvertToDec();

  bool dec = 1;

  //boutons
  CBouton bt1(CPoint(1500,200),CSize(200,50),"Top5 Années les\nplus chaudes",15.0f, (255, 16, 108, 159));
  CBouton bt2(CPoint(1500, 275), CSize(200, 50), "Top5 Années les\nplus froides", 15.0f, (255, 16, 108, 159));
  CBouton bt3(CPoint(1500, 375), CSize(200, 50), "Afficher toutes\nles années", 15.0f, (255, 16, 108, 159));
  CBouton bt4(CPoint(1500, 450), CSize(200, 50), "Afficher les\ndécennies", 15.0f, (255, 16, 108, 159));
  
 std::vector<std::shared_ptr<CBouton>> lstBouton = ListeBoutons(yearsByDec);
  

  int dec_annee;

  while (libgraph->waitForEvent(e))
  {
    switch (e.type)  //En fonction du type d'événement
    {
    case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
      //Utilisation des fonctions libgraph->beginPaint() / libgraph->endPaint() pour activer le backbuffer
      libgraph->beginPaint();
      {
          
          switch (typeAff)
          {
          case 0: //affcihage decenie par decenie
              DessinerLigne(yearsByDec);
              for (auto& pBouton : lstBouton)
                  pBouton->Afficher();
              AfficherLegend(yearsByDec);
              
              break;
          case 1: //affichage des annees les plus chaude
              DessinerLigne(graph.Top5AnneePlusChaude());
              AfficherLegend(graph.Top5AnneePlusChaude());
              
              break;
          case 2: //affichage de toute les annees
              DessinerLigne(graph);
              AfficherLegend(yearsByDec);
              break;
          case 3: //afichage des annees les plus froides
			  DessinerLigne(graph.Top5AnneePlusFroide());
			  AfficherLegend(graph.Top5AnneePlusFroide());
              break;
          case 4: //Focus sur une décenie particuliere
              if (dec_annee == 1890)
              {
                  focus = graph.ZoomDec(graph.GetAnnees()[0]);
              }
              else
              {
                  focus = graph.ZoomDec(graph.GetAnnees()[graph.GetAnnees().size() - (graph.GetAnnees().back()->GetAnnee() - dec_annee) - 1]);
              }
              
              DessinerLigne(focus);
              AfficherLegend(focus);
          }

		  bt1.Afficher();
		  bt2.Afficher();
          bt3.Afficher();
          bt4.Afficher();
          libgraph->askForRefresh();

		  
      }
      libgraph->endPaint();
      break;
    case evt_type::evtMouseDown: //verification si la souris clic sur un bouton du graphqiue
        if (bt1.Hover(LibGraph2::CPoint((float)e.x, (float)e.y)))
            typeAff = 1;
        else if (bt2.Hover(LibGraph2::CPoint((float)e.x, (float)e.y)))
            typeAff = 3;
        else if (bt3.Hover(LibGraph2::CPoint((float)e.x, (float)e.y)))
            typeAff = 2;
		else if (bt4.Hover(LibGraph2::CPoint((float)e.x, (float)e.y)))
			typeAff = 0;
        for (auto& pBouton : lstBouton)
        {
            if (pBouton->Hover(LibGraph2::CPoint((float)e.x, (float)e.y)))
            {
                dec_annee = stoi(pBouton->GetTxt());
                typeAff = 4;
            }

        }
           break;        
    case evt_type::evtKeyDown:  //Enfoncement d'une touche
      switch (e.vkKeyCode) //En fonction de la touche enfoncée
      {
      case 'W':
          typeAff = 0;
          break;
      case 'Z':
          typeAff = 1;
          break;
      case 'A':
          typeAff = 2;
          break;
      case 'E':
          typeAff = 3;
          break;
      }
      libgraph->askForRefresh();
      break;
    }
  }
  //Libération de l'objet principal de LibGraph 2
  ReleaseLibGraph2();
  return 0;
}
//!\if include
//![main]
//!\endif