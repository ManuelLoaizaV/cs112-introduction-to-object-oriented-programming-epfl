#include <iostream>
#include <string>
using namespace std;

class Timbre
{
private:
  static constexpr unsigned int ANNEE_COURANTE = 2016;

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
protected:
  static constexpr double PRIX_BASE_TRES_RARE = 600.0;
  static constexpr double PRIX_BASE_RARE = 400.0;
  static constexpr double PRIX_BASE_PEU_RARE = 50;

  string nom;
  unsigned int annee;
  string pays;
  double valeur_faciale;

public:
  Timbre() = default;
  Timbre(string, unsigned int, string, double);
  double vente() const;
  unsigned int age() const;
  ostream& afficher(ostream&) const;
};

Timbre::Timbre(string codigo, unsigned int anio, string origen = "Suisse", double valor = 1.0)
: nom(codigo), annee(anio), pays(origen), valeur_faciale(valor) {}

double Timbre::vente() const {
  unsigned int edad = age();
  if (edad < 5) return valeur_faciale;
  else return valeur_faciale * edad * 2.5;
}

unsigned int Timbre::age() const {
  return ANNEE_COURANTE - annee;
}

// Las estampas raras
class Rare : public Timbre {
protected:
  int copies;
public:
  Rare(string, unsigned int, string, double, unsigned int);
  unsigned int nb_exemplaires() const;
  double vente() const;
};

Rare::Rare(string codigo, unsigned int anio, string origen = "Suisse", double valor = 1.0, unsigned int copias = 100)
: Timbre(codigo, anio, origen, valor), copies(copias) {}

unsigned int Rare::nb_exemplaires() const {
  return copies;
}

double Rare::vente() const {
  unsigned int edad = age();
  if (edad < 5) return valeur_faciale;
  else {
    double prix_base;
    if (copies < 100) prix_base = PRIX_BASE_TRES_RARE;
    else if (copies < 1000) prix_base = PRIX_BASE_RARE;
    else prix_base = PRIX_BASE_PEU_RARE;
    return prix_base * (edad / 10.0);
  }
}

// Las estampas conmemorativas
class Commemoratif : public Timbre {
public:
  Commemoratif(string, unsigned int, string, double);
  double vente() const;
};

Commemoratif::Commemoratif(string codigo, unsigned int anio, string origen = "Suisse", double valor = 1.0)
: Timbre(codigo, anio, origen, valor) {}

double Commemoratif::vente() const {
  return 2 * Timbre::vente();
}

// Impresion en pantalla
ostream& Timbre::afficher(ostream& sortie) const {
  return sortie << " de nom " << nom << " datant de " << annee << " (provenance " << pays << ") ayant pour valeur faciale " << valeur_faciale << " francs";
}

ostream& operator<<(ostream& sortie, Timbre const& estampa) {
  sortie << "Timbre";
  return estampa.afficher(sortie);
}

ostream& operator<<(ostream& sortie, Rare const& estampa) {
  sortie << "Timbre rare (" << estampa.nb_exemplaires() << " ex.)";
  return estampa.afficher(sortie);
}

ostream& operator<<(ostream& sortie, Commemoratif const& estampa) {
  sortie << "Timbre commémoratif";
  return estampa.afficher(sortie);
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Rare t1( "Guarana-4574", 1960, "Mexique", 0.2, 98 );
  Rare t2( "Yoddle-201"  , 1916, "Suisse" , 0.8,  3 );

  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Commemoratif t3( "700eme-501"  , 2002, "Suisse", 1.5 );
  Timbre       t4( "Setchuan-302", 2004, "Chine" , 0.2 );

  /* Nous n'avons pas encore le polymorphisme :-(
   * (=> pas moyen de faire sans copie ici :-( )  */
  cout << t1 << endl;
  cout << "Prix vente : " << t1.vente() << " francs" << endl;
  cout << t2 << endl;
  cout << "Prix vente : " << t2.vente() << " francs" << endl;
  cout << t3 << endl;
  cout << "Prix vente : " << t3.vente() << " francs" << endl;
  cout << t4 << endl;
  cout << "Prix vente : " << t4.vente() << " francs" << endl;

  return 0;
}
