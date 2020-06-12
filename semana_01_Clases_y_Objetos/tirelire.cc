#include <iostream>
using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/
class Tirelire {
  private:
  double montant;
  public:
  // const son metodos que no modifican al objeto
  // Los siguientes son prototipos
  double getMontant() const;
  void afficher() const;
  void secouer() const;
  void remplir(double);
  void vider();
  void puiser(double);
  bool montant_suffisant(double, double &);
};
// Las siguientes son definiciones
double Tirelire::getMontant() const { return montant; }

void Tirelire::afficher() const {
  if (montant == 0) cout << "Vous etes sans le sou." << endl;
  else cout << "Vous avez : " << montant << " euros dans votre tirelire." << endl;
}

void Tirelire::secouer() const { if (montant > 0) cout << "Bing bing" << endl; }
  
void Tirelire::remplir(double add) { if (add > 0) montant += add; }
  
void Tirelire::vider() { montant = 0.0; }

void Tirelire::puiser(double take) {
  if (take > 0) {
    montant -= take;
    if (montant < 0) montant = 0;
  }
}

bool Tirelire::montant_suffisant(double budget, double &saldo) {
  if (budget <= 0) {
    saldo = montant;
    return true;
  }
  if (montant >= budget) {
    saldo = montant - budget;
    return true;
  } else {
    saldo = budget - montant;
    return false;
  }
}
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Tirelire piggy;

  piggy.vider();
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(20.0);
  piggy.secouer();
  piggy.afficher();

  piggy.remplir(550.0);
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(10.0);
  piggy.puiser(5.0);
  piggy.afficher();

  cout << endl;

  // le budget de vos vacances de rève.
  double budget;

  cout << "Donnez le budget de vos vacances : ";
  cin >> budget;

  // ce qui resterait dans la tirelire après les
  // vacances
  double solde(0.0);

  if (piggy.montant_suffisant(budget, solde)) {
    cout << "Vous êtes assez riche pour partir en vacances !"
         << endl
         << "Il vous restera " << solde << " euros"
         << " à la rentrée." << endl << endl;
    piggy.puiser(budget);
  } else {
    cout << "Il vous manque " << solde << " euros"
         << " pour partir en vacances !" << endl << endl;
  }
  return 0;
}
